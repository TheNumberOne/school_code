#pragma once

#include <SDL_quit.h>
#include <SDL.h>
#include <bits/unique_ptr.h>

namespace sdl
{
    class initialize
    {
    public:
        explicit initialize(Uint32 flags);
        
        initialize(const initialize &) = delete;
        
        auto operator=(const initialize &) = delete;
        
        ~initialize();
    };
    
    typedef std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_unique_ptr;
    
    window_unique_ptr createWindow(const char *title, int x, int y, int w, int h, Uint32 flags);
    
    
    void waitEvent(SDL_Event *event);
    
    bool waitEventTimeout(SDL_Event *event, int timeout);
    
    namespace gl
    {
        typedef std::unique_ptr<void, decltype(&SDL_GL_DeleteContext)> context_unique_ptr;
        
        context_unique_ptr create_context(SDL_Window *window);
        
        void set_attribute(SDL_GLattr attr, int value);
        
        void set_swap_interval(int interval);
        
        void swap_window(SDL_Window *window);
    }
}