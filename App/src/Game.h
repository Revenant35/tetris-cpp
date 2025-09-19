#pragma once

#include "Playfield.h"

struct Game {
    uint16_t m_Level;
    uint32_t m_Score;
    uint32_t m_LinesCleared;
    Playfield m_Playfield;
};