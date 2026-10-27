# Page Replacement Algorithm Explanation

## FIFO (First In, First Out)
FIFO replaces the page that entered memory first. A circular pointer selects the next frame when a page fault occurs and all frames are occupied. FIFO is easy to implement but does not consider how recently a page was used.

## LRU (Least Recently Used)
LRU replaces the page that has not been used for the longest time. The simulator tracks the most recent reference index for each occupied frame and replaces the frame with the oldest index.

## Optimal Page Replacement
Optimal replaces the page whose next use is farthest in the future. A page that is never used again is an ideal replacement candidate. This gives the minimum possible page faults for a known reference string, but requires future knowledge, so it is mainly a theoretical benchmark.

## Terminology
- **Page hit:** requested page is already in a frame.
- **Page fault:** requested page is not in memory and must be loaded.
- **Hit ratio:** (number of hits / total references) × 100.
- **Fault ratio:** (number of faults / total references) × 100.

## Complexity
Let n be the number of page references and f the number of frames.
- FIFO: O(n × f) for frame lookup.
- LRU: O(n × f) for lookup and replacement selection.
- Optimal: worst-case O(n² × f) because future references are scanned during replacement.
