#pragma once

#include "Core.h"

namespace Core {
    using KeyCode = uint32_t;

    enum : KeyCode {
        D0 = 0, D1, D2, D3, D4, D5, D6, D7, D8, D9,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        Right, Left, Down, Up,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        KP0, KP1, KP2, KP3, KP4, KP5, KP6, KP7, KP8, KP9,
        Space, Quote, Comma, Minus, Period, Slash, Semicolon, Equal, LeftBracket, Backslash, RightBracket,
        GraveAccent, Escape, Enter, Tab, Backspace, Insert, Delete, PageUp, PageDown, Home, End, CapsLock,
        ScrollLock, NumLock, PrintScreen, Pause, LeftShift, LeftControl, LeftAlt, RightShift, RightControl,
        RightAlt, Menu,
        KPDecimal, KPDivide, KPMultiply, KPSubtract, KPAdd, KPEnter, KPEqual,
    };
}
