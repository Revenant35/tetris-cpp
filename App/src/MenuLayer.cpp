#include "MenuLayer.h"

#include "Game.h"

MenuLayer::MenuLayer(const std::shared_ptr<Core::Window> &window) : Layer(window) {
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

void MenuLayer::RenderBackground() {
    constexpr SDL_Color transparentColor = {0, 0, 0, 192};

    m_Window->GetRenderer().drawFilledRect(transparentColor);
}

void MenuLayer::RenderUI() {

}

