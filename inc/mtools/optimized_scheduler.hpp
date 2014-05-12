

#ifndef MTOOLS_OPTIMIZED_SCHEDULER_INCLUDE_GUARD
#define MTOOLS_OPTIMIZED_SCHEDULER_INCLUDE_GUARD


#include "mtools/scheduler.hpp"

#include <queue>
#include <deque>
#include <map>


namespace mtools
{


class OptimizedScheduler
    : public Scheduler
{

public:

    virtual void queue_resource(const size_t resource);

    virtual void queue_job(const Job & job);

    virtual bool idle() const;

    virtual void onTick();

private:

    // the resources queue
    std::queue<size_t> m_resources;


    typedef std::map<size_t, std::deque<Job> > JobQueue;

    // the jobs queue
    JobQueue m_jobs;

};


} // namespace mtools


#endif // MTOOLS_OPTIMIZED_SCHEDULER_INCLUDE_GUARD
