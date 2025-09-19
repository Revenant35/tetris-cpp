#include "Font.h"

#include "Log.h"

Core::Font::Font(const std::string &path, const int fontSize) {
    TTF_Font *font = TTF_OpenFont(path.c_str(), fontSize);
    if (font == nullptr) {
        throw std::runtime_error("Failed to load font: " + path + ". SDL_ttf error: " + TTF_GetError());
    }

    m_Font.reset(font);
    m_FontSize = TTF_FontHeight(m_Font.get());
}

Core::Font::Font(Font &&other) noexcept : m_Font(std::move(other.m_Font)),
                                          m_FontSize(other.m_FontSize) {
    other.m_FontSize = 0;
}

Core::Font &Core::Font::operator=(Font &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    m_Font = std::move(other.m_Font);
    m_FontSize = other.m_FontSize;
    other.m_FontSize = 0;

    return *this;
}
