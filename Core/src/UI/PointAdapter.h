#pragma once

#include <SDL_rect.h>
#include "UI/Point.h"

namespace Core {
    inline SDL_Point toSDL(const Point &point) noexcept {
        return SDL_Point{ point.x, point.y };
    }

    inline Point fromSDL(const SDL_Point &point) noexcept {
        return Point{ point.x, point.y };
    }
}
