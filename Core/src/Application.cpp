#include "Application.h"

#include <SDL.h>

#include "Log.h"

namespace Core {
    static Application* s_Instance = nullptr;

    Application::Application(const ApplicationSpecification &specification)
        :m_Specification(specification)
    {
        s_Instance = this;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            TETRIS_ERROR("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            throw std::runtime_error("Failed to initialize SDL");
        }

        constexpr int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            TETRIS_ERROR("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            throw std::runtime_error("Failed to initialize SDL_image");
        }

        Log::Init();

        if (m_Specification.WindowSpec.Title.empty()) {
            m_Specification.WindowSpec.Title = m_Specification.Name;
        }

        m_Window = std::make_shared<Window>(m_Specification.WindowSpec);
    }

    Application::~Application() {
        IMG_Quit();
        SDL_QuitSubSystem(SDL_INIT_VIDEO);

        s_Instance = nullptr;
    }

    void Application::Run() {
        m_Running = true;

        float lastTime = GetTime();
        SDL_Event event;

        while (m_Running) {
            while( SDL_PollEvent( &event ) != 0 ) {
                if( event.type == SDL_QUIT ) {
                    Stop();
                    break;
                }

                if( event.type == SDL_WINDOWEVENT ) {
                    m_Window->HandleEvent(event.window);
                }

                // TODO: Define Custom Events
                // TODO: Map SDL Events to Custom Events
                // TODO: Reverse iterate the layers here. Imagine pressing a button.
                for (const std::unique_ptr<Layer>& layer : m_LayerStack) {
                    // layer->OnEvent(event);
                }
            }

            const float currentTime = GetTime();
            const float timestep = std::clamp(currentTime - lastTime, 0.001f, 0.1f);
            lastTime = currentTime;

            for (const std::unique_ptr<Layer>& layer : m_LayerStack) {
                layer->OnUpdate(timestep);
            }

            m_Window->GetRenderer().clear();

            for (const std::unique_ptr<Layer>& layer : m_LayerStack) {
                layer->OnRender();
            }

            m_Window->GetRenderer().present();
        }
    }

    void Application::Stop() {
        m_Running = false;
    }

    Application& Application::Get() {
        return *s_Instance;
    }

    float Application::GetTime() {
        return 0.0f; // TODO: Return the current time here. SDL?
    }

}
