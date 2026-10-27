#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "common.h"

#define ID_PAGES       101
#define ID_FRAMES      102
#define ID_ALGORITHM   103
#define ID_RUN         104
#define ID_RESET       105
#define ID_OUTPUT      106
#define ID_CHART       107
#define ID_STATUS      108
#define ID_CARD_REFS   109
#define ID_CARD_FRAMES 110
#define ID_CARD_HITS   111
#define ID_CARD_FAULTS 112

static HWND hPages, hFrames, hAlgorithm, hOutput, hChart, hStatus;
static HWND hCardRefs, hCardFrames, hCardHits, hCardFaults;
static HFONT hFont, hTitleFont;
static int chart_faults[3] = {0, 0, 0};
static int chart_hits[3] = {0, 0, 0};
static int chart_valid = 0;
static const char *algorithm_names[] = {"FIFO", "LRU", "Optimal"};
static const COLORREF chart_colors[] = {RGB(64, 112, 210), RGB(24, 155, 122), RGB(220, 145, 55)};

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

static void show_one(char *out, size_t cap, const int pages[],
                     const SimulationResult *r, const char *name)
{
    append_text(out, cap, "\r\n%s - STEP-BY-STEP RESULTS\r\n", name);
    append_text(out, cap, "%-8s", "Page");
    for (int j = 0; j < r->frame_count; ++j)
        append_text(out, cap, "F%-4d", j + 1);
    append_text(out, cap, "Status\r\n");
    append_text(out, cap, "---------------------------------------------\r\n");
    for (int i = 0; i < r->total_refs; ++i) {
        append_text(out, cap, "%-8d", pages[i]);
        for (int j = 0; j < r->frame_count; ++j) {
            if (r->frames[i][j] == -1) append_text(out, cap, "%-5s", "-");
            else append_text(out, cap, "%-5d", r->frames[i][j]);
        }
        append_text(out, cap, "%s\r\n", r->hit[i] ? "HIT" : "FAULT");
    }
    append_text(out, cap,
        "Hits: %d   Faults: %d   Hit ratio: %.2f%%   Fault ratio: %.2f%%\r\n",
        r->page_hits, r->page_faults,
        100.0 * r->page_hits / r->total_refs,
        100.0 * r->page_faults / r->total_refs);
}

static void update_cards(int n, int frames, const SimulationResult results[3])
{
    int best_hits = 0, fewest_faults = 0;
    for (int i = 1; i < 3; ++i) {
        if (results[i].page_hits > results[best_hits].page_hits) best_hits = i;
        if (results[i].page_faults < results[fewest_faults].page_faults) fewest_faults = i;
    }
    char text[128];
    snprintf(text, sizeof(text), "Page references: %d", n);
    SetWindowTextA(hCardRefs, text);
    snprintf(text, sizeof(text), "Frames: %d", frames);
    SetWindowTextA(hCardFrames, text);
    snprintf(text, sizeof(text), "Most hits: %s (%d)", algorithm_names[best_hits],
             results[best_hits].page_hits);
    SetWindowTextA(hCardHits, text);
    snprintf(text, sizeof(text), "Fewest faults: %s (%d)", algorithm_names[fewest_faults],
             results[fewest_faults].page_faults);
    SetWindowTextA(hCardFaults, text);
}

static void run_simulation(void)
{
    char page_text[8192], frame_text[32];
    int pages[MAX_REFERENCES];
    static SimulationResult results[3];
    char output[60000] = "";
    GetWindowTextA(hPages, page_text, (int)sizeof(page_text));
    GetWindowTextA(hFrames, frame_text, (int)sizeof(frame_text));

    int n = parse_pages(page_text, pages, MAX_REFERENCES);
    char *end = NULL;
    long frame_count = strtol(frame_text, &end, 10);
    if (n < 1) {
        MessageBoxA(NULL, "Enter 1 to 1000 non-negative page numbers, separated by spaces or commas.",
                    "Check page references", MB_OK | MB_ICONWARNING);
        SetFocus(hPages);
        return;
    }
    if (end == frame_text || *end != '\0' || frame_count < 1 || frame_count > MAX_FRAMES) {
        MessageBoxA(NULL, "Enter a frame count from 1 to 100.",
                    "Check frame count", MB_OK | MB_ICONWARNING);
        SetFocus(hFrames);
        return;
    }

    simulate_fifo(pages, n, (int)frame_count, &results[0]);
    simulate_lru(pages, n, (int)frame_count, &results[1]);
    simulate_optimal(pages, n, (int)frame_count, &results[2]);

    for (int i = 0; i < 3; ++i) {
        chart_faults[i] = results[i].page_faults;
        chart_hits[i] = results[i].page_hits;
    }
    chart_valid = 1;
    InvalidateRect(hChart, NULL, TRUE);
    update_cards(n, (int)frame_count, results);

    append_text(output, sizeof(output),
        "PAGE REPLACEMENT SIMULATOR\r\nReferences: %d    Frames: %ld\r\n"
        "HIT = page already in memory. FAULT = page must be loaded.\r\n",
        n, frame_count);

    int selection = (int)SendMessageA(hAlgorithm, CB_GETCURSEL, 0, 0);
    if (selection == 0) show_one(output, sizeof(output), pages, &results[0], "FIFO");
    else if (selection == 1) show_one(output, sizeof(output), pages, &results[1], "LRU");
    else if (selection == 2) show_one(output, sizeof(output), pages, &results[2], "OPTIMAL");
    else {
        show_one(output, sizeof(output), pages, &results[0], "FIFO");
        show_one(output, sizeof(output), pages, &results[1], "LRU");
        show_one(output, sizeof(output), pages, &results[2], "OPTIMAL");
    }

    append_text(output, sizeof(output),
        "\r\nALGORITHM COMPARISON\r\n%-12s %-8s %-8s %-12s %-12s\r\n",
        "Algorithm", "Hits", "Faults", "Hit ratio", "Fault ratio");
    for (int i = 0; i < 3; ++i) {
        append_text(output, sizeof(output), "%-12s %-8d %-8d %-11.2f%% %-11.2f%%\r\n",
            algorithm_names[i], results[i].page_hits, results[i].page_faults,
            100.0 * results[i].page_hits / n,
            100.0 * results[i].page_faults / n);
    }
    SetWindowTextA(hOutput, output);
    SetWindowTextA(hStatus, "Simulation complete. Results and page-fault chart updated.");
}

static void reset_form(void)
{
    SetWindowTextA(hPages, "7 0 1 2 0 3 0");
    SetWindowTextA(hFrames, "3");
    SendMessageA(hAlgorithm, CB_SETCURSEL, 3, 0);
    SetWindowTextA(hOutput, "Enter page references and frame count, then click Run Simulation.");
    SetWindowTextA(hStatus, "Ready for a new simulation.");
    chart_valid = 0;
    for (int i = 0; i < 3; ++i) chart_faults[i] = chart_hits[i] = 0;
    SetWindowTextA(hCardRefs, "Page references: --");
    SetWindowTextA(hCardFrames, "Frames: --");
    SetWindowTextA(hCardHits, "Most hits: --");
    SetWindowTextA(hCardFaults, "Fewest faults: --");
    InvalidateRect(hChart, NULL, TRUE);
}

static HWND make_control(HWND parent, const char *class_name, const char *text,
                         DWORD style, int x, int y, int width, int height, int id)
{
    HWND control = CreateWindowExA(0, class_name, text,
        WS_CHILD | WS_VISIBLE | style, x, y, width, height, parent,
        (HMENU)(INT_PTR)id, GetModuleHandleA(NULL), NULL);
    if (hFont) SendMessageA(control, WM_SETFONT, (WPARAM)hFont, TRUE);
    return control;
}

static LRESULT CALLBACK chart_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    (void)wParam; (void)lParam;
    if (message == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(hwnd, &ps);
        RECT rc;
        GetClientRect(hwnd, &rc);
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(dc, &rc, white);
        DeleteObject(white);
        SetBkMode(dc, TRANSPARENT);
        SetTextColor(dc, RGB(35, 45, 60));
        HFONT old_font = (HFONT)SelectObject(dc, hFont);
        TextOutA(dc, 14, 10, "Page faults by algorithm", 23);
        if (!chart_valid) {
            TextOutA(dc, 14, 42, "Run a simulation to view the chart.", 35);
        } else {
            int max_faults = 1;
            for (int i = 0; i < 3; ++i)
                if (chart_faults[i] > max_faults) max_faults = chart_faults[i];
            int chart_top = 44, chart_bottom = rc.bottom - 36;
            int usable_height = chart_bottom - chart_top;
            int bar_width = 48;
            int centers[3] = {rc.right / 4, rc.right / 2, (rc.right * 3) / 4};
            HPEN axis = CreatePen(PS_SOLID, 1, RGB(205, 212, 222));
            HPEN old_pen = (HPEN)SelectObject(dc, axis);
            MoveToEx(dc, 20, chart_bottom, NULL);
            LineTo(dc, rc.right - 12, chart_bottom);
            SelectObject(dc, old_pen);
            DeleteObject(axis);
            for (int i = 0; i < 3; ++i) {
                int height = (int)((double)chart_faults[i] / max_faults * (usable_height - 10));
                RECT bar = {centers[i] - bar_width / 2, chart_bottom - height,
                            centers[i] + bar_width / 2, chart_bottom};
                HBRUSH brush = CreateSolidBrush(chart_colors[i]);
                FillRect(dc, &bar, brush);
                DeleteObject(brush);
                char number[24];
                snprintf(number, sizeof(number), "%d faults", chart_faults[i]);
                SIZE size;
                GetTextExtentPoint32A(dc, number, (int)strlen(number), &size);
                TextOutA(dc, centers[i] - size.cx / 2, chart_bottom - height - 20,
                         number, (int)strlen(number));
                TextOutA(dc, centers[i] - 20, chart_bottom + 7, algorithm_names[i],
                         (int)strlen(algorithm_names[i]));
            }
        }
        SelectObject(dc, old_font);
        EndPaint(hwnd, &ps);
        return 0;
    }
    return DefWindowProcA(hwnd, message, wParam, lParam);
}

static LRESULT CALLBACK window_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    (void)lParam;
    switch (message) {
    case WM_CREATE: {
        hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
        hTitleFont = CreateFontA(22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");
        HWND title = make_control(hwnd, "STATIC", "Page Replacement Simulator",
            0, 22, 14, 600, 34, 0);
        SendMessageA(title, WM_SETFONT, (WPARAM)hTitleFont, TRUE);
        make_control(hwnd, "STATIC",
            "Compare FIFO, LRU and Optimal using the same page-reference string.",
            0, 24, 48, 700, 22, 0);

        make_control(hwnd, "BUTTON", "Simulation inputs", BS_GROUPBOX, 18, 78, 610, 122, 0);
        make_control(hwnd, "STATIC", "Page references", 0, 34, 106, 120, 22, 0);
        hPages = make_control(hwnd, "EDIT", "7 0 1 2 0 3 0 4 2 3 0 3 2",
            WS_BORDER | ES_AUTOHSCROLL, 34, 130, 365, 28, ID_PAGES);
        make_control(hwnd, "STATIC", "Frames (1-100)", 0, 415, 106, 110, 22, 0);
        hFrames = make_control(hwnd, "EDIT", "3", WS_BORDER | ES_NUMBER,
            415, 130, 75, 28, ID_FRAMES);
        make_control(hwnd, "STATIC", "Show details for", 0, 34, 164, 120, 22, 0);
        hAlgorithm = make_control(hwnd, "COMBOBOX", "",
            CBS_DROPDOWNLIST | WS_VSCROLL, 150, 160, 175, 130, ID_ALGORITHM);
        SendMessageA(hAlgorithm, CB_ADDSTRING, 0, (LPARAM)"FIFO");
        SendMessageA(hAlgorithm, CB_ADDSTRING, 0, (LPARAM)"LRU");
        SendMessageA(hAlgorithm, CB_ADDSTRING, 0, (LPARAM)"Optimal");
        SendMessageA(hAlgorithm, CB_ADDSTRING, 0, (LPARAM)"Compare All");
        SendMessageA(hAlgorithm, CB_SETCURSEL, 3, 0);
        make_control(hwnd, "BUTTON", "Run Simulation", BS_PUSHBUTTON,
            415, 162, 130, 30, ID_RUN);
        make_control(hwnd, "BUTTON", "Reset", BS_PUSHBUTTON,
            552, 162, 58, 30, ID_RESET);

        make_control(hwnd, "BUTTON", "Step-by-step output and comparison", BS_GROUPBOX,
            18, 212, 610, 480, 0);
        hOutput = make_control(hwnd, "EDIT",
            "Enter page references and frame count, then click Run Simulation.",
            WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL |
            WS_VSCROLL | WS_HSCROLL | ES_READONLY | ES_NOHIDESEL,
            30, 236, 586, 442, ID_OUTPUT);
        SendMessageA(hOutput, EM_SETLIMITTEXT, 60000, 0);
        SendMessageA(hOutput, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN,
                     MAKELONG(8, 8));

        make_control(hwnd, "BUTTON", "Visual comparison", BS_GROUPBOX,
            646, 78, 370, 250, 0);
        hChart = make_control(hwnd, "STATIC", "", 0, 660, 102, 342, 210, ID_CHART);
        SetWindowLongPtrA(hChart, GWLP_WNDPROC, (LONG_PTR)chart_proc);

        make_control(hwnd, "BUTTON", "Quick statistics", BS_GROUPBOX,
            646, 342, 370, 180, 0);
        hCardRefs = make_control(hwnd, "STATIC", "Page references: --",
            0, 664, 374, 330, 26, ID_CARD_REFS);
        hCardFrames = make_control(hwnd, "STATIC", "Frames: --",
            0, 664, 411, 330, 26, ID_CARD_FRAMES);
        hCardHits = make_control(hwnd, "STATIC", "Most hits: --",
            0, 664, 448, 330, 26, ID_CARD_HITS);
        hCardFaults = make_control(hwnd, "STATIC", "Fewest faults: --",
            0, 664, 485, 330, 26, ID_CARD_FAULTS);
        hStatus = make_control(hwnd, "STATIC", "Ready for a new simulation.",
            0, 24, 704, 970, 24, ID_STATUS);
        return 0;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_RUN) { run_simulation(); return 0; }
        if (LOWORD(wParam) == ID_RESET) { reset_form(); return 0; }
        break;
    case WM_DESTROY:
        if (hTitleFont) DeleteObject(hTitleFont);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR command_line, int show)
{
    (void)previous; (void)command_line;
    INITCOMMONCONTROLSEX controls = {sizeof(controls), ICC_STANDARD_CLASSES};
    InitCommonControlsEx(&controls);

    WNDCLASSA chart_class;
    ZeroMemory(&chart_class, sizeof(chart_class));
    chart_class.lpfnWndProc = chart_proc;
    chart_class.hInstance = instance;
    chart_class.lpszClassName = "PageReplacementChart";
    chart_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    chart_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassA(&chart_class);

    WNDCLASSA wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = window_proc;
    wc.hInstance = instance;
    wc.lpszClassName = "PageReplacementSimulatorWindow";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    if (!RegisterClassA(&wc)) return 1;

    HWND hwnd = CreateWindowExA(0, wc.lpszClassName,
        "Page Replacement Algorithm Simulator",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1050, 790,
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
