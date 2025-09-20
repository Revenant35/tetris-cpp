#include "AppLayer.h"
#include "Log.h"

AppLayer::AppLayer(const std::shared_ptr<Core::Window> &window) : Layer(window) {
    TETRIS_INFO("AppLayer created");
    m_BlockAtlas = Core::SpriteLoader::loadSpriteAtlas("blocks_atlas.json");
    m_BlockTexture = window->GetRenderer().loadTexture(m_BlockAtlas->file);

    m_PlayfieldAtlas = Core::SpriteLoader::loadSpriteAtlas("playfields_atlas.json");
    m_PlayfieldTexture = window->GetRenderer().loadTexture(m_PlayfieldAtlas->file);

    m_Font = std::make_unique<Core::Font>("../../App/assets/fonts/font.ttf", 8);
}

AppLayer::~AppLayer() {
    free(m_BlockAtlas);
    free(m_PlayfieldAtlas);
    TETRIS_INFO("AppLayer destroyed");
}

void AppLayer::OnRender() {
    m_Window->GetRenderer().drawTexture(*m_PlayfieldTexture, &m_PlayfieldAtlas->sprites.at("A_TYPE"), nullptr);

    SDL_Rect playfieldTypeRect {
        (int)(m_Window->GetWidth() * 0.09),
        (int)(m_Window->GetHeight() * 0.1),
        (int)(m_Window->GetWidth() * 0.195),
        (int)(m_Window->GetHeight() * 0.05),
    };

    m_Window->GetRenderer().drawFilledRect(playfieldTypeRect, {0, 0, 0, 255});
    m_Window->GetRenderer().drawText(*m_Font, "A TYPE", {255, 255, 255, 255}, playfieldTypeRect);


    SDL_Rect linesRect {
        (int)(m_Window->GetWidth() * 0.37),
        (int)(m_Window->GetHeight() * 0.065),
        (int)(m_Window->GetWidth() * 0.325),
        (int)(m_Window->GetHeight() * 0.05),
    };

    m_Window->GetRenderer().drawFilledRect(linesRect, {0, 0, 0, 255});
    m_Window->GetRenderer().drawText(*m_Font, "LINES - 140", {255, 255, 255, 255}, linesRect);

    // m_Window->GetRenderer().drawText("LINES-" + std::to_string(m_Game.m_LinesCleared), m_FontTexture, m_FontAtlas);
}

void AppLayer::OnUpdate(const float deltaTime) {
    if (deltaTime > 0.1f) {
        TETRIS_WARN("High delta time detected: {0}", deltaTime);
    }
}
