#include <stdio.h>
#include "common.h"

int main(void)
{
    const int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    SimulationResult result;
    simulate_lru(pages, 13, 3, &result);

    if (result.page_faults != 9 || result.page_hits != 4) {
        fprintf(stderr, "LRU test failed: expected 9 faults and 4 hits, got %d faults and %d hits\n",
                result.page_faults, result.page_hits);
        return 1;
    }
    puts("LRU test passed (9 faults, 4 hits).");
    return 0;
}
