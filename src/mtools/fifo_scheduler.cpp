

#include <mtools/fifo_scheduler.hpp>

#include <iostream>


void mtools::FifoScheduler::queue_resource(const size_t resource)
{
    m_resources.push(resource);
}


void mtools::FifoScheduler::queue_job(const Job & job)
{
    m_jobs.push(job);
}


bool mtools::FifoScheduler::idle()
{
    return m_running.empty();
}


void mtools::FifoScheduler::tick()
{
    for (std::vector<Job>::iterator it = m_running.begin(); it != m_running.end(); ) {
        if (--it->m_time == 0) {
            std::cout << "[FIFO Scheduler] Finished job of size: "
                << it->m_size << std::endl;
            it = m_running.erase(it);
        } else {
            ++it;
        }
    }
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
        m_jobs.pop();
    }
}
