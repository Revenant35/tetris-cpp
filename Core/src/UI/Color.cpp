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
        : m_Red(red),
          m_Green(green),
          m_Blue(blue),
          m_Alpha(alpha) {
    }

    constexpr Color::Color(const SDL_Color &color) noexcept : Color(color.r, color.g, color.b, color.a) {
    }

    constexpr SDL_Color Color::ToSDL() const noexcept {
        return SDL_Color{
            m_Red,
            m_Green,
            m_Blue,
            m_Alpha
        };
    }

    constexpr Color Color::withAlpha(const uint8_t a) const noexcept {
        return Color(m_Red, m_Green, m_Blue, a);
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
        return m_Red == other.m_Red && m_Green == other.m_Green && m_Blue == other.m_Blue && m_Alpha == other.m_Alpha;
    }

    constexpr bool Color::operator!=(const Color &other) const noexcept {
        return m_Red != other.m_Red || m_Green != other.m_Green || m_Blue != other.m_Blue || m_Alpha != other.m_Alpha;
    }
}
