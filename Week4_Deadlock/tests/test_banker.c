
#include <assert.h>
#include <stdio.h>
#include "../include/deadlock.h"

static void setupState(SystemState *state)
{
    *state = (SystemState){0};

    state->processCount = 5;
    state->resourceCount = 3;

    int allocation[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int maximum[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int available[3] = {3, 3, 2};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            state->allocation[i][j] = allocation[i][j];
            state->maximum[i][j] = maximum[i][j];
        }
    }

    for (int j = 0; j < 3; j++) {
        state->available[j] = available[j];
    }

    calculateNeed(state);
}

int main(void)
{
    SystemState state;
    int safeSequence[MAX_PROCESSES];

    setupState(&state);

    assert(checkSafety(&state, safeSequence) == 1);
    printf("PASS: Safe state detected.\n");

    setupState(&state);

    int request[MAX_RESOURCES] = {1, 0, 2};
    assert(requestResources(&state, 1, request) == 1);
    printf("PASS: Valid resource request accepted.\n");

    setupState(&state);

    int invalidRequest[MAX_RESOURCES] = {4, 0, 0};
    assert(requestResources(&state, 0, invalidRequest) == -1);
    printf("PASS: Invalid resource request rejected.\n");

    printf("All Banker's Algorithm tests passed.\n");
    return 0;
}

