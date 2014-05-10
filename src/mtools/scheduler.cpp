

#include "mtools/scheduler.hpp"


double mtools::Scheduler::getAverageLatency() const
{
    return m_latencyCounter.average();
}
