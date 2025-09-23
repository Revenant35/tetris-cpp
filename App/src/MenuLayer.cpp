#include "MenuLayer.h"

#include "Application.h"
#include "Game.h"

MenuLayer::MenuLayer(const std::shared_ptr<Core::Window> &window) : Layer(window) {
    m_Font = Core::Application::Get().GetFontRegistry().Find("font");
}

MenuLayer::~MenuLayer() {
}

void MenuLayer::OnEvent(Core::InputEvent &event) {
    if (auto* keyEvent = std::get_if<Core::KeyEvent>(&event)) {
        // TODO: Holding down the key should not toggle pause multiple times
        if (auto* keyPressedEvent = std::get_if<Core::KeyPressedEvent>(keyEvent)) {
            if (keyPressedEvent->KeyCode == Core::Key::Escape) {
                Game::Get().GetData().IsPaused = !Game::Get().GetData().IsPaused;
                keyPressedEvent->IsHandled = true;
            }
        }
    }

    if (!Game::Get().GetData().IsPaused) {
        return;
    }
}

void MenuLayer::OnUpdate(float deltaTime) {
    if (!Game::Get().GetData().IsPaused) {
        return;
    }
}

void MenuLayer::OnRender() {
    if (!Game::Get().GetData().IsPaused) {
        return;
    }

    RenderBackground();
    RenderUI();
}

void MenuLayer::RenderBackground() const {
    constexpr SDL_Color backgroundColor = {0, 0, 0, 192};

    m_Window->GetRenderer().drawFilledRect(backgroundColor);
}

void MenuLayer::RenderUI() const {
    if (const auto font = m_Font.lock()) {
        constexpr SDL_Color textColor = {255, 255, 255, 255};
        constexpr uint32_t textHeight = 50;
        const int textOffsetX = m_Window->GetWidth() / 2;
        constexpr int textOffsetY = 100;
        const SDL_Point center {textOffsetX,textOffsetY};

        m_Window->GetRenderer().drawText(*font, "PAUSED", textColor, center, textHeight);
    }

}

