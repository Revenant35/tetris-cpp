#pragma once

#include <memory>
#include <string>
#include <SDL.h>

class Window {
public:
    constexpr static int SCREEN_WIDTH = 640;
    constexpr static int SCREEN_HEIGHT = 480;

    Window(const std::string &title);
    ~Window();

    const std::string &getTitle() const { return _title; }
    SDL_Window *get() const noexcept { return _window.get(); }

private:
    std::string _title;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window{nullptr, SDL_DestroyWindow};
};
