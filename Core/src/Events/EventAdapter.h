#pragma once

#include "Core.h"
#include "Events/Event.h"
#include <SDL_events.h>

namespace Core {
    std::optional<Event> CreateEventFromSDLEvent(const SDL_Event &event);
}
