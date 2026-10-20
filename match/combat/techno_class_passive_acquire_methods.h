// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x7091D0: the slots `[EAX+0x1DC]`, `[EDX+0x84]` (GetTechnoType,
//   whose result is read at `[EAX+0xD99]`), `[EAX+0x2C]` (WhatAmI, compared
//   with 6 = building), `[EDX+0x408]`, `[EAX+0x330]` and `[EDX+0x2AC]`; the
//   members `[ESI+0x2DC]` (SlaveOwner), `[ESI+0x520]` (the building's Type,
//   read at `[ECX+0x157B]`), `[ESI+0x2BC]` (CaptureManager, handed to
//   0x4722A0 CannotControlAnyMore) and `[ESI+0x21C]` (Owner, handed to
//   0x50B730 IsControlledByHuman). Member offsets agree with
//   match/_layout/techno_class.h; a local placeholder is used because VC6
//   reads `struct TechnoClass : RadioClass` as private inheritance (C2247).
//   The method name is YRpp's TechnoClass::CanPassiveAcquireTargets (name only).
#ifndef GG_MATCH_COMBAT_TECHNO_CLASS_PASSIVE_ACQUIRE_METHODS_H
#define GG_MATCH_COMBAT_TECHNO_CLASS_PASSIVE_ACQUIRE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// TechnoTypeClass — only the byte at +0xD99 is read.
struct TechnoType_007091D0
{
    char _pad000[0xD99];   // +0x0000
    char At_D99;           // +0x0D99
};
GG_STATIC_ASSERT(offsetof(TechnoType_007091D0, At_D99) == 0xD99);

// BuildingTypeClass — only the byte at +0x157B is read.
struct BuildingType_007091D0
{
    char _pad000[0x157B];  // +0x0000
    char At_157B;          // +0x157B
};
GG_STATIC_ASSERT(offsetof(BuildingType_007091D0, At_157B) == 0x157B);

struct CaptureManager_007091D0
{
    // FUNCTION: GAMEMD 0x4722A0 (decl; reloc) — CaptureManagerClass::CannotControlAnyMore.
    bool CannotControlAnyMore();
};

struct House_007091D0
{
    // FUNCTION: GAMEMD 0x50B730 (decl; reloc) — HouseClass::IsControlledByHuman.
    bool IsControlledByHuman();
};

// Declaration order per match/_rt/gg_vslot.h.
struct Vtbl_007091D0;

struct Obj_007091D0
{
    Vtbl_007091D0*           Vtbl;                    // +0x0000
    char                     _pad004[0x21C - 0x4];    // +0x0004
    House_007091D0*          Owner;                   // +0x021C
    char                     _pad220[0x2BC - 0x220];  // +0x0220
    CaptureManager_007091D0* CaptureManager;          // +0x02BC
    char                     _pad2C0[0x2DC - 0x2C0];  // +0x02C0
    Obj_007091D0*            SlaveOwner;              // +0x02DC
    char                     _pad2E0[0x520 - 0x2E0];  // +0x02E0
    BuildingType_007091D0*   BuildingType;            // +0x0520 (BuildingClass::Type)

    // FUNCTION: GAMEMD 0x7091D0 — TechnoClass::CanPassiveAcquireTargets.
    bool CanPassiveAcquireTargets();
};
GG_STATIC_ASSERT(offsetof(Obj_007091D0, Owner)          == 0x21C);
GG_STATIC_ASSERT(offsetof(Obj_007091D0, CaptureManager) == 0x2BC);
GG_STATIC_ASSERT(offsetof(Obj_007091D0, SlaveOwner)     == 0x2DC);
GG_STATIC_ASSERT(offsetof(Obj_007091D0, BuildingType)   == 0x520);

typedef int  (Obj_007091D0::*FnInt_007091D0)();
typedef bool (Obj_007091D0::*FnBool_007091D0)();
typedef TechnoType_007091D0* (Obj_007091D0::*Fn84_007091D0)();

struct Vtbl_007091D0
{
    char             _pad000[0x2C];             // +0x0000
    FnInt_007091D0   WhatAmI;                   // +0x002C
    char             _pad030[0x84 - 0x30];      // +0x0030
    Fn84_007091D0    GetTechnoType;             // +0x0084
    char             _pad088[0x1DC - 0x88];     // +0x0088
    FnBool_007091D0  At_1DC;                    // +0x01DC
    char             _pad1E0[0x2AC - 0x1E0];    // +0x01E0
    FnBool_007091D0  At_2AC;                    // +0x02AC
    char             _pad2B0[0x330 - 0x2B0];    // +0x02B0
    FnBool_007091D0  At_330;                    // +0x0330
    char             _pad334[0x408 - 0x334];    // +0x0334
    FnInt_007091D0   At_408;                    // +0x0408
};
GG_STATIC_ASSERT(offsetof(Vtbl_007091D0, WhatAmI)       == 0x2C);
GG_STATIC_ASSERT(offsetof(Vtbl_007091D0, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(Vtbl_007091D0, At_1DC)        == 0x1DC);
GG_STATIC_ASSERT(offsetof(Vtbl_007091D0, At_2AC)        == 0x2AC);
GG_STATIC_ASSERT(offsetof(Vtbl_007091D0, At_330)        == 0x330);
GG_STATIC_ASSERT(offsetof(Vtbl_007091D0, At_408)        == 0x408);

#endif  // GG_MATCH_COMBAT_TECHNO_CLASS_PASSIVE_ACQUIRE_METHODS_H
