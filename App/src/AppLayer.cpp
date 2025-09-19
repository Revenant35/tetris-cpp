#include "AppLayer.h"
#include "Log.h"

AppLayer::AppLayer(const std::shared_ptr<Core::Window> &window) : Layer(window) {
    TETRIS_INFO("AppLayer created");
    m_FontAtlas = Core::SpriteLoader::loadSpriteAtlas("font_atlas.json");
    m_FontTexture = window->GetRenderer().loadTexture(m_FontAtlas->file);

    m_BlockAtlas = Core::SpriteLoader::loadSpriteAtlas("blocks_atlas.json");
    m_BlockTexture = window->GetRenderer().loadTexture(m_BlockAtlas->file);

    m_PlayfieldAtlas = Core::SpriteLoader::loadSpriteAtlas("playfields_atlas.json");
    m_PlayfieldTexture = window->GetRenderer().loadTexture(m_PlayfieldAtlas->file);
}

AppLayer::~AppLayer() {
    m_Window->GetRenderer().freeTexture(m_FontTexture);
    m_Window->GetRenderer().freeTexture(m_BlockTexture);
    m_Window->GetRenderer().freeTexture(m_PlayfieldTexture);

    free(m_FontAtlas);
    free(m_BlockAtlas);
    free(m_PlayfieldAtlas);
    TETRIS_INFO("AppLayer destroyed");
}

void AppLayer::OnRender() {
    m_Window->GetRenderer().drawTexture(m_PlayfieldTexture, &m_PlayfieldAtlas->sprites.at("A_TYPE"), nullptr);
}

void AppLayer::OnUpdate(const float deltaTime) {
    if (deltaTime > 0.1f) {
        TETRIS_WARN("High delta time detected: {0}", deltaTime);
    }
}
