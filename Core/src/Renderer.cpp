#include "Core.h"

#include "Renderer.h"
#include "Log.h"
#include "Texture.h"

namespace Core {
    Renderer::Renderer(SDL_Window *window) {
        m_Window = window;

        m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (m_Renderer == nullptr) {
            TETRIS_ERROR("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            throw std::runtime_error("Failed to create renderer");
        }

        SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
    }

    Renderer::~Renderer() {
        SDL_DestroyRenderer(m_Renderer);
    }

    std::unique_ptr<Texture> Renderer::loadTexture(const std::string &path) const {
        return std::make_unique<Texture>(m_Renderer, path);
    }

    void Renderer::clear(const SDL_Color &color) const {
        if (SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a) != 0) {
            TETRIS_ERROR(SDL_GetError());
        }

        if (SDL_RenderClear(m_Renderer) != 0) {
            TETRIS_ERROR(SDL_GetError());
        }
    }

    void Renderer::drawTexture(const Texture &texture, const SDL_Rect *src, const SDL_Rect *dest) const {
        SDL_RenderCopy(m_Renderer, texture.GetSDLTexture(), src, dest);
    }

    void Renderer::drawText(const Font &font, const std::string &text, const SDL_Color &color, const SDL_Rect &dest) const {
        const Texture textTexture(m_Renderer, font.GetTTFFont(), text, color);
        drawTexture(textTexture, nullptr, &dest);
    }

    void Renderer::present() const {
        SDL_RenderPresent(m_Renderer);
    }

    void Renderer::drawFilledRect(const SDL_Color &color) const {
        SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);

        if (SDL_RenderFillRect(m_Renderer, nullptr) != 0) {
            TETRIS_ERROR("Unable to draw filled rect! SDL Error: %s\n", SDL_GetError());
        }
    }

    void Renderer::drawFilledRect(const SDL_Rect &rect, const SDL_Color &color) const {
        SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);

        if (SDL_RenderFillRect(m_Renderer, &rect) != 0) {
            TETRIS_ERROR("Unable to draw filled rect! SDL Error: %s\n", SDL_GetError());
        }
    }

    bool Renderer::drawOutlinedRect(const SDL_Rect &rect, const SDL_Color &color) const {
        SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
        SDL_Point points[5];
        points[0] = {rect.x, rect.y};
        points[1] = {rect.x + rect.w, rect.y};
        points[2] = {rect.x + rect.w, rect.y + rect.h};
        points[3] = {rect.x, rect.y + rect.h};
        points[4] = {rect.x, rect.y};

        const auto success = SDL_RenderDrawLines(m_Renderer, points, 5);
        if (success != 0) {
            TETRIS_ERROR("Unable to draw outlined rect! SDL Error: %s\n", SDL_GetError());
            return false;
        }

        return true;
    }

    bool Renderer::drawPoints(const SDL_Point* points, const int count, const SDL_Color &color) const {
        SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);

        for (int i = 0; i < count; ++i) {
            auto success = SDL_RenderDrawPoint(m_Renderer, points[i].x, points[i].y);

            if (!success) {
                TETRIS_ERROR("Unable to draw point! SDL Error: %s\n", SDL_GetError());
                return false;
            }
        }
        return true;
    }
}
