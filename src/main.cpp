#include "Log.h"

int main() {
    Tetris::Log::Init();
    TETRIS_INFO("Hello world!");
    return 0;
}
