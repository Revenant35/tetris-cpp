#include "Events/Event.h"


namespace Core {
    std::optional<WindowEvent> CreateWindowEventFromSDLEvent(const SDL_WindowEvent &event) {
        switch (event.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED: {
                return WindowResizedEvent{
                    .Width=static_cast<unsigned int>(event.data1),
                    .Height=static_cast<unsigned int>(event.data2)};
            }
            case SDL_WINDOWEVENT_MINIMIZED: {
                return WindowMinimizedEvent{};
            }
            case SDL_WINDOWEVENT_MAXIMIZED: {
                return WindowMaximizedEvent{};
            }
            case SDL_WINDOWEVENT_RESTORED: {
                return WindowRestoredEvent{};
            }
            case SDL_WINDOWEVENT_FOCUS_GAINED: {
                return WindowFocusedEvent{};
            }
            case SDL_WINDOWEVENT_FOCUS_LOST: {
                return WindowUnfocusedEvent{};
            }
            case SDL_WINDOWEVENT_ENTER: {
                return WindowEnteredEvent{};
            }
            case SDL_WINDOWEVENT_LEAVE: {
                return WindowExitedEvent{};
            }
            default:
                return std::nullopt;
        }
    }

    bool IsKeyboardEvent(const SDL_Event &event) {
        return event.type == SDL_KEYDOWN || event.type == SDL_KEYUP;
    }

    std::optional<KeyEvent> CreateKeyEventFromSDLEvent(const SDL_KeyboardEvent &event) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                return KeyPressedEvent{
                    .KeyCode=static_cast<KeyCode>(event.keysym.sym),
                    .RepeatCount=event.repeat
                };
            }
            case SDL_KEYUP: {
                return KeyReleasedEvent{
                    .KeyCode=static_cast<KeyCode>(event.keysym.sym)
                };
            }
            default:
                return std::nullopt;
        }
    }

    bool IsMouseEvent(const SDL_Event &event) {
        return event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP;
    }

    std::optional<MouseEvent> CreateMouseEventFromSDLEvent(const SDL_Event &event) {
        switch (event.type) {
            case SDL_MOUSEMOTION: {
                const SDL_MouseMotionEvent &motion = event.motion;
                return MouseMovedEvent{
                    .X=static_cast<float>(motion.x),
                    .Y=static_cast<float>(motion.y),
                };
            }
            case SDL_MOUSEWHEEL: {
                const SDL_MouseWheelEvent &wheel = event.wheel;
                return MouseScrolledEvent{
                    .XOffset=wheel.preciseX,
                    .YOffset=wheel.preciseY
                };
            }
            case SDL_MOUSEBUTTONDOWN: {
                const SDL_MouseButtonEvent &button = event.button;
                return MouseButtonPressedEvent{
                    .Button=button.button,
                    .X=static_cast<float>(button.x),
                    .Y=static_cast<float>(button.y)
                };
            }
            case SDL_MOUSEBUTTONUP: {
                const SDL_MouseButtonEvent &button = event.button;
                return MouseButtonReleasedEvent{
                    .Button=button.button,
                    .X=static_cast<float>(button.x),
                    .Y=static_cast<float>(button.y)
                };
            }
            default:
                return std::nullopt;
        }
    }

    std::optional<Event> CreateEventFromSDLEvent(const SDL_Event &event) {
        if (event.type == SDL_WINDOWEVENT) {
            return CreateWindowEventFromSDLEvent(event.window);
        }

        if (IsKeyboardEvent(event)) {
            return CreateKeyEventFromSDLEvent(event.key);
        }

        if (IsMouseEvent(event)) {
            return CreateMouseEventFromSDLEvent(event);
        }

        return std::nullopt;
    }

}
