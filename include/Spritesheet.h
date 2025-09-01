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

        SDL_Surface *getSurface() const { return surface; }
        int getRowCount() const { return rowCount; }
        int getColumnCount() const { return columnCount; }

    private:
        SDL_Surface *surface;
        int rowCount;
        int columnCount;
    };
}
