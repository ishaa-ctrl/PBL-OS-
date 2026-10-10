#include <string.h>
#include "scheduler.h"

/* Add an interval to the Gantt chart */
static void add_entry(GanttChart *chart, int pid, int start, int end)
{
    if (end <= start || chart->count >= MAX_GANTT_ENTRIES)
        return;

    GanttEntry *entry = &chart->entries[chart->count++];
    entry->pid = pid;
    entry->start_time = start;
    entry->end_time = end;
}

/* Copy input and reset calculated fields */
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

/* Calculate metrics when a process finishes */
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

/* Preemptive SJF: Shortest Remaining Time First */
void sjf_preemptive(const Process input[], int n,
                    Process output[], GanttChart *chart)
{
    initialize(input, n, output, chart);

    int completed = 0;
    int time = 0;
    int previous = -1;

    while (completed < n) {
        int selected = -1;

        /* Choose the arrived process with the shortest remaining time */
        for (int i = 0; i < n; i++) {
            if (output[i].remaining_time <= 0 ||
                output[i].arrival_time > time)
                continue;

            if (selected == -1 ||
                output[i].remaining_time <
                    output[selected].remaining_time ||
                (output[i].remaining_time ==
                     output[selected].remaining_time &&
                 output[i].arrival_time <
                     output[selected].arrival_time)) {
                selected = i;
            }
        }

        /* CPU is idle until a process arrives */
        if (selected == -1) {
            if (previous == 0 && chart->count > 0 &&
                chart->entries[chart->count - 1].end_time == time) {
                chart->entries[chart->count - 1].end_time++;
            } else {
                add_entry(chart, 0, time, time + 1);
            }

            previous = 0;
            time++;
            continue;
        }

        if (output[selected].first_start_time == -1) {
            output[selected].first_start_time = time;
            output[selected].response_time =
                time - output[selected].arrival_time;
        }

        /* Merge consecutive time units for the same process */
        if (previous == output[selected].pid &&
            chart->count > 0 &&
            chart->entries[chart->count - 1].end_time == time) {
            chart->entries[chart->count - 1].end_time++;
        } else {
            add_entry(chart, output[selected].pid, time, time + 1);
        }

        output[selected].remaining_time--;
        time++;
        previous = output[selected].pid;

        if (output[selected].remaining_time == 0) {
            finish(output, selected, time);
            completed++;
        }
    }
}

/* Preemptive Priority Scheduling
   Lower numeric priority means higher priority. */
void priority_preemptive(const Process input[], int n,
                         Process output[], GanttChart *chart)
{
    initialize(input, n, output, chart);

    int completed = 0;
    int time = 0;
    int previous = -1;

    while (completed < n) {
        int selected = -1;

        /* Choose the highest-priority arrived process */
        for (int i = 0; i < n; i++) {
            if (output[i].remaining_time <= 0 ||
                output[i].arrival_time > time)
                continue;

            if (selected == -1 ||
                output[i].priority < output[selected].priority ||
                (output[i].priority == output[selected].priority &&
                 output[i].arrival_time <
                     output[selected].arrival_time)) {
                selected = i;
            }
        }

        /* CPU idle period */
        if (selected == -1) {
            if (previous == 0 && chart->count > 0 &&
                chart->entries[chart->count - 1].end_time == time) {
                chart->entries[chart->count - 1].end_time++;
            } else {
                add_entry(chart, 0, time, time + 1);
            }

            previous = 0;
            time++;
            continue;
        }

        if (output[selected].first_start_time == -1) {
            output[selected].first_start_time = time;
            output[selected].response_time =
                time - output[selected].arrival_time;
        }

        if (previous == output[selected].pid &&
            chart->count > 0 &&
            chart->entries[chart->count - 1].end_time == time) {
            chart->entries[chart->count - 1].end_time++;
        } else {
            add_entry(chart, output[selected].pid, time, time + 1);
        }

        output[selected].remaining_time--;
        time++;
        previous = output[selected].pid;

        if (output[selected].remaining_time == 0) {
            finish(output, selected, time);
            completed++;
        }
    }
}
