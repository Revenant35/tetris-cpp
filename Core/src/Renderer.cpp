#include "Core.h"

#include "Renderer.h"
#include "Log.h"
#include "Texture.h"
#include "UI/ColorAdapter.h"

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

    void Renderer::drawText(const Text &text, const SDL_Point &center) const {
        const auto font = TTF_OpenFont(text.FontPath.c_str(), text.FontSize);
        if (font == nullptr) {
            TETRIS_ERROR("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
            throw std::runtime_error("Failed to load font");
        }

        const auto surface = TTF_RenderText_Solid(font, text.Content.c_str(), toSDL(text.TextColor));

        if (surface == nullptr) {
            TTF_CloseFont(font);
            TETRIS_ERROR("Surface is null!");
            throw std::runtime_error("Surface is null");
        }

        const auto texture = SDL_CreateTextureFromSurface(m_Renderer, surface);

        if (texture == nullptr) {
            TTF_CloseFont(font);
            SDL_FreeSurface(surface);
            TETRIS_ERROR("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            throw std::runtime_error("Failed to create texture");
        }

        const auto width = surface->w;
        const auto height = surface->h;

        int x = 0, y = 0;
        switch (text.HorizontalAlignment) {
            case HAlign::Left:
                x = center.x;
                break;
            case HAlign::Center:
                x = center.x - width / 2;
                break;
            case HAlign::Right:
                x = center.x - width;
                break;
        }
        switch (text.VerticalAlignment) {
            case VAlign::Top:
                y = center.y;
                break;
            case VAlign::Middle:
                y = center.y - height / 2;
                break;
            case VAlign::Bottom:
                y = center.y - height;
                break;
        }

        const SDL_Rect rect = {x, y, width, height};

        SDL_RenderCopy(m_Renderer, texture, nullptr, &rect);

        TTF_CloseFont(font);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
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
