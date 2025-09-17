#pragma once

#include <SDL_rect.h>
#include <string>
#include <unordered_map>

namespace Core {
    struct Size {
        int w{};
        int h{};
    };

    struct SpriteAtlas {
        std::string file;
        Size size;
        std::unordered_map<std::string, SDL_Rect> sprites;
    };

    class SpriteLoader {
    public:
        [[nodiscard]] static SpriteAtlas *loadSpriteAtlas(const std::string &path);
    };
}