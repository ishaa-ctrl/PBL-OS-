//haneena

#include <stdio.h>
#include "deadlock.h"

void calculateNeed(SystemState *state)
{
    for (int i = 0; i < state->processCount; i++) {
        for (int j = 0; j < state->resourceCount; j++) {
            state->need[i][j] =
                state->maximum[i][j] - state->allocation[i][j];
        }
    }
}

int checkSafety(SystemState *state, int safeSequence[])
{
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};

    calculateNeed(state);

    for (int j = 0; j < state->resourceCount; j++)
        work[j] = state->available[j];

    int completed = 0;

    while (completed < state->processCount) {
        int found = 0;

        for (int i = 0; i < state->processCount; i++) {
            if (finish[i])
                continue;

            int canFinish = 1;

            for (int j = 0; j < state->resourceCount; j++) {
                if (state->need[i][j] > work[j]) {
                    canFinish = 0;
                    break;
                }
            }

            if (canFinish) {
                for (int j = 0; j < state->resourceCount; j++)
                    work[j] += state->allocation[i][j];

                safeSequence[completed++] = i;
                finish[i] = 1;
                found = 1;
            }
        }

        if (!found)
            return 0;
    }

    return 1;
}

/* Returns 1 = granted, 0 = denied, -1 = invalid request. */
int requestResources(SystemState *state, int processId,
                     const int request[])
{
    if (state == NULL || request == NULL ||
        processId < 0 || processId >= state->processCount)
        return -1;

    calculateNeed(state);

    for (int j = 0; j < state->resourceCount; j++) {
        if (request[j] < 0 ||
            request[j] > state->need[processId][j])
            return -1;

        if (request[j] > state->available[j])
            return 0;
    }

    /* Temporarily grant the request. */
    for (int j = 0; j < state->resourceCount; j++) {
        state->available[j] -= request[j];
        state->allocation[processId][j] += request[j];
        state->need[processId][j] -= request[j];
    }

    int sequence[MAX_PROCESSES];

    if (checkSafety(state, sequence))
        return 1;

    /* Roll back if the new state is unsafe. */
    for (int j = 0; j < state->resourceCount; j++) {
        state->available[j] += request[j];
        state->allocation[processId][j] -= request[j];
        state->need[processId][j] += request[j];
    }

    return 0;
}
