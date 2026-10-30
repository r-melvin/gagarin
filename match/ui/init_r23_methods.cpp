// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Matched against retail gamemd.exe v1.001 (round 23); disassembled from the entry point. Same
//   original translation unit as Init.cpp.
//
// Address index: 0x534DE0

#include "../platform/mix_file_class.h"

extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// GLOBAL: GAMEMD 0x884E58 -- the loaded NTRLMD.MIX archive.
extern MixFileClass* DAT_00884E58;
// GLOBAL: GAMEMD 0x884E5C -- the loaded NEUTRAL.MIX archive.
extern MixFileClass* DAT_00884E5C;

// GLOBAL: GAMEMD 0x81C320 -- "     Releasing %s\n"
extern const char STR_0081C320[];

// FUNCTION: GAMEMD 0x534DE0
// Log and free the two neutral-theatre mix archives, NEUTRAL.MIX first.
bool FUN_00534DE0()
{
    if (DAT_00884E5C) {
        FUN_004068E0(STR_0081C320, DAT_00884E5C->FileName);
        delete DAT_00884E5C;
        DAT_00884E5C = 0;
    }
    if (DAT_00884E58) {
        FUN_004068E0(STR_0081C320, DAT_00884E58->FileName);
        delete DAT_00884E58;
        DAT_00884E58 = 0;
    }
    return true;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x884E58
MixFileClass* DAT_00884E58;
// GLOBAL: GAMEMD 0x884E5C
MixFileClass* DAT_00884E5C;
// GLOBAL: GAMEMD 0x81C320
extern const char STR_0081C320[] = "     Releasing %s\n";
// END defined globals
