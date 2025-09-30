#include "Font.h"
#include "Log.h"
#include <SDL_ttf.h>

Core::Font::Font(const std::string &path, const int fontSize) {
    m_Font = TTF_OpenFont(path.c_str(), fontSize);
}

Core::Font::~Font() {
    TTF_CloseFont(m_Font);
}
