// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: the user's retail gamemd.exe v1.001 read through the local
//   Ghidra CLI at 0x487150 / 0x487160 / 0x487170 / 0x487180 / 0x487DF0 /
//   0x487E00 / 0x487EA0. The cluster carried no name in any worklist; the
//   owning class was recovered from the member-access displacements (the
//   receiver at 0x45590A..0x45591E is the cell the MapClass singleton at
//   0x87F7E8 hands back) and cross-checked against YRpp CellClass.h
//   (consult-only, no LICENSE; every offset below reconfirmed numerically).
//
// CellClass sensor counters and two small cell queries.
//
// The two counter arrays are what makes the identification certain: retail
// indexes a 16-bit element at [ECX + idx*2 + 0x7C] and at
// [ECX + idx*2 + 0xAC], exactly 0x30 == 24 * sizeof(short) apart, which is
// CellClass::SensorsOfHouses[24] immediately followed by
// CellClass::DisguiseSensorsOfHouses[24]. The same layout puts FirstObject at
// 0xE4 -- and 0xE4 is the member the caller at 0x455923 dereferences and then
// dispatches WhatAmI() on, so the whole run agrees.
#ifndef GG_MATCH_MAP_CELL_CLASS_SENSOR_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_SENSOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_class.h"   // ObjectClass: NextObject@0x30

GG_STATIC_ASSERT(offsetof(ObjectClass, NextObject) == 0x30);

// Two 16-bit components packed in one dword; retail copies the pair with a
// single 32-bit move, which is why the halves go through a temporary.
struct CellStruct
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// GLOBAL: GAMEMD 0x0089F688 — the per-direction {dX,dY} step table.
extern CellStruct AdjacentCellTable[];

// GLOBAL: GAMEMD 0x00A8E9A0 — the byte the occupier walk tests before touching
// the cell occupier list (MOV AL,[0x00A8E9A0]; TEST AL,AL).
extern unsigned char CellOccupiersValid;

// WhatAmI() — primary-vtable slot +0x2C, dispatched as
// `MOV EAX,[ESI]; MOV ECX,ESI; CALL [EAX+0x2C]`. Modelled as a __fastcall
// function pointer through the vtable so VC6 emits the indirect __thiscall
// (ECX = this, no stack arguments) with no extra register traffic.
typedef int (__fastcall* WhatAmIFunc)(const ObjectClass*);

struct CellClass
{
    char           _pad00[0x7C];               // +0x00   AbstractClass base + cell bookkeeping
    unsigned short SensorsOfHouses[24];        // +0x7C
    unsigned short DisguiseSensorsOfHouses[24];// +0xAC
    char           _padDC[0xE4 - 0xDC];        // +0xDC
    ObjectClass*   FirstObject;                // +0xE4   ground occupier list head
    char           _padE8[0xEC - 0xE8];        // +0xE8
    int            LandType;                   // +0xEC
    char           _padF0[0x100 - 0xF0];       // +0xF0
    int            OccupyHeightsCoveringMe;    // +0x100

    // FUNCTION: GAMEMD 0x487150
    void IncreaseSensorsOfHouse(int idxHouse);
    // FUNCTION: GAMEMD 0x487160
    void DecreaseSensorsOfHouse(int idxHouse);
    // FUNCTION: GAMEMD 0x487170
    void IncreaseDisguiseSensorsOfHouse(int idxHouse);
    // FUNCTION: GAMEMD 0x487180
    void DecreaseDisguiseSensorsOfHouse(int idxHouse);
    // FUNCTION: GAMEMD 0x487DF0
    bool IsLandType5() const;
    // FUNCTION: GAMEMD 0x487E00
    bool FUN_00487E00() const;
};

GG_STATIC_ASSERT(offsetof(CellClass, SensorsOfHouses)         == 0x7C);
GG_STATIC_ASSERT(offsetof(CellClass, DisguiseSensorsOfHouses) == 0xAC);
GG_STATIC_ASSERT(offsetof(CellClass, FirstObject)             == 0xE4);
GG_STATIC_ASSERT(offsetof(CellClass, LandType)                == 0xEC);
GG_STATIC_ASSERT(offsetof(CellClass, OccupyHeightsCoveringMe) == 0x100);

// FUNCTION: GAMEMD 0x487EA0
CellStruct* __fastcall FUN_00487EA0(CellStruct* dest, CellStruct const* src,
                                    int dir);

#endif  // GG_MATCH_MAP_CELL_CLASS_SENSOR_METHODS_H
