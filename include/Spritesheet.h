#pragma once

#include <SDL2/SDL.h>

namespace Tetris {
    class Spritesheet {
    public:
        Spritesheet(
            char const *path,
            int row_count,
            int column_count
        );

        ~Spritesheet();

        SDL_Surface *getSurface() const { return spritesheet_image; }
        int getRowCount() const { return row_count; }
        int getColumnCount() const { return column_count; }

    private:
        SDL_Surface *spritesheet_image;
        int row_count;
        int column_count;
    };
}
