// Provenance: own-binary-via-Ghidra
//   Reads the product serial from the registry and unscrambles it with the
//   bytes of the local key file.

#include <windows.h>
#include <stdio.h>
#include <string.h>

// FUNCTION: GAMEMD 0x005dc170
// Copies the decoded serial into out.
// out receives an all-zero default first; returns false when the key file
// cannot be opened.
bool __fastcall FUN_005dc170(char* out)
{
    char serial[128];
    memset(serial, '0', 22);
    serial[22] = '\0';
    strcpy(out, serial);
    memset(serial, 0, sizeof(serial));
    const char* keyPath = "SOFTWARE\\Westwood\\Yuri's Revenge";
    if (keyPath != 0 && strlen(keyPath) != 0) {
        char path[256];
        HKEY key;
        strcpy(path, keyPath);
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, &key) == ERROR_SUCCESS) {
            DWORD type;
            DWORD size = sizeof(serial);
            RegQueryValueExA(key, "Serial", 0, &type, (LPBYTE)serial, &size);
            RegCloseKey(key);
        }
    }
    serial[22] = '\0';
    strcpy(out, serial);
    unsigned int i = 0;
    FILE* file = fopen("woldata.key", "r");
    if (file == 0) {
        return false;
    }
    int c;
    while ((c = fgetc(file)) != EOF) {
        serial[i] = ((serial[i] - '0') % 10 - c + 1000) % 10 + '0';
        i++;
        if (i == strlen(serial)) {
            i = 0;
        }
    }
    fclose(file);
    strcpy(out, serial);
    return true;
}
