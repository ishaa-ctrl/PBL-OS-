#include <stdio.h>
#include "common.h"

int main(void)
{
    const int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    SimulationResult result;
    simulate_fifo(pages, 13, 3, &result);

    if (result.page_faults != 10 || result.page_hits != 3) {
        fprintf(stderr, "FIFO test failed: expected 10 faults and 3 hits, got %d faults and %d hits\n",
                result.page_faults, result.page_hits);
        return 1;
    }
    puts("FIFO test passed (10 faults, 3 hits).");
    return 0;
}
