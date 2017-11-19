# pthreads
Notes source: <http://www.csc.villanova.edu/~mdamian/threads/posixthreads.html>

Thread - independent stream of instructions that can be scheduled to ran as such by the os

thread group - a set of threads executing inside the same process

threads share memory - can access same global vars, same heap mem, same
    set of file descriptors
    - these threads execute in parallel (using time slices, or if many processors, then really in parallel

threads don't share: stack, registers

pthreads - implementations of threads that adhere to IEEE POSIX 1003.1c standard (1995) --> most hardware vendors offer pthreads in addition to proprietary threads

threads > processes at:
  - faster to create new ones bc they have less overhead
  - kernel doesn't have to copy as much to create a new thread since a lot is shared
  - thread creation 10x or 100x faster than process creation
  - faster to terminate thread than process
  - context switching between threads is faster because you don't have to switch the memory address space (a relatively expensive operation, also on some archs you avoid flushing processor caches that aren't sharable across address spaces [ie x86 flushes TLB and some ARM processors flush L1 cache] - thread context switching only requires switch out the processor state (such as program counter and register contents))
  - thread switching about as costly as entering and exiting the kernel
  - less communication overhead - since they share the same addr space, info produced by one thread is immediately available to all other threads

it is necessary to use pthread_exist(NULL) at the end of the main program otherwise when it exits all running threads will be killed

at any times threads are either joinable or detached

Notes source: <http://www.tutorialspoint.com/cplusplus/cpp_multithreading.htm>

* multithreading - form of multitasking

        multitasking
       /           \
process-based    thread-based

process-based
- concurrent execution of programs

thread-based
- concurrent execution of pieces of the same program

multithreaded program - program running more than one thread

each thread = separate path of execution

C++ --> no built in support for multithreaded applications???
  - relies on OS to provide this feature

pthreads - POSIX thread API

#include <pthreads.h>
pthread_create(pthread_t& tid, pthread_attr_t attr, start_routine(takes void* returns void*), arg to start routine)

- no implied hierarchy or dependency between threads - once you create one it may create other threads - each thread is a peer to the others

pthread_exit(status) -- explicitly exit a thread - if main exits with this then other threads will continue to run, if main exits by reaching the end of execution or another way, the threads it created will be terminated along with the main thread

pthread_join(tid, status)
pthread_detach(tid)

gcc hellomany.c -o hellomany -lpthread -g
gcc tutorialspoint1.cpp -lpthread

gpp tutorialspoint1.cpp -lpthread -Wall -g -O0 -v

Oh I noticed something quite interesting! Using \<\< to output data from c++
isn't atomic. It will happen with interleaving between threads.

So if I did intVar << stringvar in one thread and intVar2 << stringVar2 in
another you might see
intVarintVar2stringVar2stringvar

for example. Very interesting.
