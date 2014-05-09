

#ifndef MTOOLS_SCHEDULER_INCLUDE_GUARD
#define MTOOLS_SCHEDULER_INCLUDE_GUARD


#include <cstdlib>


namespace mtools
{


class Scheduler
{

public:

    virtual ~Scheduler();

    virtual void queue_resource(const size_t resource) = 0;

    virtual void queue_job(const size_t job) = 0;

    virtual bool idle() = 0;

    virtual void tick() = 0;

};


} // namespace mtools


inline mtools::Scheduler::~Scheduler()
{}


#endif // MTOOLS_SCHEDULER_INCLUDE_GUARD
