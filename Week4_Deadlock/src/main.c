
#include <stdio.h>
#include "deadlock.h"

int main(void)
{
    SystemState state = {0};

    printf("=== Deadlock Simulation System ===\n");

    printf("Enter number of processes (1-%d): ", MAX_PROCESSES);
    if (scanf("%d", &state.processCount) != 1 ||
        state.processCount < 1 ||
        state.processCount > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter number of resource types (1-%d): ", MAX_RESOURCES);
    if (scanf("%d", &state.resourceCount) != 1 ||
        state.resourceCount < 1 ||
        state.resourceCount > MAX_RESOURCES) {
        printf("Invalid number of resources.\n");
        return 1;
    }

    for (int i = 0; i < state.processCount; i++) {
        for (int j = 0; j < state.resourceCount; j++) {
            printf("Allocation P%d R%d: ", i, j);
            if (scanf("%d", &state.allocation[i][j]) != 1 ||
                state.allocation[i][j] < 0) {
                printf("Invalid allocation.\n");
                return 1;
            }
        }
    }

    for (int i = 0; i < state.processCount; i++) {
        for (int j = 0; j < state.resourceCount; j++) {
            printf("Maximum P%d R%d: ", i, j);
            if (scanf("%d", &state.maximum[i][j]) != 1 ||
                state.maximum[i][j] < state.allocation[i][j]) {
                printf("Invalid maximum demand.\n");
                return 1;
            }
        }
    }

    for (int j = 0; j < state.resourceCount; j++) {
        printf("Available R%d: ", j);
        if (scanf("%d", &state.available[j]) != 1 ||
            state.available[j] < 0) {
            printf("Invalid available resources.\n");
            return 1;
        }
    }

    calculateNeed(&state);
    runGUI(&state);

    return 0;
}
