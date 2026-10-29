// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembled from retail gamemd.exe v1.001 at 0x5175F0: the registry key string at 0x8254E4 is
//   copied to a local buffer, opened under HKEY_LOCAL_MACHINE (0x80000002) with KEY_ALL_ACCESS (0xF003F)
//   through RegOpenKeyExA (IAT 0x7E100C), and the value named at 0x8254DC is read with RegQueryValueExA
//   (IAT 0x7E1008) and RegCloseKey (IAT 0x7E1004).
//   FUNCTION: GAMEMD 0x5175F0

#include <windows.h>
#include <string.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A registry value cached with a flag saying whether it was read.
struct WolOptionValue_005175F0
{
    DWORD value;       // +0x00
    bool  isPresent;   // +0x04
};
GG_STATIC_ASSERT(offsetof(WolOptionValue_005175F0, isPresent) == 4);

// FUNCTION: GAMEMD 0x5175F0
// Reads the DWORD "Options" value of the HKLM Westwood online key into `option`; returns whether it was found.
bool __fastcall FUN_005175F0(WolOptionValue_005175F0* option)
{
    HKEY key;
    DWORD type;
    DWORD size;
    DWORD data;
    char path[128];

    option->isPresent = false;
    size = 4;
    // STRING: GAMEMD 0x8254E4
    strcpy(path, "SOFTWARE\\Westwood\\WOLAPI\\");
    LONG result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, path, 0, KEY_ALL_ACCESS, &key);
    if (result == 0) {
        data = result;
        // STRING: GAMEMD 0x8254DC
        if (RegQueryValueExA(key, "Options", 0, &type, (LPBYTE)&data, &size) == 0 && type == 4) {
            option->isPresent = true;
            option->value = data;
        }
        RegCloseKey(key);
    }
    return option->isPresent;
}
