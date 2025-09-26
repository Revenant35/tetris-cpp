#include "UI/Text.h"

#include "ColorAdapter.h"

Core::Text::Text(
    const Color &color,
    const std::string &fontFamily,
    const std::string &fontPath,
    const std::string& content,
    const int fontSize,
    const HAlign horizontalAlignment,
    const VAlign verticalAlignment
) : TextColor(color),
    FontFamily(fontFamily),
    FontPath(fontPath),
    Content(std::move(content)),
    FontSize(fontSize),
    HorizontalAlignment(horizontalAlignment),
    VerticalAlignment(verticalAlignment) {}

