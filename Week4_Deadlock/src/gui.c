//Vishnu


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "deadlock.h"

#define ID_SAFETY 101
#define ID_DETECT 102
#define ID_RECOVER 103
#define ID_REQUEST 104
#define ID_STATUS 105
#define ID_RAG 106
#define ID_UTIL 107

static HWND outputBox;
static SystemState *currentState;

static void showMessage(const char *message)
{
    if (outputBox != NULL)
        SetWindowTextA(outputBox, message);
}

static void addMessage(const char *message)
{
    char oldText[12000] = {0};
    char newText[14000] = {0};

    GetWindowTextA(outputBox, oldText, sizeof(oldText));
    snprintf(newText, sizeof(newText), "%s\n%s", oldText, message);
    SetWindowTextA(outputBox, newText);
}

void initializeGUI(void)
{
}

void displaySystemStatus(SystemState *state)
{
    char text[12000] = {0};
    size_t used = 0;

    calculateNeed(state);

    used += snprintf(text + used, sizeof(text) - used,
        "DEADLOCK SIMULATION SYSTEM\n\nProcesses: %d\nResources: %d\n\n"
        "AVAILABLE RESOURCES\n",
        state->processCount, state->resourceCount);

    for (int j = 0; j < state->resourceCount && used < sizeof(text); j++)
        used += snprintf(text + used, sizeof(text) - used,
                         "R%d: %d\n", j, state->available[j]);

    used += snprintf(text + used, sizeof(text) - used,
                     "\nALLOCATION MATRIX\n");

    for (int i = 0; i < state->processCount && used < sizeof(text); i++) {
        used += snprintf(text + used, sizeof(text) - used, "P%d: ", i);
        for (int j = 0; j < state->resourceCount && used < sizeof(text); j++)
            used += snprintf(text + used, sizeof(text) - used,
                             "%d ", state->allocation[i][j]);
        used += snprintf(text + used, sizeof(text) - used, "\n");
    }

    used += snprintf(text + used, sizeof(text) - used, "\nMAXIMUM MATRIX\n");

    for (int i = 0; i < state->processCount && used < sizeof(text); i++) {
        used += snprintf(text + used, sizeof(text) - used, "P%d: ", i);
        for (int j = 0; j < state->resourceCount && used < sizeof(text); j++)
            used += snprintf(text + used, sizeof(text) - used,
                             "%d ", state->maximum[i][j]);
        used += snprintf(text + used, sizeof(text) - used, "\n");
    }

    used += snprintf(text + used, sizeof(text) - used, "\nNEED MATRIX\n");

    for (int i = 0; i < state->processCount && used < sizeof(text); i++) {
        used += snprintf(text + used, sizeof(text) - used, "P%d: ", i);
        for (int j = 0; j < state->resourceCount && used < sizeof(text); j++)
            used += snprintf(text + used, sizeof(text) - used,
                             "%d ", state->need[i][j]);
        used += snprintf(text + used, sizeof(text) - used, "\n");
    }

    showMessage(text);
}

static LRESULT CALLBACK WindowProcedure(
    HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    (void)lParam;

    switch (message) {
    case WM_CREATE:
        CreateWindowA("BUTTON", "Safety Check",
            WS_VISIBLE | WS_CHILD, 20, 20, 140, 35,
            window, (HMENU)(INT_PTR)ID_SAFETY, NULL, NULL);

        CreateWindowA("BUTTON", "Detect Deadlock",
            WS_VISIBLE | WS_CHILD, 170, 20, 140, 35,
            window, (HMENU)(INT_PTR)ID_DETECT, NULL, NULL);

        CreateWindowA("BUTTON", "Recover P0",
            WS_VISIBLE | WS_CHILD, 320, 20, 120, 35,
            window, (HMENU)(INT_PTR)ID_RECOVER, NULL, NULL);

        CreateWindowA("BUTTON", "Request 1 Unit",
            WS_VISIBLE | WS_CHILD, 20, 65, 140, 35,
            window, (HMENU)(INT_PTR)ID_REQUEST, NULL, NULL);

        CreateWindowA("BUTTON", "System Status",
            WS_VISIBLE | WS_CHILD, 170, 65, 140, 35,
            window, (HMENU)(INT_PTR)ID_STATUS, NULL, NULL);

        CreateWindowA("BUTTON", "Show RAG",
            WS_VISIBLE | WS_CHILD, 320, 65, 120, 35,
            window, (HMENU)(INT_PTR)ID_RAG, NULL, NULL);

        CreateWindowA("BUTTON", "Resource Utilization",
            WS_VISIBLE | WS_CHILD, 20, 110, 200, 35,
            window, (HMENU)(INT_PTR)ID_UTIL, NULL, NULL);

        outputBox = CreateWindowExA(
            WS_EX_CLIENTEDGE, "EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_VSCROLL |
            ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            20, 155, 600, 330, window, NULL, NULL, NULL);

        displaySystemStatus(currentState);
        return 0;

    case WM_COMMAND:
        if (!currentState || !outputBox)
            return 0;

        switch (LOWORD(wParam)) {
        case ID_SAFETY: {
            int sequence[MAX_PROCESSES];
            char result[2000] = {0};
            size_t used = 0;

            if (checkSafety(currentState, sequence)) {
                used += snprintf(result + used, sizeof(result) - used,
                                 "System state: SAFE\nSafe sequence: ");
                for (int i = 0; i < currentState->processCount; i++)
                    used += snprintf(result + used, sizeof(result) - used,
                        "P%d%s", sequence[i],
                        i + 1 == currentState->processCount ? "\n" : " -> ");
            } else {
                snprintf(result, sizeof(result),
                         "System state: UNSAFE\nNo safe sequence exists.");
            }

            showMessage(result);
            break;
        }

        case ID_DETECT: {
            int deadlocked[MAX_PROCESSES];
            int count = detectDeadlock(currentState, deadlocked);
            char result[2000] = {0};
            size_t used = 0;

            if (count == 0) {
                snprintf(result, sizeof(result),
                         "Deadlock detection: No deadlocked processes found.");
            } else {
                used += snprintf(result + used, sizeof(result) - used,
                                 "DEADLOCKED PROCESSES:\n");
                for (int i = 0; i < count && used < sizeof(result); i++)
                    used += snprintf(result + used, sizeof(result) - used,
                                     "P%d\n", deadlocked[i]);
            }

            showMessage(result);
            break;
        }

        case ID_RECOVER:
            if (recoverDeadlock(currentState, 0)) {
                displaySystemStatus(currentState);
                addMessage("Recovery performed on P0.");
            } else {
                showMessage("Recovery failed for P0.");
            }
            break;

        case ID_REQUEST: {
            int request[MAX_RESOURCES] = {0};

            if (currentState->resourceCount < 1 ||
                currentState->processCount < 1) {
                showMessage("No processes or resources configured.");
                break;
            }

            request[0] = 1;
            int result = requestResources(currentState, 0, request);

            if (result == 1) {
                displaySystemStatus(currentState);
                addMessage("Request granted: P0 received one unit of R0.");
            } else if (result == 0) {
                showMessage("Request denied: insufficient resources or unsafe state.");
            } else {
                showMessage("Invalid resource request.");
            }
            break;
        }

        case ID_STATUS:
            displaySystemStatus(currentState);
            break;

        case ID_RAG: {
            char result[12000] = {0};
            size_t used = 0;

            used += snprintf(result + used, sizeof(result) - used,
                             "RESOURCE ALLOCATION GRAPH\n\n"
                             "R -> P means resource allocated to process.\n"
                             "P -> R means process requesting resource.\n\n");

            int edges = 0;
            for (int i = 0; i < currentState->processCount; i++) {
                for (int j = 0; j < currentState->resourceCount; j++) {
                    if (currentState->allocation[i][j] > 0) {
                        used += snprintf(result + used, sizeof(result) - used,
                            "R%d -> P%d (allocated: %d)\n", j, i,
                            currentState->allocation[i][j]);
                        edges++;
                    }
                    if (currentState->request[i][j] > 0) {
                        used += snprintf(result + used, sizeof(result) - used,
                            "P%d -> R%d (requested: %d)\n", i, j,
                            currentState->request[i][j]);
                        edges++;
                    }
                    if (used >= sizeof(result) - 100)
                        break;
                }
                if (used >= sizeof(result) - 100)
                    break;
            }

            if (edges == 0)
                used += snprintf(result + used, sizeof(result) - used,
                                 "No allocation or request edges currently exist.\n");

            showMessage(result);
            break;
        }

        case ID_UTIL: {
            char result[2000] = {0};
            size_t used = 0;

            used += snprintf(result + used, sizeof(result) - used,
                             "RESOURCE UTILIZATION\n\n");

            for (int j = 0; j < currentState->resourceCount &&
                            used < sizeof(result); j++) {
                int allocated = 0;
                for (int i = 0; i < currentState->processCount; i++)
                    allocated += currentState->allocation[i][j];

                int total = allocated + currentState->available[j];
                double percent = total > 0 ? 100.0 * allocated / total : 0.0;

                used += snprintf(result + used, sizeof(result) - used,
                    "R%d: %d/%d allocated (%.1f%%)\n",
                    j, allocated, total, percent);
            }

            showMessage(result);
            break;
        }
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcA(window, message, wParam, lParam);
}

void runGUI(SystemState *state)
{
    currentState = state;

    HINSTANCE instance = GetModuleHandleA(NULL);
    WNDCLASSA wc = {0};

    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = instance;
    wc.lpszClassName = "DeadlockSimulationWindow";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassA(&wc)) {
        MessageBoxA(NULL, "Failed to register window class.",
                    "GUI Error", MB_OK | MB_ICONERROR);
        return;
    }

    HWND window = CreateWindowA(
        wc.lpszClassName,
        "Week 4 - Deadlock Simulation System",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 680, 550,
        NULL, NULL, instance, NULL);

    if (!window) {
        MessageBoxA(NULL, "Failed to create GUI window.",
                    "GUI Error", MB_OK | MB_ICONERROR);
        return;
    }

    ShowWindow(window, SW_SHOW);
    UpdateWindow(window);

    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}
