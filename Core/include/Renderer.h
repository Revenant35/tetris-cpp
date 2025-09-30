#pragma once

#include "Core.h"

#include "Texture.h"
#include "UI/Button.h"
#include "UI/Text.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Point;

namespace Core {
    class Window;

    class Renderer {
    public:
        Renderer(const Window &window);
        ~Renderer();

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer(Renderer&&) noexcept;
        Renderer& operator=(Renderer&&) noexcept;

        std::unique_ptr<Texture> loadTexture(const std::string &path) const;

        void clear(const Color &color) const;
        void clear() const { clear(Color::Black); }

        void drawTexture(const Texture& texture, const SDL_Rect *src, const SDL_Rect *dest) const;

        void present() const;

        void drawFilledRect(const Color &color) const;

        void drawText(const Text &text, const SDL_Point &center) const;
        void drawButton(const Button &button, const SDL_Point &center) const;

        void drawFilledRect(const SDL_Rect &rect, const Color &color) const;
        bool drawOutlinedRect(const SDL_Rect &rect, const Color &color) const;
        bool drawPoints(const SDL_Point *points, int count, const Color &color) const;

    private:
        SDL_Renderer *m_Renderer;
    };
}
