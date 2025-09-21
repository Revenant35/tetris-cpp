#pragma once

#include "Core.h"
#include "InputEvent.h"
#include "WindowEvent.h"
#include <SDL_events.h>

namespace Core {
    using Event = std::variant<InputEvent, WindowEvent>;

    std::optional<Event> CreateEventFromSDLEvent(const SDL_Event &event);
}
