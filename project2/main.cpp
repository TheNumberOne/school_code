
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <random>
#include <array>
#include <iterator>
#include <memory>
#include <SDL.h>
#include "SimpleHouse.hpp"
#include "sdl.hpp"
#include "Camera.hpp"
#include "light.hpp"
#include "draw_container.h"
#include "display_lists_cache.h"
#include <glm/gtc/matrix_transform.inl>

uint msPerFrame = 1000 / 60;

sdl::gl::context_unique_ptr initGlContext(SDL_Window *window);

auto generate_scene() {
    return display_lists_cache(multi_transform(
        transform(
            SimpleHouse(),
            glm::translate(glm::mat4(1), {0, 0, -20})
        ),
        glm::mat4(1),
        glm::rotate(glm::mat4(1), glm::pi<float>() / 2, {0, 1, 0}),
        glm::rotate(glm::mat4(1), glm::pi<float>(), {0, 1, 0}),
        glm::rotate(glm::mat4(1), glm::pi<float>() * 3 / 2, {0, 1, 0})
    ));
}

class Application {
public:
    Application() : window(
        sdl::createWindow(
            "project2",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            850,
            600,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
        )
    ), gl_context(initGlContext(window.get())) {
        resize(850, 600);
    }

    void drawScene() {
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glLoadMatrixf(value_ptr(camera.getPerspectiveMatrix()));

        drawLightSource();
        scene.draw();

        GLenum err;
        if ((err = glGetError()) != GL_NO_ERROR) {
            std::cout << err << std::endl;
            throw std::runtime_error(std::string("Gl error: ") + std::to_string(err));
        }
    }

    void gameLoop() {
        SDL_Event event;
        unsigned int lastTime = SDL_GetTicks();
        while (!exit) {
            bool eventFound = sdl::waitEventTimeout(&event, msPerFrame);
            if (eventFound) handleEvents(event);

            uint currentTime = SDL_GetTicks();
            camera.tick((currentTime - lastTime) / 1000.f);
            lastTime = currentTime;
            drawScene();
            sdl::gl::swap_window(window.get());
        }
    }

    void handleEvents(const SDL_Event &event) {
        switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    resize(event.window.data1, event.window.data2);
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    exit = true;
                    break;
                }
                [[fallthrough]];
            case SDL_KEYUP:
                checkKeyboardState();
                break;
            case SDL_QUIT:
                exit = true;
                break;
            default:
                break;
        }
    }

    void checkKeyboardState() {
        auto keyboard = SDL_GetKeyboardState(nullptr);
        bool left = keyboard[SDL_SCANCODE_LEFT];
        bool right = keyboard[SDL_SCANCODE_RIGHT];
        bool up = keyboard[SDL_SCANCODE_UP];
        bool down = keyboard[SDL_SCANCODE_DOWN];

        if (left && !right) { camera.rotateLeft(); }
        else if (right && !left) { camera.rotateRight(); }
        else { camera.stopRotating(); }

        if (up && !down) { camera.moveForward(); }
        else if (down && !up) { camera.moveBackwards(); }
        else { camera.stopMoving(); }
    }

    // OpenGL window reshape routine.
    void resize(int w, int h) {
        glViewport(0, 0, w, h);
        camera.setAspectRatio((float) w / h);
    }

    typedef decltype(generate_scene()) scene_type;

private:
    sdl::window_unique_ptr window;
    sdl::gl::context_unique_ptr gl_context;
    Camera camera;
    scene_type scene = generate_scene();
    bool exit{false};
};

// Main routine.
int main(int argc, char **argv) {
    sdl::initialize library(SDL_INIT_VIDEO);
    std::vector<std::tuple<SDL_GLattr, int>> attrs{
//        {SDL_GL_CONTEXT_MAJOR_VERSION, 3},
//        {SDL_GL_CONTEXT_MINOR_VERSION, 2},
//        {SDL_GL_CONTEXT_PROFILE_MASK,  SDL_GL_CONTEXT_PROFILE_COMPATIBILITY},
        {SDL_GL_MULTISAMPLEBUFFERS,    1},
        {SDL_GL_MULTISAMPLESAMPLES,    16},
        {SDL_GL_RED_SIZE,              8},
        {SDL_GL_GREEN_SIZE,            8},
        {SDL_GL_BLUE_SIZE,             8},
        {SDL_GL_ALPHA_SIZE,            8},
        {SDL_GL_DOUBLEBUFFER,          1},
    };
    for (auto[key, value] : attrs) {
        sdl::gl::set_attribute(key, value);
    }

    Application app;
    app.gameLoop();

    return 0;
}

sdl::gl::context_unique_ptr initGlContext(SDL_Window *window) {
    sdl::gl::context_unique_ptr context = sdl::gl::create_context(window);
    sdl::gl::set_swap_interval(1);
    glewExperimental = GL_TRUE;
    glewInit();
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


    glm::vec4 light{.4, .4, .4, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, value_ptr(light));
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    return context;
}