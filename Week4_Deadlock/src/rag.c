#include <math.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "deadlock.h"

static SystemState *ragState;

static void drawLabel(HDC dc, int x, int y, const char *text)
{
    TextOutA(dc, x, y, text, (int)strlen(text));
}

static void drawArrow(HDC dc, int x1, int y1, int x2, int y2)
{
    MoveToEx(dc, x1, y1, NULL);
    LineTo(dc, x2, y2);

    double angle = atan2((double)(y2 - y1), (double)(x2 - x1));
    int length = 9;

    int ax = x2 - (int)(length * cos(angle - 0.5));
    int ay = y2 - (int)(length * sin(angle - 0.5));
    int bx = x2 - (int)(length * cos(angle + 0.5));
    int by = y2 - (int)(length * sin(angle + 0.5));

    MoveToEx(dc, x2, y2, NULL);
    LineTo(dc, ax, ay);
    MoveToEx(dc, x2, y2, NULL);
    LineTo(dc, bx, by);
}

static LRESULT CALLBACK RAGWindowProc(
    HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    (void)wp;
    (void)lp;

    if (msg == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(hwnd, &ps);

        TextOutA(dc, 20, 15, "RESOURCE ALLOCATION GRAPH", 25);

        if (ragState != NULL) {
            int n = ragState->processCount;
            int m = ragState->resourceCount;
            int spacing = 100;
            int startX = 40;

            for (int i = 0; i < n; i++) {
                int x = startX + i * spacing;
                Ellipse(dc, x, 70, x + 48, 118);

                char label[20];
                snprintf(label, sizeof(label), "P%d", i);
                drawLabel(dc, x + 14, 87, label);
            }

            for (int j = 0; j < m; j++) {
                int x = startX + j * spacing;
                Rectangle(dc, x, 230, x + 48, 278);

                char label[20];
                snprintf(label, sizeof(label), "R%d", j);
                drawLabel(dc, x + 14, 247, label);
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    int px = startX + i * spacing + 24;
                    int rx = startX + j * spacing + 24;

                    if (ragState->allocation[i][j] > 0)
                        drawArrow(dc, rx, 230, px, 118);

                    if (ragState->request[i][j] > 0)
                        drawArrow(dc, px, 118, rx, 230);
                }
            }

            drawLabel(dc, 20, 315, "Arrow R -> P: allocated resource");
            drawLabel(dc, 20, 340, "Arrow P -> R: resource request");
        }

        EndPaint(hwnd, &ps);
        return 0;
    }

    if (msg == WM_DESTROY)
        return 0;

    return DefWindowProcA(hwnd, msg, wp, lp);
}

void displayRAG(SystemState *state)
{
    ragState = state;

    HINSTANCE instance = GetModuleHandleA(NULL);
    WNDCLASSA wc = {0};

    wc.lpfnWndProc = RAGWindowProc;
    wc.hInstance = instance;
    wc.lpszClassName = "RAGWindowClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassA(&wc);

    HWND hwnd = CreateWindowA(
        wc.lpszClassName,
        "Resource Allocation Graph",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 420,
        NULL, NULL, instance, NULL);

    if (hwnd != NULL) {
        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);
    }
}

void calculateUtilization(SystemState *state)
{
    for (int j = 0; j < state->resourceCount; j++) {
        int allocated = 0;

        for (int i = 0; i < state->processCount; i++)
            allocated += state->allocation[i][j];

        int total = allocated + state->available[j];
        double percent = total > 0
            ? 100.0 * allocated / total : 0.0;

        printf("R%d: %d/%d allocated (%.1f%%)\n",
               j, allocated, total, percent);
    }
}
