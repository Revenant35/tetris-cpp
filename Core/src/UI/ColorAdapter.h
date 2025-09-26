#pragma once

#include "UI/Color.h"
#include <SDL.h>

namespace Core {
    inline SDL_Color toSDL(const Color &color) noexcept {
        return SDL_Color{ color.r, color.g, color.b, color.a };
    }

    inline Color fromSDL(const SDL_Color &color) noexcept {
        return Color{ color.r, color.g, color.b, color.a };
    }
}
