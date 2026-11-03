OPERATING SYSTEMS

PROJECT-BASED LEARNING – INDIVIDUAL CONTRIBUTION REPORT

Name: E Vishnu Vijayan
Subject: Operating Systems
Project Duration: 5 Weeks
Programming Language: C

---

WEEK 1 – INTER-PROCESS COMMUNICATION (IPC): SHARED MEMORY

1. Overview

Inter-Process Communication (IPC) allows two or more processes to communicate and exchange data. Shared Memory is an IPC method in which multiple processes access a common memory area to exchange information.

2. Individual Role

My contribution was studying and documenting the concept of Shared Memory in IPC, including its working, advantages, disadvantages, and synchronization requirements.

3. Working Principle

- The operating system creates a shared memory region.
- Multiple processes are given permission to access that memory.
- One process can write data into the shared memory.
- Another process can read the same data.
- Synchronization mechanisms such as mutexes, locks, and semaphores help prevent conflicts when multiple processes access the memory.

4. Advantages

- Faster communication between processes.
- Reduces data copying.
- Supports the exchange of large amounts of data.
- Improves communication efficiency.

5. Disadvantages

- Requires proper synchronization.
- May cause race conditions.
- Can lead to data inconsistency.
- Requires careful memory access management.

6. Result

Studied and documented the working of Shared Memory, its advantages, disadvantages, and the importance of synchronization in inter-process communication.

---

WEEK 2 – THREE-PROCESS OS SIMULATOR: TCP SOCKETS AND LOGGER

1. Overview

The Three-Process OS Simulator demonstrates communication between different processes. The project uses separate components such as UI, Core, and Logger to perform operations and record their execution.

2. Individual Role

My assigned contribution was working on TCP Socket Client-Server communication and the Logger process using Named Pipes (FIFO).

3. TCP Socket Communication

TCP sockets were used to establish communication between a client and a server.

Server-side operations:

- "socket()" – Creates a socket.
- "bind()" – Assigns an address and port.
- "listen()" – Waits for client connections.
- "accept()" – Accepts a client connection.
- "read()" – Receives data.
- "send()" – Sends a response.
- "close()" – Closes the connection.

Client-side operations:

- Creates a socket.
- Connects to the server using the localhost address "127.0.0.1".
- Sends a message to the server.
- Receives the server response.

The communication used TCP with "SOCK_STREAM" and port "8080".

4. Logger Process Using FIFO

The Logger process receives messages from the Core process through a Named Pipe (FIFO).

The main operations include:

- Creating a FIFO using "mkfifo()".
- Opening the FIFO for reading.
- Receiving messages using "read()".
- Recording messages with timestamps in "execution.log".
- Stopping the logger when it receives the exit message.

5. Input

Client message:

Hello from client!

Server response:

Hello from server!

The Logger receives messages from the Core process through the FIFO.

6. Testing

- Compiled and executed the TCP server and client.
- Ran the server and client in separate terminals.
- Checked whether messages were successfully sent and received.
- Tested the Logger process to verify message reception and logging.

7. Result

Worked on TCP socket communication between client and server and developed the Logger process using FIFO to receive messages and store execution records.

---

WEEK 3 – PROCESS SCHEDULING SIMULATOR: ROUND ROBIN AND GANTT CHART

1. Overview

Process Scheduling is an important function of an operating system. It decides the order in which processes are executed by the CPU.

The project includes different scheduling algorithms such as FCFS, SJF, Priority Scheduling, and Round Robin.

2. Individual Role

My assigned contribution was implementing the Round Robin Scheduling algorithm and generating the Gantt Chart to represent process execution.

3. Round Robin Algorithm

Round Robin is a preemptive CPU scheduling algorithm in which each process gets a fixed amount of CPU time called the Time Quantum.

Working steps:

1. Enter the process details.
2. Add the processes to the ready queue.
3. Select the first process from the queue.
4. Execute it for the given time quantum or until completion.
5. If the process is not completed, place it back into the ready queue.
6. Repeat until all processes are completed.
7. Generate the Gantt Chart based on the execution order.

4. Input

The algorithm uses the following inputs:

- Process ID (PID)
- Arrival Time (AT)
- Burst Time (BT)
- Time Quantum

5. Formulas Used

Turnaround Time (TAT):

[
TAT = Completion\ Time - Arrival\ Time
]

Waiting Time (WT):

[
WT = Turnaround\ Time - Burst\ Time
]

Response Time (RT):

[
RT = First\ Execution\ Time - Arrival\ Time
]

Average Waiting Time:

[
Average\ WT = \frac{Total\ Waiting\ Time}{Number\ of\ Processes}
]

Average Turnaround Time:

[
Average\ TAT = \frac{Total\ Turnaround\ Time}{Number\ of\ Processes}
]

6. Testing

- Tested Round Robin using sample process inputs.
- Verified process execution according to the given time quantum.
- Checked the Gantt Chart and execution order.
- Verified the calculation of waiting time and turnaround time.

7. Result

Implemented the Round Robin Scheduling algorithm and Gantt Chart generation to represent CPU execution and understand process scheduling performance.

---

WEEK 4 – INTERACTIVE DEADLOCK SIMULATION SYSTEM: GUI DEVELOPMENT

1. Overview

Deadlock is a situation in which two or more processes wait indefinitely for resources held by one another.

The project demonstrates deadlock management using techniques such as Banker’s Algorithm, Resource Allocation Graph (RAG), and Deadlock Detection and Recovery.

2. Individual Role

My assigned responsibility was GUI Development using C and Windows API in the file "src/gui.c".

I worked on developing the graphical interface and connecting it with the different project modules.

3. GUI Features

The graphical interface includes:

- Displaying Allocation Matrix.
- Displaying Maximum Matrix.
- Displaying Need Matrix.
- Displaying Available Resources.
- Safety Check button.
- Detect Deadlock button.
- Resource Request option.
- Deadlock Recovery option.
- System Status display.
- Safe Sequence display.
- Resource Allocation Graph option.
- Resource Utilization display.
- Operation logs.

4. Formula Used

Need Matrix:

[
Need = Maximum - Allocation
]

The Need Matrix represents the remaining resources required by each process.

5. Working

The GUI provides options to interact with the deadlock simulation system.

Users can perform safety checks, detect deadlocks, request resources, and view system status through the graphical interface.

The interface displays information such as SAFE, UNSAFE, or DEADLOCKED status based on the results provided by the project modules.

6. Testing

- Checked whether the GUI window opens correctly.
- Verified the display of resource allocation information.
- Tested the available buttons and interface options.
- Checked the interaction between the GUI and the project modules.

7. Result

Developed the graphical user interface for the Interactive Deadlock Simulation System, allowing users to access deadlock-related operations and view resource information through an interactive interface.

---

WEEK 5 – PAGE REPLACEMENT ALGORITHMS: OPTIMAL PAGE REPLACEMENT

1. Overview

Page Replacement is a memory management technique used by an operating system when a page needs to be loaded into memory but all available frames are occupied.

The project demonstrates different page replacement algorithms to understand how pages are replaced in memory.

2. Individual Role

My assigned contribution was implementing the Optimal Page Replacement Algorithm.

3. Optimal Page Replacement Algorithm

The Optimal Page Replacement Algorithm replaces the page that will not be used for the longest time in the future.

Working steps:

1. Read the page reference string.
2. Check whether the requested page is already present in memory.
3. If the page is present, count it as a Page Hit.
4. If the page is not present, count it as a Page Fault.
5. If an empty frame is available, insert the page into it.
6. If all frames are occupied, replace the page whose next use is farthest in the future.
7. Continue until all page requests are processed.
8. Calculate the total hits and faults.

4. Input

- Page Reference String
- Number of Frames

5. Formulas Used

Total Page Requests:

Total Requests = Page Hits + Page Faults

Hit Ratio:

Hit Ratio = (Page Hits / Total Page Requests) × 100

Fault Ratio:

Fault Ratio = (Page Faults / Total Page Requests) × 100

6. Testing

- Tested the algorithm using sample page reference strings.
- Verified whether existing pages were identified as hits.
- Checked page replacement when all frames were occupied.
- Verified the tracking of page hits, page faults, and frame contents.

7. Result

Implemented the Optimal Page Replacement Algorithm to simulate page replacement, track page hits and faults, and display the frame contents during execution.

---

OVERALL SUMMARY

During the five-week Operating Systems PBL, I contributed to different modules involving IPC, process communication, CPU scheduling, deadlock simulation, and memory management.

Week| Topic| Individual Contribution
Week 1| Shared Memory| Study and Documentation
Week 2| Three-Process OS Simulator| TCP Sockets and Logger using FIFO
Week 3| Process Scheduling| Round Robin Scheduling and Gantt Chart Generation
Week 4| Deadlock Simulation| GUI Development
Week 5| Page Replacement| Optimal Page Replacement Algorithm

---

TECHNOLOGIES AND TOOLS USED

- Programming Language: C
- Operating Systems: Linux / Ubuntu and Windows
- TCP Socket Programming
- POSIX Named Pipes (FIFO)
- Windows API
- GCC Compiler
- Visual Studio Code

---

LEARNING OUTCOMES

Through this five-week project, I gained knowledge and practical understanding of:

1. Inter-Process Communication and Shared Memory.
2. TCP Socket Programming and Client-Server Communication.
3. Named Pipes (FIFO) for process communication.
4. CPU Scheduling using the Round Robin algorithm.
5. Gantt Chart generation and scheduling calculations.
6. Deadlock management and GUI development.
7. Memory Management and Optimal Page Replacement.
8. Testing and debugging C programs.

---

CONCLUSION

The five-week Operating Systems Project-Based Learning activity helped me understand important operating system concepts through practical implementation and documentation.

I gained experience in process communication, CPU scheduling, deadlock simulation, GUI development, and memory management. Working on the assigned modules improved my programming skills and helped me understand how operating system concepts are applied in real-world scenarios.
