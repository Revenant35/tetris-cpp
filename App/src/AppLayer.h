#pragma once
#include "Layer.h"

class AppLayer final : public Core::Layer {
public:
    AppLayer(const std::shared_ptr<Core::Window> &window);
    ~AppLayer() override;

    void OnUpdate(float deltaTime) override;
    void OnRender() override;

    void RenderPlayfieldType() const;

    void RenderLinesCleared() const;

    void RenderPieceStatistics() const;

    void RenderNextPiece() const;

    void RenderLevelInfo() const;

private:
    Core::SpriteAtlas* m_BlockAtlas;
    Core::SpriteAtlas* m_PlayfieldAtlas;

    std::unique_ptr<Core::Texture> m_BlockTexture;
    std::unique_ptr<Core::Texture> m_PlayfieldTexture;

    std::weak_ptr<Core::Font> m_Font;
};