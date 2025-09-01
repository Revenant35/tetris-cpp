#include "Spritesheet.h"
#include "Log.h"

Tetris::Spritesheet::Spritesheet(
    const char *path,
    const int row_count,
    const int column_count
) {
    this->surface = SDL_LoadBMP(path);
    TETRIS_ASSERT(surface != nullptr, "Failed to load spritesheet image from path: {}", path);

    this->rowCount = row_count;
    TETRIS_ASSERT(row_count > 0, "Row count must be greater than 0");

    this->columnCount = column_count;
    TETRIS_ASSERT(column_count > 0, "Column count must be greater than 0");
}

Tetris::Spritesheet::~Spritesheet() {
    SDL_FreeSurface(surface);
}
