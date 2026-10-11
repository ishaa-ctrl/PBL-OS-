
# CPU Process Scheduling Simulator

## Project Overview
A C-based simulator implementing six CPU scheduling algorithms. Users can enter process details, select an algorithm, and view the Gantt chart and scheduling metrics.

## Scheduling Algorithms
1. First Come First Serve (FCFS)
2. Non-preemptive Shortest Job First (SJF)
3. Preemptive Shortest Job First (SRTF)
4. Preemptive Priority Scheduling
5. Non-preemptive Priority Scheduling
6. Round Robin Scheduling

**Priority rule:** A smaller priority number indicates a higher priority.

## Project Structure
- `include/scheduler.h` - Shared structures and function declarations
- `src/main.c` - Menu, input, and result display
- `src/haneena.c` - FCFS and non-preemptive SJF
- `src/ayman.c` - Preemptive SJF and preemptive priority
- `src/vishnu.c` - Non-preemptive priority and Round Robin
- `tests/` - Individual algorithm tests
- `Makefile` - Build and test commands

## Requirements
- GCC compiler
- GNU Make
- MSYS2 or another compatible C environment

## Build
Run from the `Week3_Process_Scheduling` directory:

```bash
make
```

## Run
```bash
./scheduler.exe
```

Enter the number of processes and their arrival time, burst time, and priority. Choose an algorithm from the menu. Round Robin also requires a positive time quantum.

## Run Tests
```bash
make test
```

## Clean Generated Files
```bash
make clean
```

## Scheduling Metrics
- **CT:** Completion Time
- **TAT:** Turnaround Time
- **WT:** Waiting Time
- **RT:** Response Time

The simulator also displays average waiting time and average turnaround time.

