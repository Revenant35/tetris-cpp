#pragma once

#include "Window.h"
#include "Events/InputEvent.h"

namespace Core {
    class Layer {
    public:
        explicit Layer(const std::shared_ptr<Window> &window);
        virtual ~Layer() = default;

        virtual void OnEvent(InputEvent &event) {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
    protected:
        std::shared_ptr<Window> m_Window;
    };
}
