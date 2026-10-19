//Header
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
    int available[MAX_RESOURCES];
} SystemState;

/* Haneena: Banker's Algorithm */
void calculateNeed(SystemState *state);
int checkSafety(SystemState *state, int safeSequence[]);
int requestResources(
    SystemState *state,
    int processId,
    const int request[]
);

/* Ayman: Deadlock detection and recovery */
int detectDeadlock(SystemState *state, int deadlocked[]);
int recoverDeadlock(SystemState *state, int processId);

/* Vishnu: GUI */
void initializeGUI(void);
void runGUI(void);
void displaySystemStatus(SystemState *state);

/* Team Leader: RAG and resource utilization */
void displayRAG(SystemState *state);
void calculateUtilization(SystemState *state);

#endif
