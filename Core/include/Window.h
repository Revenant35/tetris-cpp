#pragma once

#include <string>
#include <SDL.h>

#include "Renderer.h"

namespace Core {
    struct WindowSpecification {
        std::string Title;
        uint32_t Width = 800;
        uint32_t Height = 600;
        bool IsResizable = true;
    };

    class Window {
    public:
        Window(const WindowSpecification &specification);
        ~Window();

        void HandleEvent(const SDL_WindowEvent &windowEvent);

        const Renderer& getRenderer() const { return *m_Renderer; }
        uint32_t getWidth() const { return m_Width; }
        uint32_t getHeight() const { return m_Height; }

    private:
        std::string m_Title;
        uint32_t m_Width;
        uint32_t m_Height;
        bool m_IsResizable;
        SDL_Window *m_Window;
        std::unique_ptr<Renderer> m_Renderer;
    };
}
