//haneena

#include <stdio.h>
#include "deadlock.h"


/* Calculate Need = Maximum - Allocation */
void calculateNeed(SystemState *state)
{
    for (int i = 0; i < state->processCount; i++) {
        for (int j = 0; j < state->resourceCount; j++) {
            state->need[i][j] =
                state->maximum[i][j] -
                state->allocation[i][j];
        }
    }
}

/* Return 1 if safe, otherwise 0 */
int checkSafety(SystemState *state, int safeSequence[])
{
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int count = 0;

    for (int j = 0; j < state->resourceCount; j++) {
        work[j] = state->available[j];
    }

    calculateNeed(state);

    while (count < state->processCount) {
        int found = 0;

        for (int i = 0; i < state->processCount; i++) {
            if (finish[i]) {
                continue;
            }

            int possible = 1;

            for (int j = 0; j < state->resourceCount; j++) {
                if (state->need[i][j] > work[j]) {
                    possible = 0;
                    break;
                }
            }

            if (possible) {
                for (int j = 0; j < state->resourceCount; j++) {
                    work[j] += state->allocation[i][j];
                }

                safeSequence[count++] = i;
                finish[i] = 1;
                found = 1;
            }
        }

        if (!found) {
            return 0;
        }
    }

    return 1;
}


/* Request resources for a process.
   1 = granted, 0 = denied, -1 = invalid request */
int requestResources(
    SystemState *state,
    int processId,
    const int request[])
{
    if (processId < 0 || processId >= state->processCount) {
        return -1;
    }

    for (int j = 0; j < state->resourceCount; j++) {
        if (request[j] < 0 ||
            request[j] > state->need[processId][j]) {
            return -1;
        }

        if (request[j] > state->available[j]) {
            return 0;
        }
    }

    /* Temporarily allocate the requested resources */
    for (int j = 0; j < state->resourceCount; j++) {
        state->available[j] -= request[j];
        state->allocation[processId][j] += request[j];
    }

    calculateNeed(state);

    int safeSequence[MAX_PROCESSES];

    if (checkSafety(state, safeSequence)) {
        return 1;
    }

    /* Unsafe state: roll back the allocation */
    for (int j = 0; j < state->resourceCount; j++) {
        state->available[j] += request[j];
        state->allocation[processId][j] -= request[j];
    }

    calculateNeed(state);
    return 0;
}
