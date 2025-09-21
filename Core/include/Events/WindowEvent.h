#pragma once

#include "BaseEvent.h"
#include "Core.h"

namespace Core {
    struct WindowResizedEvent : BaseEvent {
        unsigned int Width;
        unsigned int Height;
    };

    struct WindowMinimizedEvent : BaseEvent {};
    struct WindowMaximizedEvent : BaseEvent {};
    struct WindowRestoredEvent : BaseEvent {};
    struct WindowFocusedEvent : BaseEvent {};
    struct WindowUnfocusedEvent : BaseEvent {};
    struct WindowEnteredEvent : BaseEvent {};
    struct WindowExitedEvent : BaseEvent {};

    using WindowEvent = std::variant<
        WindowResizedEvent,
        WindowMinimizedEvent,
        WindowMaximizedEvent,
        WindowRestoredEvent,
        WindowFocusedEvent,
        WindowUnfocusedEvent,
        WindowEnteredEvent,
        WindowExitedEvent
    >;
}
