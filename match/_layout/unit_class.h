// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: UnitClass ctor FUN_0x007353C0 (chains FootClass ctor
//   FUN_0x004D31E0 at offset 0, CALL @0x007353CE). Every offset in the
//   0x6C0..0x6E7 span below is read directly from a field-init store in that
//   ctor; the citations sit beside each member. The four COM vptrs are written
//   at 0x0073533A..0x0073544D and RTTI-confirmed (see below). sizeof is read
//   from the allocation site: `PUSH 0x8E8; CALL 0x007C8E17` @0x00688B37,
//   immediately before the ctor call @0x00688B66.
//
//   RTTI (read from the binary, outranks any document): the complete object
//   locator four bytes under each table resolves to ".?AVUnitClass@@" for all
//   four vptrs, with COL base-offset fields 0 / 4 / 8 / 12 — i.e. the three
//   COM interface subobjects sit at +4, +8 and +0xC exactly as the ctor stores
//   them.
//
//   Members cross-read against YRpp; all 15 named members it
//   claims were independently confirmed here. No disagreement found.
//
//   CAUTION for future scans: UnitClass::TryToDeploy @0x007393C0 contains
//   `MOV byte ptr [EBX+0x6CA],1` @0x007397ED and `[EBX+0x6CB]` @0x007397F4,
//   but EBX there is the *BuildingClass* being deployed (same body reads
//   [EBX+0x520] as a type pointer, which is BuildingClass::Type, not a
//   UnitClass field). Those two offsets are NOT UnitClass members.
//
// UnitClass — a tracked/wheeled vehicle. Derives FootClass at offset 0
// (sizeof(FootClass) == 0x6C0) and adds its own block from 0x6C0.
#ifndef GG_MATCH_LAYOUT_UNIT_CLASS_H
#define GG_MATCH_LAYOUT_UNIT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "foot_class.h"

struct UnitClass : FootClass
{
    int           CurrentFiringFrame;   // +0x6C0  ctor: MOV [ESI+0x6C0],EDI(-1) @0x007353E0
    void*         Type;                 // +0x6C4  UnitTypeClass*; ctor: MOV [ESI+0x6C4],ECX(=pType) @0x007353E6
    void*         FollowerCar;          // +0x6C8  UnitClass*;     ctor: MOV [ESI+0x6C8],EBX(0) @0x007353EC
    int           FlagHouseIndex;       // +0x6CC  ctor: MOV [ESI+0x6CC],EDI(-1) @0x007353F2
                                        //         also CMP [ECX+0x6CC],-1 @0x00740DF9 (FlagAttach)
    unsigned char IsFollowerCar;        // +0x6D0  ctor: MOV byte [ESI+0x6D0],BL @0x007353F8
    unsigned char Unloading;            // +0x6D1  ctor: MOV byte [ESI+0x6D1],BL @0x007353FE
    unsigned char IsHarvesting;         // +0x6D2  ctor: MOV byte [ESI+0x6D2],BL @0x00735404
    unsigned char TerrainPalette;       // +0x6D3  ctor: MOV byte [ESI+0x6D3],BL @0x0073540A
    int           unknown_int_6D4;      // +0x6D4  ctor: MOV [ESI+0x6D4],EDI(-1) @0x00735410
    int           DeathFrameCounter;    // +0x6D8  ctor: MOV [ESI+0x6D8],EDI(-1) @0x00735416
    void*         ElectricBolt;         // +0x6DC  EBolt*; ctor: MOV [ESI+0x6DC],EBX(0) @0x0073541C
    unsigned char Deployed;             // +0x6E0  ctor: MOV byte [ESI+0x6E0],BL @0x00735422
    unsigned char Deploying;            // +0x6E1  ctor: MOV byte [ESI+0x6E1],BL @0x00735428
    unsigned char Undeploying;          // +0x6E2  ctor: MOV byte [ESI+0x6E2],BL @0x0073542E
    unsigned char align_6E3;            // +0x6E3
    int           NonPassengerCount;    // +0x6E4  ctor: MOV [ESI+0x6E4],EBX(0) @0x00735434
    // ToolTipText is the only member below NOT proven by a member-access
    // instruction. It is proven by closure instead: the last confirmed field
    // ends at 0x6E8 and the allocation is 0x8E8, leaving exactly 0x200 bytes,
    // which is 0x100 wchar_t — the width YRpp claims. Treated as confirmed by
    // size closure, not as a named claim on YRpp's say-so.
    unsigned short ToolTipText[0x100];  // +0x6E8 .. 0x8E7 (wchar_t[256])
};

GG_STATIC_ASSERT(offsetof(UnitClass, CurrentFiringFrame) == 0x6C0);
GG_STATIC_ASSERT(offsetof(UnitClass, Type)               == 0x6C4);
GG_STATIC_ASSERT(offsetof(UnitClass, FollowerCar)        == 0x6C8);
GG_STATIC_ASSERT(offsetof(UnitClass, FlagHouseIndex)     == 0x6CC);
GG_STATIC_ASSERT(offsetof(UnitClass, IsFollowerCar)      == 0x6D0);
GG_STATIC_ASSERT(offsetof(UnitClass, Unloading)          == 0x6D1);
GG_STATIC_ASSERT(offsetof(UnitClass, IsHarvesting)       == 0x6D2);
GG_STATIC_ASSERT(offsetof(UnitClass, TerrainPalette)     == 0x6D3);
GG_STATIC_ASSERT(offsetof(UnitClass, unknown_int_6D4)    == 0x6D4);
GG_STATIC_ASSERT(offsetof(UnitClass, DeathFrameCounter)  == 0x6D8);
GG_STATIC_ASSERT(offsetof(UnitClass, ElectricBolt)       == 0x6DC);
GG_STATIC_ASSERT(offsetof(UnitClass, Deployed)           == 0x6E0);
GG_STATIC_ASSERT(offsetof(UnitClass, Deploying)          == 0x6E1);
GG_STATIC_ASSERT(offsetof(UnitClass, Undeploying)        == 0x6E2);
GG_STATIC_ASSERT(offsetof(UnitClass, NonPassengerCount)  == 0x6E4);
GG_STATIC_ASSERT(offsetof(UnitClass, ToolTipText)        == 0x6E8);
GG_STATIC_ASSERT(sizeof(UnitClass)                       == 0x8E8);

// VTABLE: GAMEMD 0x007F5C70  UnitClass            (COL @0x007F5C6C, base 0)
// VTABLE: GAMEMD 0x007F5C54  UnitClass::(+0x04)   (COL @0x007F5C50, base 4)
// VTABLE: GAMEMD 0x007F5C4C  UnitClass::(+0x08)   (COL @0x007F5C48, base 8)
// VTABLE: GAMEMD 0x007F5C44  UnitClass::(+0x0C)   (COL @0x007F5C40, base 12)

#endif  // GG_MATCH_LAYOUT_UNIT_CLASS_H
