// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x41D300. The global at 0x889FB8 is a DynamicVectorClass: its
//   fields fall at 0x889FB8 (vptr), 0x889FBC (Items), 0x889FC0 (Capacity),
//   0x889FC4/0x889FC5 (IsValid/IsAllocated), 0x889FC8 (Count) and 0x889FCC
//   (CapacityIncrement). The growth call goes through vtable slot +0x8 with the receiver in
//   ECX and two pushed arguments.
#ifndef GG_MATCH_CORE_REGISTERED_OBJECT_CTOR_METHODS_H
#define GG_MATCH_CORE_REGISTERED_OBJECT_CTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// VTABLE: GAMEMD 0x7E29A8 / 0x7E298C / 0x7E2984 / 0x7E297C — four vtables, so a
// multiply-derived class.
extern void* const VTBL_007E29A8[];
extern void* const VTBL_007E298C[];
extern void* const VTBL_007E2984[];
extern void* const VTBL_007E297C[];

struct Obj_0041D300;

// Declaration order per match/_rt/gg_vslot.h.
struct RegistryVtbl_0041D300;

struct Registry_0041D300
{
    RegistryVtbl_0041D300* Vptr;   // +0x0000  (0x889FB8)
    Obj_0041D300** Items;          // +0x0004  (0x889FBC)
    int  Capacity;                 // +0x0008  (0x889FC0)
    char IsValid;                  // +0x000C  (0x889FC4)
    char IsAllocated;              // +0x000D  (0x889FC5)
    char _pad00E[2];               // +0x000E
    int  Count;                    // +0x0010  (0x889FC8)
    int  CapacityIncrement;        // +0x0014  (0x889FCC)
};
GG_STATIC_ASSERT(offsetof(Registry_0041D300, Capacity) == 0x8);
GG_STATIC_ASSERT(offsetof(Registry_0041D300, IsAllocated) == 0xD);
GG_STATIC_ASSERT(offsetof(Registry_0041D300, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(Registry_0041D300, CapacityIncrement) == 0x14);

typedef char (Registry_0041D300::*FnSetCapacity_0041D300)(int capacity, int keep);

struct RegistryVtbl_0041D300
{
    char _pad000[0x8];                        // +0x0000
    FnSetCapacity_0041D300 SetCapacity;       // +0x0008
};
GG_STATIC_ASSERT(offsetof(RegistryVtbl_0041D300, SetCapacity) == 0x8);

// GLOBAL: GAMEMD 0x889FB8
extern Registry_0041D300 DAT_00889FB8;

struct Obj_0041D300
{
    const void* Vptr0;    // +0x0000
    const void* Vptr1;    // +0x0004
    const void* Vptr2;    // +0x0008
    const void* Vptr3;    // +0x000C

    // FUNCTION: GAMEMD 0x410170 — the base constructor.
    void BaseCtor();

    // FUNCTION: GAMEMD 0x41D300
    Obj_0041D300* Ctor();
};

#endif  // GG_MATCH_CORE_REGISTERED_OBJECT_CTOR_METHODS_H
