#include "AppLayer.h"

#include "Application.h"
#include "FontRegistry.h"
#include "Log.h"
#include "UI/Text.h"

AppLayer::AppLayer(const std::shared_ptr<Core::Window> &window) : Layer(window) {
    TETRIS_INFO("AppLayer created");
    m_BlockAtlas = Core::SpriteLoader::loadSpriteAtlas("blocks_atlas.json");
    m_BlockTexture = window->GetRenderer().loadTexture(m_BlockAtlas->file);

    m_PlayfieldAtlas = Core::SpriteLoader::loadSpriteAtlas("playfields_atlas.json");
    m_PlayfieldTexture = window->GetRenderer().loadTexture(m_PlayfieldAtlas->file);

    m_Font = Core::Application::Get().GetFontRegistry().Find("font");
}

AppLayer::~AppLayer() {
    free(m_BlockAtlas);
    free(m_PlayfieldAtlas);
    TETRIS_INFO("AppLayer destroyed");
}

void AppLayer::OnRender() {
    if (const auto font = m_Font.lock()) {
        m_Window->GetRenderer().drawTexture(*m_PlayfieldTexture, &m_PlayfieldAtlas->sprites.at("A_TYPE"), nullptr);

        RenderPlayfieldType();
        RenderLinesCleared();
        RenderPieceStatistics();
        RenderNextPiece();
        RenderLevelInfo();
    }
}

void AppLayer::RenderPlayfieldType() const {
    const auto text = Core::Text {
        Core::Color::White,
        "font",
        "../../App/assets/fonts/font.ttf",
        "B TYPE",
        24,
        Core::HAlign::Center,
        Core::VAlign::Middle
    };

    const auto center = SDL_Point {
        static_cast<int>(m_Window->GetWidth() * 0.1875),
        static_cast<int>(m_Window->GetHeight() * 0.125),
    };

    m_Window->GetRenderer().drawText(text, center);
}

void AppLayer::RenderLinesCleared() const {
    const auto text = Core::Text {
        Core::Color::White,
        "font",
        "../../App/assets/fonts/font.ttf",
        "LINES - 14000",
        20,
        Core::HAlign::Center,
        Core::VAlign::Middle
    };

    const auto center = SDL_Point {
        static_cast<int>(m_Window->GetWidth() * 0.5325),
        static_cast<int>(m_Window->GetHeight() * 0.09),
    };

    m_Window->GetRenderer().drawText(text, center);
}

void AppLayer::RenderPieceStatistics() const {
    const auto text = Core::Text {
        Core::Color::White,
        "font",
        "../../App/assets/fonts/font.ttf",
        "STATISTICS",
        18,
        Core::HAlign::Center,
        Core::VAlign::Middle
    };

    const auto center = SDL_Point {
        static_cast<int>(m_Window->GetWidth() * 0.1875),
        static_cast<int>(m_Window->GetHeight() * 0.3125),
    };

    m_Window->GetRenderer().drawText(text, center);

    // TODO: Render actual piece statistics below the "STATISTICS" text
}

void AppLayer::RenderNextPiece() const {
    const auto text = Core::Text {
        Core::Color::White,
        "font",
        "../../App/assets/fonts/font.ttf",
        "NEXT",
        24,
        Core::HAlign::Center,
        Core::VAlign::Middle
    };

    const auto center = SDL_Point {
        static_cast<int>(m_Window->GetWidth() * 0.8125),
        static_cast<int>(m_Window->GetHeight() * 0.45),
    };

    m_Window->GetRenderer().drawText(text, center);

    // TODO: Render next piece sprite
}

void AppLayer::RenderLevelInfo() const {
    const auto levelText = Core::Text {
        Core::Color::White,
        "font",
        "../../App/assets/fonts/font.ttf",
        "LEVEL",
        24,
        Core::HAlign::Center,
        Core::VAlign::Middle
    };

    const auto levelCenter = SDL_Point {
        static_cast<int>(m_Window->GetWidth() * 0.83),
        static_cast<int>(m_Window->GetHeight() * 0.695),
    };

    m_Window->GetRenderer().drawText(levelText, levelCenter);


    const auto numberText = Core::Text {
        Core::Color::White,
        "font",
        "../../App/assets/fonts/font.ttf",
        "01",
        24,
        Core::HAlign::Center,
        Core::VAlign::Middle
    };

    const auto numberCenter = SDL_Point {
        static_cast<int>(m_Window->GetWidth() * 0.83),
        static_cast<int>(m_Window->GetHeight() * 0.735),
    };

    m_Window->GetRenderer().drawText(numberText, numberCenter);
}

void AppLayer::OnUpdate(const float deltaTime) {
    if (deltaTime > 0.1f) {
        TETRIS_WARN("High delta time detected: {0}", deltaTime);
    }
}
