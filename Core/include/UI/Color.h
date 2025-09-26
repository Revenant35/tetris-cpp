#pragma once

#include "Core.h"

namespace Core {
    /**
     * @brief A class representing RGBA color values
     * 
     * The Color class provides a convenient way to represent and manipulate colors
     * in an RGBA format. It includes predefined color constants, conversion methods
     * for SDL compatibility, and utility functions for color manipulation.
     */
    class Color {
    public:
        static const Color Black;
        static const Color White;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;
        static const Color Magenta;
        static const Color Cyan;
        static const Color Transparent;

        const uint8_t r, g, b, a;

        /**
         * @brief Constructs a color with the specified RGBA components
         * @param red Red component (0-255)
         * @param green Green component (0-255)
         * @param blue Blue component (0-255)
         * @param alpha Alpha component (0-255), defaults to 255 (fully opaque)
         */
        constexpr Color(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha = 255) noexcept
            : r(red),
              g(green),
              b(blue),
              a(alpha) {
        }

        /**
         * @brief Creates a new color with the specified alpha value
         * @param alpha The new alpha component (0-255)
         * @return A new Color with the same RGB values but the specified alpha
         */
        [[nodiscard]] constexpr Color withAlpha(const uint8_t alpha) const noexcept {
            return Color{r, g, b, alpha};
        }

        /**
         * @brief Creates a color from a 24-bit RGB integer value
         * @param rgb The RGB value in format 0xRRGGBB
         * @return A new Color with alpha set to 255 (fully opaque)
         */
        [[nodiscard]] static constexpr Color FromRGB(const uint32_t rgb) noexcept {
            const uint8_t r = rgb >> 16 & 0xFF;
            const uint8_t g = rgb >> 8 & 0xFF;
            const uint8_t b = rgb & 0xFF;
            return Color{r, g, b};
        }

        /**
         * @brief Creates a color from a 32-bit RGBA integer value
         * @param rgba The RGBA value in format 0xRRGGBBAA
         * @return A new Color with the specified RGBA components
         */
        [[nodiscard]] static constexpr Color FromRGBA(uint32_t rgba) noexcept {
            const uint8_t r = rgba >> 24 & 0xFF;
            const uint8_t g = rgba >> 16 & 0xFF;
            const uint8_t b = rgba >> 8 & 0xFF;
            const uint8_t a = rgba & 0xFF;
            return Color{r, g, b, a};
        }

        /**
         * @brief Equality comparison operator
         * @param other The color to compare with
         * @return true if colors have identical RGBA values, false otherwise
         */
        constexpr bool operator==(const Color &other) const noexcept {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }

        /**
         * @brief Inequality comparison operator
         * @param other The color to compare with
         * @return true if colors have different RGBA values, false otherwise
         */
        constexpr bool operator!=(const Color &other) const noexcept {
            return r != other.r || g != other.g || b != other.b || a != other.a;
        }
    };
}
