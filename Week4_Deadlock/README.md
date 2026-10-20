# Week 4: Interactive Deadlock Simulation System

## 1. Project Overview

Deadlock is an Operating System problem in which processes become blocked while waiting for resources held by other processes.

The Interactive Deadlock Simulation System demonstrates resource allocation, deadlock avoidance, detection, and recovery through a C-based application with a Windows graphical user interface.

## 2. Objectives

- Understand deadlocks in Operating Systems.
- Implement Banker's Algorithm for deadlock avoidance.
- Implement deadlock detection.
- Construct a Resource Allocation Graph (RAG).
- Identify safe, unsafe, and deadlocked states.
- Simulate resource requests and allocation.
- Demonstrate deadlock recovery.
- Analyze resource utilization.
- Visualize system state and algorithm results.

## 3. Features

- Resource allocation and requests.
- Available resource vector.
- Allocation, Maximum, and Need matrices.
- Banker's Algorithm and safe-sequence calculation.
- Deadlock detection and recovery.
- Resource Allocation Graph visualization.
- Resource utilization analysis.
- Graphical interface for interacting with the simulation.

  ## Team Contributions

- **Haneena:** Implemented Banker's Algorithm in `src/banker.c`, including safety checking, safe sequence generation, and resource request handling.
- **Ayman:** Implemented deadlock detection and recovery in `src/detection.c`.
- **Vishnu:** Developed the graphical user interface (GUI) in `src/gui.c`.
- **Isha:** Led project integration and worked on Resource Allocation Graph visualization, resource utilization, testing, and documentation in `src/rag.c` and `src/main.c`.

## 4. Technologies Used

- Programming Language: C
- GUI Framework: Windows API
- Compiler: GCC
- Build System: Make
- Development Environment: Visual Studio Code and MSYS2 UCRT64

## 5. Project Structure

```text
Week4_Deadlock/
├── include/
├── src/
├── tests/
├── screenshots/
├── Makefile
└── README.md
```

The folders contain the implementation, header files, tests, and screenshots included in the project.

## 6. Core Modules

| Module | Responsibility |
|---|---|
| `deadlock.h` | Shared system state and declarations |
| `main.c` | Initializes the system and starts the application |
| `banker.c` | Safety checking and resource requests |
| `detection.c` | Deadlock detection and recovery |
| `gui.c` | Graphical interface and user interactions |
| `rag.c` | Resource Allocation Graph and resource utilization |

Additional modules may support the dashboard, graph display, and matrix views.

## 7. System State

The simulator maintains:

- Available Resource Vector
- Allocation Matrix
- Maximum Requirement Matrix
- Need Matrix
- Resource Requests
- Safe Sequence
- Deadlocked Processes

The Need Matrix is calculated using:

```text
Need = Maximum - Allocation
```

## 8. Algorithms

### Banker's Algorithm

Determines whether the current resource-allocation state is safe and identifies a safe sequence when one exists.

### Deadlock Detection

Examines the current allocation and available resources to identify processes that cannot complete.

### Deadlock Recovery

Demonstrates a recovery action and updates the system state.

### Resource Allocation Graph

Represents processes, resources, allocation edges, and outstanding resource requests.

## 9. Build and Run

Open an MSYS2 UCRT64 terminal and navigate to the project directory:

```bash
cd /c/Users/TEMP/Desktop/PBL-OS-/Week4_Deadlock
```

Build and run:

```bash
make
./deadlock.exe
```

## 10. Testing

Test the system using:

- A safe resource-allocation state.
- An unsafe state with no safe sequence.
- Resource requests that are granted or denied.
- A state containing deadlocked processes.
- Recovery followed by another detection check.
- Resource utilization calculations.
- GUI buttons and system-status displays.

## 11. Learning Outcomes

- Explain deadlock in Operating Systems.
- Represent resource allocation using matrices and graphs.
- Implement Banker's Algorithm and deadlock detection.
- Distinguish safe, unsafe, and deadlocked states.
- Demonstrate resource allocation and recovery.
- Analyze resource utilization.

## 12. Conclusion

The Interactive Deadlock Simulation System provides a practical demonstration of resource allocation, deadlock avoidance, detection, and recovery through an interactive graphical interface.
