// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp or the
//   seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC6_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC6_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" __declspec(dllimport) void __stdcall BinkGoto(void* bink, int frame, int flags);  // IAT 0x7E15AC
extern "C" double __cdecl FUN_004CAC40(double v);   // GAMEMD 0x4CAC40

bool __fastcall FUN_005F4D30(void* self);                 // GAMEMD 0x5F4D30

// The append is __thiscall, not __fastcall: retail pushes the item and puts
// only the collection in ECX. A second register argument lands in EDX and the
// call site stops matching.
struct Collection_0087F778
{
    void FUN_0055BAE0(void* item);   // GAMEMD 0x55BAE0
};
// GLOBAL: GAMEMD 0x87F778 — the collection 0x437030 appends to.
extern Collection_0087F778 DAT_0087F778;

struct Obj_00401100
{
    char _pad00[0x2C];
    unsigned int unknown_2C;   // +0x002C

    // FUNCTION: GAMEMD 0x401190
    int __fastcall FUN_00401190(int value) const;
};
GG_STATIC_ASSERT(offsetof(Obj_00401100, unknown_2C) == 0x2C);

struct Obj_00408500c
{
    char _pad00[0x14];
    int  unknown_14;   // +0x0014

    // FUNCTION: GAMEMD 0x408540 — the second argument is accepted and unused.
    int FUN_00408540(int value, int unused) const;
};
GG_STATIC_ASSERT(offsetof(Obj_00408500c, unknown_14) == 0x14);

struct Obj_0042E410
{
    int a, b, c, d;   // +0x0000 .. +0x000C

    // FUNCTION: GAMEMD 0x42E410
    Obj_0042E410* FUN_0042E410(int w, int x, int y, int z);
};

struct Obj_00432BD0
{
    char  _pad00[0x4];
    void* Bink;        // +0x0004
    char  _pad08[0x30 - 0x08];
    int   unknown_30;  // +0x0030

    // FUNCTION: GAMEMD 0x432BD0
    void FUN_00432BD0(int frame);
};
GG_STATIC_ASSERT(offsetof(Obj_00432BD0, unknown_30) == 0x30);

struct Obj_00437030
{
    // FUNCTION: GAMEMD 0x437030
    bool FUN_00437030();
};

// A three-float vector. Both operators return the object, and both read the
// right-hand side *first*: retail loads the scalar or the other vector and then
// multiplies/adds the member into it, which is `x = s * x`, not `x *= s`.
struct Vec3f
{
    float x, y, z;

    // FUNCTION: GAMEMD 0x43A0D0
    Vec3f* FUN_0043A0D0(float s);
    // FUNCTION: GAMEMD 0x43A100
    Vec3f* FUN_0043A100(const Vec3f* other);
    // FUNCTION: GAMEMD 0x43A130 — length, with the components promoted to
    // double for the helper.
    double FUN_0043A130() const;
};

#endif  // GG_MATCH_CORE_SMALL_MISC6_METHODS_H
