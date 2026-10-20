// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and globals read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x510ED0: the eight `CMP ECX,0x117B..
//   0x1182` arms, `MOV ECX,[0xA8B230]` / `CALL 0x68C030` (ScenarioClass
//   instance + its 0x1180-based HouseIndices lookup, seen at 0x68C03D as
//   `[ECX+EAX*4+0x1180]`), `CMP EAX,[0xA80238]` (HouseClass::Array.Count) and
//   `MOV ECX,[0xA8022C]` (Array.Items).  Names from YRpp HouseClass.h /
//   ScenarioClass.h (consult-only; every address reconfirmed here).
#ifndef GG_MATCH_AI_HOUSE_CLASS_LOOKUP_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_LOOKUP_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ScenarioClass — only the HouseIndices[16] lookup callee is needed.  The
// member is body-less so cl emits a reloc-normalised direct CALL.
struct Scenario_00510ED0
{
    // FUNCTION: GAMEMD 0x68C030 (decl; reloc) — HouseIndices[idx] or -1.
    int GetHouseIndex(int idx);
};

// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance.
extern Scenario_00510ED0* ScenarioInstance;

struct HouseClass;

// HouseClass::Array head (DynamicVectorClass<HouseClass*> @0xA80228):
// Items @+0x04 (0xA8022C), Count @+0x10 (0xA80238).
struct HouseArray_00510ED0
{
    void*        _vtable;           // +0x00
    HouseClass** Items;             // +0x04
    int          Capacity;          // +0x08
    int          IsAllocated;       // +0x0C
    int          Count;             // +0x10
    int          CapacityIncrement; // +0x14
};
GG_STATIC_ASSERT(offsetof(HouseArray_00510ED0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(HouseArray_00510ED0, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(HouseArray_00510ED0) == 0x18);

// GLOBAL: GAMEMD 0xA80228 — HouseClass::Array.
extern HouseArray_00510ED0 HouseArray;

struct HouseClass
{
    // FUNCTION: GAMEMD 0x510ED0
    static HouseClass* __fastcall FindByPlayerAt(int at);
};

#endif  // GG_MATCH_AI_HOUSE_CLASS_LOOKUP_METHODS_H
