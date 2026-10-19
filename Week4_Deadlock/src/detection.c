//Ayman
#include <stdio.h>
#include "deadlock.h"

/*
 * Detect deadlocks using the current Request matrix.
 * Returns the number of deadlocked processes.
 * deadlocked[] receives their process IDs.
 */
int detectDeadlock(SystemState *state, int deadlocked[])
{
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int deadlockCount = 0;

    /* Initially, Work = Available */
    for (int j = 0; j < state->resourceCount; j++) {
        work[j] = state->available[j];
    }

    /* Processes holding no resources can finish immediately */
    for (int i = 0; i < state->processCount; i++) {
        int holdsResources = 0;

        for (int j = 0; j < state->resourceCount; j++) {
            if (state->allocation[i][j] > 0) {
                holdsResources = 1;
                break;
            }
        }

        finish[i] = !holdsResources;
    }

    /* Find processes whose current requests can be satisfied */
    int progress;

    do {
        progress = 0;

        for (int i = 0; i < state->processCount; i++) {
            if (finish[i]) {
                continue;
            }

            int canFinish = 1;

            for (int j = 0; j < state->resourceCount; j++) {
                if (state->request[i][j] > work[j]) {
                    canFinish = 0;
                    break;
                }
            }

            if (canFinish) {
                /* Simulate process completion and resource release */
                for (int j = 0; j < state->resourceCount; j++) {
                    work[j] += state->allocation[i][j];
                }

                finish[i] = 1;
                progress = 1;
            }
        }

    } while (progress);

    /* Remaining unfinished processes are deadlocked */
    for (int i = 0; i < state->processCount; i++) {
        if (!finish[i]) {
            deadlocked[deadlockCount++] = i;
        }
    }

    return deadlockCount;
}


/*
 * Recover by terminating a selected process.
 * Returns 1 on success, 0 for an invalid process ID.
 */
int recoverDeadlock(SystemState *state, int processId)
{
    if (processId < 0 || processId >= state->processCount) {
        return 0;
    }

    /* Release the resources held by the terminated process */
    for (int j = 0; j < state->resourceCount; j++) {
        state->available[j] +=
            state->allocation[processId][j];

        state->allocation[processId][j] = 0;
        state->request[processId][j] = 0;
        state->maximum[processId][j] = 0;
        state->need[processId][j] = 0;
    }

    printf("Process P%d terminated successfully.\n", processId);
    printf("Its allocated resources have been released.\n");

    return 1;
}
