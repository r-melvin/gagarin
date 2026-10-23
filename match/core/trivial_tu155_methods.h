// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU155_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU155_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005D5850;

// LIBRARY: GAMEMD 0x7C93E8 (declaration)
void __cdecl FUN_007C93E8(int);
// Import timeEndPeriod from WINMM.dll (IAT slot 0x7E152C)
extern "C" __declspec(dllimport) void __stdcall timeEndPeriod(int);
// Import timeGetTime from WINMM.dll (IAT slot 0x7E1530)
extern "C" __declspec(dllimport) void __stdcall timeGetTime();

struct Obj_005D5850
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x5D5850
    void FUN_005D5850();
};
GG_STATIC_ASSERT(offsetof(Obj_005D5850, unknown_00) == 0x0);


// FUNCTION: GAMEMD 0x5D5860
void __stdcall FUN_005D5860(int a1);
// FUNCTION: GAMEMD 0x5D5880
void __cdecl FUN_005D5880();
// FUNCTION: GAMEMD 0x5D58A0
void __cdecl FUN_005D58A0();

#endif  // GG_MATCH_CORE_TRIVIAL_TU155_METHODS_H
