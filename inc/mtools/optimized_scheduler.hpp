

#ifndef MTOOLS_OPTIMIZED_SCHEDULER_INCLUDE_GUARD
#define MTOOLS_OPTIMIZED_SCHEDULER_INCLUDE_GUARD


#include <mtools/scheduler.hpp>


namespace mtools
{


class OptimizedScheduler
    : public Scheduler
{

public:

    virtual void queue_resource(const size_t resource);

    virtual void queue_job(const size_t job);

    virtual bool idle();

    virtual void tick();

};


} // namespace mtools


#endif // MTOOLS_OPTIMIZED_SCHEDULER_INCLUDE_GUARD
