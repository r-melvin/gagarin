// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4DA0E0: the byte `MOV byte ptr [EDI+0x6B1],1/0`, the
//   NavQueue vector `LEA ESI,[EDI+0x5AC]` with its Capacity `[EDI+0x5B4]`,
//   Count `[EDI+0x5BC]`, IsAllocated `MOV AL,[ESI+0xD]`, CapacityIncrement
//   `[ESI+0x14]`, Items `[ESI+0x4]` and Resize `CALL [EDX+0x8]` (the
//   inlined DynamicVectorClass::AddItem), Destination `[EDI+0x5A4]`, the
//   virtuals `CALL [EAX+0x184]` (no args, compared with 5) and
//   `CALL [EDX+0x484]` (pushed 0, 1), the link accessor CALL 0x65AD30 with a
//   pushed 0, the link's `CALL [EDX+0x2C]` (WhatAmI, compared with 6), its
//   type at `[ESI+0x520]` and the type byte `[EAX+0x16BD]`. All FootClass
//   offsets agree with match/_layout/foot_class.h, which is included; the
//   vector is re-typed locally because the shared DynamicVectorClass carries
//   no byte-granular IsAllocated and no AddItem. Method name from YRpp
//   FootClass.h (consult-only; name only).
#ifndef GG_MATCH_MOVEMENT_FOOT_CLASS_NAV_LIST_METHODS_H
#define GG_MATCH_MOVEMENT_FOOT_CLASS_NAV_LIST_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/foot_class.h"   // FootClass: Destination @0x5A4, NavQueue @0x5AC, unknown_bool_6B1

struct AbstractClass;

// DynamicVectorClass<AbstractClass*> as retail reads it at the AddItem site:
// slot +0x08 is Resize(newCapacity, array), the allocation flag is the byte
// at +0x0D.
struct NavVector_004DA0E0
{
    virtual void vt_000();
    virtual void vt_004();
    virtual bool Resize(int newCapacity, void* array);   // +0x0008

    AbstractClass** Items;         // +0x0004
    int   Capacity;                // +0x0008
    char  _pad0C[0x1];
    char  IsAllocated;             // +0x000D
    char  _pad0E[0x10 - 0x0E];
    int   Count;                   // +0x0010
    int   CapacityIncrement;       // +0x0014

    // DynamicVectorClass::AddItem, expanded inline by VC6 at the call site.
    // Same phrasing as match/map/cell_class_tag_methods.h (0x485250).
    bool AddItem(AbstractClass* item)
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
GG_STATIC_ASSERT(offsetof(NavVector_004DA0E0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(NavVector_004DA0E0, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(NavVector_004DA0E0, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(NavVector_004DA0E0, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(NavVector_004DA0E0, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(NavVector_004DA0E0) == 0x18);
GG_STATIC_ASSERT(sizeof(NavVector_004DA0E0) == sizeof(DynamicVectorClassLayout));

// The building type of the radio link: only the byte at +0x16BD is read.
struct BuildingType_004DA0E0
{
    char _pad0000[0x16BD];    // +0x0000
    char At_16BD;             // +0x16BD
};
GG_STATIC_ASSERT(offsetof(BuildingType_004DA0E0, At_16BD) == 0x16BD);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct LinkVtbl_004DA0E0;

// The radio link (a BuildingClass when WhatAmI says 6): Type @0x520.
struct Link_004DA0E0
{
    LinkVtbl_004DA0E0*      Vtbl;       // +0x0000
    char                    _pad004[0x520 - 4];
    BuildingType_004DA0E0*  Type;       // +0x0520
};
GG_STATIC_ASSERT(offsetof(Link_004DA0E0, Type) == 0x520);

typedef int (Link_004DA0E0::*Fn02C_004DA0E0)();

struct LinkVtbl_004DA0E0
{
    char           _pad000[0x2C];    // +0x0000
    Fn02C_004DA0E0 WhatAmI;          // +0x002C
};
GG_STATIC_ASSERT(offsetof(LinkVtbl_004DA0E0, WhatAmI) == 0x2C);

struct NavVtbl_004DA0E0;

// No-data host over the committed FootClass spine; layout identical.
struct FootNav : FootClass
{
    // FUNCTION: GAMEMD 0x65AD30 (decl; reloc) — n-th radio link.
    Link_004DA0E0* FUN_0065AD30(int index);

    // FUNCTION: GAMEMD 0x4DA0E0
    void QueueNavigationList(AbstractClass* target);
};
GG_STATIC_ASSERT(sizeof(FootNav) == sizeof(FootClass));

typedef int  (FootNav::*Fn184_004DA0E0)();
typedef bool (FootNav::*Fn484_004DA0E0)(int initial, int unused);

struct NavVtbl_004DA0E0
{
    char           _pad000[0x184];             // +0x0000
    Fn184_004DA0E0 GetCurrentMission;          // +0x0184
    char           _pad188[0x484 - 0x188];     // +0x0188
    Fn484_004DA0E0 EnterIdleMode;              // +0x0484
};
GG_STATIC_ASSERT(offsetof(NavVtbl_004DA0E0, GetCurrentMission) == 0x184);
GG_STATIC_ASSERT(offsetof(NavVtbl_004DA0E0, EnterIdleMode) == 0x484);

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_NAV_LIST_METHODS_H
