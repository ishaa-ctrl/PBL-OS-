# OPERATING SYSTEMS
# FIVE-WEEK PROJECT-BASED LEARNING (PBL) – OVERALL PROJECT README

**Project Title:** Implementation and Simulation of Operating System Concepts Using C  
**Subject:** Operating Systems (OSCO)  
**Project Duration:** 5 Weeks  
**Primary Programming Language:** C  
**Additional Language:** Python  
**Development Environments:** Linux / Ubuntu, Windows, MSYS2 UCRT64  
**Tools:** GCC, GNU Make, Visual Studio Code, Git and GitHub

## Team Members

| Member | Role |
|---|---|
| Safiyath Isha | Team Leader and Integration |
| Haneena | Team Member |
| Ayman Khan | Team Member |
| E Vishnu Vijayan | Team Member |

---

# 1. PROJECT INTRODUCTION

An Operating System is system software that manages computer hardware and software resources. It handles process management, memory management, CPU scheduling, inter-process communication, and resource allocation.

The objective of this five-week Project-Based Learning activity was to understand important Operating System concepts through theoretical study, C programming, practical implementation, simulation, and testing.

The project was divided into five major phases:

1. Inter-Process Communication (IPC).
2. Multi-Process OS Simulator and IPC Implementations.
3. CPU Process Scheduling Simulator.
4. Interactive Deadlock Simulation System.
5. Page Replacement Algorithm Simulator.

Each phase focused on a different Operating System concept and contributed to the development of practical programming and problem-solving skills.

# 2. PROJECT OBJECTIVES

- Understand fundamental Operating System concepts.
- Study and implement different IPC mechanisms.
- Develop a multi-process application using POSIX Named Pipes.
- Understand process creation and communication.
- Implement different CPU scheduling algorithms.
- Generate Gantt charts and calculate scheduling metrics.
- Understand deadlock avoidance, detection, and recovery.
- Visualize resource allocation using a Resource Allocation Graph.
- Implement and compare page replacement algorithms.
- Develop graphical interfaces for OS simulations.
- Perform testing, debugging, integration, and benchmarking.
- Use Git and GitHub for collaborative development and version control.

# 3. TECHNOLOGIES AND TOOLS

| Technology / Tool | Purpose |
|---|---|
| C Programming | Operating System simulations and implementations |
| Python | IPC pipe communication example |
| GCC | Compiling C programs |
| GNU Make | Build automation |
| POSIX Named Pipes (FIFO) | Communication between independent processes |
| Shared Memory | Sharing data between processes |
| Semaphores | Process synchronization |
| TCP Sockets | Client-server communication |
| Windows API | GUI development |
| Linux / Ubuntu | IPC implementation and testing |
| MSYS2 UCRT64 | Windows development environment |
| Visual Studio Code | Code development and debugging |
| Git | Version control |
| GitHub | Repository management and collaboration |

---

# 4. WEEK-WISE PROJECT IMPLEMENTATION

# WEEK 1 – INTER-PROCESS COMMUNICATION (IPC)

## 4.1 Introduction

Inter-Process Communication (IPC) is a mechanism that allows two or more independent processes to exchange information and coordinate their activities.

Each process normally has its own memory space. IPC mechanisms allow processes to communicate without directly accessing one another's private memory.

During Week 1, the team studied IPC fundamentals and different communication techniques.

## 4.2 Topics Covered

### 1. Pipes

A pipe is an IPC mechanism used to transfer data between processes.

It has two ends:

- **Read end:** Receives data.
- **Write end:** Sends data.

Types of pipes:

- **Anonymous Pipe:** Commonly used for communication between related processes, such as parent and child.
- **Named Pipe (FIFO):** Has a name in the file system and can allow communication between unrelated processes.

Example using a Linux command pipeline:

```bash
ls | grep ".txt"
```

### 2. Shared Memory

Shared Memory allows multiple processes to access a common memory region.

- One process can write data.
- Another process can read the same data.
- It reduces repeated data copying.
- Synchronization is required to prevent race conditions.

### 3. Message Passing

Message Passing allows processes to communicate by sending and receiving messages.

Main operations:

- Send
- Receive

Types:

- Direct communication.
- Indirect communication.
- Synchronous communication.
- Asynchronous communication.

### 4. FIFO Principle

FIFO stands for First In, First Out.

The first item inserted into a queue is the first item removed.

### 5. Producer-Consumer Communication

The Producer creates data and places it in a shared communication area. The Consumer receives and processes that data.

## 4.3 Python Pipe Example

The following example demonstrates communication between two processes using Python's multiprocessing module.

```python
from multiprocessing import Pipe

conn1, conn2 = Pipe()

conn1.send("Hello from Process 1")
print(conn2.recv())
```

**Expected output:**

```text
Hello from Process 1
```

## 4.4 Learning Outcomes

- Understood the importance of IPC.
- Learned how pipes transfer data.
- Understood the difference between anonymous and named pipes.
- Studied shared memory and synchronization.
- Learned message passing and producer-consumer communication.

---

# WEEK 2 – THREE-PROCESS OS SIMULATOR AND ADDITIONAL IPC IMPLEMENTATIONS

## 5.1 Project Overview

The Three-Process OS Simulator demonstrates communication between three independent processes:

1. UI Process
2. Core Process
3. Logger Process

The processes communicate using POSIX Named Pipes (FIFO).

Each process performs a separate responsibility, demonstrating how multiple processes coordinate to perform operations.

## 5.2 System Architecture

```text
                     USER
                       |
                       v
                 +-----------+
                 | UI Process|
                 +-----------+
                       |
                       | ui_to_core
                       v
                 +-------------+
                 | Core Process|
                 +-------------+
                    |       |
                    |       |
           core_to_ui       core_to_logger
                    |       |
                    v       v
               UI Process  Logger Process
                                |
                                v
                          execution.log
```

## 5.3 Process Responsibilities

| Process | Responsibility | Team Member |
|---|---|---|
| UI Process | Accepts commands and displays responses | Haneena |
| Core Process | Processes commands and coordinates operations | Ayman Khan |
| Logger Process | Receives log messages and records execution details | E Vishnu Vijayan |
| Integration | Connects processes, verifies communication, tests the system | Safiyath Isha |

## 5.4 FIFO Communication Channels

The simulator uses three named pipes:

| FIFO Name | Communication |
|---|---|
| `ui_to_core` | UI → Core |
| `core_to_ui` | Core → UI |
| `core_to_logger` | Core → Logger |

### Communication Flow

1. The user enters a command through the UI Process.
2. The UI sends the command through `ui_to_core`.
3. The Core Process reads and processes the command.
4. The Core sends the response through `core_to_ui`.
5. The UI receives and displays the response.
6. The Core sends execution information through `core_to_logger`.
7. The Logger receives the message and records it in `execution.log`.

## 5.5 Commands Implemented

| Command | Function |
|---|---|
| `start` | Starts simulated CPU execution |
| `status` | Displays CPU, memory, stack, and queue status |
| `stop` | Stops simulated CPU execution |
| `exit` | Terminates the simulator processes |

## 5.6 Important System Calls and Functions

| Function | Purpose |
|---|---|
| `mkfifo()` | Creates a named pipe |
| `open()` | Opens a FIFO |
| `read()` | Receives data |
| `write()` | Sends data |
| `close()` | Closes a file descriptor |
| `fork()` | Creates a child process |
| `wait()` | Waits for a child process |
| `strcmp()` | Compares strings |
| `snprintf()` | Formats messages |

## 5.7 Additional IPC Implementations

Apart from the three-process simulator, the team independently implemented additional IPC mechanisms.

### A. Ordinary Pipes

**Assigned Member:** Ayman Khan

Files:

- `ipc_implementations/ordinary_pipes/pipe.c`

Concepts and functions:

- `pipe()`
- `fork()`
- `read()`
- `write()`
- `wait()`

Demonstrates parent-child communication through an unnamed pipe.

### B. Message Queues

**Assigned Member:** Haneena

Files:

- `ipc_implementations/message_queues/sender.c`
- `ipc_implementations/message_queues/reciever.c`

Concepts and functions:

- `msgget()`
- `msgsnd()`
- `msgrcv()`
- `msgctl()`

Demonstrates sending and receiving messages through a System V message queue.

### C. Shared Memory

**Assigned Member:** Safiyath Isha

Files:

- `ipc_implementations/shared_memory/writer.c`
- `ipc_implementations/shared_memory/reader.c`

Concepts and functions:

- `shm_open()`
- `ftruncate()`
- `mmap()`
- `munmap()`
- `shm_unlink()`

Demonstrates sharing data through a common memory region.

### D. Semaphores

**Assigned Member:** Safiyath Isha

File:

- `ipc_implementations/semaphores/semaphore.c`

Concepts and functions:

- `sem_init()`
- `sem_wait()`
- `sem_post()`
- `sem_destroy()`

Demonstrates process synchronization and controlled access to a critical section.

### E. Signals

**Assigned Member:** Ayman Khan

Files:

- `ipc_implementations/signals/signal_sender.c`
- `ipc_implementations/signals/signal_reciever.c`

Concepts and functions:

- `signal()`
- `kill()`
- `getpid()`
- `pause()`
- `SIGUSR1`

Demonstrates how one process can notify another process using signals.

### F. TCP Sockets

**Assigned Member:** E Vishnu Vijayan

Files:

- `ipc_implementations/sockets/server.c`
- `ipc_implementations/sockets/client.c`

Concepts and functions:

- `socket()`
- `bind()`
- `listen()`
- `accept()`
- `connect()`
- `send()`
- `read()`
- `close()`

The implementation uses TCP with `SOCK_STREAM`, localhost address `127.0.0.1`, and port `8080`.

It demonstrates client-server communication.

## 5.8 Individual Responsibilities

| Member | Week 2 Contribution |
|---|---|
| Haneena | UI Process and Message Queue implementation |
| Ayman Khan | Core Process, Ordinary Pipes and Signals |
| E Vishnu Vijayan | Logger Process and TCP Sockets |
| Safiyath Isha | Team leadership, integration, FIFO verification, testing, benchmarking, Shared Memory and Semaphores |

## 5.9 Testing

The team tested:

- UI-to-Core communication.
- Core-to-UI response communication.
- Core-to-Logger communication.
- FIFO creation and operation.
- Process startup and termination.
- Command execution.
- Message Queue communication.
- Shared Memory data transfer.
- Semaphore synchronization.
- Signal-based communication.
- TCP Socket client-server communication.

The additional IPC implementations were compiled and tested independently.

## 5.10 Build and Execution

From the simulator project directory:

```bash
make
```

Create the required FIFO channels if they are not created automatically:

```bash
mkdir -p fifos

mkfifo fifos/ui_to_core
mkfifo fifos/core_to_ui
mkfifo fifos/core_to_logger
```

Run the simulator:

```bash
./launcher
```

Clean generated files:

```bash
make clean
```

**Note:** The exact FIFO paths depend on the project's implementation and Makefile.

## 5.11 Learning Outcomes

- Understood multi-process architecture.
- Learned POSIX Named Pipe communication.
- Implemented different IPC techniques.
- Understood process synchronization.
- Learned client-server communication.
- Gained experience in project integration and testing.

---

# WEEK 3 – CPU PROCESS SCHEDULING SIMULATOR

## 6.1 Project Overview

CPU Scheduling is an important function of an Operating System. It determines which process gets access to the CPU and for how long.

During Week 3, the team developed a C-based CPU Scheduling Simulator that implements six scheduling algorithms.

The simulator accepts process details, executes the selected algorithm, generates a Gantt chart, and calculates scheduling performance metrics.

## 6.2 Scheduling Algorithms

### 1. First Come First Serve (FCFS)

- Non-preemptive scheduling algorithm.
- Processes execute in order of arrival.
- The process that arrives first gets the CPU first.

### 2. Shortest Job First (SJF) – Non-preemptive

- Selects the available process with the shortest burst time.
- Once execution begins, the process continues until completion.

### 3. Shortest Remaining Time First (SRTF)

- Preemptive version of SJF.
- Selects the process with the shortest remaining execution time.
- A running process can be interrupted if a process with a shorter remaining time arrives.

### 4. Priority Scheduling – Non-preemptive

- Selects the available process with the highest priority.
- The selected process runs until completion.
- In this implementation, a lower numerical value represents a higher priority.

### 5. Priority Scheduling – Preemptive

- Executes the highest-priority available process.
- A running process can be interrupted when a higher-priority process arrives.

### 6. Round Robin (RR)

- Preemptive scheduling algorithm.
- Each process receives a fixed time quantum.
- Unfinished processes return to the ready queue.

## 6.3 Team Responsibilities

| Member | Individual Contribution |
|---|---|
| Haneena | FCFS and Non-preemptive SJF |
| Ayman Khan | Preemptive SJF (SRTF) and Preemptive Priority Scheduling |
| E Vishnu Vijayan | Round Robin and Gantt Chart generation |
| Safiyath Isha | Main program, menu design, integration, overall testing and documentation |

## 6.4 Input Requirements

The simulator accepts:

- Number of processes.
- Process ID (PID).
- Arrival Time (AT).
- Burst Time (BT).
- Priority.
- Time Quantum for Round Robin.

## 6.5 Output Requirements

The simulator displays:

- Gantt Chart.
- Completion Time (CT).
- Turnaround Time (TAT).
- Waiting Time (WT).
- Response Time (RT).
- Average Waiting Time.
- Average Turnaround Time.
- CPU Utilization.

## 6.6 Scheduling Formulas

| Metric | Formula |
|---|---|
| Completion Time | Time at which a process finishes |
| Turnaround Time | `TAT = CT − AT` |
| Waiting Time | `WT = TAT − BT` |
| Response Time | `RT = First Start Time − AT` |
| Average Waiting Time | `Total WT / Number of Processes` |
| Average Turnaround Time | `Total TAT / Number of Processes` |
| CPU Utilization | `(Total CPU Busy Time / Total Elapsed Schedule Time) × 100` |

## 6.7 Gantt Chart

A Gantt Chart is a visual representation of the order in which processes execute on the CPU.

Example:

```text
|  P1  |  P2  |  P3  |
0      3      6      9
```

It helps identify process execution order and CPU time allocation.

## 6.8 Testing

- Tested all six scheduling algorithms.
- Verified process selection and execution order.
- Checked preemption where applicable.
- Verified Gantt chart generation.
- Checked completion time, turnaround time, and waiting time.
- Verified average scheduling metrics.
- Tested CPU idle periods.

## 6.9 Compilation

Example integrated compilation command:

```bash
gcc -Wall -Wextra -std=c11 -Iinclude \
src/main.c src/haneena.c src/ayman.c src/vishnu.c \
-o scheduler.exe
```

Run:

```bash
./scheduler.exe
```

The exact build command may vary depending on the Makefile and operating system.

## 6.10 Learning Outcomes

- Understood preemptive and non-preemptive scheduling.
- Learned how the CPU selects processes.
- Implemented scheduling algorithms.
- Generated Gantt charts.
- Calculated scheduling metrics.
- Practised modular programming and integration.

---

# WEEK 4 – INTERACTIVE DEADLOCK SIMULATION SYSTEM

## 7.1 Project Overview

Deadlock is a condition in which two or more processes become blocked because each process is waiting for resources held by another process.

During Week 4, the team developed an interactive Deadlock Simulation System using C.

The system demonstrates resource allocation, deadlock avoidance, detection, recovery, and graphical visualization.

## 7.2 Main Concepts

### 1. Banker’s Algorithm

Banker's Algorithm is a deadlock avoidance algorithm.

It checks whether granting a resource request will keep the system in a safe state.

Important data structures:

- Available.
- Allocation.
- Maximum.
- Need.

**Need Matrix Formula:**

```text
Need = Maximum − Allocation
```

Main operations:

- Calculate Need.
- Check system safety.
- Find a safe sequence.
- Process resource requests.

### 2. Deadlock Detection

Deadlock Detection identifies processes that cannot proceed because their resource requests cannot be satisfied.

Important data structures:

- Available.
- Allocation.
- Request.
- Work.
- Finish.

Basic working:

1. Initialize Work using Available.
2. Initialize Finish.
3. Find an unfinished process whose request can be satisfied.
4. Simulate its completion.
5. Release its allocated resources into Work.
6. Repeat until no more processes can finish.
7. Identify unfinished processes as potentially deadlocked.

### 3. Deadlock Recovery

Deadlock Recovery attempts to restore the system to a workable state.

The implemented recovery approach includes terminating a selected process and releasing its allocated resources.

### 4. Resource Allocation Graph (RAG)

A Resource Allocation Graph represents the relationship between processes and resources.

It contains:

- Process nodes.
- Resource nodes.
- Allocation edges.
- Request edges.

It helps visualize resource allocation and requests.

## 7.3 Team Responsibilities

| Member | Individual Contribution |
|---|---|
| Haneena | Banker’s Algorithm |
| Ayman Khan | Deadlock Detection and Recovery |
| E Vishnu Vijayan | GUI development using C and Windows API |
| Safiyath Isha | Resource Allocation Graph, resource utilization, integration, testing and documentation |

## 7.4 Main System Features

- Display Allocation Matrix.
- Display Maximum Matrix.
- Display Need Matrix.
- Display Available Resources.
- Safety Check.
- Deadlock Detection.
- Resource Request.
- Deadlock Recovery.
- Safe Sequence display.
- Resource Allocation Graph visualization.
- Resource Utilization display.
- System Status.
- Operation logs.

## 7.5 GUI Development

The graphical interface allows users to interact with the deadlock simulation system.

The GUI provides options to:

- View resource information.
- Perform safety checks.
- Detect deadlocks.
- Request resources.
- Perform recovery operations.
- View system status and safe sequence.
- View the Resource Allocation Graph.

The interface displays the appropriate system status based on the results returned by the project modules.

## 7.6 Important Formulas

**Need Matrix:**

```text
Need = Maximum − Allocation
```

**Available Resources:**

Available resources represent the number of resource instances that are currently free for allocation.

## 7.7 Testing

- Tested safe and unsafe system states.
- Verified Banker’s Algorithm safety checks.
- Tested resource requests.
- Checked granted and denied resource requests.
- Tested deadlock detection.
- Tested deadlock recovery.
- Checked resource availability after recovery.
- Verified Resource Allocation Graph display.
- Tested resource utilization.
- Checked GUI and module integration.

## 7.8 Learning Outcomes

- Understood deadlock conditions.
- Learned deadlock avoidance using Banker’s Algorithm.
- Implemented deadlock detection and recovery.
- Understood resource allocation matrices.
- Learned Resource Allocation Graph visualization.
- Gained experience integrating GUI and backend modules.

---

# WEEK 5 – PAGE REPLACEMENT ALGORITHMS

## 8.1 Project Overview

Page Replacement is an important memory management technique used by an Operating System.

When a process requests a page that is not currently available in physical memory and all memory frames are occupied, the operating system must select an existing page to replace.

During Week 5, the team developed a C-based Page Replacement Simulator that implements and compares three algorithms.

## 8.2 Algorithms Implemented

### 1. FIFO – First In, First Out

FIFO replaces the page that entered memory first.

- Pages are maintained in arrival order.
- The oldest page is replaced first.

### 2. LRU – Least Recently Used

LRU replaces the page that has not been accessed for the longest period of time.

- Tracks the last-used position of each page.
- Replaces the least recently used page.

### 3. Optimal Page Replacement

Optimal Page Replacement replaces the page whose next use is farthest in the future.

- Checks future page references.
- Replaces the page that will be needed latest.
- Produces the minimum possible page faults for a given reference string and frame count, assuming future references are known.

## 8.3 Team Responsibilities

| Member | Individual Contribution |
|---|---|
| Haneena | FIFO algorithm |
| Ayman Khan | LRU algorithm |
| E Vishnu Vijayan | Optimal Page Replacement |
| Safiyath Isha | Integration of all algorithms, statistics, comparative analysis, GUI development and testing |

## 8.4 Input Requirements

- Page Reference String.
- Number of Memory Frames.

## 8.5 Simulator Features

- Page-reference string input.
- Frame count input.
- Individual algorithm selection.
- Compare All option.
- Step-by-step frame contents.
- Page hit and page fault identification.
- Total page hits.
- Total page faults.
- Hit ratio and fault ratio.
- Page-fault comparison chart.
- Quick statistics.
- Reset option.

## 8.6 Page Hit and Page Fault

**Page Hit:** Occurs when the requested page is already present in memory.

**Page Fault:** Occurs when the requested page is not available in memory and must be loaded.

## 8.7 Performance Formulas

**Total Page Requests:**

```text
Total Requests = Page Hits + Page Faults
```

**Hit Ratio:**

```text
Hit Ratio = (Page Hits / Total Page Requests) × 100
```

**Fault Ratio:**

```text
Fault Ratio = (Page Faults / Total Page Requests) × 100
```

## 8.8 Sample Comparison

**Input:**

```text
Number of pages: 13
Page reference string: 7 0 1 2 0 3 0 4 2 3 0 3 2
Number of frames: 3
```

**Expected Results:**

| Algorithm | Hits | Faults | Hit Ratio | Fault Ratio |
|---|---:|---:|---:|---:|
| FIFO | 3 | 10 | 23.08% | 76.92% |
| LRU | 4 | 9 | 30.77% | 69.23% |
| Optimal | 6 | 7 | 46.15% | 53.85% |

These results provide a comparison of the three algorithms using the same input.

## 8.9 GUI Features

The GUI provides:

- Page reference input.
- Frame count selection.
- Individual algorithm selection.
- Compare All option.
- Step-by-step simulation.
- Page-fault chart.
- Quick statistics.
- Reset option.

## 8.10 Build and Execution

The following commands are defined in the project report and should be used when the corresponding Makefile targets are available.

```bash
# Build console simulator
make

# Run console simulator
./simulator.exe

# Build GUI
make gui

# Run GUI
./simulator_gui.exe

# Run tests
make test
```

**Validation note:** The GUI must be built and executed in the target Windows environment before claiming successful GUI verification. Actual execution screenshots should be stored in `docs/screenshots/`.

## 8.11 Learning Outcomes

- Understood virtual memory and page replacement.
- Implemented FIFO, LRU, and Optimal algorithms.
- Learned how page hits and page faults occur.
- Calculated hit and fault ratios.
- Compared page replacement performance.
- Integrated algorithms with a graphical interface.

---

# 9. OVERALL TEAM CONTRIBUTION SUMMARY

| Week | Project | Haneena | Ayman Khan | E Vishnu Vijayan | Safiyath Isha |
|---|---|---|---|---|---|
| 1 | IPC | IPC topic study | Message Passing study | Shared Memory study | Pipes study |
| 2 | Three-Process Simulator | UI Process | Core Process | Logger Process | Team Leader and Integration |
| 2 | Additional IPC | Message Queues | Ordinary Pipes and Signals | TCP Sockets | Shared Memory and Semaphores |
| 3 | CPU Scheduling | FCFS and Non-preemptive SJF | SRTF and Preemptive Priority | Round Robin | Main Program and Integration |
| 4 | Deadlock Simulation | Banker’s Algorithm | Detection and Recovery | GUI Development | RAG and Resource Utilization |
| 5 | Page Replacement | FIFO | LRU | Optimal | Integration, Statistics and GUI |

---

# 10. OVERALL PROJECT STRUCTURE

The following is a logical overview of the project's modules. Individual filenames and folder locations should match the actual GitHub repository.

```text
PBL-OS/
│
├── Week1/
│   └── IPC/
│       ├── Pipes/
│       ├── Shared_Memory/
│       └── Message_Passing/
│
├── Week2/
│   └── 3-process-os-simulator/
│       │
│       ├── ui/
│       │   └── ui.c
│       │
│       ├── core/
│       │   └── core.c
│       │
│       ├── logger/
│       │   └── logger.c
│       │
│       ├── fifos/
│       │   ├── ui_to_core
│       │   ├── core_to_ui
│       │   └── core_to_logger
│       │
│       ├── ipc_implementations/
│       │   ├── ordinary_pipes/
│       │   ├── message_queues/
│       │   ├── shared_memory/
│       │   ├── semaphores/
│       │   ├── signals/
│       │   └── sockets/
│       │
│       ├── benchmark/
│       ├── docs/
│       ├── launcher.c
│       ├── Makefile
│       └── README.md
│
├── Week3_Process_Scheduling/
│   ├── include/
│   │   └── scheduler.h
│   ├── src/
│   │   ├── main.c
│   │   ├── haneena.c
│   │   ├── ayman.c
│   │   └── vishnu.c
│   ├── tests/
│   └── Makefile
│
├── Week4_Deadlock_Simulation/
│   ├── src/
│   │   ├── main.c
│   │   ├── banker.c
│   │   ├── detection.c
│   │   ├── rag.c
│   │   └── gui.c
│   ├── include/
│   ├── tests/
│   └── Makefile
│
└── Week5_Page_Replacement/
    ├── fifo.c
    ├── lru.c
    ├── optimal.c
    ├── main.c
    ├── common.h
    ├── tests/
    ├── Makefile
    └── docs/
        └── screenshots/
```

**Note:** This is a documentation-level structure, not a claim that every listed directory and filename already exists in the repository. Update it to match the actual project before publishing.

---

# 11. TESTING AND VERIFICATION

Testing was performed throughout the five-week project to verify individual modules and integrated systems.

## Week 1 – IPC

- Studied IPC concepts.
- Tested the Python Pipe communication example.
- Verified message transfer between the two connections.

## Week 2 – Three-Process Simulator and IPC

- Verified UI-to-Core communication.
- Verified Core-to-UI responses.
- Verified Core-to-Logger communication.
- Tested FIFO creation.
- Tested commands such as `start`, `status`, `stop`, and `exit`.
- Tested Ordinary Pipes.
- Tested Message Queues.
- Tested Shared Memory.
- Tested Semaphores.
- Tested Signals.
- Tested TCP Sockets.

## Week 3 – CPU Scheduling

- Tested all six scheduling algorithms.
- Verified process execution order.
- Checked Gantt charts.
- Verified scheduling calculations.
- Tested preemption and CPU idle periods.

## Week 4 – Deadlock Simulation

- Tested safe and unsafe states.
- Verified resource requests.
- Tested deadlock detection.
- Tested recovery operations.
- Checked resource availability after recovery.
- Verified GUI and module integration.

## Week 5 – Page Replacement

- Tested FIFO, LRU, and Optimal algorithms.
- Verified frame contents.
- Checked page hits and page faults.
- Compared results using identical input.
- Tested statistics and GUI features.

---

# 12. PROJECT LEARNING OUTCOMES

Through this five-week project, the team gained practical experience in:

1. Understanding Inter-Process Communication.
2. Implementing pipes, FIFOs, shared memory, and message queues.
3. Using semaphores for process synchronization.
4. Implementing signal-based communication.
5. Understanding TCP socket client-server communication.
6. Developing a multi-process application.
7. Implementing CPU scheduling algorithms.
8. Generating Gantt charts and calculating scheduling metrics.
9. Understanding deadlock avoidance, detection, and recovery.
10. Visualizing resource allocation through RAG.
11. Implementing page replacement algorithms.
12. Comparing memory management performance.
13. Developing graphical interfaces.
14. Integrating independent modules.
15. Testing, debugging, and documenting C programs.
16. Using Git and GitHub for collaborative development.

---

# 13. CONCLUSION

The five-week Operating Systems Project-Based Learning activity provided practical experience with important concepts used in modern operating systems.

The project progressed from IPC fundamentals to multi-process communication, CPU scheduling, deadlock simulation, and memory management.

Through individual module development and team integration, the members gained experience in C programming, process communication, synchronization, scheduling algorithms, resource allocation, memory management, GUI development, and software testing.

The project also strengthened teamwork, debugging, documentation, and collaborative development skills.

Overall, this PBL activity helped translate theoretical Operating System concepts into practical simulations and working software modules.

---

# 14. TEAM MEMBERS AND RESPONSIBILITIES

| Member | Main Responsibilities |
|---|---|
| Haneena | UI Process, Message Queues, FCFS, Non-preemptive SJF, Banker’s Algorithm, FIFO Page Replacement |
| Ayman Khan | Core Process, Ordinary Pipes, Signals, SRTF, Preemptive Priority, Deadlock Detection and Recovery, LRU |
| E Vishnu Vijayan | Logger Process, TCP Sockets, Round Robin, GUI Development, Optimal Page Replacement |
| Safiyath Isha | Team Leadership, Integration, Shared Memory, Semaphores, Main Program Development, RAG, Resource Utilization, Testing, Benchmarking and Documentation |

---
