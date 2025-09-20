#include "MenuLayer.h"

#include "Game.h"

MenuLayer::MenuLayer(const std::shared_ptr<Core::Window> &window) : Layer(window) {
}

MenuLayer::~MenuLayer() {

}

void MenuLayer::OnEvent(SDL_Event &event) {
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
}




