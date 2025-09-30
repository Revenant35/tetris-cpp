#pragma once

#include "Core.h"

struct SDL_Texture;
struct SDL_Renderer;
struct TTF_Font;
struct SDL_Color;

namespace Core {
    class Texture {
    public:
        Texture(SDL_Renderer *renderer, const std::string &path);
        Texture(SDL_Renderer* renderer, TTF_Font *font, const std::string &textureText, SDL_Color textColor);
        ~Texture();

        SDL_Texture* GetSDLTexture() const { return m_Texture; }
        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }
    private:
        SDL_Texture* m_Texture = nullptr;

        int m_Width, m_Height;
    };
}
