#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "Window.h"
#include "SpriteAtlas.h"

class Renderer {
public:
    constexpr static int IMG_FLAGS = IMG_INIT_PNG;

    Renderer(const std::shared_ptr<Window>& window, int width, int height);
    ~Renderer();

    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
    SDL_Renderer *get() const noexcept { return _renderer.get(); }

    SDL_Texture *loadTexture(const std::string &path) const;
    void freeTexture(SDL_Texture *texture) const;

    void clear() const;
    void drawTexture(SDL_Texture *texture, const SDL_Rect *src, const SDL_Rect *dest) const;

    void drawText(const std::string &text, SDL_Texture *fontTexture, SpriteAtlas *fontAtlas) const;

    void present() const;

    bool drawFilledRect(const SDL_Rect &rect, const SDL_Color &color) const;
    bool drawOutlinedRect(const SDL_Rect &rect, const SDL_Color &color) const;
    bool drawPoints(const SDL_Point *points, int count, const SDL_Color &color) const;

private:
    int _width, _height;
    std::shared_ptr<Window> _window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _renderer{nullptr, SDL_DestroyRenderer};

    static std::vector<std::string> getTextSprites(const std::string &text);

    SDL_Rect toWindowCoordinates(const SDL_Rect &rect) const;
    SDL_Rect fromWindowCoordinates(const SDL_Rect &rect) const;
};
