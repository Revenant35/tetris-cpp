#pragma once

#include "Core.h"
#include "MouseCodes.h"
#include <SDL_mouse.h>

namespace Core {
    std::optional<MouseCode> fromSDL(uint16_t mouseCode);
    std::optional<uint16_t> toSDL(MouseCode mouseCode);
}
