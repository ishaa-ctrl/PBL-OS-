INTER-PROCESS COMMUNICATION (IPC)
PART : SHARED MEMORY
WRITTEN BY : E VISHNU VIJAYAN

What is Shared Memory?
Shared Memory is an IPC method that allows two or more processes to communicate by using a common area of memory.
Normally, each process has its own separate memory space. In shared memory, the operating system allows processes to access a particular memory region that is shared between them.

Basic flow:

Process A → Shared Memory ← Process B
How Shared Memory Works:
The operating system creates a shared memory area.
The required processes are given access to this memory.
One process can write data into the shared memory.
Another process can read the data from the same memory.
Since the processes access the same memory, communication is very fast.

Simple working:
Process A
↓
Writes Data
↓
Shared Memory
↓
Reads Data
↓
Process B

For example, Process A can write "Hello" into shared memory, and Process B can read "Hello" from the same memory.
Synchronization Basics:
When multiple processes access shared memory at the same time, data conflicts can occur.
For example, if one process is writing data while another process is changing the same data, the result may be incorrect.
To avoid this problem, synchronization methods such as locks, mutexes, and semaphores are used.

Simple flow:

Process A → Lock → Access Shared Memory → Unlock
Process B → Wait → Access Shared Memory → Unlock
This ensures that processes access the shared data in a controlled manner.

Advantages of Shared Memory:

-Very fast communication between processes.
-Less data copying is required.
-Useful for sharing large amounts of data.
-Processes can directly access shared data.
-Efficient for communication between processes on the same computer.

Disadvantages of Shared Memory:

-Synchronization is required.
-Race conditions can occur.
-Data may become inconsistent if not properly managed.
-More difficult to implement than simple IPC methods.
-Improper access can cause errors.

Simple Example:

Suppose there are two processes: Process A and Process B.
Process A writes "Hello" into the shared memory.

Process A
↓
Writes "Hello"
↓
Shared Memory
↓
Reads "Hello"
↓
Process B

Process B can then read "Hello" from the shared memory.

CONCLUSION :

Shared Memory is an IPC mechanism that allows multiple processes to access a common memory area.
It provides fast communication because processes can directly access shared data.
It is useful when processes need to exchange large amounts of data.
Synchronization is important to prevent data conflicts and race conditions.
Locks, mutexes, and semaphores can be used to safely control access to shared memory 
