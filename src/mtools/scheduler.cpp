

#include "mtools/scheduler.hpp"


void mtools::Scheduler::tick()
{
    ++m_ticks;
    if (!m_running.empty()) {
        m_lastBusy = m_ticks;
    }
    onTick();
}
