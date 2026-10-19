
#include <stdio.h>
#include "deadlock.h"

void displayRAG(SystemState *state)
{
    printf("\n=== Resource Allocation Graph ===\n");

    for (int i = 0; i < state->processCount; i++) {
        for (int j = 0; j < state->resourceCount; j++) {
            if (state->allocation[i][j] > 0) {
                printf("R%d -> P%d (allocated: %d)\n",
                       j, i, state->allocation[i][j]);
            }

            if (state->request[i][j] > 0) {
                printf("P%d -> R%d (requested: %d)\n",
                       i, j, state->request[i][j]);
            }
        }
    }
}

void calculateUtilization(SystemState *state)
{
    printf("\n=== Resource Utilization ===\n");

    for (int j = 0; j < state->resourceCount; j++) {
        int allocated = 0;

        for (int i = 0; i < state->processCount; i++) {
            allocated += state->allocation[i][j];
        }

        int total = allocated + state->available[j];

        if (total > 0) {
            printf("Resource R%d: %d/%d units allocated (%.2f%%)\n",
                   j, allocated, total,
                   100.0 * allocated / total);
        } else {
            printf("Resource R%d: no units available in the system\n", j);
        }
    }
}

