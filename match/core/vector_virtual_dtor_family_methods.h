// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x765960 and its three duplicates: the plain destructor of
//   a vector whose element block is released through the element's own
//   virtual vector-deleting destructor (`PUSH 3; CALL [EAX]`) instead of the
//   CRT free. The extra null test before that call is the compiler's own
//   guard on a delete expression, not a source-level test. Members: the items
//   pointer at +4, the capacity at +8, the allocated flag at +0xD.
#ifndef GG_MATCH_CORE_VECTOR_VIRTUAL_DTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_VIRTUAL_DTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct VirtElem_00765960
{
    virtual ~VirtElem_00765960();
};

struct VirtVector_00765960
{
    char*              Vptr;         // +0x0000
    VirtElem_00765960* Items;        // +0x0004
    int                Capacity;     // +0x0008
    char               _pad00C;      // +0x000C
    char               IsAllocated;  // +0x000D
};
GG_STATIC_ASSERT(offsetof(VirtVector_00765960, Items) == 0x4);
GG_STATIC_ASSERT(offsetof(VirtVector_00765960, Capacity) == 0x8);
GG_STATIC_ASSERT(offsetof(VirtVector_00765960, IsAllocated) == 0xD);

// FUNCTION: GAMEMD 0x00765960
void __fastcall FUN_0000765960(VirtVector_00765960* self);
// FUNCTION: GAMEMD 0x00766D30
void __fastcall FUN_0000766D30(VirtVector_00765960* self);
// FUNCTION: GAMEMD 0x00769F50
void __fastcall FUN_0000769F50(VirtVector_00765960* self);
// FUNCTION: GAMEMD 0x0076B9E0
void __fastcall FUN_000076B9E0(VirtVector_00765960* self);

#endif  // GG_MATCH_CORE_VECTOR_VIRTUAL_DTOR_FAMILY_METHODS_H
