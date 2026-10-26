#include "common.h"

void simulate_optimal(const int pages[], int n, int frame_count,
                      SimulationResult *result)
{
    int frames[MAX_FRAMES];

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

            int replace = -1;

            for (int j = 0; j < frame_count; j++) {
                if (frames[j] == -1) {
                    replace = j;
                    break;
                }
            }

            if (replace == -1) {
                int farthest = -1;

                for (int j = 0; j < frame_count; j++) {
                    int next_use = n;

                    for (int k = i + 1; k < n; k++) {
                        if (pages[k] == frames[j]) {
                            next_use = k;
                            break;
                        }
                    }

                    if (next_use > farthest) {
                        farthest = next_use;
                        replace = j;
                    }
                }
            }

            frames[replace] = pages[i];
        }

        for (int j = 0; j < frame_count; j++)
            result->frames[i][j] = frames[j];
    }
}//vishnu
