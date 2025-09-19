#pragma once
#include <cstdint>
#include <memory>
#include <SDL_render.h>

struct PlayfieldCell {
    uint8_t m_XIndex, m_YIndex;
    std::shared_ptr<SDL_Texture> m_Texture;
    SDL_Rect m_SrcRect;
};
