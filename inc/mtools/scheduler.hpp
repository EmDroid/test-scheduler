

#ifndef MTOOLS_SCHEDULER_INCLUDE_GUARD
#define MTOOLS_SCHEDULER_INCLUDE_GUARD


#include <cstdlib>


namespace mtools
{


class Scheduler
{

public:

    struct Job
    {

    public:

        Job(const size_t size, const size_t time)
            : m_size(size)
            , m_time(time)
        {}

        size_t m_size;
        size_t m_time;
    };

public:

    virtual ~Scheduler();

    virtual void queue_resource(const size_t resource) = 0;

    virtual void queue_job(const Job & job) = 0;

    virtual bool idle() const = 0;

    virtual void tick() = 0;

};


} // namespace mtools


inline mtools::Scheduler::~Scheduler()
{}


#endif // MTOOLS_SCHEDULER_INCLUDE_GUARD
