// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x69A340 in the user's gamemd.exe v1.001.
//
// Address index: 0x69A340

#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <string.h>

// FUNCTION: GAMEMD 0x48DD50 (decl; reloc)
unsigned long __fastcall FUN_0048DD50();
// FUNCTION: GAMEMD 0x64DE80 (decl; reloc) -- rotate the running checksum left one bit and add a value.
void __fastcall FUN_0064DE80(unsigned long* accumulator, unsigned long value);

// FUNCTION: GAMEMD 0x69A340
// Build a checksum from the tick count, FUN_0048DD50 and the PATH environment string.
unsigned long FUN_0069A340()
{
    unsigned long value = timeGetTime();
    FUN_0064DE80(&value, FUN_0048DD50());
    const char* path = getenv("PATH");
    if (path) {
        for (unsigned int index = 0; index < strlen(path); ++index)
            FUN_0064DE80(&value, path[index]);
    }
    return value;
}
