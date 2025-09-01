#pragma once

#include "Spritesheet.h"
#include <SDL2/SDL.h>

namespace Tetris {
    class Renderer {
    public:
        Renderer();

        void drawSprite(
            const Spritesheet &sheet,
            SDL_Rect *position,
            int row,
            int column
        );
    private:
        SDL_Window *window;
        SDL_Surface *windowSurface;
    };
}

