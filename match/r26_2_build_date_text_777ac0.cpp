// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x777AC0 and the format string at 0x849F20 in the user's gamemd.exe
//   v1.001.
//
// Address index: 0x777AC0

#include <windows.h>
#include <stdio.h>

// GLOBAL: GAMEMD 0x822D5C -- the build time stamp.
extern FILETIME DAT_00822D5C;

// FUNCTION: GAMEMD 0x777AC0
// Format the build time stamp as "MM/DD/YYYY - HH:MM:SS" into the buffer.
void __fastcall FUN_00777AC0(char* text)
{
    SYSTEMTIME time;
    if (FileTimeToSystemTime(&DAT_00822D5C, &time)) {
        sprintf(text,
            // STRING: GAMEMD 0x849F20
            "%02d/%02d/%04d - %02d:%02d:%02d",
            time.wMonth, time.wDay, time.wYear, time.wHour, time.wMinute, time.wSecond);
    }
}
