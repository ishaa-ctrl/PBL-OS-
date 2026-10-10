#include <string.h>
#include "scheduler.h"

/* Add a segment to the Gantt chart */
static void add_entry(GanttChart *chart, int pid, int start, int end)
{
    if (end <= start || chart->count >= MAX_GANTT_ENTRIES)
        return;

    GanttEntry *entry = &chart->entries[chart->count++];
    entry->pid = pid;
    entry->start_time = start;
    entry->end_time = end;
}

/* Initialize process data and chart */
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

/* Calculate metrics for a completed process */
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

/* Non-Preemptive Priority Scheduling
   Lower numeric value means higher priority. */
void priority_non_preemptive(const Process input[], int n,
                             Process output[], GanttChart *chart)
{
    initialize(input, n, output, chart);

    int completed[MAX_PROCESSES] = {0};
    int finished = 0;
    int time = 0;

    while (finished < n) {
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (completed[i] ||
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

        /* If no process is ready, advance to the next arrival */
        if (selected == -1) {
            int next = -1;

            for (int i = 0; i < n; i++) {
                if (!completed[i] &&
                    (next == -1 ||
                     output[i].arrival_time <
                         output[next].arrival_time)) {
                    next = i;
                }
            }

            if (next == -1)
                break;

            add_entry(chart, 0, time, output[next].arrival_time);
            time = output[next].arrival_time;
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

/* Round Robin Scheduling */
void round_robin(const Process input[], int n, int quantum,
                 Process output[], GanttChart *chart)
{
    initialize(input, n, output, chart);

    if (quantum <= 0)
        return;

    int queue[MAX_GANTT_ENTRIES];
    int front = 0;
    int rear = 0;
    int queued[MAX_PROCESSES] = {0};
    int completed[MAX_PROCESSES] = {0};
    int finished = 0;
    int time = 0;

    /* Start at the earliest arrival time */
    int earliest = 0;
    for (int i = 1; i < n; i++) {
        if (output[i].arrival_time < output[earliest].arrival_time)
            earliest = i;
    }
    time = output[earliest].arrival_time;

    /* Enqueue processes that have arrived */
    for (int i = 0; i < n; i++) {
        if (output[i].arrival_time <= time && !queued[i]) {
            queue[rear++] = i;
            queued[i] = 1;
        }
    }

    while (finished < n) {
        if (front == rear) {
            int next_time = -1;

            for (int i = 0; i < n; i++) {
                if (!completed[i] &&
                    !queued[i] &&
                    (next_time == -1 ||
                     output[i].arrival_time < next_time)) {
                    next_time = output[i].arrival_time;
                }
            }

            if (next_time == -1)
                break;

            add_entry(chart, 0, time, next_time);
            time = next_time;

            for (int i = 0; i < n; i++) {
                if (!completed[i] && !queued[i] &&
                    output[i].arrival_time <= time) {
                    queue[rear++] = i;
                    queued[i] = 1;
                }
            }
            continue;
        }

        int current = queue[front++];

        if (output[current].first_start_time == -1) {
            output[current].first_start_time = time;
            output[current].response_time =
                time - output[current].arrival_time;
        }

        int run = output[current].remaining_time < quantum
                    ? output[current].remaining_time
                    : quantum;

        int start = time;
        time += run;
        output[current].remaining_time -= run;

        add_entry(chart, output[current].pid, start, time);

        /* Enqueue processes arriving during this time slice */
        for (int i = 0; i < n; i++) {
            if (!completed[i] && !queued[i] &&
                output[i].arrival_time <= time) {
                queue[rear++] = i;
                queued[i] = 1;
            }
        }

        if (output[current].remaining_time == 0) {
            finish(output, current, time);
            completed[current] = 1;
            finished++;
        } else {
            queue[rear++] = current;
        }
    }
}#
