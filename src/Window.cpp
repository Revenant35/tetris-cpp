#include "Window.h"

Window::Window(const std::string &title) {
    _title = title;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to initialize SDL");
    }

    const auto window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    _window.reset(window);
}

Window::~Window() {
    SDL_DestroyWindow(_window.get());
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
