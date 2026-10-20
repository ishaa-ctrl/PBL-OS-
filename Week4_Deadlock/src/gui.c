
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "deadlock.h"

#define ID_SAFETY  101
#define ID_DETECT  102
#define ID_RECOVER 103
#define ID_REQUEST 104
#define ID_STATUS  105
#define ID_RAG     106
#define ID_UTIL    107

static HWND outputBox;
static SystemState *currentState;
static int terminated[MAX_PROCESSES] = {0};

static void showMessage(const char *message)
{
    if (outputBox != NULL)
        SetWindowTextA(outputBox, message);
}

static void appendMessage(const char *message)
{
    char oldText[16000];
    char newText[20000];

    if (outputBox == NULL)
        return;

    GetWindowTextA(outputBox, oldText, sizeof(oldText));
    snprintf(newText, sizeof(newText), "%s\r\n%s", oldText, message);
    SetWindowTextA(outputBox, newText);
}

void initializeGUI(void)
{
    /* GUI is initialized in runGUI(). */
}

void displaySystemStatus(SystemState *state)
{
    char text[16000];
    size_t used = 0;

    calculateNeed(state);

    used += snprintf(text + used, sizeof(text) - used,
        "DEADLOCK SIMULATION SYSTEM\r\n"
        "===========================\r\n\r\n"
        "Processes: %d\r\n"
        "Resource types: %d\r\n\r\n"
        "AVAILABLE RESOURCES\r\n",
        state->processCount, state->resourceCount);

    for (int j = 0; j < state->resourceCount && used < sizeof(text); j++)
        used += snprintf(text + used, sizeof(text) - used,
            "R%d: %d\r\n", j, state->available[j]);

    used += snprintf(text + used, sizeof(text) - used,
        "\r\nALLOCATION MATRIX\r\n");

    for (int i = 0; i < state->processCount && used < sizeof(text); i++) {
        used += snprintf(text + used, sizeof(text) - used, "P%d: ", i);
        for (int j = 0; j < state->resourceCount && used < sizeof(text); j++)
            used += snprintf(text + used, sizeof(text) - used,
                "%d  ", state->allocation[i][j]);
        used += snprintf(text + used, sizeof(text) - used, "\r\n");
    }

    used += snprintf(text + used, sizeof(text) - used,
        "\r\nMAXIMUM MATRIX\r\n");

    for (int i = 0; i < state->processCount && used < sizeof(text); i++) {
        used += snprintf(text + used, sizeof(text) - used, "P%d: ", i);
        for (int j = 0; j < state->resourceCount && used < sizeof(text); j++)
            used += snprintf(text + used, sizeof(text) - used,
                "%d  ", state->maximum[i][j]);
        used += snprintf(text + used, sizeof(text) - used, "\r\n");
    }

    used += snprintf(text + used, sizeof(text) - used,
        "\r\nNEED MATRIX\r\n");

    for (int i = 0; i < state->processCount && used < sizeof(text); i++) {
        used += snprintf(text + used, sizeof(text) - used, "P%d: ", i);
        for (int j = 0; j < state->resourceCount && used < sizeof(text); j++)
            used += snprintf(text + used, sizeof(text) - used,
                "%d  ", state->need[i][j]);
        used += snprintf(text + used, sizeof(text) - used, "\r\n");
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
            WS_VISIBLE | WS_CHILD, 320, 20, 130, 35,
            window, (HMENU)(INT_PTR)ID_RECOVER, NULL, NULL);

        CreateWindowA("BUTTON", "Request 1 Unit",
            WS_VISIBLE | WS_CHILD, 20, 65, 140, 35,
            window, (HMENU)(INT_PTR)ID_REQUEST, NULL, NULL);

        CreateWindowA("BUTTON", "System Status",
            WS_VISIBLE | WS_CHILD, 170, 65, 140, 35,
            window, (HMENU)(INT_PTR)ID_STATUS, NULL, NULL);

        CreateWindowA("BUTTON", "Show RAG",
            WS_VISIBLE | WS_CHILD, 320, 65, 130, 35,
            window, (HMENU)(INT_PTR)ID_RAG, NULL, NULL);

        CreateWindowA("BUTTON", "Resource Utilization",
            WS_VISIBLE | WS_CHILD, 20, 110, 200, 35,
            window, (HMENU)(INT_PTR)ID_UTIL, NULL, NULL);

        outputBox = CreateWindowExA(
            WS_EX_CLIENTEDGE, "EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_VSCROLL |
            ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            20, 155, 600, 330,
            window, NULL, NULL, NULL);

        SendMessageA(outputBox, EM_SETLIMITTEXT, 16000, 0);
        displaySystemStatus(currentState);
        return 0;

    case WM_COMMAND:
        if (currentState == NULL || outputBox == NULL)
            return 0;

        switch (LOWORD(wParam)) {
        case ID_SAFETY: {
            int sequence[MAX_PROCESSES];
            char result[2000];
            size_t used = 0;

            if (checkSafety(currentState, sequence)) {
                used += snprintf(result + used, sizeof(result) - used,
                    "BANKER'S ALGORITHM\r\n"
                    "System state: SAFE\r\n"
                    "Safe sequence: ");

                for (int i = 0; i < currentState->processCount &&
                                used < sizeof(result); i++)
                    used += snprintf(result + used, sizeof(result) - used,
                        "P%d%s", sequence[i],
                        i + 1 == currentState->processCount ? "\r\n" : " -> ");
            } else {
                snprintf(result, sizeof(result),
                    "BANKER'S ALGORITHM\r\n"
                    "System state: UNSAFE\r\n"
                    "No safe sequence exists.");
            }

            showMessage(result);
            break;
        }

        case ID_DETECT: {
            int deadlocked[MAX_PROCESSES];
            int count = detectDeadlock(currentState, deadlocked);
            char result[2000];
            size_t used = 0;

            if (count == 0) {
                snprintf(result, sizeof(result),
                    "DEADLOCK DETECTION\r\n"
                    "No deadlocked processes found.");
            } else {
                used += snprintf(result + used, sizeof(result) - used,
                    "DEADLOCKED PROCESSES\r\n");

                for (int i = 0; i < count && used < sizeof(result); i++)
                    used += snprintf(result + used, sizeof(result) - used,
                        "P%d\r\n", deadlocked[i]);
            }

            showMessage(result);
            break;
        }

        case ID_RECOVER:
            if (currentState->processCount > 0 && !terminated[0] &&
                recoverDeadlock(currentState, 0)) {
                terminated[0] = 1;
                displaySystemStatus(currentState);
                appendMessage("\r\nP0 terminated. Its resources were released.");
            } else {
                showMessage("Recovery failed: P0 is already terminated or unavailable.");
            }
            break;

        case ID_REQUEST: {
            int request[MAX_RESOURCES] = {0};

            if (currentState->processCount < 1 ||
                currentState->resourceCount < 1) {
                showMessage("No processes or resources are configured.");
                break;
            }

            if (terminated[0]) {
                showMessage("Request rejected: P0 has been terminated.");
                break;
            }

            request[0] = 1;
            int result = requestResources(currentState, 0, request);

            if (result == 1) {
                displaySystemStatus(currentState);
                appendMessage("\r\nRequest granted: P0 received one unit of R0.");
            } else if (result == 0) {
                showMessage("Request denied: resources unavailable or state unsafe.");
            } else {
                showMessage("Invalid resource request. Check request validation.");
            }
            break;
        }

        case ID_STATUS:
            displaySystemStatus(currentState);
            break;

        case ID_RAG:
            displayRAG(currentState);
            showMessage("Resource Allocation Graph opened in a separate window.");
            break;

        case ID_UTIL: {
            char result[2000];
            size_t used = 0;

            used += snprintf(result + used, sizeof(result) - used,
                "RESOURCE UTILIZATION\r\n"
                "====================\r\n\r\n");

            for (int j = 0; j < currentState->resourceCount &&
                            used < sizeof(result); j++) {
                int allocated = 0;

                for (int i = 0; i < currentState->processCount; i++)
                    allocated += currentState->allocation[i][j];

                int total = allocated + currentState->available[j];
                double percent = total > 0
                    ? 100.0 * allocated / total : 0.0;

                used += snprintf(result + used, sizeof(result) - used,
                    "R%d: %d/%d allocated (%.1f%%)\r\n",
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

    RegisterClassA(&wc);

    HWND window = CreateWindowA(
        wc.lpszClassName,
        "Week 4 - Deadlock Simulation System",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 680, 550,
        NULL, NULL, instance, NULL);

    if (window == NULL) {
        MessageBoxA(NULL, "Failed to create the simulation window.",
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
