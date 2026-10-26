//haneena

#include "common.h"

void simulate_fifo(const int pages[], int n, int frame_count,
                   SimulationResult *result)
{
    int frames[MAX_FRAMES];
    int next = 0;

    result->total_refs = n;
    result->frame_count = frame_count;
    result->page_hits = 0;
    result->page_faults = 0;

    for (int j = 0; j < frame_count; j++)
        frames[j] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (found) {
            result->hit[i] = 1;
            result->page_hits++;
        } else {
            result->hit[i] = 0;
            result->page_faults++;

            frames[next] = pages[i];
            next = (next + 1) % frame_count;
        }

        for (int j = 0; j < frame_count; j++)
            result->frames[i][j] = frames[j];
    }
}
