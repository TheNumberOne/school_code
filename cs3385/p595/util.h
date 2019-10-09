#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>
#include <iterator>

#define TEST(test) { \
  testNum++; \
  if (!(test)) { \
    cerr << "  Test " << testNum << " failed" << endl; \
    numFails++; \
  } \
}

#define TEST_EQUAL(a, b) {                        \
  testNum++; \
  if (a != b) { \
    cerr << "  Test " << testNum << " failed" << endl; \
    if (b) { \
      cerr << "  a = " << a << ". Should be " << b << "." << endl;  \
    } else { \
      cerr << "  a = " << a << ". Should be NULL." << endl;  \
    } \
    numFails++; \
  } \
}

// inline std::string removeWhitespace(const std::string& s) {
//   using namespace std;
//   regex e("\\s");
//   string s2;
//   regex_replace(back_inserter(s2), s.begin(), s.end(), e, "");
//   return s2;
// }

// inline bool stringEquals(const std::string& a, const std::string& b) {
//   return removeWhitespace(a) == removeWhitespace(b);
// }

template<typename T>
void printArray(const T *A, int n)
{
    using namespace std;
    for (int i = 0; i < n; ++i) {
        cout << A[i] << endl;
    }
    cout << endl;
}

template<typename T>
bool arrayEquals(const T *A, const T *B, int n)
{
    for (int i = 0; i < n; ++i) {
        if (A[i] != B[i]) return false;
    }
    return true;
}

struct Movie
{
    Movie(const std::string &name_) : name(name_) { }
    
    std::string name;
    std::vector<std::string> actors;
};

inline std::vector<Movie> readMovieFile(const std::string &filename)
{
    using namespace std;
    
    ifstream in(filename);
    if (!in) {
        cerr << "Failed to open " << filename << endl;
        return std::vector<Movie>();
    }
    // get length of file:
    in.seekg(0, in.end);
    unsigned int in_len = in.tellg();
    in.seekg(0, in.beg);
    
    unsigned char *uncompressed = new unsigned char[in_len];
    
    // Graph G;
    
    vector<Movie> movies;
    
    // read data as a block:
    in.read((char *) uncompressed, in_len);
    char *line = new char[in_len];
    std::unique_ptr<char[]> ptr(line);
    stringstream ss(string((char *)uncompressed, in_len));
    // cout << uncompressed[0] << endl;
    // vector<string> actors;
    
    // int degrees = 0;
    // unordered_set<string> good_movies;
    // unordered_set<string> global_within;
    // global_within.insert("Bacon, Kevin (I)");
    // unordered_set<string> local_within;
    // while (degrees < MAX_DEGREES) {
    //   degrees++;
    //   local_within.clear();
    int count = 0;
    // ss.clear();
    // ss.seekp(0, ss.beg);
    // ss.seekg(0, ss.beg);
    while (!ss.eof()) {
        // count++;
        // if (count % 10000 == 0) {
        //   cout << count << endl;
        // }
        
        ss.getline(line, in_len);
        char *pch = strtok(line, ";");
        if (pch) {
            Movie movie(string(pch, strlen(pch)));
            // actors.clear();
            pch = strtok(NULL, ";");
            // bool good = false;
            while (pch != NULL) {
                movie.actors.push_back(pch);
                // string str(pch);
                // if (global_within.find(str) != global_within.end()) {
                //   good = true;
                // }
                pch = strtok(NULL, ";");
            }
            movies.push_back(movie);
            // if (good) {
            //   for (int i = 0; i < actors.size(); ++i) {
            //     local_within.insert(actors[i]);
            //     Vertex* u = G.ensureVertex(actors[i]);
            //     for (int j = i+1; j < actors.size(); ++j) {
            //       Vertex* v = G.ensureVertex(actors[j]);
            //       // G.ensureEdge(u, v, movie);
            //       G.addEdge(u, v, movie);
            //       good_movies.insert(movie);
            //     }
            //   }
            // }
        }
    }
    return movies;
}
