
#include "sdl.hpp"

template<typename T>
static T check_error(T toCheck, T errorValue) {
    if (toCheck == errorValue) {
        throw std::runtime_error(SDL_GetError());
    }
    return toCheck;
}

sdl::initialize::~initialize() { SDL_Quit(); }

sdl::initialize::initialize(Uint32 flags) {
    check_error(SDL_Init(flags), -1);
}

sdl::window_unique_ptr sdl::createWindow(const char *title, int x, int y, int w, int h, Uint32 flags) {
    return {check_error<SDL_Window *>(SDL_CreateWindow(title, x, y, w, h, flags), nullptr), &SDL_DestroyWindow};
}

void sdl::waitEvent(SDL_Event *event) {
    check_error(SDL_WaitEvent(event), 0);
}

/**
 * Waits for @param timeout ms for an event. Returns true if an event was found.
 */
bool sdl::waitEventTimeout(SDL_Event *event, int timeout) {
    // Don't check for errors here because it will return the same error code for an error sometimes
    return SDL_WaitEventTimeout(event, timeout) != 0;
}

void sdl::gl::set_swap_interval(int interval) {
    check_error(SDL_GL_SetSwapInterval(interval), -1);
}

sdl::gl::context_unique_ptr sdl::gl::create_context(SDL_Window *window) {
    return {check_error<SDL_GLContext>(SDL_GL_CreateContext(window), nullptr), &SDL_GL_DeleteContext};
}

void sdl::gl::set_attribute(SDL_GLattr attr, int value) {
    check_error(SDL_GL_SetAttribute(attr, value), -1);
}

void sdl::gl::swap_window(SDL_Window *window) {
    // Don't have to check error here because it doesn't return a code that we can check for an error.
    SDL_GL_SwapWindow(window);
}
