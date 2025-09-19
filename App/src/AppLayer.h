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
    Core::SpriteAtlas* m_BlockAtlas;
    Core::SpriteAtlas* m_PlayfieldAtlas;

    std::unique_ptr<Core::Texture> m_BlockTexture;
    std::unique_ptr<Core::Texture> m_PlayfieldTexture;

    std::unique_ptr<Core::Font> m_Font;

    Game m_Game;
};