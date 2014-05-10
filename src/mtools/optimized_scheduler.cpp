

#include "mtools/optimized_scheduler.hpp"

#include <iostream>


void mtools::OptimizedScheduler::queue_resource(const size_t resource)
{
    m_resources.push(resource);
}


void mtools::OptimizedScheduler::queue_job(const Job & job)
{
    m_jobs.push_back(job);
}


bool mtools::OptimizedScheduler::idle() const
{
    return m_running.empty();
}


void mtools::OptimizedScheduler::tick()
{
    // process the running jobs
    for (std::vector<Job>::iterator it = m_running.begin(); it != m_running.end(); ) {
        if (--it->m_timeRequired == 0) {
            std::cout << "[OPTIMIZED Scheduler] Finished job of size: "
                << it->m_size << std::endl;
            it = m_running.erase(it);
        } else {
            ++it;
        }
    }
    // check if any new job can be started
    while (m_jobs.size() > 0 && m_resources.size() > 0) {
        // try to find the biggest job which will fit the currently available nodes
        std::vector<Job>::iterator itLaunch = m_jobs.end();
        for (std::vector<Job>::iterator it = m_jobs.begin(); it != m_jobs.end(); ++it) {
            if (itLaunch != m_jobs.end() && it->m_size > m_resources.size()) {
                break;
            }
            if (it->m_size <= m_resources.size()
                && (itLaunch == m_jobs.end()
                || it->m_size > itLaunch->m_size)) {
                itLaunch = it;
            }
        }
        if (itLaunch == m_jobs.end()) {
            // nothing possible to launch
            break;
        } else {
            std::cout << "[OPTIMIZED Scheduler] Started job of size: "
                << itLaunch->m_size << std::endl;
            std::cout << "\tnodes:";
            for (size_t i = 0; i < itLaunch->m_size; ++i) {
                std::cout << " #" << m_resources.front();
                m_resources.pop();
            }
            std::cout << std::endl;
            m_running.push_back(*itLaunch);
            // trace the latency
            m_latencyCounter.add(itLaunch->m_timeWaiting);
            // remove from waiting jobs
            m_jobs.erase(itLaunch);
        }
    }
    // increase the latency of waiting jobs
    for (std::vector<Job>::iterator it = m_jobs.begin(); it != m_jobs.end(); ++it) {
        ++it->m_timeWaiting;
    }
}
