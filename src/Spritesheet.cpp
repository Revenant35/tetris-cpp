#include "Spritesheet.h"
#include "Log.h"

namespace Tetris {
    Spritesheet::Spritesheet(
        const char *path,
        const int row_count,
        const int column_count
    ) {
        this->spritesheet_image = SDL_LoadBMP(path);
        TETRIS_ASSERT(spritesheet_image != nullptr, "Failed to load spritesheet image from path: {}", path);

        this->row_count = row_count;
        TETRIS_ASSERT(row_count > 0, "Row count must be greater than 0");

        this->column_count = column_count;
        TETRIS_ASSERT(column_count > 0, "Column count must be greater than 0");
    }

    Spritesheet::~Spritesheet() {
        SDL_FreeSurface(spritesheet_image);
    }
}
