// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4109C0. The three globals it touches — 0xA8E968, 0xA8E96C
//   and 0xA8E978 — are 0x0, 0x4 and 0x10 into one vector object, so they are
//   modelled as its vptr, Items and Count. The removal is RA1's
//   DynamicVectorClass::Delete (structure reference only).
#ifndef GG_MATCH_CORE_DEREGISTERING_DTOR_METHODS_H
#define GG_MATCH_CORE_DEREGISTERING_DTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// VTABLE: GAMEMD 0x7E2000 / 0x7E1FE4 / 0x7E1FDC / 0x7E1FD4
extern void* const VTBL_007E2000[];
extern void* const VTBL_007E1FE4[];
extern void* const VTBL_007E1FDC[];
extern void* const VTBL_007E1FD4[];

struct Obj_004109C0;

// Declaration order per match/_rt/gg_vslot.h.
struct RegistryVtbl_004109C0;

struct Registry_004109C0
{
    RegistryVtbl_004109C0* Vptr;   // +0x0000  (0xA8E968)
    Obj_004109C0** Items;          // +0x0004  (0xA8E96C)
    char _pad008[0x8];             // +0x0008
    int  Count;                    // +0x0010  (0xA8E978)
};
GG_STATIC_ASSERT(offsetof(Registry_004109C0, Items) == 0x4);
GG_STATIC_ASSERT(offsetof(Registry_004109C0, Count) == 0x10);

// Slot +0x10 takes the *address* of the caller's pointer (`LEA EAX,[ESP+4]` then
// `PUSH EAX`), which is RA1's `ID(T const &)` overload with T = Obj*.
typedef int (Registry_004109C0::*FnID_004109C0)(Obj_004109C0* const* item);

struct RegistryVtbl_004109C0
{
    char _pad000[0x10];            // +0x0000
    FnID_004109C0 ID;              // +0x0010
};
GG_STATIC_ASSERT(offsetof(RegistryVtbl_004109C0, ID) == 0x10);

// GLOBAL: GAMEMD 0xA8E968
extern Registry_004109C0 DAT_00A8E968;

struct Obj_004109C0
{
    const void* Vptr0;    // +0x0000
    const void* Vptr1;    // +0x0004
    const void* Vptr2;    // +0x0008
    const void* Vptr3;    // +0x000C

    // FUNCTION: GAMEMD 0x4101F0 — the base destructor.
    void BaseDtor();

    // FUNCTION: GAMEMD 0x4109C0
    void Dtor();
};

#endif  // GG_MATCH_CORE_DEREGISTERING_DTOR_METHODS_H
