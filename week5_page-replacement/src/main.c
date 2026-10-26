
#include <stdio.h>
#include "common.h"

void display_result(const char *name, const int pages[],
                    const SimulationResult *r)
{
    printf("\n===== %s =====\n", name);
    printf("Page\t");

    for (int j = 0; j < r->frame_count; j++)
        printf("F%d\t", j + 1);

    printf("Status\n");

    for (int i = 0; i < r->total_refs; i++) {
        printf("%d\t", pages[i]);

        for (int j = 0; j < r->frame_count; j++) {
            if (r->frames[i][j] == -1)
                printf("-\t");
            else
                printf("%d\t", r->frames[i][j]);
        }

        printf("%s\n", r->hit[i] ? "Hit" : "Fault");
    }

    printf("\nTotal references: %d\n", r->total_refs);
    printf("Page hits: %d\n", r->page_hits);
    printf("Page faults: %d\n", r->page_faults);
    printf("Hit ratio: %.2f%%\n",
           100.0 * r->page_hits / r->total_refs);
    printf("Fault ratio: %.2f%%\n",
           100.0 * r->page_faults / r->total_refs);
}

int main(void)
{
    int pages[MAX_REFERENCES];
    int n, frame_count, choice;

    printf("====================================\n");
    printf(" PAGE REPLACEMENT ALGORITHM SIMULATOR\n");
    printf("====================================\n");

    printf("Enter number of page references (1-%d): ",
           MAX_REFERENCES);

    if (scanf("%d", &n) != 1 ||
        n < 1 || n > MAX_REFERENCES) {
        printf("Invalid number of references.\n");
        return 1;
    }

    printf("Enter %d page numbers (non-negative): ", n);

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &pages[i]) != 1 || pages[i] < 0) {
            printf("Invalid page number.\n");
            return 1;
        }
    }

    printf("Enter number of frames (1-%d): ", MAX_FRAMES);

    if (scanf("%d", &frame_count) != 1 ||
        frame_count < 1 || frame_count > MAX_FRAMES) {
        printf("Invalid frame count.\n");
        return 1;
    }

    printf("\nSelect an algorithm:\n");
    printf("1. FIFO\n");
    printf("2. LRU\n");
    printf("3. Optimal\n");
    printf("4. Compare all algorithms\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1 ||
        choice < 1 || choice > 4) {
        printf("Invalid choice.\n");
        return 1;
    }

    SimulationResult results[3];
    const char *names[] = {"FIFO", "LRU", "Optimal"};

    if (choice == 1 || choice == 4)
        simulate_fifo(pages, n, frame_count, &results[0]);

    if (choice == 2 || choice == 4)
        simulate_lru(pages, n, frame_count, &results[1]);

    if (choice == 3 || choice == 4)
        simulate_optimal(pages, n, frame_count, &results[2]);

    if (choice == 1) {
        display_result(names[0], pages, &results[0]);
    } else if (choice == 2) {
        display_result(names[1], pages, &results[1]);
    } else if (choice == 3) {
        display_result(names[2], pages, &results[2]);
    } else {
        printf("\n========== ALGORITHM COMPARISON ==========\n");
        printf("Algorithm\tHits\tFaults\tHit Ratio\tFault Ratio\n");

        for (int i = 0; i < 3; i++) {
            display_result(names[i], pages, &results[i]);

            printf("\n%s\t\t%d\t%d\t%.2f%%\t\t%.2f%%\n",
                   names[i],
                   results[i].page_hits,
                   results[i].page_faults,
                   100.0 * results[i].page_hits / n,
                   100.0 * results[i].page_faults / n);
        }
    }

    return 0;
}
