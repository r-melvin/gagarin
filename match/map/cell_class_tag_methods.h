// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x485250: `[ESI+0x3C]` (the attached tag), `[EAX+0x2C]`
//   / `[ESI+0x2C]` (the tag's instance count, DEC/INC'd), `[ESI+0x24]` (the
//   cell's map coordinate, stored into the vector). The vector at 0x880944 is
//   read as `[0x88094C]` capacity, `[0x880951]` byte allocated flag,
//   `[0x880954]` count, `[0x880958]` increment, `[0x880948]` items, and its
//   slot +0x08 is reached through `MOV EAX,[0x880944]; CALL [EAX+8]`. Names
//   (ReplaceTag, AttachedTag, InstanceCount) cross-checked against YRpp.
#ifndef GG_MATCH_MAP_CELL_CLASS_TAG_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_TAG_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 0x4);

#include "../_layout/tag_class.h"

// DynamicVectorClass<CellStruct> — the "cells carrying a tag" list. Slot +0x08
// is Resize(newCapacity, array): two stack arguments, `this` in ECX, a byte
// result tested with `TEST AL,AL`.
struct TaggedCellVector
{
    virtual void vt_000();
    virtual void vt_004();
    virtual bool Resize(int newCapacity, void* array);   // +0x0008

    CellStruct* Items;         // +0x0004
    int   Capacity;            // +0x0008
    char  _pad0C[0x1];
    char  IsAllocated;         // +0x000D
    char  _pad0E[0x10 - 0x0E];
    int   Count;               // +0x0010
    int   CapacityIncrement;   // +0x0014

    // DynamicVectorClass::AddItem, expanded inline by VC6 at the ReplaceTag
    // call site (retail keeps the virtual Resize dispatch through `this`, so
    // the body must reach Resize via a member call, not on the global object,
    // which VC6 would devirtualise).
    //
    // Capacity is bound to a local: with the member re-read at each use VC6
    // sinks the vtable load below the argument pushes and puts the new size in
    // EAX (`ADD EAX,ECX; PUSH 0; PUSH EAX; MOV EAX,[vtbl]`), scoring 90.2%;
    // with the local it keeps retail's `ADD ECX,EAX; MOV EAX,[vtbl]; PUSH 0;
    // PUSH ECX`. The index is `Count++` bound to a local so the increment is
    // sequenced before the store (`MOV EAX,ECX; INC ECX`), where
    // `Items[Count++]` re-reads Count after the store and `index = Count;
    // Count = index + 1` becomes an LEA.
    bool AddItem(const CellStruct& item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && Resize(cap + CapacityIncrement, 0))) {
            int index = Count++;
            Items[index] = item;
            return true;
        }
        return false;
    }
};
GG_STATIC_ASSERT(offsetof(TaggedCellVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(TaggedCellVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(TaggedCellVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(TaggedCellVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(TaggedCellVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(TaggedCellVector) == 0x18);

// GLOBAL: GAMEMD 0x880944 — the tagged-cell vector (an object, not a pointer:
// retail loads its address as the immediate `MOV ECX,0x880944`).
extern TaggedCellVector DAT_00880944;

#include "../_layout/cell_class.h"

#endif  // GG_MATCH_MAP_CELL_CLASS_TAG_METHODS_H
