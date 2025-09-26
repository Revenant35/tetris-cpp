#pragma once

#include "UI/Color.h"
#include "Core.h"

namespace Core {
    enum class HAlign : uint8_t { Left, Center, Right };

    enum class VAlign : uint8_t { Top, Middle, Bottom };

    class Text {
    public:
        const Color TextColor;
        const std::string FontFamily;
        const std::string FontPath;
        const std::string Content;
        const int FontSize;
        const HAlign HorizontalAlignment;
        const VAlign VerticalAlignment;

        constexpr Text(
            const Color &color,
            const std::string &fontFamily,
            const std::string &fontPath,
            const std::string &content,
            const int fontSize,
            const HAlign horizontalAlignment = HAlign::Left,
            const VAlign verticalAlignment = VAlign::Top
        ) noexcept
            : TextColor(color),
              FontFamily(fontFamily),
              FontPath(fontPath),
              Content(content),
              FontSize(fontSize),
              HorizontalAlignment(horizontalAlignment),
              VerticalAlignment(verticalAlignment) {
        }
    };
}
