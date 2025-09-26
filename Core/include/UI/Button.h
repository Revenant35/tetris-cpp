#pragma once
#include "Color.h"

namespace Core {
    struct Button {
        const Color TextColor;
        const Color BackgroundColor;

        const std::string FontFamily;
        const std::string FontPath;
        const std::string Content;
        const int FontSize;

        const int Width;
        const int Height;
        const int PaddingLeft = 8;
        const int PaddingRight = 8;
        const int PaddingTop = 8;
        const int PaddingBottom = 8;

        const bool isHovered = false;
        const bool isPressed = false;
    };
}
