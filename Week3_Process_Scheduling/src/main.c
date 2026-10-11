
#include <stdio.h>
#include <string.h>
#include "scheduler.h"

static void display_results(const Process output[], int n,
                            const GanttChart *chart)
{
    double total_wt = 0;
    double total_tat = 0;

    printf("\n========== GANTT CHART ==========\n");

    for (int i = 0; i < chart->count; i++) {
        if (chart->entries[i].pid == 0) {
            printf("| IDLE (%d-%d) ",
                   chart->entries[i].start_time,
                   chart->entries[i].end_time);
        } else {
            printf("| P%d (%d-%d) ",
                   chart->entries[i].pid,
                   chart->entries[i].start_time,
                   chart->entries[i].end_time);
        }
    }
    printf("|\n");

    printf("\n========== PROCESS METRICS ==========\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               output[i].pid,
               output[i].arrival_time,
               output[i].burst_time,
               output[i].priority,
               output[i].completion_time,
               output[i].turnaround_time,
               output[i].waiting_time,
               output[i].response_time);

        total_wt += output[i].waiting_time;
        total_tat += output[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main(void)
{
    Process input[MAX_PROCESSES];
    Process output[MAX_PROCESSES];
    GanttChart chart;
    int choice;
    int n;
    int quantum;

    printf("====================================\n");
    printf("   CPU PROCESS SCHEDULING SIMULATOR\n");
    printf("====================================\n");

    printf("\nEnter number of processes (1-%d): ",
           MAX_PROCESSES);

    if (scanf("%d", &n) != 1 ||
        n < 1 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        input[i].pid = i + 1;

        printf("\nProcess P%d\n", i + 1);
        printf("Arrival time: ");

        if (scanf("%d", &input[i].arrival_time) != 1 ||
            input[i].arrival_time < 0) {
            printf("Invalid arrival time.\n");
            return 1;
        }

        printf("Burst time: ");

        if (scanf("%d", &input[i].burst_time) != 1 ||
            input[i].burst_time <= 0) {
            printf("Burst time must be positive.\n");
            return 1;
        }

        printf("Priority (smaller number = higher priority): ");

        if (scanf("%d", &input[i].priority) != 1) {
            printf("Invalid priority.\n");
            return 1;
        }

        input[i].remaining_time = input[i].burst_time;
        input[i].completion_time = 0;
        input[i].turnaround_time = 0;
        input[i].waiting_time = 0;
        input[i].response_time = -1;
        input[i].first_start_time = -1;
    }

    printf("\n========== SCHEDULING MENU ==========\n");
    printf("1. First Come First Serve (FCFS)\n");
    printf("2. Shortest Job First (Non-preemptive)\n");
    printf("3. Shortest Remaining Time First (Preemptive SJF)\n");
    printf("4. Priority Scheduling (Preemptive)\n");
    printf("5. Priority Scheduling (Non-preemptive)\n");
    printf("6. Round Robin\n");
    printf("0. Exit\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid choice.\n");
        return 1;
    }

    if (choice == 0) {
        printf("Exiting simulator.\n");
        return 0;
    }

    if (choice < 1 || choice > 6) {
        printf("Invalid choice.\n");
        return 1;
    }

    if (choice == 6) {
        printf("Enter time quantum: ");

        if (scanf("%d", &quantum) != 1 || quantum <= 0) {
            printf("Time quantum must be positive.\n");
            return 1;
        }
    }

    memset(&chart, 0, sizeof(chart));
    memset(output, 0, sizeof(output));

    switch (choice) {
        case 1:
            fcfs(input, n, output, &chart);
            printf("\nAlgorithm: FCFS\n");
            break;

        case 2:
            sjf_non_preemptive(input, n, output, &chart);
            printf("\nAlgorithm: Non-preemptive SJF\n");
            break;

        case 3:
            sjf_preemptive(input, n, output, &chart);
            printf("\nAlgorithm: Preemptive SJF (SRTF)\n");
            break;

        case 4:
            priority_preemptive(input, n, output, &chart);
            printf("\nAlgorithm: Preemptive Priority\n");
            break;

        case 5:
            priority_non_preemptive(input, n, output, &chart);
            printf("\nAlgorithm: Non-preemptive Priority\n");
            break;

        case 6:
            round_robin(input, n, quantum, output, &chart);
            printf("\nAlgorithm: Round Robin\n");
            break;
    }

    display_results(output, n, &chart);

    return 0;
}
