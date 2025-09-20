#include "Window.h"

#include "Log.h"

namespace Core {
    Window::Window(const WindowSpecification &specification) {
        m_Title = specification.Title;
        m_Width = specification.Width;
        m_Height = specification.Height;
        m_IsResizable = specification.IsResizable;
        m_IsMinimized = false;
        m_HasMouseFocus = false;
        m_HasKeyboardFocus = false;

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

        SDL_SetWindowMinimumSize(m_Window, specification.MinWidth, specification.MinHeight);
        SDL_SetWindowMaximumSize(m_Window, specification.MaxWidth, specification.MaxHeight);

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
            case SDL_WINDOWEVENT_MINIMIZED:
                m_IsMinimized = true;
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                m_IsMinimized = false;
                break;
            case SDL_WINDOWEVENT_RESTORED:
                m_IsMinimized = false;
                break;
            case SDL_WINDOWEVENT_ENTER:
                m_HasMouseFocus = true;
                break;
            case SDL_WINDOWEVENT_LEAVE:
                m_HasMouseFocus = false;
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                m_HasKeyboardFocus = true;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                m_HasKeyboardFocus = false;
                break;
        }
    }

    void Window::SetTitle(const std::string &value) {
        m_Title = value;
        SDL_SetWindowTitle(m_Window, m_Title.c_str());
    }

    void Window::SetWidth(const uint32_t value) const {
        SDL_SetWindowSize(m_Window, static_cast<int>(value), static_cast<int>(m_Height));
    }

    void Window::SetHeight(const uint32_t value) const {
        SDL_SetWindowSize(m_Window, static_cast<int>(m_Width), static_cast<int>(value));
    }

    void Window::SetSize(const uint32_t width, const uint32_t height) const {
        SDL_SetWindowSize(m_Window, static_cast<int>(width), static_cast<int>(height));
    }
}
