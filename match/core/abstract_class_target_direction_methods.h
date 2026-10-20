// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Slots, argument slots and constants read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x5F3DB0: the
//   `[EAX+0x48]` slot on both the target and `this` (each handed a 12-byte
//   stack buffer), the X/Y reads at +0x0/+0x4 of the returned pointers, the
//   doubles at 0x7E2820 (1.5707963267948966) and 0x7E2818
//   (-10430.060040584269) via `ghidra memory read`, and the dword copy out
//   through the first stack argument. YRpp names the function
//   (AbstractClass::GetTargetDirection) and slot 18 (GetCoords) - name-only
//   cross-check. The AbstractClass base layout is match/_layout/abstract_class.h.
#ifndef GG_MATCH_CORE_ABSTRACT_CLASS_TARGET_DIRECTION_METHODS_H
#define GG_MATCH_CORE_ABSTRACT_CLASS_TARGET_DIRECTION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// FUNCTION: GAMEMD 0x4CAE30 (decl; reloc) — two-argument arctangent, __cdecl.
double __cdecl FUN_004CAE30(double y, double x);

struct Coord_005F3DB0
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_005F3DB0) == 0xC);

// Four bytes with only the low word computed: retail writes
// `MOV word ptr [ESP+0x2C],AX` and copies the whole dword out.
struct Dir_005F3DB0
{
    short Value;      // +0x0000
    short Unwritten;  // +0x0002
};
GG_STATIC_ASSERT(sizeof(Dir_005F3DB0) == 4);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_005F3DB0;

struct Obj_005F3DB0
{
    Vtbl_005F3DB0* Vtbl;   // +0x0000  (the first of AbstractClass's four vptrs)

    // FUNCTION: GAMEMD 0x5F3DB0
    Dir_005F3DB0* FUN_005F3DB0(Dir_005F3DB0* result, Obj_005F3DB0* target);
};

typedef Coord_005F3DB0* (Obj_005F3DB0::*Fn48_005F3DB0)(Coord_005F3DB0* buffer);

struct Vtbl_005F3DB0
{
    char _pad000[0x48];      // +0x0000
    Fn48_005F3DB0 At_48;     // +0x0048  YRpp: GetCoords
};
GG_STATIC_ASSERT(offsetof(Vtbl_005F3DB0, At_48) == 0x48);

#endif  // GG_MATCH_CORE_ABSTRACT_CLASS_TARGET_DIRECTION_METHODS_H
