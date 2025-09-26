#pragma once

#include "Core.h"
#include "KeyCodes.h"
#include <SDL_keycode.h>

namespace Core {
    std::optional<KeyCode> fromSDL(SDL_Keycode k);
    std::optional<SDL_Keycode> toSDL(KeyCode k);
}