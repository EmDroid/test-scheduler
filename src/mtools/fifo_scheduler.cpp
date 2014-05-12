

#include "mtools/fifo_scheduler.hpp"

#include <iostream>


void mtools::FifoScheduler::queue_resource(const size_t resource)
{
    m_resources.push(resource);
}


void mtools::FifoScheduler::queue_job(const Job & job)
{
    m_jobs.push_back(job);
}


bool mtools::FifoScheduler::idle() const
{
    return m_running.empty();
}


void mtools::FifoScheduler::onTick()
{
    // process the running jobs
    for (std::vector<Job>::iterator it = m_running.begin(); it != m_running.end(); ) {
        if (--it->m_timeRequired == 0) {
            std::cout << "[FIFO Scheduler] Finished job of size: "
                << it->m_size << std::endl;
            it = m_running.erase(it);
        } else {
            ++it;
        }
    }
    // check if any new job can be started
    while (m_jobs.size() > 0 && m_resources.size() >= m_jobs.front().m_size) {
        std::cout << "[FIFO Scheduler] Started job of size: "
            << m_jobs.front().m_size << std::endl;
        std::cout << "\tnodes:";
        for (size_t i = 0; i < m_jobs.front().m_size; ++i) {
            std::cout << " #" << m_resources.front();
            m_resources.pop();
        }
        std::cout << std::endl;
        m_running.push_back(m_jobs.front());
        // trace the latency
        m_latencyCounter.add(m_jobs.front().m_timeWaiting);
        // remove from waiting jobs
        m_jobs.pop_front();
    }
    // increase the latency of waiting jobs
    for (std::deque<Job>::iterator it = m_jobs.begin(); it != m_jobs.end(); ++it) {
        ++it->m_timeWaiting;
    }
}
