#include "Window.h"

#include "Log.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"

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

    void Window::HandleEvent(WindowEvent &event) {
        std::visit(overloaded{
                       [this](WindowResizedEvent &e) {
                           m_Width = e.Width;
                           m_Height = e.Height;
                           e.IsHandled = true;
                       },
                       [this](WindowMinimizedEvent &e) {
                           m_IsMinimized = true;
                           e.IsHandled = true;
                       },
                       [this](WindowMaximizedEvent &e) {
                           m_IsMinimized = false;
                           e.IsHandled = true;
                       },
                       [this](WindowRestoredEvent &e) {
                           m_IsMinimized = false;
                           e.IsHandled = true;
                       },
                       [this](WindowFocusedEvent &e) {
                           m_HasKeyboardFocus = true;
                           e.IsHandled = true;
                       },
                       [this](WindowUnfocusedEvent &e) {
                           m_HasKeyboardFocus = false;
                           e.IsHandled = true;
                       },
                       [this](WindowEnteredEvent &e) {
                           m_HasMouseFocus = true;
                           e.IsHandled = true;
                       },
                       [this](WindowExitedEvent &e) {
                           m_HasMouseFocus = false;
                           e.IsHandled = true;
                       }
                   }, event);
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
