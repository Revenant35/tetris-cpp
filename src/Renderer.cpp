#include "../include/Renderer.h"

#include "Log.h"

Tetris::Renderer::Renderer() {
    window = SDL_CreateWindow(
        "Pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    TETRIS_ASSERT(window != nullptr, "Failed to create window: {}", SDL_GetError());

    windowSurface = SDL_GetWindowSurface(window);

    TETRIS_ASSERT(windowSurface != nullptr, "Failed to get window surface: {}", SDL_GetError());
}

void Tetris::Renderer::drawSprite(
    const Spritesheet &sheet,
    SDL_Rect *position,
    const int row,
    const int column
) {
    const auto sheetSurface = sheet.getSurface();
    TETRIS_ASSERT(sheetSurface != nullptr, "Spritesheet surface is null");

    SDL_Rect clip;
    clip.w = sheetSurface->w / sheet.getColumnCount();
    clip.h = sheetSurface->h / sheet.getRowCount();
    clip.x = row * clip.w;
    clip.y = column * clip.h;
    SDL_BlitSurface(sheetSurface, &clip, windowSurface, position);
}