#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>
#include <wininet.h>
#include <json-c/json.h>

// Replace with your server URL
#define SERVER_URL "https://example.com/api/process-logs"
// Buffer size for process logging
#define PROCESS_BUFFER_SIZE 8192
// Replace with your actual auth token
#define AUTH_TOKEN "REPLACE_WITH_AUTH_TOKEN"

// Function prototypes
void printBanner();
void setConsoleColor(WORD color);
void resetConsoleColor();
void printError(const char *message);
void printInfo(const char *message);
void getProcessList(char *buffer, size_t bufferSize);
void sendJsonPayload(const char *steamId, const char *matchId, const char *log);

// Function to set console text color
void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to reset console color
void resetConsoleColor() {
    setConsoleColor(7);  // Default console color
}

// Function to print ASCII banner
void printBanner() {
    const char *banner[] = {
        "888'Y88                               888   Y8b Y8b Y888P           d8            888                    ",
        "888 ,'Y 888,8,  ,\"Y88b 8888 8888  e88 888    Y8b Y8b Y8P   ,\"Y88b  d88    e88'888 888 ee   ,e e,  888,8, ",
        "888C8   888 \"  \"8\" 888 8888 8888 d888 888     Y8b Y8b Y   \"8\" 888 d88888 d888  '8 888 88b d88 88b 888 \"  ",
        "888 \"   888    ,ee 888 Y888 888P Y888 888      Y8b Y8b    ,ee 888  888   Y888   , 888 888 888   , 888    ",
        "888     888    \"88 888  \"88 88\"   \"88 888       Y8P Y     \"88 888  888    \"88,e8' 888 888  \"YeeP\" 888   "
    };

    int bannerSize = sizeof(banner) / sizeof(banner[0]);
    WORD colors[] = {9, 11, 10, 14, 12, 13}; // Gradient colors (blue, cyan, green, yellow, red, magenta)
    int colorCount = sizeof(colors) / sizeof(colors[0]);

    for (int i = 0; i < bannerSize; i++) {
        setConsoleColor(colors[i % colorCount]);  // Cycle through colors
        printf("%s\n", banner[i]);
    }

    resetConsoleColor();
    printf("\n");

    setConsoleColor(11); // Cyan
    printf("            Created by Bharat Ascend Esports - Empowering Gaming and Innovation\n");
    resetConsoleColor();
    printf("\n");
}

// Function to print detailed errors
void printError(const char *message) {
    DWORD errorCode = GetLastError();
    char *errorMsg;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                  NULL, errorCode, 0, (LPSTR)&errorMsg, 0, NULL);
    setConsoleColor(12);  // Red
    printf("[ERROR] %s: %s (Error code: %lu)\n", message, errorMsg, errorCode);
    resetConsoleColor();
    LocalFree(errorMsg);
}

// Function to print informational messages
void printInfo(const char *message) {
    setConsoleColor(10);  // Green
    printf("[INFO] %s\n", message);
    resetConsoleColor();
}

// Function to enumerate running processes and collect their names
void getProcessList(char *buffer, size_t bufferSize) {
    HANDLE hSnapshot;
    PROCESSENTRY32 processEntry;

    buffer[0] = '\0'; // Initialize the buffer

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        printError("Failed to create process snapshot");
        return;
    }

    processEntry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &processEntry)) {
        do {
            strncat(buffer, processEntry.szExeFile, bufferSize - strlen(buffer) - 1);
            strncat(buffer, "\\n", bufferSize - strlen(buffer) - 1);
        } while (Process32Next(hSnapshot, &processEntry));
    } else {
        printError("Failed to retrieve process list");
    }

    CloseHandle(hSnapshot);
}

// Function to send JSON payload to the server
void sendJsonPayload(const char *steamId, const char *matchId, const char *log) {
    HINTERNET hSession, hConnect, hRequest;
    BOOL result;
    const char *headers = "Content-Type: application/json\r\nAuthorization: Bearer " AUTH_TOKEN;
    char *jsonPayload;

    struct json_object *jsonObject = json_object_new_object();
    json_object_object_add(jsonObject, "steam_id", json_object_new_string(steamId));
    json_object_object_add(jsonObject, "match_id", json_object_new_string(matchId));
    json_object_object_add(jsonObject, "log", json_object_new_string(log));

    jsonPayload = strdup(json_object_to_json_string(jsonObject));
    json_object_put(jsonObject);

    hSession = InternetOpen("ProcessLogger", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hSession) {
        printError("InternetOpen failed");
        free(jsonPayload);
        return;
    }

    hConnect = InternetConnect(hSession, "example.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) {
        printError("InternetConnect failed");
        InternetCloseHandle(hSession);
        free(jsonPayload);
        return;
    }

    hRequest = HttpOpenRequest(hConnect, "POST", "/api/process-logs", NULL, NULL, NULL, INTERNET_FLAG_SECURE, 0);
    if (!hRequest) {
        printError("HttpOpenRequest failed");
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hSession);
        free(jsonPayload);
        return;
    }

    result = HttpSendRequest(hRequest, headers, strlen(headers), jsonPayload, strlen(jsonPayload));
    if (result) {
        printInfo("JSON request sent successfully.");
    } else {
        printError("HttpSendRequest failed");
    }

    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hSession);
    free(jsonPayload);
}

int main() {
    char steamId[64], matchId[64], processList[PROCESS_BUFFER_SIZE];

    printBanner();

    setConsoleColor(14);  // Yellow
    printf("Enter your Steam ID: ");
    resetConsoleColor();
    fgets(steamId, sizeof(steamId), stdin);
    steamId[strcspn(steamId, "\n")] = '\0';

    setConsoleColor(14);  // Yellow
    printf("Enter your Match ID: ");
    resetConsoleColor();
    fgets(matchId, sizeof(matchId), stdin);
    matchId[strcspn(matchId, "\n")] = '\0';

    printInfo("Logger started");

    while (1) {
        getProcessList(processList, sizeof(processList));
        sendJsonPayload(steamId, matchId, processList);

        printf("[INFO] Waiting for 30 seconds before next cycle...\n");
        Sleep(30000);
    }

    return 0;
}
