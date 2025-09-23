#pragma once
#include "Layer.h"
#include "Events/InputEvent.h"

class MenuLayer final : public Core::Layer {
public:
    MenuLayer(const std::shared_ptr<Core::Window> &window);
    ~MenuLayer() override;

    void OnEvent(Core::InputEvent &event) override;
    void OnUpdate(float deltaTime) override;
    void OnRender() override;
private:
    void RenderBackground();
    void RenderUI();
};
