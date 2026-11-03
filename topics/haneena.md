# Individual PBL Contributions – Haneena Zohara

**Student:** Haneena Zohara  
**Course:** B.Tech Artificial Intelligence and Machine Learning (AIML)  
**Project:** Operating Systems – Project-Based Learning (PBL)

---

## Week 1 – Interprocess Communication (IPC): Basics, Signals and Sockets

### Contribution
Prepared theoretical documentation on Interprocess Communication (IPC), focusing on IPC basics, signals and sockets.

### Topics Covered
- Definition and importance of Interprocess Communication.
- Different IPC techniques, including pipes, shared memory, message passing, message queues, sockets and signals.
- Why processes need to communicate.
- Basic working of IPC between two processes.
- Introduction to signals and their purpose.
- Common signals: SIGINT, SIGTERM, SIGKILL, SIGSTOP and SIGCONT.
- Python example of signal handling.
- Introduction to sockets and client-server communication.
- Difference between TCP stream sockets and UDP datagram sockets.
- Advantages, disadvantages and real-world applications of sockets.

### Outcome
Gained an understanding of how processes communicate and exchange information in an operating system.

---

## Week 2 – IPC Implementation: Message Queues and UI Process

### Contribution 1: Message Queue Implementation in C

Implemented Interprocess Communication using System V Message Queues in C.

**Files:** `sender.c`, `receiver.c`

### Functions Used

| Function | Purpose |
|---|---|
| `ftok()` | Generates an IPC key. |
| `msgget()` | Creates or accesses a message queue. |
| `msgsnd()` | Sends messages into the queue. |
| `msgrcv()` | Receives messages from the queue. |
| `msgctl()` | Controls or deletes the message queue. |

### Work Involved
- Developed sender and receiver programs.
- Implemented message sending and receiving between independent processes.
- Compiled programs using GCC in Ubuntu/Linux.
- Executed sender and receiver in separate terminals.
- Tested message communication and queue deletion.

### Contribution 2: UI Process

Developed a separate C-based UI program for the OS simulator.

### Work Involved
- Accepted commands and input from the user.
- Sent commands to the Core Process through IPC.
- Received responses from the Core Process.
- Displayed the received responses to the user.
- Used POSIX Named Pipes (FIFO) for communication between the UI and Core Process.

### Outcome
Understood and implemented interprocess communication using System V Message Queues and POSIX Named Pipes.

---

## Week 3 – Process Scheduling Simulator

### Contribution
Worked on implementing CPU scheduling algorithms using C.

**Files:** `src/haneena.c`, `tests/test_haneena.c`

### Algorithms Assigned

**1. FCFS – First Come First Served**
- Executes processes according to their arrival time.
- The process that arrives first gets the CPU first.
- Each process executes until completion.

**2. Non-Preemptive SJF – Shortest Job First**
- Selects the available process with the shortest burst time.
- Executes the selected process completely without interruption.
- Repeats until all processes are completed.

**3. Non-Preemptive Priority Scheduling**
- Selects processes according to their priority.
- A smaller priority number represents a higher priority.
- Executes the selected process until completion.

### Implementation Details
- Initialized process information and scheduling metrics.
- Created helper functions for adding entries to the Gantt chart.
- Implemented FCFS and Non-Preemptive SJF scheduling.
- Calculated Completion Time (CT), Turnaround Time (TAT), Waiting Time (WT) and Response Time (RT).
- Created a test program using three sample processes.
- Compiled and tested the scheduling code using GCC.

### Testing Results

| Algorithm | Average Waiting Time | Average Turnaround Time |
|---|---:|---:|
| FCFS | 3.33 | 6.33 |
| Non-Preemptive SJF | 2.67 | 5.67 |

### Outcome
Learned how CPU scheduling algorithms work and how their performance can be evaluated using scheduling metrics and Gantt charts.

---

## Week 4 – Interactive Deadlock Simulation System

### Contribution: Banker's Algorithm

**File:** `src/banker.c`

Implemented Banker's Algorithm in C to check whether a system is in a safe or unsafe state.

### Functions Implemented

**1. `calculateNeed()`**
- Calculates the Need matrix.
- Uses the formula:

  `Need = Maximum - Allocation`

**2. `checkSafety()`**
- Checks whether the system is in a safe state.
- Determines whether available resources can satisfy process requirements.
- Generates a safe sequence.
- Identifies unsafe states.

**3. `requestResources()`**
- Accepts resource requests from processes.
- Checks whether the requested resources are valid and available.
- Temporarily allocates resources.
- Checks whether the allocation keeps the system safe.
- Rolls back the allocation if the resulting state is unsafe.

### Outcome
Understood deadlock avoidance, safe states, resource allocation and safe sequence generation using Banker's Algorithm.

---

## Week 5 – Page Replacement Algorithms

### Contribution: FIFO Page Replacement

Worked on implementing the FIFO (First In First Out) page replacement algorithm in C.

### Work Involved
- Implemented the FIFO page replacement approach.
- Managed page references and available memory frames.
- Checked whether a requested page was already present in memory.
- Identified page hits and page faults.
- Replaced the oldest loaded page when a page fault occurred and all frames were occupied.

### Outcome
Understood how operating systems manage memory frames and replace pages when memory is full.

---

## Git Commit Convention

Used descriptive Git commit messages ending with `-haneena` to identify individual contributions.

Examples:

```bash
git commit -m "Add IPC documentation -haneena"

git commit -m "Implement UI process and FIFO communication -haneena"

git commit -m "Implement System V message queues -haneena"

git commit -m "Implement FCFS and non-preemptive SJF -haneena"

git commit -m "Implement Banker's algorithm -haneena"

git commit -m "Implement FIFO page replacement -haneena"
```

---

## Overall Learning Outcomes

Through these five weeks of PBL activities, I gained practical knowledge of:

- Interprocess Communication techniques.
- Signals, sockets, message queues and named pipes.
- CPU process scheduling algorithms.
- Gantt chart representation and scheduling metrics.
- Deadlock avoidance using Banker's Algorithm.
- Memory management and FIFO page replacement.
- C programming, GCC compilation and testing.
- Git and GitHub for version control and collaboration.

## Conclusion

I contributed to the development of the Operating Systems PBL projects across five weeks. My individual work covered IPC concepts and implementation, UI process development, CPU scheduling algorithms, Banker's Algorithm and FIFO page replacement.

These activities helped me understand important operating system concepts through theoretical study, C programming, testing and team collaboration.
