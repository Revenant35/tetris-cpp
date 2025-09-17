#include "AppLayer.h"

#include "Log.h"

AppLayer::AppLayer(const std::shared_ptr<Core::Window> &window) : Layer(window) {
    TETRIS_INFO("AppLayer created");
}

AppLayer::~AppLayer() {

}

void AppLayer::OnRender() {
    m_Window->getRenderer().clear({255, 255, 255, 255});

    SDL_Rect dest = {0, 0, (int)m_Window->getWidth() / 2, (int)m_Window->getHeight() / 2};

    m_Window->getRenderer().drawFilledRect(dest, {255, 0, 255, 255});
}

void AppLayer::OnUpdate(const float deltaTime) {
    if (deltaTime > 0.1f) {
        TETRIS_WARN("High delta time detected: {0}", deltaTime);
    }
}
