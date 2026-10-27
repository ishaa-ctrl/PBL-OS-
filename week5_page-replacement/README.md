# Page Replacement Algorithms

## Project overview
A C-based simulator and comparative analysis of three operating-system page replacement algorithms: FIFO, LRU, and Optimal.

## Features
- Accepts a page-reference string and number of frames.
- Displays frame contents after each page request.
- Marks each request as a page hit or page fault.
- Calculates hit/fault totals and percentages.
- Compares all three algorithms using identical input.
- Includes unit tests for FIFO, LRU, and Optimal.
- Includes a Windows-native GUI source file for graphical comparison.

## Team
- Haneena: FIFO algorithm
- Ayman: LRU algorithm
- Vishnu: Optimal algorithm
- Isha: Integration, statistics, and GUI

## Requirements
GCC and GNU Make. The GUI target requires a Windows/MSYS2 GCC toolchain.

## Build the console simulator
From this directory, run: make

This creates simulator.exe.

## Run the console simulator
Run: ./simulator.exe

## Build and run the GUI on Windows
Run: make gui
Then run: ./simulator_gui.exe

The GUI accepts page numbers separated by spaces or commas and a frame count. Click “Compare FIFO, LRU and Optimal” to display frame-by-frame results and summary statistics.

## Run tests
Run: make test

## Sample comparison input
For the console program, enter these values when prompted:
13
7 0 1 2 0 3 0 4 2 3 0 3 2
3
4

Expected results:
| Algorithm | Hits | Faults | Hit ratio | Fault ratio |
|---|---:|---:|---:|---:|
| FIFO | 3 | 10 | 23.08% | 76.92% |
| LRU | 4 | 9 | 30.77% | 69.23% |
| Optimal | 6 | 7 | 46.15% | 53.85% |

## Documentation
- Algorithm explanation: docs/algorithm_explaination.md
- Project report: docs/project_report.md
- Test cases: tests/test_cases.txt

## Validation note
The console implementation and GUI source are included. Build and run the GUI on the target Windows environment before presenting it as verified. Store actual screenshots in docs/screenshots/.
