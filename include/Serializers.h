#pragma once

#include <SDL_rect.h>
#include "nlohmann/json.hpp"
#include "Size.h"
#include "SpriteAtlas.h"

inline void to_json(nlohmann::json &json, const SDL_Rect &rect) {
    json = nlohmann::json{
        {"x", rect.x},
        {"y", rect.y},
        {"w", rect.w},
        {"h", rect.h}
    };
}

inline void from_json(const nlohmann::json &json, SDL_Rect &rect) {
    json.at("x").get_to(rect.x);
    json.at("y").get_to(rect.y);
    json.at("w").get_to(rect.w);
    json.at("h").get_to(rect.h);
}

inline void to_json(nlohmann::json &json, const Size &size) {
    json = nlohmann::json{
        {"w", size.w},
        {"h", size.h}
    };
}

inline void from_json(const nlohmann::json &json, Size &size) {
    json.at("w").get_to(size.w);
    json.at("h").get_to(size.h);
}

inline void to_json(nlohmann::json &json, const SpriteAtlas &atlas) {
    json = nlohmann::json{
        {"file", atlas.file},
        {"size", atlas.size},
        {"sprites", atlas.sprites}
    };
}

inline void from_json(const nlohmann::json &json, SpriteAtlas &atlas) {
    json.at("file").get_to(atlas.file);
    json.at("size").get_to(atlas.size);
    json.at("sprites").get_to(atlas.sprites);
}
