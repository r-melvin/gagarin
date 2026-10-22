// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every offset, the virtual slot and the growth policy are read numerically
//   off the user's retail gamemd.exe v1.001 via the local Ghidra CLI at
//   0x413A70 and 0x42D830.
//
// Two instances of DynamicVectorClass<T>::AddItem for a 4-byte T. The pair is
// byte-identical; each is written out longhand rather than shared, per the
// family rule.
//
// Layout confirmed from the member accesses themselves:
//   +0x00  vtable            (`MOV EDX,[ESI]` then `CALL [EDX+8]`)
//   +0x04  Items             (`MOV EDX,[ESI+4]`, indexed `[EDX+EAX*4]`)
//   +0x08  Capacity          (compared against Count, and added to the step)
//   +0x0D  IsAllocated       (byte, `MOV AL,[ESI+0xD]`)
//   +0x10  Count             (post-incremented via `LEA ECX,[EAX+1]`)
//   +0x14  CapacityIncrement (`JLE` on it, so signed)
// The `[EDX+EAX*4]` scale pins the element at 4 bytes, and the argument is
// dereferenced once (`MOV ECX,[ECX]`) before the store, so it arrives by
// reference rather than by value.
#ifndef GG_MATCH_CORE_VECTOR_ADD_ITEM_METHODS_H
#define GG_MATCH_CORE_VECTOR_ADD_ITEM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct VectorAddTarget
{
    // Slot +0x08 is Resize(newCapacity, array): two stack arguments, `this` in
    // ECX, a byte result tested with `TEST AL,AL`.
    virtual void vt_000();
    virtual void vt_004();
    virtual bool Resize(int newCapacity, void* array);   // +0x0008

    void* Items;              // +0x0004
    int   Capacity;           // +0x0008
    char  _pad0C[0x1];
    char  IsAllocated;        // +0x000D
    char  _pad0E[0x10 - 0x0E];
    int   Count;              // +0x0010
    int   CapacityIncrement;  // +0x0014

    // FUNCTION: GAMEMD 0x413A70
    bool FUN_00413A70(const int& item);
    // FUNCTION: GAMEMD 0x42D830
    bool FUN_0042D830(const int& item);
    // FUNCTION: GAMEMD 0x439030
    // By *value*, not by reference: retail stores the argument word straight
    // into the slot (`MOV ECX,[ESP+8]; MOV [EDX+EAX*4],ECX`) with no
    // dereference, unlike the pair above.
    void FUN_00439030(int item);
};
GG_STATIC_ASSERT(offsetof(VectorAddTarget, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(VectorAddTarget, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(VectorAddTarget, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(VectorAddTarget, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(VectorAddTarget, CapacityIncrement) == 0x14);

#endif  // GG_MATCH_CORE_VECTOR_ADD_ITEM_METHODS_H
