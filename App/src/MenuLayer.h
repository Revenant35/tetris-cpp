#pragma once
#include "Layer.h"

class MenuLayer final : public Core::Layer {
public:
    MenuLayer(const std::shared_ptr<Core::Window> &window);
    ~MenuLayer() override;

    void OnEvent(SDL_Event &event) override;
    void OnUpdate(float deltaTime) override;
    void OnRender() override;
};