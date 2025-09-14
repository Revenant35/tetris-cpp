#include "Renderer.h"

#include <stdexcept>
#include "SDL_image.h"
#include "Window.h"
#include "SpriteAtlas.h"

Renderer::Renderer(const Window &window) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to initialize SDL");
    }

    renderer = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to create renderer");
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        throw std::runtime_error("Failed to initialize SDL_image");
    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture *Renderer::loadTexture(const std::string &path) const {
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (newTexture == nullptr) {
        printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return nullptr;
    }

    return newTexture;
}

void Renderer::freeTexture(SDL_Texture *texture) const {
    SDL_DestroyTexture(texture);
}

void Renderer::clear() const {
    SDL_RenderClear(renderer);
}

void Renderer::drawTexture(SDL_Texture *texture, const SDL_Rect *src, const SDL_Rect *dest) const {
    SDL_RenderCopy(renderer, texture, src, dest);
}

void Renderer::drawText(const std::string &text, SDL_Texture *fontTexture, SpriteAtlas *fontAtlas) const {
    constexpr int fontSize = 40;
    SDL_Rect spriteDest {
        .x = 10,
        .y = 10,
        .w = fontSize,
        .h = fontSize
    };

    const auto sprites = getTextSprites(text);

    for (auto sprite : sprites) {
        constexpr int textSpacing = 8;
        drawTexture(fontTexture, &fontAtlas->sprites[sprite], &spriteDest);
        spriteDest.x += fontSize + textSpacing;
    }
}

void Renderer::present() const {
    SDL_RenderPresent(renderer);
}

bool Renderer::drawFilledRect(const SDL_Rect &rect, const SDL_Color &color) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    const auto success = SDL_RenderFillRect(renderer, &rect);
    if (success != 0) {
        printf("Unable to draw filled rect! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool Renderer::drawOutlinedRect(const SDL_Rect &rect, const SDL_Color &color) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Point points[5];
    points[0] = {rect.x, rect.y};
    points[1] = {rect.x + rect.w, rect.y};
    points[2] = {rect.x + rect.w, rect.y + rect.h};
    points[3] = {rect.x, rect.y + rect.h};
    points[4] = {rect.x, rect.y};

    const auto success = SDL_RenderDrawLines(renderer, points, 5);
    if (success != 0) {
        printf("Unable to draw outlined rect! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool Renderer::drawPoints(const SDL_Point* points, const int count, const SDL_Color &color) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int i = 0; i < count; ++i) {
        auto success = SDL_RenderDrawPoint(renderer, points[i].x, points[i].y);

        if (!success) {
            printf("Unable to draw point! SDL Error: %s\n", SDL_GetError());
            return false;
        }
    }
    return true;
}

std::vector<std::string> Renderer::getTextSprites(const std::string &text) {
    std::vector<std::string> sprites;
    sprites.reserve(text.length());
    for (const char c : text) {
        if (isdigit(c)) {
            sprites.push_back(std::string(1, c));
            continue;
        }

        if (islower(c)) {
            sprites.push_back(std::string(1, static_cast<char>(std::toupper(c))));
            continue;
        }

        if (isupper(c)) {
            sprites.push_back(std::string(1, c));
            continue;
        }


        switch (c) {
            case '-': sprites.push_back("DASH"); break;
            case ',': sprites.push_back("COMMA"); break;
            case '\'': sprites.push_back("APOSTROPHE"); break;
            case '!': sprites.push_back("EXCLAMATION"); break;
            case ' ': sprites.push_back("SPACE"); break;
            default: {
                sprites.push_back("SPACE");
                break;
            }
        }
    }
    return sprites;
}