#pragma once

#include <SDL_rect.h>

namespace Tetris
{
    struct Spritesheet
    {
        const int spriteWidth;
        const int spriteHeight;
        const int columns;
        const int rows;
        const int horizontalSpacing;
        const int verticalSpacing;

        SDL_Rect &getSprite(int column, int row) const;
    };
}
