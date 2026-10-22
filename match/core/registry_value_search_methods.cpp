// Provenance: own-binary-via-Ghidra
//   Depth-first registry search for a subkey holding a given string value.

#include <windows.h>
#include <string.h>

// Opens subkey name under root; returns 0 on failure.
HKEY __fastcall FUN_007741c0(HKEY root, const char* name, int flags);

// FUNCTION: GAMEMD 0x005bb580
// Returns the first subkey (searched depth-first below root) whose string
// value valueName equals match, still open; 0 when none is found.
HKEY __fastcall FUN_005bb580(HKEY root, const char* valueName, const char* match)
{
    DWORD size = 256;
    DWORD index = 0;
    char* name = new char[size];
    DWORD dataSize = size;
    char* data = new char[dataSize];
    DWORD nameSize = size;
    FILETIME stamp;
    for (;;) {
        nameSize = 256;
        if (RegEnumKeyExA(root, index++, name, &nameSize, 0, 0, 0, &stamp) != ERROR_SUCCESS) {
            break;
        }
        HKEY sub = FUN_007741c0(root, name, 0);
        if (sub == 0) {
            continue;
        }
        DWORD type;
        dataSize = 256;
        if (RegQueryValueExA(sub, valueName, 0, &type, (LPBYTE)data, &dataSize) == ERROR_SUCCESS
            && type == REG_SZ && strcmp(data, match) == 0) {
            delete name;
            delete data;
            return sub;
        }
        HKEY found = FUN_005bb580(sub, valueName, match);
        RegCloseKey(sub);
        if (found != 0) {
            delete name;
            delete data;
            return found;
        }
    }
    delete name;
    delete data;
    return 0;
}
