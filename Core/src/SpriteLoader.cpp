#include "SpriteLoader.h"

#include <fstream>
#include <SDL_rect.h>
#include "Serializers.h"

// TODO: Handle errors
namespace Core {
    SpriteAtlas *SpriteLoader::loadSpriteAtlas(const std::string &path) {
        std::ifstream fileStream("../../App/assets/sprites/" + path);
        const auto parsedJson = nlohmann::json::parse(fileStream);

        std::unordered_map<std::string, SDL_Rect> sprites;
        for (auto& [key, value] : parsedJson.at("sprites").items()) {
            sprites[key] = value.get<SDL_Rect>();
        }

        return new SpriteAtlas{
            .file = "../../App/assets/sprites/" + parsedJson.at("file").get<std::string>(),
            .size = parsedJson.at("size").get<Size>(),
            .sprites = sprites,
        };
    }
}
