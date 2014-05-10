# Scheduler test

A test implementation of an optimizing scheduler.

## Compilation and running
### Windows
Contains MSVC 2010 project files (can be used by MSVC Express 2010 or newer).

### Linux
GNU makefile available, to build under Linux.
* make [all]: build the scheduler test
* make test: build and run the test
* make clean: clean intermediate object files
* make cleanall: full cleanup including the target executable

## Schedulers description

Contains two scheduler implementations:

### FIFO Scheduler
First come-first serve simple scheduler


### Optimizing scheduler
Scheduler, which tries to schedule the biggest requests first, as long as enough
nodes are available.

This lowers the average latency in general (i.e. the jobs will be waiting less
average time between being added to the Scheduler queue and being started).

However, on the other hand, for some particular jobs, the latency can be higher.

The "larger" jobs preference is grounded on the intent to make as few nodes idle
as possible all the time ("keep the hamsters busy"). Thus the optimizing
scheduler always wants to match the largest requests to the available nodes.

This could however lead to the situation, where the "smaller" jobs wait for more
time than with the FIFO scheduler, and if large jobs are coming and a big number
of nodes gets always free, the small jobs migh wait for a very long time
(this could be improved by taking the job actual latency into the weights too).

Also, if the "larger" jobs take a longer time, they might keep the resources, so
the "smaller" jobs could wait more because of that. Although in general it might
be true, that the larger jobs (which need a larger amount of nodes) can run for
a longer time than the smaller jobs, it is actually not necessarily always true
(as the smaller job can run for a long time too, and in the fact, the "larger"
job can actually finish faster, because it is using a larger number of nodes).
To take the job expected running time into account, we would need to know that
beforehand (i.e. the expected running time might not necessarily correlate
with the count of nodes requested by the job).

In the optimal usecase for the FIFO Scheduler (i.e. if there is always just
enough available nodes to run the first job in the queue), the Optimized
scheduler should run the jobs in the same order, thus the average latency would
be the same. But the average latency should never be worse than the FIFO
scheduler's average latency.
