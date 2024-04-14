#include <iostream>
#include <stdio.h>
#include <windows.h>

#define REG_READ_STRING(hKey, valueName, buffer, bufferSize) \
    do { \
        DWORD dwType = REG_SZ; \
        DWORD dwSize = bufferSize; \
        if (RegQueryValueExA(hKey, valueName, NULL, &dwType, (LPBYTE)buffer, &dwSize) != ERROR_SUCCESS) { \
            printf("Failed to read value '%s'.\n", valueName); \
            return -1; \
        } \
        if (dwType != REG_SZ) { \
            printf("Invalid value type for '%s'.\n", valueName); \
            return -1; \
        } \
    } while (0)

#define REG_READ_DWORD(hKey, valueName, dwValue) \
    do { \
        DWORD dwType = REG_DWORD; \
        DWORD dwSize = sizeof(DWORD); \
        if (RegQueryValueExA(hKey, valueName, NULL, &dwType, (LPBYTE)dwValue, &dwSize) != ERROR_SUCCESS) { \
            printf("Failed to read DWORD value '%s'.\n", valueName); \
            return -1; \
        } \
        if (dwType != REG_DWORD) { \
            printf("Invalid value type for DWORD value '%s'.\n", valueName); \
            return -1; \
        } \
    } while (0)

int main() {
  HKEY hKey;
  LPCSTR subKey = "Software\\SimonTatham\\PuTTY\\Sessions\\WinSCP%20temporary%20session";
  CHAR hostName[MAX_PATH];
  CHAR protocol[MAX_PATH];
  CHAR userName[MAX_PATH];
  CHAR winTitle[MAX_PATH];
  DWORD port;

  if (RegOpenKeyExA(HKEY_CURRENT_USER, subKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
    printf("Failed to open registry key.\n");
    return -1;
  }

  REG_READ_STRING(hKey, "HostName", hostName, sizeof(hostName));
  REG_READ_STRING(hKey, "Protocol", protocol, sizeof(protocol));
  REG_READ_STRING(hKey, "WinTitle", winTitle, sizeof(winTitle));
  REG_READ_STRING(hKey, "UserName", userName, sizeof(userName));
  REG_READ_DWORD(hKey, "PortNumber", &port);

  char exec_buffer[1024];

  sprintf(exec_buffer, "start /unix /usr/bin/konsole -p tabtitle=\"%s\" -e \"ssh %s@%s -p %ld\"", winTitle, userName, hostName, port);
  printf("%s\n", exec_buffer);

  system(exec_buffer);
//  getchar();


  return 0;
}