#pragma once

#include <string>
#include <SDL.h>
#include <memory>

#include "Renderer.h"

namespace Core {
    struct WindowSpecification {
        std::string Title;
        uint32_t Width = 800;
        uint32_t Height = 600;
        uint32_t MinWidth = 320;
        uint32_t MinHeight = 240;
        uint32_t MaxWidth = 1920;
        uint32_t MaxHeight = 1080;
        bool IsResizable = true;
        bool IsFullscreen = false;
    };

    class Window {
    public:
        Window(const WindowSpecification &specification);
        
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        
        Window(Window&& other) noexcept;
        Window& operator=(Window&& other) noexcept;

        void HandleEvent(const SDL_WindowEvent &windowEvent);

        const Renderer& GetRenderer() const { return *m_Renderer; }
        const std::string& GetTitle() const { return m_Title; }
        uint32_t GetWidth() const { return m_Width; }
        uint32_t GetHeight() const { return m_Height; }
        bool GetIsMinimized() const { return m_IsMinimized; }
        bool GetHasMouseFocus() const { return m_HasMouseFocus; }
        bool GetHasKeyboardFocus() const { return m_HasKeyboardFocus; }

        void SetTitle(const std::string &value);
        void SetWidth(uint32_t value) const;
        void SetHeight(uint32_t value) const;
        void SetSize(uint32_t width, uint32_t height) const;

    private:
        struct WindowDeleter {
            void operator()(SDL_Window* window) const {
                if (window) {
                    SDL_DestroyWindow(window);
                }
            }
        };
        
        std::string m_Title;
        uint32_t m_Width;
        uint32_t m_Height;
        bool m_IsResizable;
        bool m_IsMinimized;
        bool m_HasMouseFocus;
        bool m_HasKeyboardFocus;
        std::unique_ptr<SDL_Window, WindowDeleter> m_Window;
        std::unique_ptr<Renderer> m_Renderer;
    };
}
