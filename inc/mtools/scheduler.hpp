

#ifndef MTOOLS_SCHEDULER_INCLUDE_GUARD
#define MTOOLS_SCHEDULER_INCLUDE_GUARD


#include <cstdlib>
#include <vector>


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
            , m_timeRequired(time)
            , m_timeWaiting(0)
        {}

        size_t m_size;
        size_t m_timeRequired;
        size_t m_timeWaiting;
    };

public:

    virtual ~Scheduler();

    virtual void queue_resource(const size_t resource) = 0;

    virtual void queue_job(const Job & job) = 0;

    virtual bool idle() const = 0;

    virtual void tick() = 0;

    double getAverageLatency() const;

protected:

    // the running jobs
    std::vector<Job> m_running;

    class LatencyCounter
    {

    public:

        LatencyCounter()
            : m_total(0)
            , m_jobs(0)
        {}

        bool add(const size_t latency)
        {
            const size_t total = m_total + latency;
            if (total < m_total) {
                // overflow
                return false;
            }
            m_total = total;
            ++m_jobs;
            return true;
        }

        double average() const {
            if (!m_jobs) {
                return 0.0;
            } else {
                return static_cast<double>(m_total) / m_jobs;
            }
        }

    private:

        // total latency
        size_t m_total;

        // count of jobs taken into account
        size_t m_jobs;

    };

    LatencyCounter m_latencyCounter;

};


} // namespace mtools


inline mtools::Scheduler::~Scheduler()
{}


#endif // MTOOLS_SCHEDULER_INCLUDE_GUARD
