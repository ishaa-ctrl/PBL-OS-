#include <stdio.h>
#include "graph_view.h"

void graphViewDisplay(SystemState *state)
{
    if (state == NULL) return;

    printf("\n===== RESOURCE ALLOCATION GRAPH =====\n");

    printf("\nAllocation edges (Resource -> Process):\n");

    for (int i = 0; i < state->processCount; i++) {
        for (int j = 0; j < state->resourceCount; j++) {
            if (state->allocation[i][j] > 0) {
                printf("R%d -> P%d (%d unit(s))\n",
                       j, i, state->allocation[i][j]);
            }
        }
    }

    printf("\nOutstanding request edges (Process -> Resource):\n");

    for (int i = 0; i < state->processCount; i++) {
        for (int j = 0; j < state->resourceCount; j++) {
            if (state->request[i][j] > 0) {
                printf("P%d -> R%d (%d unit(s))\n",
                       i, j, state->request[i][j]);
            }
        }
    }

    printf("=====================================\n");
}
