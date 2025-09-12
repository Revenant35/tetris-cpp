#include "Log.h"
#include "Renderer.h"
#include "Spritesheet.h"

int main()
{
    bool quit = false;
    SDL_Event e;

    Tetris::Log::Init();
    TETRIS_INFO("Hello world!");

    const Tetris::Renderer renderer;
    const auto texture = renderer.loadTexture("../assets/sprites/font.png");

    const Tetris::Spritesheet spritesheet{
        .columns = 16,
        .rows = 3,
        .horizontalSpacing = 1,
        .verticalSpacing = 1,
        .spriteWidth = 7,
        .spriteHeight = 7
    };

    const SDL_Point* sprites = new SDL_Point[8]{
        {3, 2},
        {10, 0},
        {12, 0},
        {1, 1},
        {10, 2},
        {11, 0},
        {10, 2},
        {9, 2},
    };

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            renderer.clear();

            int x = 10;
            int y = 10;
            for (int i = 0; i < 8; i++)
            {
                constexpr int spriteHeight = 14;
                constexpr int spriteWidth = 14;
                renderer.drawTexture(
                    *texture,
                    spritesheet.getSprite(sprites[i].x, sprites[i].y),
                    {
                        .x = x,
                        .y = y,
                        .w = spriteWidth,
                        .h = spriteHeight
                    }
                );
                x += spriteWidth + 2;
            }

            renderer.present();
        }
    }

    return 0;
}
