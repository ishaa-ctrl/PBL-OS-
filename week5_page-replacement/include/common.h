
#ifndef COMMON_H
#define COMMON_H

#define MAX_REFERENCES 1000
#define MAX_FRAMES 100

/* Stores the simulation results for one algorithm */
typedef struct {
    int total_refs;
    int frame_count;

    /* Frame contents after each page request */
    int frames[MAX_REFERENCES][MAX_FRAMES];

    /* 1 = Page Hit, 0 = Page Fault */
    int hit[MAX_REFERENCES];

    int page_hits;
    int page_faults;

} SimulationResult;

/* Haneena: FIFO Algorithm */
void simulate_fifo(
    const int pages[],
    int n,
    int frame_count,
    SimulationResult *result
);

/* Ayman: LRU Algorithm */
void simulate_lru(
    const int pages[],
    int n,
    int frame_count,
    SimulationResult *result
);

/* Vishnu: Optimal Algorithm */
void simulate_optimal(
    const int pages[],
    int n,
    int frame_count,
    SimulationResult *result
);

void display_statistics(const char *name,
                        const SimulationResult *result);

void compare_algorithms(const SimulationResult *fifo,
                        const SimulationResult *lru,
                        const SimulationResult *optimal);

#endif
