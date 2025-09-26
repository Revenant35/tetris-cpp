#include "MenuLayer.h"

#include "Application.h"
#include "Game.h"

MenuLayer::MenuLayer(const std::shared_ptr<Core::Window> &window) : Layer(window) {
}

MenuLayer::~MenuLayer() {
}

void MenuLayer::OnEvent(Core::InputEvent &event) {
    if (auto* keyEvent = std::get_if<Core::KeyEvent>(&event)) {
        // TODO: Holding down the key should not toggle pause multiple times
        if (auto* keyPressedEvent = std::get_if<Core::KeyPressedEvent>(keyEvent)) {
            if (keyPressedEvent->KeyCode == Core::Escape) {
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
    const auto text = Core::Text {
        Core::Color::White,
        "font",
        "../../App/assets/fonts/font.ttf",
        "PAUSED",
        50,
        Core::HAlign::Center,
        Core::VAlign::Middle
    };

    const int textOffsetX = m_Window->GetWidth() / 2;
    constexpr int textOffsetY = 100;
    const SDL_Point center {textOffsetX,textOffsetY};
    m_Window->GetRenderer().drawText(text, center);

    Core::Button button {
        Core::Color::White,
        Core::Color {64, 64, 64, 255},
        "font",
        "../../App/assets/fonts/font.ttf",
        "PRESS ESC TO RESUME",
        24,
        300,
        50
    };

    m_Window->GetRenderer().drawButton(button, {textOffsetX, textOffsetY + 100} );
}

