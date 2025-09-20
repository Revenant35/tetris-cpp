#include "Game.h"

static Game* s_Instance = nullptr;

Game::Game() {
    s_Instance = this;

    m_Data = {
        .Level = 1,
        .Score = 0,
        .LinesCleared = 0,
        .Playfield = Playfield{
            .cells = std::vector<PlayfieldCell>(200) // 10x20 playfield
        },
        .IsPaused = false
    };
}

Game::~Game() {
    s_Instance = nullptr;
}

Game& Game::Get() {
    return *s_Instance;
}

