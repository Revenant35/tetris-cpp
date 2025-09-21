#pragma once

#include "KeyCodes.h"
#include "BaseEvent.h"
#include "Core.h"

namespace Core {
    struct KeyPressedEvent : BaseEvent {
        KeyCode KeyCode;
        uint8_t RepeatCount;
    };

    struct KeyReleasedEvent : BaseEvent {
        KeyCode KeyCode;
    };

    using KeyEvent = std::variant<
        KeyPressedEvent,
        KeyReleasedEvent
    >;
}
