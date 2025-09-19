#include "Texture.h"
#include <SDL_ttf.h>
#include "Log.h"
#include <SDL_image.h>

Core::Texture::Texture(SDL_Renderer *renderer, const std::string &path) {
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        TETRIS_ERROR("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        throw std::runtime_error("Failed to load image");
    }

    m_Width = loadedSurface->w;
    m_Height = loadedSurface->h;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (texture == nullptr) {
        TETRIS_ERROR("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        throw std::runtime_error("Failed to create texture");
    }

    m_Texture.reset(texture);
}

Core::Texture::Texture(SDL_Renderer *renderer, TTF_Font *font, const std::string &textureText, SDL_Color textColor) {
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == nullptr) {
        TETRIS_ERROR("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        throw std::runtime_error("Failed to render text surface");
    }

    m_Width = textSurface->w;
    m_Height = textSurface->h;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    if (texture == nullptr) {
        TETRIS_ERROR("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to create texture");
    }

    m_Texture.reset(texture);
}

Core::Texture::Texture(Texture &&other) noexcept
    : m_Texture(std::move(other.m_Texture)),
      m_Width(other.m_Width),
      m_Height(other.m_Height) {
    other.m_Width = 0;
    other.m_Height = 0;
}

Core::Texture &Core::Texture::operator=(Texture &&other) noexcept {
    if (this != &other) {
        m_Texture = std::move(other.m_Texture);
        m_Width = other.m_Width;
        m_Height = other.m_Height;

        other.m_Width = 0;
        other.m_Height = 0;
    }
    return *this;
}
