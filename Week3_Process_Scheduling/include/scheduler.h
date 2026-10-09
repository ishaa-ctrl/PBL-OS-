#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX_PROCESSES 100
#define MAX_GANTT_ENTRIES 10000

/* Common process structure used by everyone */
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;

    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int first_start_time;
} Process;

/* Stores one CPU execution interval */
typedef struct {
    int pid;  /* PID 0 represents CPU idle time */
    int start_time;
    int end_time;
} GanttEntry;

/* Stores the complete Gantt chart */
typedef struct {
    GanttEntry entries[MAX_GANTT_ENTRIES];
    int count;
} GanttChart;

/* Haneena: FCFS and non-preemptive SJF */
void fcfs(const Process input[], int n,
          Process output[], GanttChart *chart);

void sjf_non_preemptive(const Process input[], int n,
                        Process output[], GanttChart *chart);

/* Ayman: Preemptive SJF and preemptive Priority */
void sjf_preemptive(const Process input[], int n,
                    Process output[], GanttChart *chart);

void priority_preemptive(const Process input[], int n,
                         Process output[], GanttChart *chart);

/* Vishnu: Non-preemptive Priority and Round Robin */
void priority_non_preemptive(const Process input[], int n,
                             Process output[], GanttChart *chart);

void round_robin(const Process input[], int n, int quantum,
                 Process output[], GanttChart *chart);

#endif
