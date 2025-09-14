#include "Renderer.h"
#include "SpriteLoader.h"

void drawBlocks(SpriteAtlas *atlas, SDL_Texture *texture, const Renderer &renderer) {
    constexpr int blockSize = 32;
    SDL_Rect dest{0, 60, blockSize, blockSize};
    for (int j = 0; j < 10; j++) {
        const auto level = j+1;
        std::string key = "LEVEL_" + std::to_string(level);
        for (int i = 0; i < 4; i++) {
            std::string spriteKey = key + "_";
            switch (i) {
            case 0: spriteKey += "HOLLOW"; break;
            case 1: spriteKey += "LIGHT"; break;
            case 2: spriteKey += "DARK"; break;
            case 3: spriteKey += "STRIPE"; break;
            default: throw std::runtime_error("Unreachable");
            }

            renderer.drawTexture(texture, &atlas->sprites[spriteKey], &dest);
            dest.x += blockSize;
        }
        dest.x = 0;
        dest.y += blockSize;
    }

}

int main() {
    const Window window("SDL2 Tetris");
    const Renderer r(window);
    bool quit = false;
    SDL_Event e;

    const auto fontAtlas = SpriteLoader::loadSpriteAtlas("../assets/sprites/font_atlas.json");
    const auto fontTexture = r.loadTexture(fontAtlas->file);

    const auto blockAtlas = SpriteLoader::loadSpriteAtlas("../assets/sprites/blocks_atlas.json");
    const auto blockTexture = r.loadTexture(blockAtlas->file);

    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }

            r.clear();

            r.drawText("Hello, World!", fontTexture, fontAtlas);
            drawBlocks(blockAtlas, blockTexture, r);

            r.present();
        }
    }
    return 0;
}
