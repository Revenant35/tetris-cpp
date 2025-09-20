#pragma once

#include <cstdint>

namespace Core {
    class Timer {
    public:
        Timer();

        void Start();

        void Stop();

        void Pause();

        void Unpause();

        uint32_t GetTicks() const;
        float GetSeconds() const { return GetTicks() / 1000.0f; }

        bool IsStarted() const { return m_Started; }
        bool IsPaused() const { return m_Paused && m_Started; }

    private:
        uint32_t m_StartTicks;
        uint32_t m_PausedTicks;

        bool m_Paused;
        bool m_Started;
    };
}
