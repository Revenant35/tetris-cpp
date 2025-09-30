#include "Texture.h"
#include "Log.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

Core::Texture::Texture(SDL_Renderer *renderer, const std::string &path) {
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        TETRIS_ERROR("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        throw std::runtime_error("Failed to load image");
    }

    m_Width = loadedSurface->w;
    m_Height = loadedSurface->h;
    m_Texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (m_Texture == nullptr) {
        TETRIS_ERROR("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        throw std::runtime_error("Failed to create texture");
    }
}

Core::Texture::Texture(SDL_Renderer *renderer, TTF_Font *font, const std::string &textureText, SDL_Color textColor) {
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == nullptr) {
        TETRIS_ERROR("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        throw std::runtime_error("Failed to render text surface");
    }

    m_Width = textSurface->w;
    m_Height = textSurface->h;
    m_Texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (m_Texture == nullptr) {
        TETRIS_ERROR("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to create texture");
    }

    SDL_FreeSurface(textSurface);
}

Core::Texture::~Texture() {
    SDL_DestroyTexture(m_Texture);
}
