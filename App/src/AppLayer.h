#pragma once
#include "Game.h"
#include "Layer.h"

class AppLayer final : public Core::Layer {
public:
    AppLayer(const std::shared_ptr<Core::Window> &window);
    ~AppLayer() override;

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
private:
    Core::SpriteAtlas* m_FontAtlas;
    Core::SpriteAtlas* m_BlockAtlas;
    Core::SpriteAtlas* m_PlayfieldAtlas;

    SDL_Texture* m_FontTexture;
    SDL_Texture* m_BlockTexture;
    SDL_Texture* m_PlayfieldTexture;

    Game m_Game;
};