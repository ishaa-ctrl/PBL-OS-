#include <stdio.h>
#include "matrix_view.h"

void displayAllocationMatrix(SystemState *state)
{
    if (state == NULL) return;

    printf("\nAllocation Matrix:\n");

    for (int i = 0; i < state->processCount; i++) {
        printf("P%d: ", i);

        for (int j = 0; j < state->resourceCount; j++) {
            printf("%d ", state->allocation[i][j]);
        }

        printf("\n");
    }
}

void displayMaximumMatrix(SystemState *state)
{
    if (state == NULL) return;

    printf("\nMaximum Matrix:\n");

    for (int i = 0; i < state->processCount; i++) {
        printf("P%d: ", i);

        for (int j = 0; j < state->resourceCount; j++) {
            printf("%d ", state->maximum[i][j]);
        }

        printf("\n");
    }
}

void displayNeedMatrix(SystemState *state)
{
    if (state == NULL) return;

    calculateNeed(state);

    printf("\nNeed Matrix:\n");

    for (int i = 0; i < state->processCount; i++) {
        printf("P%d: ", i);

        for (int j = 0; j < state->resourceCount; j++) {
            printf("%d ", state->need[i][j]);
        }

        printf("\n");
    }
}

void displayAvailableVector(SystemState *state)
{
    if (state == NULL) return;

    printf("\nAvailable Resources:\n");

    for (int j = 0; j < state->resourceCount; j++) {
        printf("R%d: %d\n", j, state->available[j]);
    }
}
