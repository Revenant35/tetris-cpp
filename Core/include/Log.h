#pragma once

#include "Core.h"
#include <spdlog/logger.h>

namespace Core {
    class Log {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger> &GetLogger() { return s_Logger; }

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
}

#define TETRIS_TRACE(...)    ::Core::Log::GetLogger()->trace(__VA_ARGS__)
#define TETRIS_INFO(...)     ::Core::Log::GetLogger()->info(__VA_ARGS__)
#define TETRIS_WARN(...)     ::Core::Log::GetLogger()->warn(__VA_ARGS__)
#define TETRIS_ERROR(...)    ::Core::Log::GetLogger()->error(__VA_ARGS__)
#define TETRIS_ASSERT(x, ...) if(!(x)) { TETRIS_ERROR(__VA_ARGS__); exit(-1); }
