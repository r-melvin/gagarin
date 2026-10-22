// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC7_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC7_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

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

// A three-double vector. 0x41C350 and 0x41C430 are byte-identical and are
// written out separately per the family rule. Both use the fields at +0x00 and
// +0x08 - the first two - and skip the third.
struct Vec3d
{
    double x;   // +0x0000
    double y;   // +0x0008
    double z;   // +0x0010

    // FUNCTION: GAMEMD 0x41C350
    double FUN_0041C350() const;
    // FUNCTION: GAMEMD 0x41C430
    double FUN_0041C430() const;
    // FUNCTION: GAMEMD 0x41C3C0 — the full three-component length, against
    // 0x41C350's two-component one.
    double FUN_0041C3C0() const;
    // FUNCTION: GAMEMD 0x46B960
    Vec3d* FUN_0046B960(const Vec3d* other);
};
GG_STATIC_ASSERT(offsetof(Vec3d, z) == 0x10);

struct Obj_00470C00
{
    char* _vtable;   // +0x0000

    // FUNCTION: GAMEMD 0x470C00
    Obj_00470C00* FUN_00470C00();
};

#endif  // GG_MATCH_CORE_SMALL_MISC7_METHODS_H
