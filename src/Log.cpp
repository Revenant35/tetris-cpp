#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Tetris {
    std::shared_ptr<spdlog::logger> Log::s_Logger;

    void Log::Init() {
        s_Logger = spdlog::stdout_color_mt("TETRIS");
    }
} // Tetris
