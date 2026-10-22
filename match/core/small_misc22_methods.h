// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC22_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC22_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef void (__fastcall* ElemFn2)(void* elem);

// FUNCTION: GAMEMD 0x40AFD0 — the backwards counterpart of the forward walk at
// 0x4068F0. The cursor starts one past the end and steps back before each call,
// so the first element visited is the last one.
void __stdcall FUN_0040AFD0(char* base, int stride, int count, ElemFn2 fn);

struct Obj_00432690
{
    // __thiscall: retail pushes the argument rather than passing it in EDX.
    void FUN_00432750(int arg);   // GAMEMD 0x432750

    unsigned char unknown_00;   // +0x0000
    char          _pad01[0x3];
    int           unknown_04;   // +0x0004
    char          _pad08[0x4];
    int           unknown_0C;   // +0x000C
    char          _pad10[0x20 - 0x10];
    int           unknown_20;   // +0x0020
    char          _pad24[0x4];
    int           unknown_28;   // +0x0028
    unsigned char unknown_2C;   // +0x002C
    unsigned char unknown_2D;   // +0x002D

    // FUNCTION: GAMEMD 0x432690
    Obj_00432690* FUN_00432690(int arg);
    // FUNCTION: GAMEMD 0x4326C0 — the same construction with an extra field
    // taken from a second argument.
    Obj_00432690* FUN_004326C0(int arg, int extra);
};
GG_STATIC_ASSERT(offsetof(Obj_00432690, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(Obj_00432690, unknown_2D) == 0x2D);

#endif  // GG_MATCH_CORE_SMALL_MISC22_METHODS_H
