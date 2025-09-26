#include <SDL.h>
#include <SDL_ttf.h>

#include "Application.h"
#include "FontRegistry.h"
#include "Log.h"
#include "Events/EventAdapter.h"

namespace Core {
    static Application* s_Instance = nullptr;

    Application::Application(const ApplicationSpecification &specification)
        : m_Specification(specification), m_FontRegistry(8) {
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

        if (TTF_Init() != 0) {
            TETRIS_ERROR("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            throw std::runtime_error("Failed to initialize SDL_ttf");
        }

        Log::Init();

        if (m_Specification.WindowSpec.Title.empty()) {
            m_Specification.WindowSpec.Title = m_Specification.Name;
        }

        m_Window = std::make_shared<Window>(m_Specification.WindowSpec);
    }

    Application::~Application() {
        m_FontRegistry.Clear();
        IMG_Quit();
        TTF_Quit();
        SDL_QuitSubSystem(SDL_INIT_VIDEO);

        s_Instance = nullptr;
    }

    void Application::Run() {
        m_Running = true;

        float lastTime = GetTime();
        SDL_Event sdlEvent;

        m_FPSTimer.Start();

        while (m_Running) {
            while( SDL_PollEvent( &sdlEvent ) != 0 ) {
                if( sdlEvent.type == SDL_QUIT ) {
                    Stop();
                    break;
                }

                if (auto event = CreateEventFromSDLEvent(sdlEvent); event.has_value()) {
                    std::visit(overloaded{
                                   [this](WindowEvent &e) {
                                       m_Window->HandleEvent(e);
                                   },
                                   [this](InputEvent &e) {
                                       for (int i = static_cast<int>(m_LayerStack.size()) - 1; i >= 0; i--) {
                                           m_LayerStack[i]->OnEvent(e);
                                       }
                                   }
                    }, event.value());
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

            m_FrameCount++;
        }
    }

    void Application::Stop() {
        m_FPSTimer.Stop();
        m_LayerStack.clear();
        m_Running = false;
    }

    void Application::RegisterFont(const std::string &key, const std::string &path) {
        m_FontRegistry.Register(path, key);
    }

    Application& Application::Get() {
        return *s_Instance;
    }

    float Application::GetTime() {
        return 0.0f; // TODO: Return the current time here. SDL?
    }

}
