#include "AppLayer.h"
#include "Log.h"

AppLayer::AppLayer(const std::shared_ptr<Core::Window> &window) : Layer(window) {
    TETRIS_INFO("AppLayer created");
    m_BlockAtlas = Core::SpriteLoader::loadSpriteAtlas("blocks_atlas.json");
    m_BlockTexture = window->GetRenderer().loadTexture(m_BlockAtlas->file);

    m_PlayfieldAtlas = Core::SpriteLoader::loadSpriteAtlas("playfields_atlas.json");
    m_PlayfieldTexture = window->GetRenderer().loadTexture(m_PlayfieldAtlas->file);

    m_Font = std::make_unique<Core::Font>("../../App/assets/fonts/font.ttf", 8);

    m_Game = Game{
        .m_Level = 1,
        .m_Score = 0,
        .m_LinesCleared = 0,
        .m_Playfield = Playfield{
            .cells = std::vector<PlayfieldCell>(200) // 10x20 playfield
        }
    };
}

AppLayer::~AppLayer() {
    free(m_BlockAtlas);
    free(m_PlayfieldAtlas);
    TETRIS_INFO("AppLayer destroyed");
}

void AppLayer::OnRender() {
    m_Window->GetRenderer().drawTexture(*m_PlayfieldTexture, &m_PlayfieldAtlas->sprites.at("A_TYPE"), nullptr);
    m_Window->GetRenderer().drawText(*m_Font, "FOOBAR", {255, 255, 255, 255}, SDL_Rect{10, 10, 50, 10});

    // m_Window->GetRenderer().drawText("LINES-" + std::to_string(m_Game.m_LinesCleared), m_FontTexture, m_FontAtlas);
}

void AppLayer::OnUpdate(const float deltaTime) {
    if (deltaTime > 0.1f) {
        TETRIS_WARN("High delta time detected: {0}", deltaTime);
    }
}
