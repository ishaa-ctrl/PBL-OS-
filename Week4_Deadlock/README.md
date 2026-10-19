# Week 4: Interactive Deadlock Simulation System

## 1. Project Overview

Deadlock is an Operating System problem in which a group of processes cannot proceed because each process is waiting for resources held by another process.

The **Interactive Deadlock Simulation System** demonstrates resource allocation, deadlock avoidance, detection, and recovery through a C-based application with a Windows graphical user interface.

## 2. Objectives

- Understand deadlocks in Operating Systems.
- Implement Banker's Algorithm for deadlock avoidance.
- Implement a deadlock detection algorithm.
- Construct a Resource Allocation Graph (RAG).
- Identify safe, unsafe, and deadlocked states.
- Simulate resource requests and allocation.
- Demonstrate deadlock recovery.
- Analyze resource utilization.
- Visualize system state and algorithm results.

## 3. Features

The project is designed to support:

- Process and resource management.
- Allocation, maximum, and need matrices.
- Available resource tracking.
- Resource requests and allocation.
- Banker's Algorithm and safe-sequence calculation.
- Deadlock detection and recovery.
- Resource Allocation Graph visualization.
- Resource utilization analysis.
- A graphical interface for interacting with the simulation.

**Note:** Each feature must be verified against the implemented code before being described as fully functional.

## 4. Technologies Used

- **Programming Language:** C
- **GUI Framework:** Windows API
- **Compiler:** GCC
- **Build System:** Make
- **Development Environment:** Visual Studio Code with a compatible GCC environment

## 5. Project Structure

```text
Week4_Deadlock/
├── include/
│   ├── deadlock.h
│   ├── dashboard.h
│   ├── graph_view.h
│   └── matrix_view.h
├── src/
│   ├── main.c
│   ├── banker.c
│   ├── detection.c
│   ├── gui.c
│   ├── rag.c
│   ├── dashboard.c
│   ├── graph_view.c
│   └── matrix_view.c
├── tests/
│   ├── test_banker.c
│   └── test_detection.c
├── screenshots/
│   └── simulation_output.png
├── Makefile
└── README.md
```

*This structure describes the intended organization. Include only files that actually exist in the repository.*

## 6. Core Modules

| Module | Responsibility |
|---|---|
| `deadlock.h` | Shared system state and function declarations |
| `main.c` | Initializes the system and starts the application |
| `banker.c` | Safety checking and resource-request handling |
| `detection.c` | Deadlock detection and recovery |
| `gui.c` | Windows graphical interface and user interactions |
| `rag.c` | Resource Allocation Graph and resource utilization |
| `dashboard.c` | System status and algorithm results |
| `graph_view.c` | Graph display functionality |
| `matrix_view.c` | Allocation, maximum, need, and available resource displays |

## 7. System State

The simulator maintains the following information:

- **Available Vector:** Resources currently available.
- **Allocation Matrix:** Resources allocated to each process.
- **Maximum Matrix:** Maximum resource requirements of each process.
- **Need Matrix:** Remaining resources required by each process.

The need matrix is calculated using:

```text
Need = Maximum - Allocation
```

## 8. Algorithms

### Banker's Algorithm

Banker's Algorithm determines whether the current resource-allocation state is safe. If a safe sequence exists, the system can show an order in which all processes can complete.

### Deadlock Detection

The detection algorithm examines the current allocation and available resources to identify processes that cannot complete because of resource dependencies.

### Deadlock Recovery

The recovery module demonstrates a recovery action, such as releasing resources held by a selected process, and updates the system state.

### Resource Allocation Graph

The Resource Allocation Graph represents processes, resources, allocation edges, and outstanding resource requests.

## 9. Build and Run

Open a compatible MSYS2 UCRT64 terminal and navigate to this directory:

```bash
cd /c/Users/TEMP/Desktop/PBL-OS-/Week4_Deadlock
```

Compile using the Makefile:

```bash
make
```

Run the application:

```bash
./deadlock.exe
```

If compilation fails, check that GCC, the Windows API headers, and all required source files are available.

## 10. Testing

The system should be tested with:

- A safe resource-allocation state.
- An unsafe state with no safe sequence.
- A resource request that can be granted.
- A resource request that must be denied.
- A state containing deadlocked processes.
- A recovery operation followed by another detection check.
- Resource utilization calculations.
- GUI buttons and system-status displays.

## 11. Expected Outcomes

The project aims to demonstrate how Operating Systems manage competing resource requests, determine safe states, detect deadlocks, and recover from resource-allocation problems.

It also provides practical experience with C programming, operating-system algorithms, graphical interfaces, testing, and software integration.

## 12. Learning Outcomes

After completing the project, students should be able to:

- Explain the necessary conditions for deadlock.
- Represent resource allocation using matrices and graphs.
- Implement Banker's Algorithm and deadlock detection.
- Distinguish safe, unsafe, and deadlocked states.
- Demonstrate resource allocation and recovery.
- Analyze resource utilization.
- Apply Operating System concepts in a practical simulation.

## 13. Team Contributions

Add the final team member names and responsibilities here, based on the actual division of work.

## 14. Conclusion

The Interactive Deadlock Simulation System provides a practical demonstration of deadlock avoidance, detection, resource allocation, and recovery. Its graphical interface is intended to make Operating System concepts easier to understand through interactive simulation and visualization.
