#include "Renderer.h"
#include <stdexcept>
#include <SDL_image.h>

Tetris::Renderer::Renderer() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to initialize SDL");
    }

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to create window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to create renderer");
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        throw std::runtime_error("Failed to initialize SDL_image");
    }
}

Tetris::Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* Tetris::Renderer::loadTexture(const std::string &path) const {
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

void Tetris::Renderer::freeTexture(SDL_Texture *texture) const {
    SDL_DestroyTexture(texture);
}

void Tetris::Renderer::clear() const {
    SDL_RenderClear(renderer);
}

void Tetris::Renderer::drawTexture(SDL_Texture *texture, const SDL_Rect *src, const SDL_Rect *dest) const {
    SDL_RenderCopy(renderer, texture, src, dest);
}

void Tetris::Renderer::present() const {
    SDL_RenderPresent(renderer);
}

bool Tetris::Renderer::drawFilledRect(const SDL_Rect &rect, const SDL_Color &color) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    if (SDL_RenderFillRect(renderer, &rect) != 0) {
        printf("Unable to draw filled rect! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool Tetris::Renderer::drawOutlinedRect(const SDL_Rect &rect, const SDL_Color &color) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Point points[5];
    points[0] = {rect.x, rect.y};
    points[1] = {rect.x + rect.w, rect.y};
    points[2] = {rect.x + rect.w, rect.y + rect.h};
    points[3] = {rect.x, rect.y + rect.h};
    points[4] = {rect.x, rect.y};

    if (SDL_RenderDrawLines(renderer, points, 5) != 0) {
        printf("Unable to draw outlined rect! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool Tetris::Renderer::drawPoints(const SDL_Point* points, const int count, const SDL_Color &color) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    bool success = true;
    for (int i = 0; i < count; ++i) {
        if (SDL_RenderDrawPoint(renderer, points[i].x, points[i].y) == 0) {
            printf("Unable to draw point! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
    }
    return success;
}
