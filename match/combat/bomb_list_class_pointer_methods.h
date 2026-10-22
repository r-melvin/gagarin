// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x439150. Address binding from YRpp
//   (`BombListClass::PointerGotInvalid`).
//
// The bomb vector sits at offset 0 of BombListClass — the existing sibling TU
// models it as an opaque `char Bombs[0x18]`, but this function calls a *virtual*
// on it (`MOV EAX,[ESI]; MOV ECX,ESI; CALL [EAX+0x10]`), with ESI serving as
// both the list and the vector. That only works if the vector is the object's
// own prefix, so it is modelled here as a real base class with the slot run up
// to +0x10.
#ifndef GG_MATCH_COMBAT_BOMB_LIST_CLASS_POINTER_METHODS_H
#define GG_MATCH_COMBAT_BOMB_LIST_CLASS_POINTER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct AbstractClass;

// BombClass — only the target back-pointer is needed (`CMP [EAX+0x24],EDI`).
struct BombClass
{
    char           _pad00[0x24];   // +0x0000
    AbstractClass* Target;         // +0x0024
};
GG_STATIC_ASSERT(offsetof(BombClass, Target) == 0x24);

// DynamicVectorClass<BombClass*> — vptr at +0x00, then the standard vector
// fields. FindItemIndex takes its argument by reference: retail hands it the
// address of a stack temporary (`LEA ECX,[ESP+8]; PUSH ECX`).
struct BombVectorClass
{
    virtual void v00() = 0;
    virtual void v04() = 0;
    virtual void v08() = 0;
    virtual void v0C() = 0;
    virtual int  FindItemIndex(BombClass* const& item);   // +0x10 (declared; reloc)

    BombClass** Items;         // +0x04
    int         Capacity;      // +0x08
    int         IsAllocated;   // +0x0C
    int         Count;         // +0x10
};
GG_STATIC_ASSERT(offsetof(BombVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(BombVectorClass, Count) == 0x10);

struct BombListClass : BombVectorClass
{
    void PointerGotInvalid(AbstractClass* invalid);   // GAMEMD 0x439150
};

#endif  // GG_MATCH_COMBAT_BOMB_LIST_CLASS_POINTER_METHODS_H
