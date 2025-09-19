#pragma once

#include <SDL_render.h>
#include <string>

namespace Core {
    class Texture {
    public:
        Texture(SDL_Renderer *renderer, const std::string &path);
        ~Texture();

        SDL_Texture* GetSDLTexture() const { return m_Texture; }
    private:
        SDL_Texture* m_Texture = nullptr;

        int m_Width, m_Height;
    };
}
