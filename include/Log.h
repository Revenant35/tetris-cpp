#pragma once

#include "spdlog/logger.h"

namespace Tetris {
    class Log {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger> &GetLogger() { return s_Logger; }

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
}

#define TETRIS_TRACE(...)    ::Tetris::Log::GetLogger()->trace(__VA_ARGS__)
#define TETRIS_INFO(...)     ::Tetris::Log::GetLogger()->info(__VA_ARGS__)
#define TETRIS_WARN(...)     ::Tetris::Log::GetLogger()->warn(__VA_ARGS__)
#define TETRIS_ERROR(...)    ::Tetris::Log::GetLogger()->error(__VA_ARGS__)
#define TETRIS_ASSERT(x, ...) if(!(x)) { TETRIS_ERROR(__VA_ARGS__); exit(-1); }
