# Week 3 — Process Scheduling Simulator

## 1. Project Overview

The Process Scheduling Simulator is a C-based application that simulates different CPU scheduling algorithms and compares their performance using scheduling metrics and Gantt charts.

The user can enter process details, select a scheduling algorithm, and view the resulting execution order and performance metrics.

## 2. Objectives

- Implement six CPU scheduling algorithms.
- Accept process arrival time, burst time, and priority.
- Display a Gantt chart for process execution.
- Calculate completion time, turnaround time, waiting time, and response time.
- Display average waiting time and average turnaround time.
- Compare scheduling algorithms using sample test cases.

## 3. Scheduling Algorithms

The simulator supports:

1. First Come First Served (FCFS)
2. Shortest Job First (SJF), Non-preemptive
3. Shortest Remaining Time First (SRTF), Preemptive SJF
4. Priority Scheduling, Preemptive
5. Priority Scheduling, Non-preemptive
6. Round Robin (RR), with configurable time quantum

**Priority convention:** A smaller priority number represents a higher priority.

## 4. Project Structure

```text
Week3_Process_Scheduling/
├── include/
│   └── scheduler.h
├── src/
│   ├── main.c
│   ├── haneena.c
│   ├── ayman.c
│   └── vishnu.c
├── tests/
│   ├── test_haneena.c
│   ├── test_ayman.c
│   └── test_vishnu.c
├── docs/
│   └── Week3_Process_Scheduling_Test_Results.md
├── Makefile
├── .gitignore
└── README.md
```

## 5. Technologies Used

- **Programming language:** C
- **Compiler:** GCC
- **Development environment:** Visual Studio Code and MSYS2 UCRT64
- **Version control:** Git and GitHub

## 6. Input Requirements

The simulator accepts:

- Number of processes
- Arrival time for each process
- Burst time for each process
- Priority for each process
- Time quantum when Round Robin is selected

Process IDs are assigned by the program.

## 7. Output

The simulator displays:

- Selected scheduling algorithm
- Gantt chart showing process execution intervals
- Completion Time (CT)
- Turnaround Time (TAT)
- Waiting Time (WT)
- Response Time (RT)
- Average Waiting Time
- Average Turnaround Time

CPU utilization should also be included in the final program output to satisfy the project requirements.

## 8. Compilation and Execution

Run these commands from the `Week3_Process_Scheduling` directory in an MSYS2 UCRT64 terminal.

### Compile the integrated simulator

```bash
gcc -Wall -Wextra -std=c11 -Iinclude src/main.c src/haneena.c src/ayman.c src/vishnu.c -o scheduler.exe
```

### Run the simulator

```bash
./scheduler.exe
```

### Run individual tests

**Haneena:**

```bash
gcc -Wall -Wextra -std=c11 -Iinclude src/haneena.c tests/test_haneena.c -o test_haneena.exe
./test_haneena.exe
```

**Ayman:**

```bash
gcc -Wall -Wextra -std=c11 -Iinclude src/ayman.c tests/test_ayman.c -o test_ayman.exe
./test_ayman.exe
```

**Vishnu:**

```bash
gcc -Wall -Wextra -std=c11 -Iinclude src/vishnu.c tests/test_vishnu.c -o test_vishnu.exe
./test_vishnu.exe
```

## 9. Performance Metrics

- **Turnaround Time:** Completion Time − Arrival Time
- **Waiting Time:** Turnaround Time − Burst Time
- **Response Time:** First Start Time − Arrival Time
- **CPU Utilization:** Total CPU Busy Time ÷ Total Elapsed Schedule Time × 100%

## 10. Testing and Documentation

Individual algorithm tests are maintained in the `tests/` directory.

The `docs/` directory contains the sample test results and performance analysis report. The integrated simulator should be tested with at least three different process input sets before final submission.

Actual integrated-program output should be checked against the documented sample results.

## 11. Team Contributions

| Team Member | Responsibility |
|---|---|
| Haneena | FCFS and Non-preemptive SJF |
| Ayman | Preemptive SJF and Preemptive Priority |
| Vishnu | Non-preemptive Priority and Round Robin |
| Isha | Integration, main menu, overall testing, and documentation |

## 12. Expected Deliverables

- C source code for all six scheduling algorithms
- Integrated command-line interface
- Gantt charts and scheduling metrics
- Test cases and sample outputs
- Performance analysis and documentation

## 13. Repository

Project repository: [PBL-OS- on GitHub](https://github.com/ishaa-ctrl/PBL-OS-)
