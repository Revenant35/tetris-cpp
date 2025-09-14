#pragma once

#include "SpriteAtlas.h"
#include "nlohmann/json.hpp"

class SpriteLoader {
public:
    [[nodiscard]] static SpriteAtlas *loadSpriteAtlas(const std::string &path);
};
