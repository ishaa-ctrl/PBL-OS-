
#ifndef DEADLOCK_H
#define DEADLOCK_H

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

typedef struct {
    int processCount;
    int resourceCount;
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int maximum[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int request[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
} SystemState;

void calculateNeed(SystemState *state);
int checkSafety(SystemState *state, int safeSequence[]);
int requestResources(SystemState *state, int processId, const int request[]);
int detectDeadlock(SystemState *state, int deadlocked[]);
int recoverDeadlock(SystemState *state, int processId);

void initializeGUI(void);
void runGUI(SystemState *state);
void displaySystemStatus(SystemState *state);
void displayRAG(SystemState *state);
void calculateUtilization(SystemState *state);

#endif
