#pragma once

#include <SDL_render.h>
#include <string>
#include <memory>
#include <stdexcept>
#include "Font.h"

namespace Core {
    /**
     * @brief Wrapper class for SDL_Texture management
     * Handles loading, rendering, and cleanup of textures
     */
    class Texture {
    public:
        Texture(SDL_Renderer *renderer, const std::string &path);
        Texture(SDL_Renderer *renderer, TTF_Font *font, const std::string &textureText, SDL_Color textColor);
        Texture(const Texture &) = delete;
        Texture &operator=(const Texture &) = delete;
        Texture(Texture &&other) noexcept;
        Texture &operator=(Texture &&other) noexcept;

        /**
         * @brief Get the underlying SDL_Texture pointer
         * @return The SDL_Texture pointer
         * @note This returns a non-owning pointer - do not delete it
         */
        SDL_Texture *GetSDLTexture() const { return m_Texture.get(); }

        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }

    private:
        struct TextureDeleter {
            void operator()(SDL_Texture *texture) const {
                if (texture) {
                    SDL_DestroyTexture(texture);
                }
            }
        };

        std::unique_ptr<SDL_Texture, TextureDeleter> m_Texture;
        int m_Width = 0, m_Height = 0;
    };
}
