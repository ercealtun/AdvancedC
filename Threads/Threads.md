# THREADS

## Overview

- Programs often need to do several things at the same time.
- Games need to update the graphics on the screen while also reading input from a game controller.
- Chat programs will need to read text from the network and send data to the network at the same time.
- Media players will need to stream video to the display as well as watch for input from the user controls

## Threads

- You need something that starts a separate task quickly, can share all of your current data, and will not require a lot of code
to write
    - The answer is to use threads

- Threads are a way to divide a single process into sub-runnable parts
    - A separate path of execution inside a program 
    - Sometimes called "lightweight processes"

- A thread can also be scheduled independently of the larger program that is inside of (done by the OS)
    - Means that a single program may actually use more than 100% of CPU resources on multi-processor machines

- A thread has its own unique id, program counter (PC), register set, and a stack space just like a process

- Threads share memory across each thread by having the same address space (unlike multi-processes)
    - Two threads have access to the same set of variables and can alter each other's variable values
        - If one thread changes a global variable, all of the other threads will see the change immediately

- Threads also share OS resources like open files and signals
    - All of the threads will all be able to read and write to the same files and talk on the same network sockets

### Multi-threading

- Threads are popular way to improve an application through parallelism (simultaneous running of code)
    - Several tasks can execute concurrently (many tasks can run in any order and possibly in parallel)

- A multithreaded program is like a shop with several people working in it

- If one person is running the checkout, another is filling the shelves, and someone else is waxing the surfboards
    - Everybody can work without interruptions
    - If one person answers the phone, it won't stop the other people in the shop

- In the same way that several people can work in the same shop, you can have several threads living inside the same process (program)
    - Each thread runs independently (a thread of execution)

- Multi-threading means you can give each thread a separate task and they will all be performed at the same time
    - In a browser, multiple tabs can be different threads
    - MS word uses multiple threads, one thread to format the text, other thread to process inputs, etc.

### Advantages of using threads

- Threads require less overhead than "forking" or spawning a new process
    - The system does not initialize a new system virtual memory space and environment

- Threads provide efficient communication and data exchange because they share the same address space

- Threaded applications offer potential performance gains and practical advantages over non-threaded applications in several ways
    - The creation of a thread is much faster (much less operating system overhead)
    - Faster context switching
    - Faster termination of a thread

### Disadvantages of using threads

- Very easy to overlook the consequences of interactions between concurrently executing threads
    - Considerable potential for very obscure errors in your code

- Providing for thread synchronization is the biggest issue
    - The potential for two or more threads attempting to access the same data at the same time

- Imagine a program with several threads that may access a variable containing salary data

- Suppose that two independent threads can modify the value

- If one thread accesses the value to change it and the second thread does the same before the first thread has stored the modified value
    - You will have inconsistent data


### POSIX thread (pthread) libraries

- The POSIX thread libraries are a standards base thread API for C/C++
    - Allow one to spawn a new concurrent process flow
    - Can be found on almost any modern POSIX-compliant OS

- It is most effective on multi-processor or multi-core systems where the process flow can be scheduled to run on another processor
    - Thus gaining speed through parallel or distributed processing

- A thread is spawned by defining a function and it's arguments which will be processed in the thread

- The purpose of using the POSIX thread library in your software is to execute software faster

- pthread functions are defined in a pthread.h header/include file and implemented in a thread library

### pthreads API

- The functions that comprise the pthreads API can be grouped into 3 major categories

- Thread management
    - Routines that work directly on threads - creating, detaching, joining, etc.
    - Also include functions to set/query thread attributes (joinable, scheduling etc.)

- Synchronization
    - Routines that manage read/write locks and barriers and deal with synchronization
    - Mutex functions provide for creating, destroying, locking and unlocking mutexes (mutual exclusion)

- Condition variables
    - Routines that address communications between threads that share a mutex
    - Based upon programmer specified conditions

- Operations that can be performed on threads include
    - Thread creation
    - Termination
    - Synchronization (joins, blocking)
    - Scheduling
    - Data management
    - Process interaction

### Creating a thread

- The lifecycle of a thread, much like a process, begins with creation
    - Threads are not forked from a parent to create a child
    - Instead they are simply created with a starting function as the entry point

- On POSIX operating systems, there is a library named pthread.h
    - Allows you to create threads and perform many operations on threads
    - Must include this library when creating and using threads

- The pthread_create function is called to create a new thread and make it executable
    - Initially, your main() program comprises a single, default thread and all other threads must be explicitly created by programmer

- The maximum number of threads that may be created by a process is implementation dependent
    - Once created, threads are peers, and may create other threads
    - There is no implied hierarchy or dependency between threads

#### pthread_create

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void*(*start_routine)(void*), void* arg);

- pthread_create() takes 4 arguments

- Thew 1st argument is of type pthread_t
    - An integer used to identify the thread in the system
    - Upon successful completion, pthread_create() stores the ID of the created thread in the location referenced by thread

- The 2nd argument specifies attributes for the thread
    - You can specify a thread attributes object, or NULL for the default values
    - Examples of attributes that can be specified include detached state, scheduling policy, scope, stack address and stack size

- The 3rd argument is name of the function that the thread will execute once it is created

- The 4th argument is used to pass arguments to the function (start_routine)
    - A pointer cast of type void is required
    - NULL may be used if no argument is to be passed
    - To pass multiple arguments, you would need to use a pointer to a structure

#### pthread_join

- It is often useful to be able to identify when a thread has completed or exited

- The method for doing this is to join the thread, which is a lot like the wait() call for processes

- A join is performed when one wants to wait for a thread to finish
    - Used to link the current thread process to another thread
    - A thread calling routine may launch multiple threads then wait for them to finish to get the results

- A call to pthread_join blocks the calling thread until the thread with identifier equal to the first argument terminates
    - Makes the program stops in order to wait for the end of the selected thread

- Typically, only the main thread calls join, but other threads can also join each other

- All threads are automatically joined when the main thread terminates

- Thew pthread_join() also receives the return value of your thread function and stores it in a void pointer variable
    - Once both threads have finished, your program can exit smoothly

int pthread_join(pthread_t thread, void **value_ptr);,

- The 1st argument is the thread id of the thread you want to wait for

- If the 2nd argument is not NULL, this value is passed to pthread_exit() by the terminating thread

#### pthread_exit

- Threads can be terminated in a number of ways
    - By explicitly calling pthread_exit
    - By letting the thread function return
    - By a call to the function exit which will terminate the process including any threads

- Typically, the pthread_exit() routine is called after a thread has completed its work and is no longer required to exist

- If main() finishes before the threads it has created finish, and exits with pthread_exit(), the other threads will continue to execute
    - Otherwise, they will be automatically terminated when main() finishes

- Although not explicitly required to call pthread_exit() at the end of the thread function
    - It is good practice to do so, as you may have the need to return some arbitrary data back to the caller via pthread_join()

void pthread_exit(void *value_ptr);

-  The first argument makes the value_ptr available to any successful join with the terminating thread

- Sometimes it is desirable for a thread not to terminate (e.g., a server with a worker thread pool)
    - Can be solved by placing the thread code in an infinite loop and using condition variables