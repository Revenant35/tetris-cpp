#include "Texture.h"
#include "Log.h"
#include "SDL_image.h"

Core::Texture::Texture(SDL_Renderer* renderer, const std::string &path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
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

Core::Texture::~Texture() {
    SDL_DestroyTexture(m_Texture);
}

