#pragma once
#include <SDL_ttf.h>
#include <string>
#include <stdexcept>

namespace Core {
    /**
     * @brief Wrapper class for SDL_ttf font management
     * Handles loading, rendering, and cleanup of TTF fonts
     */
    class Font {
    public:
        Font(const std::string &path, int fontSize);
        Font(const Font&) = delete;
        Font& operator=(const Font&) = delete;
        Font(Font&& other) noexcept;
        Font& operator=(Font&& other) noexcept;

        /**
         * @brief Get the underlying TTF_Font pointer
         * @return The SDL TTF_Font pointer
         * @note This returns a non-owning pointer - do not delete it
         */
        TTF_Font* GetTTFFont() const { return m_Font.get(); }

        /**
         * @brief Gets the point size of the loaded font
         * @return Font size in points, or 0 if font is invalid
         */
        int GetPointSize() const { return m_FontSize; }

    private:
        struct FontDeleter {
            void operator()(TTF_Font* font) const {
                if (font) {
                    TTF_CloseFont(font);
                }
            }
        };
        
        std::unique_ptr<TTF_Font, FontDeleter> m_Font;
        int m_FontSize = 0;
    };
}

