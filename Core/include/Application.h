#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Layer.h"
#include "Timer.h"
#include "Window.h"

namespace Core {
    struct ApplicationSpecification {
        std::string Name = "Application";
        WindowSpecification WindowSpec;
    };

    class Application {
    public:
        Application(const ApplicationSpecification& specification = ApplicationSpecification());
        ~Application();

        void Run();
        void Stop();

        float GetFPS() const { return m_FrameCount / m_FPSTimer.GetSeconds(); }

        template<typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
        void PushLayer() {
            m_LayerStack.push_back(std::make_unique<TLayer>(m_Window));
        }

        static Application& Get();
        static float GetTime();
    private:
        ApplicationSpecification m_Specification;
        std::shared_ptr<Window> m_Window;
        bool m_Running = false;
        std::vector<std::unique_ptr<Layer>> m_LayerStack;
        Timer m_FPSTimer;
        uint64_t m_FrameCount = 0;
    };
}
