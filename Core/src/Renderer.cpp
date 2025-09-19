#include <stdexcept>

#include "Renderer.h"

#include <SDL_ttf.h>

#include "Log.h"
#include "Texture.h"

namespace Core {
    Renderer::Renderer(SDL_Window *window) {
        m_Window = window;

        m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
        if (m_Renderer == nullptr) {
            TETRIS_ERROR("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            throw std::runtime_error("Failed to create renderer");
        }
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

    // TODO: Use TTF here.
    void Renderer::drawText(const std::string &text, const Texture& fontTexture, SpriteAtlas *fontAtlas) const {
        constexpr int fontSize = 40;
        SDL_Rect spriteDest {
            .x = 10,
            .y = 10,
            .w = fontSize,
            .h = fontSize
        };

        const auto sprites = getTextSprites(text);

        for (auto sprite : sprites) {
            constexpr int textSpacing = 8;
            drawTexture(fontTexture, &fontAtlas->sprites[sprite], &spriteDest);
            spriteDest.x += fontSize + textSpacing;
        }
    }

    void Renderer::present() const {
        SDL_RenderPresent(m_Renderer);
    }

    bool Renderer::drawFilledRect(const SDL_Rect &rect, const SDL_Color &color) const {
        SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);

        const auto success = SDL_RenderFillRect(m_Renderer, &rect);
        if (success != 0) {
            TETRIS_ERROR("Unable to draw filled rect! SDL Error: %s\n", SDL_GetError());
            return false;
        }

        return true;
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

    std::vector<std::string> Renderer::getTextSprites(const std::string &text) {
        std::vector<std::string> sprites;
        sprites.reserve(text.length());
        for (const char c : text) {
            if (isdigit(c)) {
                sprites.push_back(std::string(1, c));
                continue;
            }

            if (islower(c)) {
                sprites.push_back(std::string(1, static_cast<char>(std::toupper(c))));
                continue;
            }

            if (isupper(c)) {
                sprites.push_back(std::string(1, c));
                continue;
            }


            switch (c) {
                case '-': sprites.push_back("DASH"); break;
                case ',': sprites.push_back("COMMA"); break;
                case '\'': sprites.push_back("APOSTROPHE"); break;
                case '!': sprites.push_back("EXCLAMATION"); break;
                case ' ': sprites.push_back("SPACE"); break;
                default: {
                    sprites.push_back("SPACE");
                    break;
                }
            }
        }
        return sprites;
    }
}
