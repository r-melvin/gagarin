// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x412870. The array base is 0x887888, the stride 0x18
//   (`ADD ESI,0x18`) and the count 0x190 (`MOV EDI,0x190`), which places the
//   single trailing instance at 0x887888 + 0x190*0x18 = 0x889E08 — exactly the
//   address the tail stores reach. Field names are the project's YRpp-cross-checked vector names; the offsets
//   are the binary's.
#ifndef GG_MATCH_CORE_VECTOR_ARRAY_INIT_METHODS_H
#define GG_MATCH_CORE_VECTOR_ARRAY_INIT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7E17AC — shared by the array and the trailing instance.
extern void* const VTBL_007E17AC[];

// Declaration order per match/_rt/gg_vslot.h: the element must be complete
// before the member-pointer typedefs, so the vtable is forward-declared here and
// defined after the class.
struct Vtbl_00412870;

struct Vec_00412870
{
    Vtbl_00412870* Vptr;     // +0x0000
    const void* Vector;      // +0x0004
    int   Capacity;         // +0x0008
    char  IsValid;           // +0x000C
    char  IsAllocated;       // +0x000D
    char  _pad00E[2];        // +0x000E
    int   Count;       // +0x0010
    int   CapacityIncrement;        // +0x0014

    // FUNCTION: GAMEMD 0x40BD00 — the VectorClass base constructor.
    void BaseCtor(unsigned int size, const void* array);
};
GG_STATIC_ASSERT(sizeof(Vec_00412870) == 0x18);

typedef int (Vec_00412870::*Fn08_00412870)(int capacity, int keep);
typedef int (Vec_00412870::*Fn0C_00412870)();

struct Vtbl_00412870
{
    char _pad000[0x8];           // +0x0000
    Fn08_00412870 At_08;         // +0x0008
    Fn0C_00412870 At_0C;         // +0x000C
};
GG_STATIC_ASSERT(offsetof(Vtbl_00412870, At_0C) == 0xC);

// VTABLE: GAMEMD 0x7E180C — installed on every element as it is torn down.
extern void* const VTBL_007E180C[];
GG_STATIC_ASSERT(offsetof(Vec_00412870, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(Vec_00412870, CapacityIncrement) == 0x14);

// GLOBAL: GAMEMD 0x887888 — the array.
extern Vec_00412870 DAT_00887888[0x190];
// GLOBAL: GAMEMD 0x889E08 — the trailing instance.
extern Vec_00412870 DAT_00889E08;

extern "C" void __cdecl FUN_007C8B3D(void* block);   // GAMEMD 0x7C8B3D

// FUNCTION: GAMEMD 0x7C978A — atexit.
extern "C" int __cdecl FUN_007C978A(void (__cdecl* fn)());
// FUNCTION: GAMEMD 0x4128F0 — the matching teardown, registered by 0x412870 and
// defined in the same TU.
extern "C" void __cdecl FUN_004128F0_atexit();

// FUNCTION: GAMEMD 0x412870
void FUN_00412870();
// FUNCTION: GAMEMD 0x4128F0
void __cdecl FUN_004128F0();

#endif  // GG_MATCH_CORE_VECTOR_ARRAY_INIT_METHODS_H
