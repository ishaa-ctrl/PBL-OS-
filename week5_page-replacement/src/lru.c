#include "common.h"

void simulate_lru(const int pages[], int n, int frame_count,
                  SimulationResult *result)
{
    int frames[MAX_FRAMES];
    int last_used[MAX_FRAMES];

    result->total_refs = n;
    result->frame_count = frame_count;
    result->page_hits = 0;
    result->page_faults = 0;

    for (int j = 0; j < frame_count; j++) {
        frames[j] = -1;
        last_used[j] = -1;
    }

    for (int i = 0; i < n; i++) {
        int found = -1;

        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == pages[i]) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            result->hit[i] = 1;
            result->page_hits++;
            last_used[found] = i;
        } else {
            result->hit[i] = 0;
            result->page_faults++;

            int replace = -1;

            for (int j = 0; j < frame_count; j++) {
                if (frames[j] == -1) {
                    replace = j;
                    break;
                }
            }

            if (replace == -1) {
                replace = 0;

                for (int j = 1; j < frame_count; j++) {
                    if (last_used[j] < last_used[replace])
                        replace = j;
                }
            }

            frames[replace] = pages[i];
            last_used[replace] = i;
        }

        for (int j = 0; j < frame_count; j++)
            result->frames[i][j] = frames[j];
    }
}//ayman
