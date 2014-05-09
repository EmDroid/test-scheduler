

#include <mtools/fifo_scheduler.hpp>

#include <iostream>


void mtools::FifoScheduler::queue_resource(const size_t resource)
{
    m_resources.push(resource);
}


void mtools::FifoScheduler::queue_job(const size_t job)
{
    m_jobs.push(job);
}


bool mtools::FifoScheduler::idle()
{
    return m_jobs.empty();
}


void mtools::FifoScheduler::tick()
{
    while (m_jobs.size() > 0 && m_resources.size() >= m_jobs.front()) {
        std::cout << "[FIFO Scheduler] Started job of size: "
            << m_jobs.front() << std::endl;
        std::cout << "\tnodes:";
        for (size_t i = 0; i < m_jobs.front(); ++i) {
            std::cout << " #" << m_resources.front();
            m_resources.pop();
        }
        std::cout << std::endl;
        m_jobs.pop();
    }
}
