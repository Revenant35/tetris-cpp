#pragma once

#include <string>
#include <unordered_map>
#include "Size.h"
#include <SDL.h>

struct SpriteAtlas {
    std::string file;
    Size size;
    std::unordered_map<std::string, SDL_Rect> sprites;
};
