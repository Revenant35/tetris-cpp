#pragma once

#include "BaseEvent.h"
#include "MouseCodes.h"
#include "Core.h"

namespace Core {
    struct MouseMovedEvent : BaseEvent {
        float X;
        float Y;
    };

    struct MouseScrolledEvent : BaseEvent {
        float XOffset;
        float YOffset;
    };

    struct MouseButtonPressedEvent : BaseEvent {
        MouseCode Button;
        float X;
        float Y;
    };

    struct MouseButtonReleasedEvent : BaseEvent {
        MouseCode Button;
        float X;
        float Y;
    };

    using MouseEvent = std::variant<
        MouseMovedEvent,
        MouseScrolledEvent,
        MouseButtonPressedEvent,
        MouseButtonReleasedEvent
    >;
}
