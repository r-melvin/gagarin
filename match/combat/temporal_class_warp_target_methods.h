// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x71AE50: the target's virtuals
//   `CALL [EAX+0x84]` (type getter), `CALL [EDX+0x160]` (byte result) and
//   `CALL [EAX+0x2C]` (WhatAmI, compared with 1 and 6); the type byte
//   `[EAX+0xD3A]`; the link's type at `[EDI+0x520]` and its byte
//   `[EAX+0x16BD]`; the coordinate copied from `this+0x9C` (`ADD ESI,0x9C`,
//   three dwords); CALL 0x65AD30 with a pushed 0 (link accessor), CALL
//   0x565730 with ECX = 0x87F7E8 (the map singleton) and a pointer to the
//   copied coordinate, and CALL 0x47C520 on its result. `this` (ECX) is never
//   read; the method name is YRpp's TemporalClass::CanWarpTarget (name only).
#ifndef GG_MATCH_COMBAT_TEMPORAL_CLASS_WARP_TARGET_METHODS_H
#define GG_MATCH_COMBAT_TEMPORAL_CLASS_WARP_TARGET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct CoordStruct_0071AE50
{
    int X;   // +0x0
    int Y;   // +0x4
    int Z;   // +0x8
};
GG_STATIC_ASSERT(sizeof(CoordStruct_0071AE50) == 0xC);

// The techno type: only the byte at +0xD3A (warpable flag) is read.
struct TechnoType_0071AE50
{
    char _pad000[0xD3A];      // +0x0000
    char At_D3A;              // +0x0D3A
};
GG_STATIC_ASSERT(offsetof(TechnoType_0071AE50, At_D3A) == 0xD3A);

// The building type of the radio link: only the byte at +0x16BD is read.
struct BuildingType_0071AE50
{
    char _pad0000[0x16BD];    // +0x0000
    char At_16BD;             // +0x16BD
};
GG_STATIC_ASSERT(offsetof(BuildingType_0071AE50, At_16BD) == 0x16BD);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_0071AE50;

struct Techno_0071AE50
{
    Vtbl_0071AE50*          Vtbl;       // +0x0000
    char                    _pad004[0x9C - 4];      // +0x0004
    CoordStruct_0071AE50    Location;   // +0x009C
    char                    _pad0A8[0x520 - 0xA8];  // +0x00A8
    BuildingType_0071AE50*  Type;       // +0x0520 (BuildingClass::Type)

    // FUNCTION: GAMEMD 0x65AD30 (decl; reloc) — n-th radio link.
    Techno_0071AE50* FUN_0065AD30(int index);
};
GG_STATIC_ASSERT(offsetof(Techno_0071AE50, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(Techno_0071AE50, Type) == 0x520);

typedef int                  (Techno_0071AE50::*Fn02C_0071AE50)();
typedef TechnoType_0071AE50* (Techno_0071AE50::*Fn084_0071AE50)();
typedef char                 (Techno_0071AE50::*Fn160_0071AE50)();

struct Vtbl_0071AE50
{
    char           _pad000[0x2C];             // +0x0000
    Fn02C_0071AE50 WhatAmI;                   // +0x002C
    char           _pad030[0x84 - 0x30];      // +0x0030
    Fn084_0071AE50 GetTechnoType;             // +0x0084
    char           _pad088[0x160 - 0x88];     // +0x0088
    Fn160_0071AE50 At_160;                    // +0x0160
};
GG_STATIC_ASSERT(offsetof(Vtbl_0071AE50, WhatAmI) == 0x2C);
GG_STATIC_ASSERT(offsetof(Vtbl_0071AE50, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(Vtbl_0071AE50, At_160) == 0x160);

struct Cell_0071AE50
{
    // FUNCTION: GAMEMD 0x47C520 (decl; reloc) — CellClass::GetBuilding.
    Techno_0071AE50* GetBuilding();
};

// The map singleton lives at the fixed address 0x87F7E8 (`MOV ECX,0x87F7E8`).
struct Map_0071AE50
{
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) — MapClass::GetTargetCell.
    Cell_0071AE50* GetTargetCell(CoordStruct_0071AE50 const& crd);
};
#define MapInstance_0071AE50 (reinterpret_cast<Map_0071AE50*>(0x0087F7E8))

struct TemporalClass_0071AE50
{
    // FUNCTION: GAMEMD 0x71AE50 — TemporalClass::CanWarpTarget.
    bool CanWarpTarget(Techno_0071AE50* target);
};

#endif  // GG_MATCH_COMBAT_TEMPORAL_CLASS_WARP_TARGET_METHODS_H
