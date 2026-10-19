#include <stdio.h>
#include "dashboard.h"

void dashboardShowStatus(SystemState *state)
{
    if (state == NULL) {
        printf("System state is not available.\n");
        return;
    }

    printf("\n===== DEADLOCK SIMULATION DASHBOARD =====\n");
    printf("Processes: %d\n", state->processCount);
    printf("Resources: %d\n", state->resourceCount);

    printf("\nAvailable Resources:\n");
    for (int j = 0; j < state->resourceCount; j++) {
        printf("R%d: %d\n", j, state->available[j]);
    }

    printf("\n=========================================\n");
}

void dashboardShowSafety(SystemState *state)
{
    int sequence[MAX_PROCESSES];

    if (state == NULL) {
        return;
    }

    if (checkSafety(state, sequence)) {
        printf("System State: SAFE\nSafe Sequence: ");

        for (int i = 0; i < state->processCount; i++) {
            printf("P%d%s", sequence[i],
                   i == state->processCount - 1 ? "\n" : " -> ");
        }
    } else {
        printf("System State: UNSAFE\n");
    }
}

void dashboardShowDeadlock(SystemState *state)
{
    int deadlocked[MAX_PROCESSES];

    if (state == NULL) {
        return;
    }

    int count = detectDeadlock(state, deadlocked);

    if (count == 0) {
        printf("No deadlocked processes found.\n");
        return;
    }

    printf("Deadlocked Processes:\n");

    for (int i = 0; i < count; i++) {
        printf("P%d\n", deadlocked[i]);
    }
}
