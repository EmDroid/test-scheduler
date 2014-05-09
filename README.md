Scheduler test
==============

Some test implementation of an optimizing scheduler.

Contains two scheduler implementations:

FIFO Scheduler
--------------
First come-first serve simple scheduler


Optimizing scheduler
--------------------
Scheduler, which tries to schedule the biggest requests first, as long as enough
nodes are available.


Compilation and running
-----------------------
Windows: Contains MSVC 2010 project files (can be used by MSVC Express 2010 or
         newer).

Linux: GNU makefile to build under Linux.
       make [all]: build the scheduler test
       make test: build and run the test
       make clean: clean intermediate object files
       make cleanall: full cleanup including the target executable
