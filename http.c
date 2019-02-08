#include "http.h"
#include "string.h"
#include "response.h"
#include "uri.h"
#include "httpRequest.h"
#include <unistd.h>
#include <stdbool.h>
#include <memory.h>
#include <malloc.h>
#include <assert.h>
#include <fcntl.h>

httpResponse_t readRequest(int fd, httpRequest_t *request);

enum result {
    OK,
    IO_ERROR,
    OOM_ERROR,
    EOF_ERROR,
    INVALID_METHOD,
    INVALID_VERSION,
    INVALID_HEADER
};
typedef enum result result_t;

result_t readMethod(int fd, string_t *methodPtr);

result_t readTarget(int fd, uri_t *uri);

result_t readUntil(int fd, string_t *pString, char c);

result_t readHttpVersion(int fd, string_t *pString);

result_t readUntilChars(int fd, string_t *pString, const char *chars);

void writeResponse(int fd, httpResponse_t response);

void writeString(int fd, string_t str);

result_t readHeaders(int fd, httpHeaders_t *headers) ;

int openFile(uri_t path);

string_t readAllContents(int f);

void handleHttpConnection(int socketFd) {
    httpRequest_t request;
    httpResponse_t response = readRequest(socketFd, &request);
    if (response != NULL) {
        writeResponse(socketFd, response);
        close(socketFd);
        destroyHttpResponse(response);
        return;
    }

    int f = openFile(request->target);
    string_t s = readAllContents(f);

    if (s == NULL) {
        response = createHttpResponse();
        httpResponseStatus(response, HTTP_STATUS_CODE_NOT_FOUND);
        writeResponse(socketFd, response);
        destroyHttpResponse(response);
        destroyHttpRequest(request);
        close(socketFd);
        return;
    }

    response = createHttpResponse();
    httpResponseStatus(response, HTTP_STATUS_CODE_OK);
    setHttpContent(response, s);
    addContentLengthHeader(response);
    writeResponse(socketFd, response);

    destroyHttpResponse(response);
    destroyHttpRequest(request);
    close(socketFd);
}

string_t readAllContents(int fd) {
    string_t s = createString();
    char c;
    ssize_t ret;
    while ((ret = read(fd, &c, 1)) > 0) {
        append(s, c);
    }

    if (ret < 0) {
        destroyString(s);
        return NULL;
    }

    return s;
}

int openFile(uri_t path) {
    // Don't open files starting with . (i.e. hidden files)
    for (size_t i = 0; i < path->numParts; i++) {
        string_t s = path->parts[i];
        if (stringLength(s) == 0) continue;
        if (*charAt(s, 0) == '.') {
            return -1;
        }
    }

    //Initial size 1 for null char
    size_t pathSize = 1;
    for (size_t i = 0; i < path->numParts; i++) {
        string_t s = path->parts[i];
        if (stringLength(s) == 0) continue;

        // Don't reveal hidden files.
        if (*charAt(s, 0) == '.') {
            return -1;
        }

        // Check for invalid characters (/ and NULL) in the path.
        for (size_t j = 0; j < stringLength(s); j++) {
            char c = *charAt(s, j);
            if (c == '/' || c == 0) {
                return -1;
            }
        }

        pathSize += stringLength(s);

        // Every element but first has slash in front.
        if (i != 0) pathSize++;
    }

    // build path
    char *p = malloc(pathSize * sizeof(char));
    p[pathSize - 1] = '\0';
    char *j = p;
    for (size_t i = 0; i < path->numParts; i++) {
        if (i != 0) {
            *(j++) = '/';
        }

        memcpy(j, stringData(path->parts[i]), stringLength(path->parts[i]));
        j += stringLength(path->parts[i]);
    }

    int f = open(p, O_RDONLY);
    free(p);
    return f;
}

void writeResponse(int fd, httpResponse_t response) {
    writeString(fd, response->httpVersion);
    write(fd, " ", 1);
    dprintf(fd, "%03u", response->statusCode);
    write(fd, " ", 1);
    writeString(fd, response->reasonPhrase);
    write(fd, "\r\n", 2);
    for (httpHeader_t h = httpHeadersFirst(response->header); h != NULL; h = httpHeaderNext(h)) {
        writeString(fd, httpHeaderKey(h));
        write(fd, ": ", 2);
        writeString(fd, httpHeaderValue(h));
        write(fd, "\r\n", 2);
    }
    write(fd, "\r\n", 2);
    writeString(fd, response->content);
}

void writeString(int fd, string_t str) {
    write(fd, stringData(str), stringLength(str));
}

httpResponse_t readRequest(int fd, httpRequest_t *request) {
    string_t method;
    result_t r = readMethod(fd, &method);

    if (r == INVALID_METHOD) {
        httpResponse_t response = createHttpResponse();
        httpResponseStatus(response, HTTP_STATUS_CODE_INVALID_METHOD);
        return response;
    }

    uri_t target;
    readTarget(fd, &target);

    string_t version;
    r = readHttpVersion(fd, &version);

    if (r == INVALID_VERSION) {
        httpResponse_t response = createHttpResponse();
        httpResponseStatus(response, HTTP_STATUS_CODE_INVALID_VERSION);
        return response;
    } else if (r != OK) {
        httpResponse_t response = createHttpResponse();
        httpResponseStatus(response, HTTP_STATUS_CODE_SERVER_ERROR);
        return response;
    }

    httpHeaders_t  headers;
    r = readHeaders(fd, &headers);

    if (r == INVALID_HEADER) {
        httpResponse_t response = createHttpResponse();
        httpResponseStatus(response, HTTP_STATUS_CODE_INVALID_REQUEST);
        return response;
    }
    printf("Method: %s\n", stringData(method));

    printf("Target Parts:\n");

    for (int i = 0; i < target->numParts; i++) {
        printf("%s\n", stringData(target->parts[i]));
    }

    printf("Version: %s\n", charAt(version, 0));
    printf("Headers:\n");
    for (httpHeader_t h = httpHeadersFirst(headers); h != NULL; h = httpHeaderNext(h)) {
        printf("%s: %s\n", stringData(httpHeaderKey(h)), stringData(httpHeaderValue(h)));
    }

    *request = createHttpRequest(method, target, version, headers);
    return NULL;
}

result_t readHeaders(int fd, httpHeaders_t *headers) {
    *headers = createHttpHeaders();

    while(true) {
        string_t line;
        readUntilChars(fd, &line, "\r\n");

        if (stringLength(line) == 0) {
            destroyString(line);
            return OK;
        }

        string_t key = createString();
        size_t i = 0;
        for (;; i++) {
            if (i == stringLength(line)) {
                destroyString(key);
                destroyString(line);
                destroyHttpHeaders(*headers);
                return INVALID_HEADER;
            }
            if (*charAt(line, i) == ':') {
                i++;
                break;
            }
            append(key, *charAt(line, i));
        }

        // Skip past spaces
        for (; i < stringLength(line) && *charAt(line, i) == ' '; i++);

        string_t value = createString();
        size_t spaces = 0;
        for (; i < stringLength(line); i++) {
            char c = *charAt(line, i);
            append(value, c);
            if (c == ' ') {
                spaces++;
            } else {
                spaces = 0;
            }
        }

        //Trim last spaces.
        removeLastChars(value, spaces);
        destroyString(line);

        httpHeadersAppend(*headers, key, value);
    }
}

result_t readHttpVersion(int fd, string_t *pString) {
    result_t r = readUntilChars(fd, pString, "\r\n");

    if (r != OK) return r;

    if (strcmp("HTTP/1.1", stringData(*pString)) != 0) {
        destroyString(*pString);
        return INVALID_VERSION;
    }
    return OK;
}

result_t readUntilChars(int fd, string_t *pString, const char *chars) {
    size_t charsLength = strlen(chars);
    assert(charsLength > 0);

    result_t ret;

    // Basic state machine
    bool *matchedChar = malloc(charsLength * sizeof(bool));

    if (matchedChar == NULL) return OOM_ERROR;

    for (size_t i = 0; i < charsLength; i++) matchedChar[i] = false;


    *pString = createString();
    if (*pString == NULL) {
        ret = OOM_ERROR;
        goto freeMatched;
    }

    while (true) {
        char c;
        ssize_t readRet = read(fd, &c, 1);
        if (readRet == 0) {
            ret = EOF_ERROR;
            goto freeString;
        }

        if (readRet < 0) {
            ret = IO_ERROR;
            goto freeString;
        }

        if (matchedChar[charsLength - 2] && chars[charsLength - 1] == c) {
            removeLastChars(*pString, charsLength - 1);
            ret = OK;
            goto freeMatched;
        }

        if (append(*pString, c) < 0) {
            ret = OOM_ERROR;
            goto freeString;
        }


        for (size_t i = charsLength - 1; i > 0; i--) {
            matchedChar[i] = (matchedChar[i - 1] && c == chars[i]);
        }
        matchedChar[0] = c == chars[0];
    }

    freeString:
    destroyString(*pString);
    freeMatched:
    free(matchedChar);
    return ret;
}

result_t readTarget(int fd, uri_t *uri) {
    string_t s;
    result_t ret;
    if ((ret = readUntil(fd, &s, ' ')) != OK) return ret;
    *uri = parseUri(s);
    destroyString(s);
    return OK;
}

result_t readUntil(int fd, string_t *pString, char c) {
    *pString = createString();

    size_t i = 0;
    while (true) {
        // Out of memory error.
        if (*pString == NULL) return OOM_ERROR;

        //Read next character.
        char next;
        ssize_t bytesRead = read(fd, &next, 1);

        // Check if EOF
        if (bytesRead == 0) {
            destroyString(*pString);
            return EOF_ERROR;
        }

        // Error reading file.
        if (bytesRead < 0) {
            destroyString(*pString);
            return IO_ERROR;
        }

        // Stop reading if next character is the one looked for
        if (next == c) {
            return OK;
        }

        // Append the character
        if (append(*pString, next) < 0) {
            destroyString(*pString);
            return OOM_ERROR;
        }

        i++;
    }
}

result_t readMethod(int fd, string_t *methodPtr) {
    result_t ret = readUntil(fd, methodPtr, ' ');
    if (ret != OK) return ret;
    if (strcmp(charAt(*methodPtr, 0), "GET") != 0) {
        destroyString(*methodPtr);
        return INVALID_METHOD;
    }
    return OK;
}
