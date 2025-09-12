
#include "Spritesheet.h"

#include "Log.h"
SDL_Rect& Tetris::Spritesheet::getSprite(int column, int row) const
{
    if (column < 0 || column >= columns || row < 0 || row >= rows) {
        TETRIS_ERROR("Sprite index out of bounds: ({}, {})", column, row);
        static SDL_Rect empty = {0, 0, 0, 0};
        return empty;
    }

    static SDL_Rect rect;
    rect.x = column * (spriteWidth + horizontalSpacing);
    rect.y = row * (spriteHeight + verticalSpacing);
    rect.w = spriteWidth;
    rect.h = spriteHeight;

    return rect;
}
