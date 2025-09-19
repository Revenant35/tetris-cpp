#pragma once

#include <SDL_render.h>
#include <string>
#include "Font.h"

namespace Core {
    class Texture {
    public:
        Texture(SDL_Renderer *renderer, const std::string &path);
        Texture(SDL_Renderer* renderer, TTF_Font *font, const std::string &textureText, SDL_Color textColor);
        ~Texture();

        SDL_Texture* GetSDLTexture() const { return m_Texture; }
    private:
        SDL_Texture* m_Texture = nullptr;

        int m_Width, m_Height;
    };
}
