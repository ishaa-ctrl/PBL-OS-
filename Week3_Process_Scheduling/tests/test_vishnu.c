#include <stdio.h>
#include "scheduler.h"

static void print_results(const char *name,
                          Process processes[],
                          int n,
                          const GanttChart *chart)
{
    double total_wt = 0;
    double total_tat = 0;

    printf("\n========== %s ==========\n", name);
    printf("Gantt Chart:\n");

    for (int i = 0; i < chart->count; i++) {
        const GanttEntry *entry = &chart->entries[i];

        if (entry->pid == 0)
            printf("| IDLE (%d-%d) ",
                   entry->start_time, entry->end_time);
        else
            printf("| P%d (%d-%d) ",
                   entry->pid, entry->start_time, entry->end_time);
    }
    printf("|\n");

    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time,
               processes[i].response_time);

        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main(void)
{
    Process input[] = {
        {.pid = 1, .arrival_time = 0, .burst_time = 5, .priority = 2},
        {.pid = 2, .arrival_time = 1, .burst_time = 3, .priority = 1},
        {.pid = 3, .arrival_time = 2, .burst_time = 1, .priority = 3}
    };

    int n = sizeof(input) / sizeof(input[0]);
    Process output[MAX_PROCESSES];
    GanttChart chart;

    priority_non_preemptive(input, n, output, &chart);
    print_results("Non-Preemptive Priority", output, n, &chart);

    round_robin(input, n, 2, output, &chart);
    print_results("Round Robin (Quantum = 2)", output, n, &chart);

    return 0;
}