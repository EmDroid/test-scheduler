

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
    // create the job snapshot
    JobSnapshot snapshot;
    for (JobQueue::const_iterator it = m_jobs.begin(); it != m_jobs.end(); ++it) {
        snapshot[it->first] = it->second.size();
    }
    // check if any new job can be started
    size_t matchSize = 0;
    std::vector<size_t> jobs;
    matchJobs(m_resources.size(), snapshot,  matchSize, jobs);
    for (std::vector<size_t>::const_iterator it = jobs.begin(); it != jobs.end(); ++it) {
        //std::cout << "[OPTIMIZED Scheduler] Started job of size: "
        //    << *it << std::endl;
        //std::cout << "\tnodes:";
        for (size_t i = 0; i < *it; ++i) {
            //std::cout << " #" << m_resources.front();
            m_resources.pop();
        }
        //std::cout << std::endl;
        const JobQueue::iterator itJobQueue = m_jobs.find(*it);
        std::deque<Job> & bucket = itJobQueue->second;
        m_running.push_back(bucket.front());
        // trace the latency
        m_latencyCounter.add(bucket.front().m_timeWaiting);
        // remove from waiting jobs
        bucket.pop_front();
        if (bucket.empty()) {
            m_jobs.erase(itJobQueue);
        }
    }
    // increase the latency of waiting jobs
    for (JobQueue::iterator it = m_jobs.begin(); it != m_jobs.end(); ++it) {
        for (std::deque<Job>::iterator in = it->second.begin(); in != it->second.end(); ++in) {
            ++(in->m_timeWaiting);
        }
    }
}


void mtools::OptimizedScheduler::matchJobs(
    const size_t maxSize,
    JobSnapshot & status,
    size_t & matchSize,
    std::vector<size_t> & jobs) const
{
    // try to find the largest job(s) which will fit the currently available nodes
    JobSnapshot::iterator start = status.upper_bound(maxSize);
    if (start == status.begin()) {
        // nothing else available to launch
        return;
    }
    for (JobSnapshot::reverse_iterator it(start); it != status.rend(); ++it) {
        if (!it->second) {
            continue;
        }
        const size_t left = maxSize - it->first;
        // remove the current item from the snapshot
        --(it->second);
        // try to match the rest to (maxSize - current item)
        size_t tmpSize = 0;
        std::vector<size_t> tmpJobs;
        matchJobs(left, status, tmpSize, tmpJobs);
        tmpSize += it->first;
        if (matchSize < tmpSize) {
            jobs.clear();
            jobs.push_back(it->first);
            jobs.insert(jobs.end(), tmpJobs.begin(), tmpJobs.end());
            matchSize = tmpSize;
            if (matchSize == maxSize) {
                return;
            }
        }
        // return the current item back to the snapshot
        ++(it->second);
    }
}
