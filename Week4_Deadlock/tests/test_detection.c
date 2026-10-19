
#include <assert.h>
#include <stdio.h>
#include "../include/deadlock.h"

int main(void)
{
    SystemState state = {0};
    int deadlocked[MAX_PROCESSES];

    state.processCount = 2;
    state.resourceCount = 2;

    state.allocation[0][0] = 1;
    state.allocation[1][1] = 1;

    state.request[0][1] = 1;
    state.request[1][0] = 1;

    state.available[0] = 0;
    state.available[1] = 0;

    int count = detectDeadlock(&state, deadlocked);

    assert(count == 2);
    printf("PASS: Deadlock detected.\n");

    assert(recoverDeadlock(&state, 0) == 1);
    printf("PASS: Recovery function executed.\n");

    printf("All deadlock detection tests passed.\n");
    return 0;
}
