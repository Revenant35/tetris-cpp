#pragma once

#include "Playfield.h"

class Game {
    struct GameData {
        uint16_t Level;
        uint32_t Score;
        uint32_t LinesCleared;
        Playfield Playfield;
        bool IsPaused;
    };
public:
    Game();
    ~Game();

    GameData &GetData() { return m_Data; }
    const GameData &GetData() const { return m_Data; }

    static Game& Get();
private:
    GameData m_Data;
};
