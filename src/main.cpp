#include "Log.h"
#include "Renderer.h"

int main() {
    Tetris::Log::Init();
    TETRIS_INFO("Hello world!");

    Tetris::Renderer renderer;
    Tetris::Spritesheet spritesheet{"assets/sprites/font.png", 16, 3};

    SDL_Rect position{100, 100, 64, 64};

    renderer.drawSprite(
        spritesheet,
        &position,
        0,
        0
    );

    return 0;
}
