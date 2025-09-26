#pragma once

#include "MouseCodeAdapter.h"

namespace Core {
    std::optional<MouseCode> fromSDL(const uint16_t mouseCode) {
        switch (mouseCode) {
			case SDL_BUTTON_LEFT: return ButtonLeft;
			case SDL_BUTTON_RIGHT: return ButtonRight;
			case SDL_BUTTON_MIDDLE: return ButtonMiddle;
			case SDL_BUTTON_X1: return Button3;
			case SDL_BUTTON_X2: return Button4;
        	default: return std::nullopt;
		}
	}

    std::optional<uint16_t> toSDL(const MouseCode mouseCode) {
        switch (mouseCode) {
			case ButtonLeft: return SDL_BUTTON_LEFT;
			case ButtonRight: return SDL_BUTTON_RIGHT;
			case ButtonMiddle: return SDL_BUTTON_MIDDLE;
			case Button3: return SDL_BUTTON_X1;
			case Button4: return SDL_BUTTON_X2;
        	default: return std::nullopt;
		}
	}
}
