#include "Window.h"

#include "Log.h"

namespace Core {
    Window::Window(const WindowSpecification &specification) {
        m_Title = specification.Title;
        m_Width = specification.Width;
        m_Height = specification.Height;
        m_IsResizable = specification.IsResizable;

        uint32_t flags = SDL_WINDOW_SHOWN;
        if (m_IsResizable) {
            flags |= SDL_WINDOW_RESIZABLE;
        }

        m_Window = SDL_CreateWindow(
            m_Title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            m_Width,
            m_Height,
            flags
        );

        if (m_Window == nullptr) {
            TETRIS_ERROR("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            throw std::runtime_error("Failed to create window");
        }

        m_Renderer = std::make_unique<Renderer>(m_Window);
    }

    Window::~Window() {
        SDL_DestroyWindow(m_Window);
    }

    void Window::HandleEvent(const SDL_WindowEvent &windowEvent) {
        switch (windowEvent.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                m_Width = static_cast<uint32_t>(windowEvent.data1);
                m_Height = static_cast<uint32_t>(windowEvent.data2);
                break;
        }
    }
}
