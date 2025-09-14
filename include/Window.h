#pragma once

#include <memory>
#include <string>
#include <SDL.h>

class Window {
public:
    Window(const std::string &title, int width, int height);
    ~Window();

    const std::string &getTitle() const { return _title; }
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
    SDL_Window *get() const noexcept { return _window.get(); }

private:
    std::string _title;
    int _width, _height;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window{nullptr, SDL_DestroyWindow};
};
