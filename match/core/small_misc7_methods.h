// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC7_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC7_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "vec3d_layout.h"

// GLOBAL: GAMEMD 0x89E008 / 0x89E020 / 0x89DFD4 — reset with the record.
extern int  DAT_0089E008;
extern int  DAT_0089E020;
extern int  DAT_0089DFD4;
// VTABLE: GAMEMD 0x7E4AB8
extern char VT_007E4AB8[];

struct Obj_004035F0;
Obj_004035F0* FUN_004035F0(void* self, int kind);        // GAMEMD 0x4035F0
void          FUN_00402440(Obj_004035F0* p, int arg);    // GAMEMD 0x402440

struct Obj_004036C0
{
    // FUNCTION: GAMEMD 0x4036C0
    Obj_004035F0* __fastcall FUN_004036C0(int arg);
};

// Takes its argument as a double and returns one — the value is marshalled
// through the stack (`SUB ESP,8; FSTP qword ptr [ESP]`), not the FPU stack.
double __cdecl FUN_004CAC40(double v);   // GAMEMD 0x4CAC40

#endif  // GG_MATCH_CORE_SMALL_MISC7_METHODS_H
