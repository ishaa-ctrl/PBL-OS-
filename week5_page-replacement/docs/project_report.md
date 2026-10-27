# Project Report: Simulation and Comparative Analysis of Page Replacement Algorithms

## Abstract
This project implements a simulator for three operating-system page replacement algorithms: FIFO, LRU, and Optimal. It accepts a page-reference string and frame count, records frame contents after each reference, identifies hits and faults, calculates ratios, and compares the algorithms.

## Problem statement
When a requested page is not present in memory and all frames are occupied, the operating system must choose a page to replace. Replacement policies can produce different page-fault counts, affecting memory-system performance.

## Objectives
1. Implement FIFO, LRU, and Optimal in C.
2. Record frame state after every page request.
3. Count page hits and page faults.
4. Calculate hit and fault ratios.
5. Compare the algorithms on the same reference string.
6. Provide test cases and a graphical comparison interface for Windows.

## Methodology
The console program asks for the number of references, page numbers, frame count, and algorithm choice. The comparison option executes all algorithms on identical input. Each algorithm stores its frame history and hit/fault status. A Windows-native GUI is included in src/gui.c; it accepts page references and frame count and presents frame-by-frame results.

## Sample evaluation
Reference string: 7 0 1 2 0 3 0 4 2 3 0 3 2
Number of references: 13
Number of frames: 3

| Algorithm | Hits | Faults | Hit ratio | Fault ratio |
|---|---:|---:|---:|---:|
| FIFO | 3 | 10 | 23.08% | 76.92% |
| LRU | 4 | 9 | 30.77% | 69.23% |
| Optimal | 6 | 7 | 46.15% | 53.85% |

These are expected results for the listed input. Use make test to check the algorithm counts in the local GCC environment. Capture screenshots after running the actual application.

## Conclusion
The tested reference string demonstrates that replacement policy affects page-fault count. Optimal has the fewest faults in this example, followed by LRU and FIFO. Optimal relies on future knowledge and therefore serves as a benchmark rather than a directly implementable online policy.

## Limitations
- The implementation is a simulator, not a real operating-system memory manager.
- The Optimal algorithm assumes the complete future reference string is known.
- The Windows GUI target must be built and run on a compatible Windows GCC environment.
