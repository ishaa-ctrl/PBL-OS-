# OPERATING SYSTEMS PBL
## Individual Contribution Report

**Student Name:** Safiyath Isha  
**Subject:** Operating Systems  
**Duration:** Week 1 – Week 5

---

# 1. WEEK 1 – INTER-PROCESS COMMUNICATION (IPC): PIPES

### Individual Contribution
Prepared and documented the topic of Pipes in Inter-Process Communication.

### Concepts Covered
- IPC and its importance.
- Working of pipes.
- Read end and write end.
- Anonymous Pipes and Named Pipes (FIFO).
- FIFO (First In, First Out).
- Producer-Consumer communication.
- Linux command pipelines.
- Advantages and disadvantages of pipes.

### Implementation

**Linux example:**
```bash
ls | grep ".txt"
```

**Python implementation:**
```python
from multiprocessing import Pipe

conn1, conn2 = Pipe()

conn1.send("Hello from Process 1")
print(conn2.recv())
```

**Output:**
```text
Hello from Process 1
```

---

# 2. WEEK 2 – THREE-PROCESS OS SIMULATOR AND ADDITIONAL IPC IMPLEMENTATIONS

### Project Overview
A multi-process OS simulator consisting of UI, Core, and Logger processes communicating through POSIX Named Pipes (FIFO).

### My Role: Team Leader / Integration

My responsibilities:
- Integration of UI, Core, and Logger processes.
- Verification of UI-to-Core communication.
- Verification of Core-to-UI responses.
- Verification of Core-to-Logger communication.
- FIFO creation and verification.
- Process communication testing.
- Benchmarking and performance evaluation.
- Project documentation.

### FIFO Channels

| FIFO | Communication |
|---|---|
| ui_to_core | UI → Core |
| core_to_ui | Core → UI |
| core_to_logger | Core → Logger |

### Additional IPC Implementations – Individual Work

**A. Shared Memory**
- Creating and attaching shared memory segments.
- Reading and writing shared data.
- Detaching and cleaning up shared memory.
- Understanding synchronization requirements.

**B. Semaphores**
- Semaphore operations.
- Process synchronization.
- Critical section management.
- Controlling access to shared resources.
- Preventing race conditions.

---

# 3. WEEK 3 – PROCESS SCHEDULING SIMULATOR

### Project Overview
A C-based CPU scheduling application implementing six algorithms, displaying Gantt charts and calculating scheduling performance metrics.

### My Individual Role

- Developed the main program (`main.c`).
- Designed the main menu.
- Integrated all six scheduling algorithms.
- Performed overall testing.
- Maintained documentation.
- Verified integrated outputs.

### Algorithms Integrated

1. First Come First Served (FCFS).
2. Shortest Job First (SJF) – Non-preemptive.
3. Shortest Remaining Time First (SRTF) – Preemptive.
4. Priority Scheduling – Non-preemptive.
5. Priority Scheduling – Preemptive.
6. Round Robin (RR) – Configurable time quantum.

### Input Requirements
- Number of processes.
- Arrival Time (AT).
- Burst Time (BT).
- Priority.
- Time quantum for Round Robin.

### Output Requirements
- Gantt Chart.
- Completion Time (CT).
- Turnaround Time (TAT).
- Waiting Time (WT).
- Response Time (RT).
- Average Waiting Time.
- Average Turnaround Time.
- CPU Utilization.

### Performance Formulas

| Metric | Formula |
|---|---|
| TAT | CT − AT |
| WT | TAT − BT |
| RT | First Start Time − AT |
| CPU Utilization | (Total CPU Busy Time / Total Elapsed Schedule Time) × 100% |

### Testing
- Tested different process input sets.
- Verified algorithm selection.
- Checked Gantt charts and scheduling metrics.
- Compared actual outputs with expected results.

**Technologies:** C, GCC, VS Code, MSYS2 UCRT64, Git and GitHub.

---

# 4. WEEK 4 – INTERACTIVE DEADLOCK SIMULATION SYSTEM

### Project Overview
A C-based application with a Windows GUI demonstrating resource allocation, deadlock avoidance, detection, and recovery.

### My Individual Role

- Led project integration.
- Worked on Resource Allocation Graph (RAG) visualization.
- Worked on resource utilization.
- Performed overall testing.
- Maintained documentation.
- Worked through `src/rag.c` and `src/main.c`.

### Resource Allocation Graph (RAG)

Worked on visualizing:
- Process nodes.
- Resource nodes.
- Allocation edges.
- Request edges.

### Resource Utilization

Worked with the system's resource information:

- Available Resource Vector.
- Allocation Matrix.
- Maximum Requirement Matrix.
- Need Matrix.
- Resource Requests.
- Safe Sequence.
- Deadlocked Processes.

**Formula:**

`Need = Maximum − Allocation`

### Integration and Testing

- Integration of RAG with other modules.
- Resource allocation and graph display checks.
- Resource utilization calculations.
- Testing safe and unsafe states.
- Testing granted and denied resource requests.
- Testing deadlocked processes.
- Recovery followed by another detection check.
- GUI and system-status integration.

**Technologies:** C, Windows API, GCC, GNU Make, VS Code and MSYS2 UCRT64.

---

# 5. WEEK 5 – PAGE REPLACEMENT ALGORITHMS

### Project Overview
A C-based simulator for implementing and comparing FIFO, LRU, and Optimal page replacement algorithms.

### My Individual Role

- Integration of all three algorithms.
- Statistics calculation.
- Comparative analysis.
- GUI development and integration.

### Algorithms

1. FIFO – First In, First Out.
2. LRU – Least Recently Used.
3. Optimal Page Replacement.

### Simulator Features

- Page-reference string input.
- Frame count input.
- Step-by-step frame contents.
- Page hit and page fault identification.
- Total hits and faults.
- Hit and fault percentages.
- Comparison using identical inputs.
- Individual algorithm unit tests.

### GUI Responsibilities

- Page numbers separated by spaces or commas.
- Frame count selection.
- Individual algorithm selection.
- Compare All option.
- Step-by-step simulation results.
- Page-fault chart.
- Quick statistics.
- Reset option.

### Sample Comparison

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

### Build and Execution

**Technologies:** C, GCC, GNU Make, Windows API and MSYS2 UCRT64.

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

**Validation:** The GUI must be built and run in the target Windows environment before claiming successful verification. Actual screenshots should be stored in `docs/screenshots/`.

---

# 6. SUMMARY OF INDIVIDUAL CONTRIBUTIONS

| Week | Project | My Work |
|---|---|---|
| 1 | IPC – Pipes | Topic explanation and Python implementation |
| 2 | Three-Process OS Simulator | Team Leader, integration, FIFO verification, testing, benchmarking and documentation |
| 2 | Additional IPC | Shared Memory and Semaphores |
| 3 | Process Scheduling | Main program, menu, algorithm integration, testing and documentation |
| 4 | Deadlock Simulation | RAG visualization, resource utilization, integration, testing and documentation |
| 5 | Page Replacement | Algorithm integration, statistics, comparative analysis and GUI |

---

# 7. TECHNOLOGIES AND TOOLS

| Technology | Usage |
|---|---|
| C | OS simulations and IPC implementations |
| Python | Pipe communication |
| GCC | Compilation |
| GNU Make | Build automation |
| POSIX FIFO | Inter-process communication |
| Windows API | GUI development |
| Linux / MSYS2 UCRT64 | Development and execution |
| VS Code | Code development |
| Git and GitHub | Version control and integration |

---

# 8. OVERALL LEARNING OUTCOMES

- IPC using Pipes, Shared Memory and Semaphores.
- POSIX FIFO communication and multi-process integration.
- Modular C programming and main-program development.
- CPU scheduling algorithms and performance metrics.
- Gantt chart generation and scheduling analysis.
- Deadlock avoidance, detection and recovery concepts.
- Resource Allocation Graph visualization.
- Resource utilization analysis.
- FIFO, LRU and Optimal page replacement.
- Page hit and fault analysis.
- GUI development and integration.
- Testing, debugging and benchmarking.
- Project documentation and version control.

---

# 9. CONCLUSION

**My individual work across the five weeks:**

1. Pipes – IPC concepts and implementation example.
2. Shared Memory and Semaphores – additional IPC implementations.
3. OS Simulator – team leadership, FIFO integration, testing and benchmarking.
4. CPU Scheduling – main program, menu, integration and testing.
5. Deadlock Simulation – RAG visualization and resource utilization.
6. Page Replacement – algorithm integration, statistics and GUI.
7. Documentation – project reports, testing records and technical documentation.


