#pragma once

#include "Core.h"
#include <SDL.h>
#include <SDL_image.h>

#include "SpriteLoader.h"
#include "Texture.h"
#include "UI/Button.h"
#include "UI/Text.h"

namespace Core {
    class Renderer {
    public:
        constexpr static int IMG_FLAGS = IMG_INIT_PNG;

        Renderer(SDL_Window *window);
        ~Renderer();

        std::unique_ptr<Texture> loadTexture(const std::string &path) const;

        void clear(const SDL_Color &color) const;
        void clear() const { clear(m_defaultClearColor); }

        void drawTexture(const Texture& texture, const SDL_Rect *src, const SDL_Rect *dest) const;

        void present() const;

        void drawFilledRect(const SDL_Color &color) const;

        void drawText(const Text &text, const SDL_Point &center) const;
        void drawButton(const Button &button, const SDL_Point &center) const;

        void drawFilledRect(const SDL_Rect &rect, const SDL_Color &color) const;
        bool drawOutlinedRect(const SDL_Rect &rect, const SDL_Color &color) const;
        bool drawPoints(const SDL_Point *points, int count, const SDL_Color &color) const;

    private:
        SDL_Window *m_Window;
        SDL_Renderer *m_Renderer;

        SDL_Color m_defaultClearColor{0, 0, 0, 0};
    };
}
