
#include <stdio.h>
#include "common.h"

/* Calculate and display statistics for one algorithm */
void display_statistics(const char *name,
                        const SimulationResult *result)
{
    int total = result->total_refs;

    if (total <= 0) {
        printf("%s: No page references to process.\n", name);
        return;
    }

    double hit_ratio =
        (double)result->page_hits / total * 100.0;

    double fault_ratio =
        (double)result->page_faults / total * 100.0;

    printf("\nAlgorithm: %s\n", name);
    printf("Total references : %d\n", total);
    printf("Page hits        : %d\n", result->page_hits);
    printf("Page faults      : %d\n", result->page_faults);
    printf("Hit ratio        : %.2f%%\n", hit_ratio);
    printf("Fault ratio      : %.2f%%\n", fault_ratio);
}

/* Compare the page faults of all three algorithms */
void compare_algorithms(const SimulationResult *fifo,
                        const SimulationResult *lru,
                        const SimulationResult *optimal)
{
    const SimulationResult *results[] = {fifo, lru, optimal};
    const char *names[] = {"FIFO", "LRU", "Optimal"};

    printf("\n========== ALGORITHM COMPARISON ==========\n");
    printf("%-12s %-10s %-12s %-12s %-12s\n",
           "Algorithm", "Hits", "Faults", "Hit Ratio", "Fault Ratio");

    for (int i = 0; i < 3; i++) {
        int total = results[i]->total_refs;

        if (total <= 0)
            continue;

        printf("%-12s %-10d %-12d %-11.2f%% %-11.2f%%\n",
               names[i],
               results[i]->page_hits,
               results[i]->page_faults,
               100.0 * results[i]->page_hits / total,
               100.0 * results[i]->page_faults / total);
    }

    /* Identify the algorithm with the fewest page faults */
    int best = 0;

    for (int i = 1; i < 3; i++) {
        if (results[i]->page_faults < results[best]->page_faults)
            best = i;
    }

    printf("\nFewest page faults: %s (%d faults)\n",
           names[best], results[best]->page_faults);
}
