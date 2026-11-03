OPERATING SYSTEMS

PROJECT-BASED LEARNING (PBL) REPORT

Project Title: Implementation and Simulation of Operating System Concepts Using C

Course: Operating Systems (OSCO)
Programming Language: C
Development Environment: Linux / Ubuntu, GCC, Visual Studio Code
Version Control: Git and GitHub
Project Duration: 5 Weeks

Submitted By:
Ayman Khan

---

1. INTRODUCTION

Operating Systems play an important role in managing computer hardware and software resources. They are responsible for process management, inter-process communication, CPU scheduling, memory management, and resource allocation.

The objective of this Project-Based Learning (PBL) project is to understand and implement important Operating System concepts through practical programming using the C language.

The project was completed over five weeks. Each week focused on a different Operating System concept, progressing from theoretical understanding to practical implementation and simulation.

The project covers:

1. Inter-Process Communication (IPC).
2. Multi-process communication using pipes and signals.
3. CPU Process Scheduling Algorithms.
4. Deadlock Detection and Recovery.
5. Page Replacement Algorithms.

This report provides a detailed description of my individual contributions to the project.

2. PROJECT OBJECTIVES

The major objectives of this project are:

- To understand fundamental Operating System concepts.
- To implement Inter-Process Communication using different communication mechanisms.
- To understand how multiple processes communicate and coordinate.
- To implement and analyse CPU scheduling algorithms.
- To understand deadlock detection and recovery techniques.
- To simulate page replacement algorithms used in memory management.
- To improve practical C programming, debugging, and problem-solving skills.
- To gain experience with Git and GitHub for version control.

3. TECHNOLOGIES AND TOOLS USED

Technology| Purpose
C Programming| Implementation of OS concepts
GCC Compiler| Compiling and executing C programs
Linux / Ubuntu| Execution environment
VS Code| Writing and debugging code
Git| Version control
GitHub| Code management

4. WEEK-WISE PROJECT IMPLEMENTATION

WEEK 1: INTER-PROCESS COMMUNICATION (IPC)

Introduction

Inter-Process Communication (IPC) is a mechanism that allows two or more independent processes to exchange information and coordinate their activities.

Since each process has its own memory space, processes require communication mechanisms to exchange data.

During this week, I studied the fundamentals of IPC, particularly the Message Passing technique.

Topics Covered

1. Message Passing

Message Passing is an IPC technique in which processes communicate by sending and receiving messages.

It mainly consists of two operations:

- Send: A process sends information to another process.
- Receive: A process receives information sent by another process.

For example:

Process A → Send(Message) → Process B → Receive(Message)

2. Direct Communication

In direct communication, the sender explicitly identifies the receiver process.

Example:

Process A → Process B

3. Indirect Communication

In indirect communication, processes exchange messages through an intermediate mechanism such as a mailbox or message queue.

Example:

Process A → Mailbox → Process B

4. Synchronous Communication

The sender or receiver waits until the required communication operation is completed.

5. Asynchronous Communication

The sender can continue its execution without waiting for the receiver to receive the message. Messages may be stored temporarily in a buffer or queue.

Advantages of Message Passing

- Provides simple communication between processes.
- Helps synchronize process execution.
- Does not require shared memory.
- Supports communication in distributed systems.
- Maintains process isolation.
- Supports synchronous and asynchronous communication.

My Contribution

During Week 1, I studied and documented the fundamentals of Inter-Process Communication, focusing on Message Passing.

I understood how independent processes exchange information through send and receive operations, the differences between direct and indirect communication, and the working principles of synchronous and asynchronous communication.

This theoretical foundation helped me understand the practical implementation of IPC in the following weeks.

---

WEEK 2: MULTI-PROCESS COMMUNICATION USING PIPES AND SIGNALS

Introduction

During the second week, I moved from theoretical IPC concepts to practical implementation using C programming.

I explored different communication mechanisms provided by the Linux operating system, including unnamed pipes, named pipes (FIFOs), and signals.

2.1 Three-Process OS Simulator

One of the major implementations involved developing a three-process architecture consisting of:

1. UI Process
2. Core Process
3. Logger Process

Each process performs a specific function.

- UI Process: Accepts commands from the user and communicates them to the Core Process.
- Core Process: Receives commands, executes the corresponding operations, and sends responses back to the UI Process.
- Logger Process: Receives information from the Core Process and records the executed commands.

My Contribution: Core Process Implementation

My assigned responsibility was designing and implementing the Core Process.

The Core Process acts as the central component of the simulator.

Its main responsibilities include:

- Creating the required FIFO communication channels.
- Receiving commands from the UI Process.
- Identifying and executing commands.
- Sending execution responses back to the UI Process.
- Sending execution logs to the Logger Process.
- Handling the exit command and terminating execution.

Commands Implemented

Command| Function
"start"| Starts simulated CPU execution
"status"| Displays CPU, memory, stack, and queue status
"stop"| Stops simulated CPU execution
"exit"| Shuts down the Core Process

Working of the Core Process

The implementation uses POSIX named pipes (FIFOs) for communication.

The following FIFO channels are used:

- "ui_to_core": Transfers commands from the UI Process to the Core Process.
- "core_to_ui": Transfers execution responses from the Core Process to the UI Process.
- "core_to_logger": Transfers log messages from the Core Process to the Logger Process.

The Core Process uses functions such as:

- "mkfifo()" – Creates named pipes.
- "open()" – Opens communication channels.
- "read()" – Receives commands.
- "write()" – Sends responses and log messages.
- "close()" – Closes communication channels.
- "strcmp()" – Compares incoming commands.
- "snprintf()" – Prepares log messages.

Communication Flow

UI Process
    |
    v
UI-to-Core FIFO
    |
    v
Core Process
    |
    |---- Executes Command
    |
    |---- Core-to-UI FIFO ----> UI Process
    |
    |---- Core-to-Logger FIFO -> Logger Process

This architecture demonstrates how multiple independent processes communicate through named pipes.

2.2 Unnamed Pipe Implementation

I also worked with a basic parent-child communication program using the "pipe()" and "fork()" system calls.

The parent process sends the message:

Hello from parent

The child process receives and displays the message.

Important functions used:

- "pipe()" – Creates an unnamed pipe.
- "fork()" – Creates a child process.
- "write()" – Sends data through the pipe.
- "read()" – Receives data from the pipe.
- "wait()" – Allows the parent to wait for the child process.

2.3 Signal-Based Communication

I also studied and worked with signal communication using two separate programs.

Signal Receiver:

- Registers a signal handler using "signal()".
- Displays its Process ID (PID).
- Waits for an incoming signal using "pause()".
- Displays a confirmation message when the signal is received.

Signal Sender:

- Accepts the receiver's PID as a command-line argument.
- Uses "kill()" to send the "SIGUSR1" signal.
- Displays a confirmation message after successfully sending the signal.

This demonstrates how one process can notify another process through signals.

Learning Outcome

Through this week's implementation, I gained practical knowledge of named pipes, unnamed pipes, process creation, and signal-based communication.

My main responsibility was the Core Process, which helped me understand how a central process can coordinate multiple independent processes.

---

WEEK 3: CPU PROCESS SCHEDULING SIMULATOR

Introduction

CPU Scheduling is an important function of an Operating System. It determines which process gets access to the CPU and for how long.

During this week, I worked on a CPU scheduling simulator that included six scheduling algorithms:

1. First Come First Serve (FCFS).
2. Non-Preemptive Shortest Job First (SJF).
3. Preemptive Shortest Job First (SRTF).
4. Non-Preemptive Priority Scheduling.
5. Preemptive Priority Scheduling.
6. Round Robin Scheduling.

The simulator generates Gantt charts and calculates important scheduling metrics.

My Contribution

My assigned responsibility was implementing two preemptive scheduling algorithms:

1. Preemptive Shortest Job First (SJF) – SRTF

Preemptive SJF is also known as Shortest Remaining Time First (SRTF).

In this algorithm, the CPU is allocated to the process with the shortest remaining burst time among all arrived processes.

If a new process arrives with a shorter remaining execution time than the currently running process, the CPU switches to the newly arrived process.

My implementation performs the following operations:

- Initializes the process information.
- Tracks the remaining burst time of each process.
- Checks which processes have arrived.
- Selects the process with the shortest remaining time.
- Preempts the current process when necessary.
- Records the first execution time.
- Updates the completion time when a process finishes.
- Generates the corresponding Gantt chart.

2. Preemptive Priority Scheduling

In Preemptive Priority Scheduling, the CPU executes the process with the highest priority.

In my implementation, a lower numerical priority value represents a higher priority.

For example:

- Priority 1 has higher priority than Priority 2.
- Priority 2 has higher priority than Priority 3.

If a new process arrives with a higher priority than the currently executing process, the CPU preempts the current process.

My implementation includes:

- Checking the arrival time of processes.
- Comparing the priority values.
- Selecting the highest-priority available process.
- Preempting processes when a higher-priority process arrives.
- Tracking remaining execution time.
- Calculating scheduling metrics.
- Generating Gantt chart entries.

Important Scheduling Metrics

Completion Time (CT):

The time at which a process finishes execution.

Turnaround Time (TAT):

TAT = Completion Time − Arrival Time

Waiting Time (WT):

WT = Turnaround Time − Burst Time

Response Time (RT):

RT = First Start Time − Arrival Time

Average Waiting Time:

Average WT = Total Waiting Time / Number of Processes

Average Turnaround Time:

Average TAT = Total Turnaround Time / Number of Processes

Testing and Verification

I created a separate test program to verify the implementation of both scheduling algorithms.

The test program uses three processes:

Process| Arrival Time| Burst Time| Priority
P1| 0| 5| 2
P2| 1| 3| 1
P3| 2| 1| 3

The program executes both algorithms and displays:

- Gantt charts.
- Completion time.
- Turnaround time.
- Waiting time.
- Response time.
- Average waiting time.
- Average turnaround time.

The implementation also handles CPU idle periods and combines consecutive execution intervals of the same process in the Gantt chart.

Learning Outcome

Through this implementation, I gained a deeper understanding of preemption, process selection, remaining burst time, priority comparison, and CPU scheduling performance.

I also learned how to calculate scheduling metrics programmatically and represent process execution through Gantt charts.

---

WEEK 4: INTERACTIVE DEADLOCK SIMULATION SYSTEM

Introduction

Deadlock is a condition in which a group of processes becomes permanently blocked because each process is waiting for a resource held by another process.

During this week, I worked on the Interactive Deadlock Simulation System to understand deadlock detection and recovery.

The system works with resource allocation, resource request, and available resource information.

My Contribution: Deadlock Detection and Recovery

My assigned responsibility was implementing the Deadlock Detection module.

I developed the detection implementation using the current Request matrix, Allocation matrix, and Available resource vector.

4.1 Deadlock Detection Algorithm

The detection algorithm determines whether processes are unable to proceed because the required resources are unavailable.

My implementation uses the following data structures:

- Available: Stores the number of currently available instances of each resource.
- Allocation: Represents the resources currently allocated to each process.
- Request: Represents the resources currently requested by each process.
- Work: A temporary array used to simulate resource availability.
- Finish: Tracks whether a process can complete execution.

Steps Involved in Detection

1. Initialize the Work array with the Available resource values.
2. Initialize the Finish array.
3. Identify processes that do not hold any resources and mark them as finished.
4. Check whether the current resource requests of unfinished processes can be satisfied using the available Work values.
5. If a process can finish, simulate its completion and release its allocated resources back into Work.
6. Repeat the process until no additional process can finish.
7. Identify the remaining unfinished processes as deadlocked processes.

The function "detectDeadlock()" returns the number of detected deadlocked processes and stores their process indices in an array.

4.2 Deadlock Recovery

Along with detection, I implemented a recovery function called "recoverDeadlock()".

The recovery mechanism terminates a selected process and releases the resources allocated to it.

The implementation performs the following operations:

- Validates the selected process ID.
- Returns the allocated resources to the Available array.
- Clears the process's allocated resources.
- Resets its resource requests.
- Clears its maximum resource and need information.
- Displays a confirmation message after successful termination.

This allows the simulation system to demonstrate how terminating a process can help recover from a deadlock situation.

Important Functions

"detectDeadlock()"

Identifies processes that remain unfinished after the resource-availability simulation.

"recoverDeadlock()"

Terminates a selected process and releases its allocated resources.

Learning Outcome

This implementation helped me understand resource allocation, deadlock conditions, detection techniques, and recovery mechanisms.

I also gained practical experience working with matrices, arrays, loops, and resource-management logic in C.

---

WEEK 5: PAGE REPLACEMENT ALGORITHMS

Introduction

Page Replacement is an important concept in Operating System memory management.

When a process requires a page that is not currently available in physical memory and all memory frames are occupied, the Operating System must select an existing page to replace.

During this week, I worked on implementing and simulating page replacement algorithms.

My Contribution: Least Recently Used (LRU) Algorithm

My assigned responsibility was implementing the Least Recently Used (LRU) page replacement algorithm.

5.1 Understanding LRU

LRU stands for Least Recently Used.

It is a page replacement algorithm that replaces the page that has not been accessed for the longest period of time.

The main idea is that pages used recently are more likely to be used again in the near future.

When a page fault occurs and all frames are occupied, LRU identifies the page with the oldest last-used time and replaces it with the newly requested page.

5.2 Implementation Details

I implemented the algorithm using C programming.

The main function is:

simulate_lru()

It accepts:

- "pages[]" – The reference string containing the sequence of requested pages.
- "n" – The total number of page references.
- "frame_count" – The number of available memory frames.
- "result" – A structure that stores simulation results.

Working of My Implementation

The implementation uses two arrays:

1. Frames Array

Stores the pages currently loaded into memory frames.

Initially, all frames are initialized to "-1", indicating that they are empty.

2. Last Used Array

Stores the most recent reference position of each page in its corresponding frame.

Initially, all values are set to "-1".

Steps Involved

1. Initialize all memory frames as empty.
2. Read each page from the reference string.
3. Check whether the requested page is already present in any frame.
4. If the page is present, record a page hit and update its last-used position.
5. If the page is absent, record a page fault.
6. If an empty frame is available, insert the new page into it.
7. If all frames are occupied, identify the page with the smallest last-used position.
8. Replace that page with the newly requested page.
9. Update the frame information after every page reference.

Page Hits and Page Faults

Page Hit: Occurs when the requested page is already present in memory.

Page Fault: Occurs when the requested page is not available in memory and must be loaded.

My implementation records:

- Total page references.
- Total page hits.
- Total page faults.
- Frame contents after every reference.
- Whether each reference resulted in a hit or fault.

Learning Outcome

Through this implementation, I understood how page replacement algorithms manage limited memory frames.

I learned how to track page usage, identify the least recently used page, perform replacement, and calculate page hits and page faults.

This improved my understanding of virtual memory and memory management techniques.

---

5. SUMMARY OF MY INDIVIDUAL CONTRIBUTIONS

My major responsibilities throughout the five-week project are summarized below:

Week| Topic| My Individual Contribution
Week 1| IPC and Message Passing| Studied and documented Message Passing concepts
Week 2| Multi-Process Communication| Designed and implemented the Core Process using named pipes; worked with pipe and signal communication
Week 3| CPU Scheduling| Implemented Preemptive SJF (SRTF) and Preemptive Priority Scheduling
Week 4| Deadlock Simulation| Implemented Deadlock Detection and Recovery
Week 5| Page Replacement| Implemented the Least Recently Used (LRU) algorithm

6. OVERALL PROJECT LEARNING OUTCOMES

Throughout the five weeks, this PBL project provided practical experience with several important Operating System concepts.

The major learning outcomes include:

1. Understanding how independent processes communicate using IPC mechanisms.
2. Learning the practical use of named pipes, unnamed pipes, and signals.
3. Understanding how multiple processes coordinate through a multi-process architecture.
4. Learning how CPU scheduling algorithms select processes for execution.
5. Understanding preemption and its impact on scheduling performance.
6. Implementing deadlock detection and recovery using resource allocation information.
7. Understanding how page replacement algorithms manage limited memory.
8. Improving C programming, debugging, testing, and logical problem-solving skills.
9. Gaining experience with Git and GitHub for version control.
10. Developing the ability to translate theoretical Operating System concepts into practical C programs.

7. CONCLUSION

The five-week Operating Systems Project-Based Learning experience helped me understand how important Operating System concepts work in practical environments.

Through my individual contributions, I gained hands-
