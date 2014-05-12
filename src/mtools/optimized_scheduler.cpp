

#include "mtools/optimized_scheduler.hpp"

#include <iostream>


void mtools::OptimizedScheduler::queue_resource(const size_t resource)
{
    m_resources.push(resource);
}


void mtools::OptimizedScheduler::queue_job(const Job & job)
{
    m_jobs[job.m_size].push_back(job);
}


bool mtools::OptimizedScheduler::idle() const
{
    return m_jobs.empty() && m_running.empty();
}


void mtools::OptimizedScheduler::onTick()
{
    // process the running jobs
    for (std::vector<Job>::iterator it = m_running.begin(); it != m_running.end(); ) {
        if (--it->m_timeRequired == 0) {
            //std::cout << "[OPTIMIZED Scheduler] Finished job of size: "
            //    << it->m_size << std::endl;
            it = m_running.erase(it);
        } else {
            ++it;
        }
    }
    // check if any new job can be started
    while (m_jobs.size() > 0 && m_resources.size() > 0) {
        // try to find the largest job which will fit the currently available nodes
        JobQueue::iterator itLaunch = m_jobs.upper_bound(m_resources.size());
        if (itLaunch == m_jobs.begin()) {
            // nothing else available to launch
            break;
        }
        --itLaunch;
        if (itLaunch->first > m_resources.size()) {
            // nothing else available to launch
            break;
        }
        //std::cout << "[OPTIMIZED Scheduler] Started job of size: "
        //    << itLaunch->m_size << std::endl;
        //std::cout << "\tnodes:";
        for (size_t i = 0; i < itLaunch->first; ++i) {
            //std::cout << " #" << m_resources.front();
            m_resources.pop();
        }
        //std::cout << std::endl;
        std::deque<Job> & bucket = itLaunch->second;
        m_running.push_back(bucket.front());
        // trace the latency
        m_latencyCounter.add(bucket.front().m_timeWaiting);
        // remove from waiting jobs
        bucket.pop_front();
        if (bucket.empty()) {
            m_jobs.erase(itLaunch);
        }
    }
    // increase the latency of waiting jobs
    for (JobQueue::iterator it = m_jobs.begin(); it != m_jobs.end(); ++it) {
        for (std::deque<Job>::iterator in = it->second.begin(); in != it->second.end(); ++in) {
            ++(in->m_timeWaiting);
        }
    }
}
