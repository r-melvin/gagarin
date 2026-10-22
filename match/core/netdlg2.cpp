// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit netdlg2.cpp. The name is the source-file string at 0x831288
//   in retail gamemd.exe v1.001, passed by the assert at 0x5db257 inside this object's
//   code range (0x5dacf0-0x5e242f). Functions are in ascending retail address order.
//
//   Reads the product serial from the registry and unscrambles it with the
//   bytes of the local key file.

#include "trivial_tu160_methods.h"

#include <windows.h>
#include <stdio.h>
#include <string.h>

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EEF08
extern const double DAT_007EEF08;
// GLOBAL: GAMEMD 0xAC01C0
extern double DAT_00AC01C0;
// GLOBAL: GAMEMD 0xAC0218
extern double DAT_00AC0218;
// GLOBAL: GAMEMD 0xAC0240
extern int DAT_00AC0240;
// GLOBAL: GAMEMD 0xAC0244
extern int DAT_00AC0244;
// GLOBAL: GAMEMD 0xAC0248
extern int DAT_00AC0248;
// GLOBAL: GAMEMD 0xAC0250
extern double DAT_00AC0250;

// FUNCTION: GAMEMD 0x5DAD20
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005DAD20()
{
    DAT_00AC0250 = DAT_00AC01C0 / DAT_007EEF08;
}

// FUNCTION: GAMEMD 0x5DAD40
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005DAD40()
{
    DAT_00AC0218 = DAT_007E1718 / DAT_00AC0250;
}

// FUNCTION: GAMEMD 0x5DAEC0
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_005DAEC0()
{
    DAT_00AC0248 = 0;
    DAT_00AC0240 = 0x80;
    DAT_00AC0244 = 0x80;
}

// FUNCTION: GAMEMD 0x5DAF10
// Empty function.
void __cdecl FUN_005DAF10()
{
}

// FUNCTION: GAMEMD 0x5DAFD0
// Tail-calls a method on a global object.
void FUN_005DAFD0(int a1, int a2)
{
    FUN_005DAFE0(0, a2);
}

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

// FUNCTION: GAMEMD 0x5DFDD0
// Empty function.
void __cdecl FUN_005DFDD0()
{
}

// FUNCTION: GAMEMD 0x5DFDE0
// Empty function.
void __cdecl FUN_005DFDE0()
{
}

// FUNCTION: GAMEMD 0x5DFDF0
// Empty function.
void __cdecl FUN_005DFDF0()
{
}
