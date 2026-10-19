# Interactive Deadlock Simulation System

## Overview

The Interactive Deadlock Simulation System demonstrates operating system resource allocation, safety checking, deadlock detection, and resource utilization.

## Features

- Banker's Algorithm for safety checking
- Resource request handling
- Deadlock detection and recovery
- Resource Allocation Graph (RAG) representation
- Resource utilization calculation
- Simulation output for system-state analysis

## Project Structure

```text
Week4_Deadlock/
├── README.md
├── include/
│   └── deadlock.h
├── src/
│   ├── main.c
│   ├── banker.c
│   ├── detection.c
│   ├── gui.c
│   └── rag.c
├── tests/
└── screenshots/
    └── simulation_output.png
```

## Technologies Used

- C programming language
- GCC compiler
- Windows and MSYS2 UCRT64 development environment

## Compilation

Run the following command from the `Week4_Deadlock` directory:

```bash
gcc -Wall -Wextra -std=c11 -Iinclude src/main.c src/banker.c src/detection.c src/gui.c src/rag.c -o deadlock.exe
```

## Execution

```bash
./deadlock.exe
```

Enter the number of processes, resource types, allocation matrix, maximum demand matrix, and available resources when prompted.

## Simulation Output

![Deadlock Simulation Output](screenshots/simulation_output.png)

## Team Responsibilities

- Haneena: Banker's Algorithm
- Ayman: Deadlock detection and recovery
- Vishnu: GUI development
- Isha: Resource Allocation Graph, resource utilization, integration, testing, and report

## Project Status

The console simulation has been executed and its output captured. GUI functionality should be verified separately.

