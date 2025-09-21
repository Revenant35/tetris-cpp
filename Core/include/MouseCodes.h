#pragma once

#include "Core.h"
#include <SDL_mouse.h>

namespace Core {
    using MouseCode = uint16_t;

    namespace Mouse {
        enum : MouseCode {
			Button0                = SDL_BUTTON_LEFT,
			Button1                = SDL_BUTTON_RIGHT,
			Button2                = SDL_BUTTON_MIDDLE,
			Button3                = SDL_BUTTON_X1,
			Button4                = SDL_BUTTON_X2,

			ButtonLeft             = Button0,
			ButtonRight            = Button1,
			ButtonMiddle           = Button2
        };
    }
}
