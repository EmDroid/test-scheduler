
#include <mtools/fifo_scheduler.hpp>
#include <mtools/optimized_scheduler.hpp>


#include <cstdlib>
#include <cassert>

#include <memory>


namespace mtools
{


class SchedulerTester
{

public:

    class Resources
    {

    public:

        Resources & operator << (const size_t resource)
        {
            assert(m_fifoScheduler != NULL);
            assert(m_optimizedScheduler != NULL);
            m_fifoScheduler->queue_resource(resource);
            m_optimizedScheduler->queue_resource(resource);
            return *this;
        }

        void reset(
            FifoScheduler * const fifoScheduler,
            OptimizedScheduler * const optimizedScheduler)
        {
            assert(fifoScheduler != NULL);
            assert(optimizedScheduler != NULL);
            m_fifoScheduler = fifoScheduler;
            m_optimizedScheduler = optimizedScheduler;
        }

    private:

        FifoScheduler * m_fifoScheduler;
        OptimizedScheduler * m_optimizedScheduler;

    };

    class Jobs
    {

    public:

        Jobs & operator << (const size_t job)
        {
            assert(m_fifoScheduler != NULL);
            assert(m_optimizedScheduler != NULL);
            m_fifoScheduler->queue_job(job);
            m_optimizedScheduler->queue_job(job);
            return *this;
        }

        void reset(
            FifoScheduler * const fifoScheduler,
            OptimizedScheduler * const optimizedScheduler)
        {
            assert(fifoScheduler != NULL);
            assert(optimizedScheduler != NULL);
            m_fifoScheduler = fifoScheduler;
            m_optimizedScheduler = optimizedScheduler;
        }

    private:

        FifoScheduler * m_fifoScheduler;
        OptimizedScheduler * m_optimizedScheduler;

    };

public:

    SchedulerTester()
        : m_fifoScheduler()
        , m_optimizedScheduler()
        , m_resources()
        , m_jobs()
    {
        reset();
    }

    void reset()
    {
        m_fifoScheduler.reset(new FifoScheduler);
        m_optimizedScheduler.reset(new OptimizedScheduler());
        m_resources.reset(m_fifoScheduler.get(), m_optimizedScheduler.get());
        m_jobs.reset(m_fifoScheduler.get(), m_optimizedScheduler.get());
    }

public:

    Resources & resources()
    {
        return m_resources;
    }

    Jobs & jobs()
    {
        return m_jobs;
    }

private:

    std::auto_ptr< FifoScheduler > m_fifoScheduler;
    std::auto_ptr< OptimizedScheduler > m_optimizedScheduler;

    Resources m_resources;
    Jobs m_jobs;

};


} // namespace mtools


int main()
{
    //// the resource and request streams
    //std::vector< int > resources;
    //std::vector< int > requests;

    mtools::SchedulerTester tester;

    tester.resources() << 2 << 7;
    tester.jobs() << 3 << 1 << 4;
    tester.jobs() << 1;
    tester.resources() << 1 << 8;
    tester.jobs() << 5;
    tester.resources() << 2 << 8 << 1 << 8;
    tester.jobs() << 9;
    tester.resources()  << 2 << 8 << 4 << 5 << 9 << 0 << 4 << 5 << 2
        << 3 << 5 << 3 << 6;

    tester.reset();

    return EXIT_SUCCESS;
}
