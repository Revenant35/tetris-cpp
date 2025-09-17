#pragma once
#include "Layer.h"

class AppLayer final : public Core::Layer {
public:
    AppLayer(const std::shared_ptr<Core::Window> &window);
    ~AppLayer() override;

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
};