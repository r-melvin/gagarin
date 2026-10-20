// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x659110: `PUSH 0xC8` into operator new (the object
//   size), `FSTP qword [EDI+0x18]` (the double written after allocation), and
//   the global vector at 0xB04A60 read as `[0xB04A68]` capacity, `[0xB04A6D]`
//   byte allocated flag, `[0xB04A70]` count, `[0xB04A74]` increment,
//   `[0xB04A64]` items, with its slot +0x08 reached through
//   `MOV EAX,[0xB04A60]; CALL [EAX+8]`. The method name and the vector's
//   identity (RadBeam::Array) are cross-checked against YRpp RadBeam.h
//   (consult-only, no LICENSE).
#ifndef GG_MATCH_COMBAT_RAD_BEAM_ALLOCATE_METHODS_H
#define GG_MATCH_COMBAT_RAD_BEAM_ALLOCATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct RadBeam;

// DynamicVectorClass<RadBeam*> — the live-beam list. Slot +0x08 is
// Resize(newCapacity, array): two stack arguments, `this` in ECX, a byte
// result tested with `TEST AL,AL`.
struct RadBeamVector
{
    virtual void vt_000();
    virtual void vt_004();
    virtual bool Resize(int newCapacity, void* array);   // +0x0008

    RadBeam** Items;           // +0x0004
    int   Capacity;            // +0x0008
    char  _pad0C[0x1];
    char  IsAllocated;         // +0x000D
    char  _pad0E[0x10 - 0x0E];
    int   Count;               // +0x0010
    int   CapacityIncrement;   // +0x0014

    // DynamicVectorClass::AddItem, expanded inline by VC6 at the Allocate call
    // site. Same phrasing as match/map/cell_class_tag_methods.h (0x485250):
    // Capacity bound to a local so the vtable load stays ahead of the argument
    // pushes, and `Count++` bound to an index so the increment is sequenced
    // before the store.
    bool AddItem(RadBeam* item)
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
GG_STATIC_ASSERT(offsetof(RadBeamVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(RadBeamVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(RadBeamVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(RadBeamVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(RadBeamVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(RadBeamVector) == 0x18);

// GLOBAL: GAMEMD 0xB04A60 — RadBeam::Array (an object, not a pointer: retail
// loads its address as the immediate `MOV ECX,0xB04A60`).
extern RadBeamVector DAT_00B04A60;

// RadBeam — 0xC8 bytes (the operator new size). No vtable: the constructor
// zeroes the first dword. Only the double at +0x18 is touched here.
struct RadBeam
{
    char   _pad000[0x18];         // +0x0000
    double At_18;                 // +0x0018  10 for type 1, 20 otherwise
    char   _pad020[0xC8 - 0x20];  // +0x0020

    // FUNCTION: GAMEMD 0x6593F0 (decl; reloc) — the constructor, one stack
    // argument (the beam type).
    RadBeam(int type) throw();

    // FUNCTION: GAMEMD 0x659110
    static RadBeam* __fastcall Allocate(int type);
};
GG_STATIC_ASSERT(offsetof(RadBeam, At_18) == 0x18);
GG_STATIC_ASSERT(sizeof(RadBeam) == 0xC8);

#endif  // GG_MATCH_COMBAT_RAD_BEAM_ALLOCATE_METHODS_H
