# Linux makefile for the mtools Scheduler project

TARGET = scheduler_test

OBJS = \
	scheduler.o \
	fifo_scheduler.o \
	optimized_scheduler.o \
	scheduler_test.o

VPATH = src/mtools:inc/mtools:test

all: $(TARGET)

test: $(TARGET)
	./$(TARGET)

clean:
	rm $(OBJS)

cleanall: clean
	rm $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -g -o2 -o $@ $^

.cpp.o:
	$(CXX) -c -Wall -o2 -I inc -o $@ $<

# dependencies
scheduler.cpp: scheduler.hpp

fifo_scheduler.hpp: scheduler.hpp

optimized_scheduler.hpp: scheduler.hpp

fifo_scheduler.cpp: fifo_scheduler.hpp

optimized_scheduler.cpp: optimized_scheduler.hpp

scheduler_test.cpp: fifo_scheduler.hpp optimized_scheduler.hpp

# EOF
