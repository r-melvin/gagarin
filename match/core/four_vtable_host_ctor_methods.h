// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x43B680. The two embedded vectors sit at +0x66C and
//   +0x684 and have their base constructor inlined, so their four base stores
//   appear literally (Vector, VectorMax, IsValid, IsAllocated) followed by the
//   derived vptr, GrowthStep and ActiveCount. Field names follow RA1's
//   VectorClass/DynamicVectorClass (structure reference only).
#ifndef GG_MATCH_CORE_FOUR_VTABLE_HOST_CTOR_METHODS_H
#define GG_MATCH_CORE_FOUR_VTABLE_HOST_CTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7E3EBC / 0x7E3EA0 / 0x7E3E98 / 0x7E3E90 — four vtables on one
// object, so this is a multiply-derived (COM-style) class.
extern void* const VTBL_007E3EBC[];
extern void* const VTBL_007E3EA0[];
extern void* const VTBL_007E3E98[];
extern void* const VTBL_007E3E90[];
// VTABLE: GAMEMD 0x7E43C8 — shared by both embedded vectors.
extern void* const VTBL_007E43C8[];

// GLOBAL: GAMEMD 0xA8ED84 — the engine frame counter.
extern int DAT_00A8ED84;

struct Vec_0043B680
{
    const void* Vptr;        // +0x0000
    const void* Vector;      // +0x0004
    int   VectorMax;         // +0x0008
    char  IsValid;           // +0x000C
    char  IsAllocated;       // +0x000D
    char  _pad00E[2];        // +0x000E
    int   ActiveCount;       // +0x0010
    int   GrowthStep;        // +0x0014
};
GG_STATIC_ASSERT(sizeof(Vec_0043B680) == 0x18);

struct Host_0043B680
{
    const void* Vptr0;       // +0x0000
    const void* Vptr1;       // +0x0004
    const void* Vptr2;       // +0x0008
    const void* Vptr3;       // +0x000C
    char _pad010[0x610];     // +0x0010
    int  At_620;             // +0x0620
    char At_624;             // +0x0624
    char _pad625[0x3];       // +0x0625
    int  Stamp;              // +0x0628  seeded from the frame counter
    char _pad62C[0x4];       // +0x062C
    int  At_630;             // +0x0630
    int  At_634;             // +0x0634
    int  At_638;             // +0x0638
    char _pad63C[0x30];      // +0x063C
    Vec_0043B680 FirstVec;   // +0x066C
    Vec_0043B680 SecondVec;  // +0x0684

    // FUNCTION: GAMEMD 0x6F4300 — the base constructor.
    void BaseCtor(int arg);

    // FUNCTION: GAMEMD 0x43B680
    Host_0043B680* Ctor(int arg);
};
GG_STATIC_ASSERT(offsetof(Host_0043B680, At_620) == 0x620);
GG_STATIC_ASSERT(offsetof(Host_0043B680, Stamp) == 0x628);
GG_STATIC_ASSERT(offsetof(Host_0043B680, At_638) == 0x638);
GG_STATIC_ASSERT(offsetof(Host_0043B680, FirstVec) == 0x66C);
GG_STATIC_ASSERT(offsetof(Host_0043B680, SecondVec) == 0x684);

#endif  // GG_MATCH_CORE_FOUR_VTABLE_HOST_CTOR_METHODS_H
