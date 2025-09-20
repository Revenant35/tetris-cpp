#pragma once
#include <SDL_ttf.h>
#include <string>

namespace Core {
    class Font {
    public:
        Font(const std::string &path, int fontSize);
        ~Font();

        TTF_Font * GetTTFFont() const { return m_Font; }
    private:
        TTF_Font *m_Font = nullptr;
    };
}
