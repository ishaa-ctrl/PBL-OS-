#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "common.h"

#define ID_PAGES 101
#define ID_FRAMES 102
#define ID_COMPARE 103
#define ID_OUTPUT 104

static HWND hPages, hFrames, hOutput;
static HFONT hFont;

static void append_text(char *buffer, size_t capacity, const char *format, ...)
{
    size_t used = strlen(buffer);
    if (used >= capacity - 1) return;
    va_list args;
    va_start(args, format);
    vsnprintf(buffer + used, capacity - used, format, args);
    va_end(args);
}

static int parse_pages(const char *text, int pages[], int max_pages)
{
    int count = 0;
    const char *p = text;
    while (*p) {
        while (*p == ' ' || *p == ',' || *p == '\t' || *p == '\r' || *p == '\n') p++;
        if (!*p) break;
        char *end = NULL;
        long value = strtol(p, &end, 10);
        if (end == p || value < 0 || value > 2147483647L || count >= max_pages) return -1;
        pages[count++] = (int)value;
        p = end;
        if (*p && *p != ' ' && *p != ',' && *p != '\t' && *p != '\r' && *p != '\n') return -1;
    }
    return count;
}

static void show_one(char *out, size_t cap, const char *name,
                     const int pages[], const SimulationResult *r)
{
    append_text(out, cap, "\r\n=== %s ===\r\nPage  ", name);
    for (int j = 0; j < r->frame_count; ++j) append_text(out, cap, "F%d  ", j + 1);
    append_text(out, cap, "Status\r\n");
    for (int i = 0; i < r->total_refs; ++i) {
        append_text(out, cap, "%-5d ", pages[i]);
        for (int j = 0; j < r->frame_count; ++j) {
            if (r->frames[i][j] == -1) append_text(out, cap, "-   ");
            else append_text(out, cap, "%-4d", r->frames[i][j]);
        }
        append_text(out, cap, "%s\r\n", r->hit[i] ? "HIT" : "FAULT");
    }
    append_text(out, cap, "Hits: %d   Faults: %d   Hit ratio: %.2f%%   Fault ratio: %.2f%%\r\n",
        r->page_hits, r->page_faults, 100.0 * r->page_hits / r->total_refs,
        100.0 * r->page_faults / r->total_refs);
}

static void run_comparison(void)
{
    char page_text[8192], frame_text[32];
    int pages[MAX_REFERENCES];
    SimulationResult results[3];
    char output[60000] = "";
    GetWindowTextA(hPages, page_text, (int)sizeof(page_text));
    GetWindowTextA(hFrames, frame_text, (int)sizeof(frame_text));
    int n = parse_pages(page_text, pages, MAX_REFERENCES);
    char *end = NULL;
    long frame_count = strtol(frame_text, &end, 10);
    if (n < 1) {
        MessageBoxA(NULL, "Enter page numbers separated by spaces or commas (up to 1000).",
                    "Invalid page reference string", MB_OK | MB_ICONWARNING);
        return;
    }
    if (end == frame_text || *end != '\0' || frame_count < 1 || frame_count > MAX_FRAMES) {
        MessageBoxA(NULL, "Enter a frame count from 1 to 100.",
                    "Invalid frame count", MB_OK | MB_ICONWARNING);
        return;
    }
    simulate_fifo(pages, n, (int)frame_count, &results[0]);
    simulate_lru(pages, n, (int)frame_count, &results[1]);
    simulate_optimal(pages, n, (int)frame_count, &results[2]);
    append_text(output, sizeof(output),
        "PAGE REPLACEMENT ALGORITHM SIMULATOR\r\nReferences: %d    Frames: %ld\r\n"
        "HIT = page already in memory; FAULT = page must be loaded.\r\n", n, frame_count);
    show_one(output, sizeof(output), "FIFO", pages, &results[0]);
    show_one(output, sizeof(output), "LRU", pages, &results[1]);
    show_one(output, sizeof(output), "OPTIMAL", pages, &results[2]);
    append_text(output, sizeof(output), "\r\n=== SUMMARY ===\r\nAlgorithm   Hits   Faults   Hit ratio   Fault ratio\r\n");
    const char *names[] = {"FIFO", "LRU", "Optimal"};
    for (int i = 0; i < 3; ++i)
        append_text(output, sizeof(output), "%-10s  %-5d  %-7d  %6.2f%%     %6.2f%%\r\n",
            names[i], results[i].page_hits, results[i].page_faults,
            100.0 * results[i].page_hits / n, 100.0 * results[i].page_faults / n);
    SetWindowTextA(hOutput, output);
}

static HWND make_control(HWND parent, const char *class_name, const char *text,
                         DWORD style, int x, int y, int width, int height, int id)
{
    HWND control = CreateWindowExA(0, class_name, text, WS_CHILD | WS_VISIBLE | style,
        x, y, width, height, parent, (HMENU)(INT_PTR)id, GetModuleHandleA(NULL), NULL);
    if (hFont) SendMessageA(control, WM_SETFONT, (WPARAM)hFont, TRUE);
    return control;
}

static LRESULT CALLBACK window_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    (void)lParam;
    switch (message) {
    case WM_CREATE:
        hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
        make_control(hwnd, "STATIC", "Page references (space/comma separated):", 0, 16, 16, 290, 22, 0);
        hPages = make_control(hwnd, "EDIT", "7 0 1 2 0 3 0 4 2 3 0 3 2",
            WS_BORDER | ES_AUTOHSCROLL, 16, 40, 500, 28, ID_PAGES);
        make_control(hwnd, "STATIC", "Number of frames (1-100):", 0, 16, 78, 190, 22, 0);
        hFrames = make_control(hwnd, "EDIT", "3", WS_BORDER | ES_NUMBER, 210, 74, 70, 28, ID_FRAMES);
        make_control(hwnd, "BUTTON", "Compare FIFO, LRU and Optimal", BS_PUSHBUTTON,
            300, 72, 216, 32, ID_COMPARE);
        hOutput = make_control(hwnd, "EDIT", "", WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL |
            ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL | ES_READONLY, 16, 116, 900, 510, ID_OUTPUT);
        SendMessageA(hOutput, EM_SETLIMITTEXT, 60000, 0);
        return 0;
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_COMPARE) { run_comparison(); return 0; }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR command_line, int show)
{
    (void)previous; (void)command_line;
    const char class_name[] = "PageReplacementSimulatorWindow";
    WNDCLASSA wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = window_proc;
    wc.hInstance = instance;
    wc.lpszClassName = class_name;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    if (!RegisterClassA(&wc)) return 1;
    HWND hwnd = CreateWindowExA(0, class_name, "Page Replacement Algorithm Simulator",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 960, 700,
        NULL, NULL, instance, NULL);
    if (!hwnd) return 1;
    ShowWindow(hwnd, show);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return (int)msg.wParam;
}
