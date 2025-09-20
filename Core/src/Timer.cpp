#include <SDL_timer.h>

#include "Timer.h"

namespace Core {
    Timer::Timer() {
        m_StartTicks = 0;
        m_PausedTicks = 0;

        m_Paused = false;
        m_Started = false;
    }

    void Timer::Start() {
        m_Started = true;
        m_Paused = false;

        m_StartTicks = SDL_GetTicks();
        m_PausedTicks = 0;
    }

    void Timer::Stop() {
        m_Started = false;
        m_Paused = false;

        m_StartTicks = 0;
        m_PausedTicks = 0;
    }

    void Timer::Pause() {
        if (m_Started && !m_Paused) {
            m_Paused = true;
            m_PausedTicks = SDL_GetTicks() - m_StartTicks;
            m_StartTicks = 0;
        }
    }

    void Timer::Unpause() {
        if (m_Started && m_Paused) {
            m_Paused = false;
            m_StartTicks = SDL_GetTicks() - m_PausedTicks;
            m_PausedTicks = 0;
        }
    }

    uint32_t Timer::GetTicks() const {
        Uint32 time = 0;

        if (!m_Started) {
            return time;
        }

        if (m_Paused) {
            time = m_PausedTicks;
        } else {
            time = SDL_GetTicks() - m_StartTicks;
        }

        return time;
    }
}
