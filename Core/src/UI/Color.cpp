#include "UI/Color.h"

namespace Core {
    const Color Color::Black = {0, 0, 0};
    const Color Color::White = {255, 255, 255};
    const Color Color::Red = {255, 0, 0};
    const Color Color::Green = {0, 255, 0};
    const Color Color::Blue = {0, 0, 255};
    const Color Color::Yellow = {255, 255, 0};
    const Color Color::Magenta = {255, 0, 255};
    const Color Color::Cyan = {0, 255, 255};
    const Color Color::Transparent = {0, 0, 0, 0};

    constexpr Color::Color(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha) noexcept
        : r(red),
          g(green),
          b(blue),
          a(alpha) {
    }

    constexpr Color Color::withAlpha(const uint8_t alpha) const noexcept {
        return Color(r, g, b, alpha);
    }

    constexpr Color Color::FromRGB(const uint32_t rgb) noexcept {
        const uint8_t r = rgb >> 16 & 0xFF;
        const uint8_t g = rgb >> 8 & 0xFF;
        const uint8_t b = rgb & 0xFF;
        return Color(r, g, b);
    }

    constexpr Color Color::FromRGBA(const uint32_t rgba) noexcept {
        const uint8_t r = rgba >> 24 & 0xFF;
        const uint8_t g = rgba >> 16 & 0xFF;
        const uint8_t b = rgba >> 8 & 0xFF;
        const uint8_t a = rgba & 0xFF;
        return Color(r, g, b, a);
    }

    constexpr bool Color::operator==(const Color &other) const noexcept {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }

    constexpr bool Color::operator!=(const Color &other) const noexcept {
        return r != other.r || g != other.g || b != other.b || a != other.a;
    }
}
