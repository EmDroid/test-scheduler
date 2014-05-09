

#ifndef MTOOLS_SCHEDULER_INCLUDE_GUARD
#define MTOOLS_SCHEDULER_INCLUDE_GUARD


#include <cstdlib>


namespace mtools
{


class Scheduler
{

public:

    virtual ~Scheduler();

    void queue_resource(const size_t resource);

    void queue_job(const size_t job);

};


} // namespace mtools


inline mtools::Scheduler::~Scheduler()
{}


#endif // MTOOLS_SCHEDULER_INCLUDE_GUARD
