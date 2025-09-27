#pragma once

#include <SDL_rect.h>
#include "UI/Rect.h"

namespace Core {
    inline SDL_Rect toSDL(const Rect &rect) noexcept {
        return SDL_Rect{ rect.x, rect.y, rect.w, rect.h };
    }

    inline Rect fromSDL(const SDL_Rect &rect) noexcept {
        return Rect{ rect.x, rect.y, rect.w, rect.h };
    }
}
