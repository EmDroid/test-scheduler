
#include <mtools/fifo_scheduler.hpp>
#include <mtools/optimized_scheduler.hpp>


#include <cstdlib>
#include <cassert>

#include <memory>
#include <iostream>


namespace mtools
{


class SchedulerTester
{

public:

    class Resources
    {

    public:

        Resources(
            FifoScheduler * const fifoScheduler,
            OptimizedScheduler * const optimizedScheduler)
            : m_fifoScheduler(fifoScheduler)
            , m_optimizedScheduler(optimizedScheduler)
        {
            assert(fifoScheduler != NULL);
            assert(optimizedScheduler != NULL);
        }

        Resources & operator << (const size_t resource)
        {
            std::cout << "A resource unit is available on compute node #"
                << resource << std::endl;
            assert(m_fifoScheduler != NULL);
            assert(m_optimizedScheduler != NULL);
            m_fifoScheduler->queue_resource(resource);
            m_optimizedScheduler->queue_resource(resource);
            return *this;
        }

    private:

        FifoScheduler * m_fifoScheduler;
        OptimizedScheduler * m_optimizedScheduler;

    };

    class Jobs
    {

    public:

        Jobs(
            FifoScheduler * const fifoScheduler,
            OptimizedScheduler * const optimizedScheduler)
            : m_fifoScheduler(fifoScheduler)
            , m_optimizedScheduler(optimizedScheduler)
        {
            assert(fifoScheduler != NULL);
            assert(optimizedScheduler != NULL);
        }

        Jobs & operator << (const size_t job)
        {
            std::cout << "Added job of size: "
                << job << std::endl;
            assert(m_fifoScheduler != NULL);
            assert(m_optimizedScheduler != NULL);
            m_fifoScheduler->queue_job(job);
            m_optimizedScheduler->queue_job(job);
            return *this;
        }

    private:

        FifoScheduler * m_fifoScheduler;
        OptimizedScheduler * m_optimizedScheduler;

    };

public:

    SchedulerTester()
        : m_fifoScheduler(new FifoScheduler)
        , m_optimizedScheduler(new OptimizedScheduler())
        , m_resources(m_fifoScheduler.get(), m_optimizedScheduler.get())
        , m_jobs(m_fifoScheduler.get(), m_optimizedScheduler.get())
    {}

public:

    Resources & resources()
    {
        return m_resources;
    }

    Jobs & jobs()
    {
        return m_jobs;
    }

    void tick(const size_t ticks = 1)
    {
        std::cout << "... tick ..." << std::endl;
        for (size_t i = 0; i < ticks; ++i) {
            m_fifoScheduler->tick();
            m_optimizedScheduler->tick();
        }
    }

    void finish()
    {
        while (!m_fifoScheduler->idle() || !m_optimizedScheduler->idle()) {
            tick();
        }
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

    tester.tick();

    tester.resources() << 2 << 7;
    tester.tick();
    tester.jobs() << 3 << 1 << 4;
    tester.tick(2);
    tester.jobs() << 1;
    tester.tick(3);
    tester.resources() << 1 << 8;
    tester.tick(2);
    tester.jobs() << 5;
    tester.tick(2);
    tester.resources() << 2 << 8 << 1 << 8;
    tester.tick(2);
    tester.jobs() << 9;
    tester.resources() << 2 << 8 << 4 << 5 << 9 << 0 << 4 << 5 << 2;
    tester.tick(2);
    tester.resources() << 3 << 5 << 3 << 6;
    tester.tick(2);
    tester.resources() << 2 << 8 << 4 << 5 << 9 << 0 << 4 << 5 << 2;
    tester.finish();

    return EXIT_SUCCESS;
}
