#include <stdio.h>
#include "common.h"

int main(void)
{
    const int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    SimulationResult result;
    simulate_optimal(pages, 13, 3, &result);

    if (result.page_faults != 7 || result.page_hits != 6) {
        fprintf(stderr, "Optimal test failed: expected 7 faults and 6 hits, got %d faults and %d hits\n",
                result.page_faults, result.page_hits);
        return 1;
    }
    puts("Optimal test passed (7 faults, 6 hits).");
    return 0;
}
