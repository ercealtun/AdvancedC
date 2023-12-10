# THREADS

## Overview

- Programs often need to do several things at the same time.
- Games need to update the graphics on the screen while also reading input from a game controller.
- Chat programs will need to read text from the network and send data to the network at the same time.
- Media players will need to stream video to the display as well as watch for input from the user controls

## Threads

- You need something that starts a separate task quickly, can share all of your current data, and will not require a lot of code
to write
    * The answer is to use threads

- Threads are a way to divide a single process into sub-runnable parts
    * A separate path of execution inside a program 
    * Sometimes called "lightweight processes"

- A thread can also be scheduled independently of the larger program that is inside of (done by the OS)
    * Means that a single program may actually use more than 100% of CPU resources on multi-processor machines

- A thread has its own unique id, program counter (PC), register set, and a stack space just like a process

- Threads share memory across each thread by having the same address space (unlike multi-processes)
    * Two threads have access to the same set of variables and can alter each other's variable values
        > If one thread changes a global variable, all of the other threads will see the change immediately

- Threads also share OS resources like open files and signals
    * All of the threads will all be able to read and write to the same files and talk on the same network sockets
