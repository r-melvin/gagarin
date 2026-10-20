// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, slot displacements and vtable addresses read numerically off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI at 0x43A600.
//
// The destructor for the object whose release loop is already matched at
// 0x43A670. This TU gives the same object a *fuller* layout than
// small_misc38_methods.h does: what that header models as an opaque `Sub` with
// a vtable at +0x04 is a whole DynamicVectorClass embedded there, and this
// function reaches its buffer, its IsAllocated byte and its capacity word.
//
// The correspondence is exact - the vector's Items at +0x04+0x04 is the same
// word as the outer Items at +0x08, and its Count at +0x04+0x10 is the outer
// Count at +0x14. The two views are kept separate rather than merged so the
// already-matched functions in small_misc38 are left untouched.
#ifndef GG_MATCH_CORE_VECTOR_OWNER_DTOR_METHODS_H
#define GG_MATCH_CORE_VECTOR_OWNER_DTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

extern char VT_007E3E74;   // VTABLE: GAMEMD 0x7E3E74 — the owner
extern char VT_007E3E54;   // VTABLE: GAMEMD 0x7E3E54 — the embedded vector

struct Item_0043A600
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vt_020(int flag);   // +0x0020
};

struct Vector_0043A600
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();           // +0x000C

    Item_0043A600** Items;         // +0x0004
    int             Capacity;      // +0x0008
    char            _pad00C[0x1];
    char            IsAllocated;   // +0x000D
    char            _pad00E[0x10 - 0x0E];
    int             Count;         // +0x0010
};
GG_STATIC_ASSERT(offsetof(Vector_0043A600, IsAllocated) == 0xD);
GG_STATIC_ASSERT(offsetof(Vector_0043A600, Count) == 0x10);

struct Owner_0043A600
{
    char*           Vtable;   // +0x0000
    Vector_0043A600 Items;    // +0x0004

    // FUNCTION: GAMEMD 0x43A600
    void FUN_0043A600();
};
GG_STATIC_ASSERT(offsetof(Owner_0043A600, Items) == 0x4);

#endif  // GG_MATCH_CORE_VECTOR_OWNER_DTOR_METHODS_H
