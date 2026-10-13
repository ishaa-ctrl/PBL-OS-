# Week 3: Process Scheduling
## Test Results and Performance Analysis

**Project:** CPU Process Scheduling Simulator

## 1. Algorithms Covered

1. First Come First Served (FCFS)
2. Shortest Job First (SJF), Non-preemptive
3. Shortest Remaining Time First (SRTF), Preemptive
4. Priority Scheduling, Preemptive
5. Priority Scheduling, Non-preemptive
6. Round Robin (RR), Time Quantum = 2

**Assumptions:** A smaller priority number indicates higher priority. Context-switch overhead is not included.

## 2. Test Case 1: Mixed Arrivals and Priorities

### Input

| Process | Arrival Time | Burst Time | Priority |
|---|---:|---:|---:|
| P1 | 0 | 5 | 2 |
| P2 | 1 | 3 | 1 |
| P3 | 2 | 1 | 3 |

### Gantt Charts and Average Metrics

| Algorithm | Gantt Chart | Average WT | Average TAT |
|---|---|---:|---:|
| FCFS | P1 (0-5) → P2 (5-8) → P3 (8-9) | 3.33 | 6.33 |
| SJF Non-preemptive | P1 (0-5) → P3 (5-6) → P2 (6-9) | 2.67 | 5.67 |
| SJF Preemptive (SRTF) | P1 (0-1) → P2 (1-2) → P3 (2-3) → P2 (3-5) → P1 (5-9) | 1.67 | 4.67 |
| Priority Preemptive | P1 (0-1) → P2 (1-4) → P1 (4-8) → P3 (8-9) | 3.00 | 6.00 |
| Priority Non-preemptive | P1 (0-5) → P2 (5-8) → P3 (8-9) | 3.33 | 6.33 |
| Round Robin (q = 2) | P1 (0-2) → P2 (2-4) → P3 (4-5) → P1 (5-7) → P2 (7-8) → P1 (8-9) | 3.33 | 6.33 |

### Performance Metrics

| Algorithm | Process | CT | TAT | WT | RT |
|---|---|---:|---:|---:|---:|
| FCFS | P1 | 5 | 5 | 0 | 0 |
| FCFS | P2 | 8 | 7 | 4 | 4 |
| FCFS | P3 | 9 | 7 | 6 | 6 |
| SJF Non-preemptive | P1 | 5 | 5 | 0 | 0 |
| SJF Non-preemptive | P2 | 9 | 8 | 5 | 5 |
| SJF Non-preemptive | P3 | 6 | 4 | 3 | 3 |
| SJF Preemptive | P1 | 9 | 9 | 4 | 0 |
| SJF Preemptive | P2 | 5 | 4 | 1 | 0 |
| SJF Preemptive | P3 | 3 | 1 | 0 | 0 |
| Priority Preemptive | P1 | 8 | 8 | 3 | 0 |
| Priority Preemptive | P2 | 4 | 3 | 0 | 0 |
| Priority Preemptive | P3 | 9 | 7 | 6 | 6 |
| Priority Non-preemptive | P1 | 5 | 5 | 0 | 0 |
| Priority Non-preemptive | P2 | 8 | 7 | 4 | 4 |
| Priority Non-preemptive | P3 | 9 | 7 | 6 | 6 |
| Round Robin | P1 | 9 | 9 | 4 | 0 |
| Round Robin | P2 | 8 | 7 | 4 | 1 |
| Round Robin | P3 | 5 | 3 | 2 | 2 |

## 3. Test Case 2: Different Burst Lengths

### Input

| Process | Arrival Time | Burst Time | Priority |
|---|---:|---:|---:|
| P1 | 0 | 4 | 3 |
| P2 | 1 | 2 | 1 |
| P3 | 2 | 3 | 2 |

### Gantt Charts and Average Metrics

| Algorithm | Gantt Chart | Average WT | Average TAT |
|---|---|---:|---:|
| FCFS | P1 (0-4) → P2 (4-6) → P3 (6-9) | 2.33 | 5.33 |
| SJF Non-preemptive | P1 (0-4) → P2 (4-6) → P3 (6-9) | 2.33 | 5.33 |
| SJF Preemptive (SRTF) | P1 (0-1) → P2 (1-3) → P1 (3-6) → P3 (6-9) | 1.00 | 4.00 |
| Priority Preemptive | P1 (0-1) → P2 (1-3) → P3 (3-6) → P1 (6-9) | 2.67 | 5.67 |
| Priority Non-preemptive | P1 (0-4) → P2 (4-6) → P3 (6-9) | 2.33 | 5.33 |
| Round Robin (q = 2) | P1 (0-2) → P2 (2-4) → P3 (4-6) → P1 (6-8) → P3 (8-9) | 2.67 | 5.67 |

## 4. Test Case 3: CPU Idle Intervals

### Input

| Process | Arrival Time | Burst Time | Priority |
|---|---:|---:|---:|
| P1 | 0 | 3 | 2 |
| P2 | 4 | 2 | 1 |
| P3 | 8 | 1 | 3 |

### Gantt Chart Example: FCFS

`P1 (0-3) → IDLE (3-4) → P2 (4-6) → IDLE (6-8) → P3 (8-9)`

This case checks whether the simulator handles periods when no process is ready to execute.

- Total CPU busy time = 6 units.
- Total elapsed schedule time = 9 units.
- CPU utilization = (6 / 9) × 100 = **66.67%**.

## 5. Performance Analysis

- **FCFS:** Executes processes in arrival order. A long process can cause later processes to wait.
- **Non-preemptive SJF:** Selects the shortest available burst and runs it to completion.
- **Preemptive SJF (SRTF):** Can switch to a process with a shorter remaining time.
- **Priority Scheduling:** Selects processes based on priority. A smaller number represents a higher priority in these test cases.
- **Round Robin:** Gives each ready process a time slice. Performance depends on the time quantum and ready-queue order.
- **CPU Utilization:** Indicates the percentage of elapsed time during which the CPU is busy.

## 6. Formulae

- **Turnaround Time (TAT) = Completion Time (CT) - Arrival Time (AT)**
- **Waiting Time (WT) = Turnaround Time (TAT) - Burst Time (BT)**
- **Response Time (RT) = First Start Time - Arrival Time (AT)**
- **CPU Utilization = (Total CPU Busy Time / Total Elapsed Schedule Time) × 100%**

