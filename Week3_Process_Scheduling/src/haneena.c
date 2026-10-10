#include <stdio.h>
#include <string.h>
#include "scheduler.h"

/* Add one entry to the Gantt chart */
static void add_entry(GanttChart *chart, int pid, int start, int end)
{
    if (end <= start || chart->count >= MAX_GANTT_ENTRIES)
        return;

    GanttEntry *entry = &chart->entries[chart->count++];
    entry->pid = pid;
    entry->start_time = start;
    entry->end_time = end;
}

/* Copy input processes and reset calculated values */
static void initialize(const Process input[], int n,
                       Process output[], GanttChart *chart)
{
    memcpy(output, input, n * sizeof(Process));
    chart->count = 0;

    for (int i = 0; i < n; i++) {
        output[i].remaining_time = output[i].burst_time;
        output[i].completion_time = 0;
        output[i].turnaround_time = 0;
        output[i].waiting_time = 0;
        output[i].response_time = -1;
        output[i].first_start_time = -1;
    }
}

/* Calculate final metrics for a completed process */
static void finish(Process output[], int i, int time)
{
    output[i].completion_time = time;
    output[i].turnaround_time =
        time - output[i].arrival_time;

    output[i].waiting_time =
        output[i].turnaround_time - output[i].burst_time;

    output[i].response_time =
        output[i].first_start_time - output[i].arrival_time;

    output[i].remaining_time = 0;
}

/* FCFS: First Come, First Served */
void fcfs(const Process input[], int n,
          Process output[], GanttChart *chart)
{
    initialize(input, n, output, chart);

    int order[MAX_PROCESSES];

    for (int i = 0; i < n; i++)
        order[i] = i;

    /* Sort process indices by arrival time */
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (output[order[j]].arrival_time >
                output[order[j + 1]].arrival_time) {
                int temp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = temp;
            }
        }
    }

    int time = 0;

    for (int k = 0; k < n; k++) {
        int i = order[k];

        /* CPU remains idle until the next process arrives */
        if (time < output[i].arrival_time) {
            add_entry(chart, 0, time,
                      output[i].arrival_time);
            time = output[i].arrival_time;
        }

        output[i].first_start_time = time;
        output[i].response_time =
            time - output[i].arrival_time;

        int start = time;
        time += output[i].burst_time;

        add_entry(chart, output[i].pid, start, time);
        finish(output, i, time);
    }
}

/* Non-Preemptive SJF: Shortest Job First */
void sjf_non_preemptive(const Process input[], int n,
                        Process output[], GanttChart *chart)
{
    initialize(input, n, output, chart);

    int completed[MAX_PROCESSES] = {0};
    int finished = 0;
    int time = 0;

    while (finished < n) {
        int selected = -1;

        /* Select the shortest available process */
        for (int i = 0; i < n; i++) {
            if (!completed[i] &&
                output[i].arrival_time <= time) {

                if (selected == -1 ||
                    output[i].burst_time <
                    output[selected].burst_time ||
                    (output[i].burst_time ==
                     output[selected].burst_time &&
                     output[i].arrival_time <
                     output[selected].arrival_time)) {
                    selected = i;
                }
            }
        }

        /* No process has arrived yet */
        if (selected == -1) {
            int next_arrival = -1;

            for (int i = 0; i < n; i++) {
                if (!completed[i] &&
                    (next_arrival == -1 ||
                     output[i].arrival_time <
                     output[next_arrival].arrival_time)) {
                    next_arrival = i;
                }
            }

            if (next_arrival == -1)
                break;

            add_entry(chart, 0, time,
                      output[next_arrival].arrival_time);
            time = output[next_arrival].arrival_time;
            continue;
        }

        output[selected].first_start_time = time;
        output[selected].response_time =
            time - output[selected].arrival_time;

        int start = time;
        time += output[selected].burst_time;

        add_entry(chart, output[selected].pid, start, time);
        finish(output, selected, time);

        completed[selected] = 1;
        finished++;
    }
}

