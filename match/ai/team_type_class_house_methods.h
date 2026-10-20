// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/convention derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x6F0A70 / 0x6F2040 /
//   0x6F2070), cross-checked against YRpp TeamTypeClass.h / AbstractTypeClass.h
//   / TeamClass.h (consult-only, no LICENSE; every offset/global/call target
//   reconfirmed numerically below).
//
// TeamTypeClass — house/taskforce/instance helpers.  Three retail functions:
//   GetHouse              (__thiscall)  reads Owner@0xC4 + idxHouse@0xC8
//   ProcessAllTaskforces  (static)      walks TeamTypeClass::Array (0xA8ECA0)
//   DestroyAllInstances   (__thiscall)  walks TeamClass::Array (0x8B40E8),
//                                       `this` used only as a pointer-identity
//                                       key against each team's Type@0x24.
#ifndef GG_MATCH_AI_TEAM_TYPE_CLASS_HOUSE_METHODS_H
#define GG_MATCH_AI_TEAM_TYPE_CLASS_HOUSE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_type_class.h"
#include "../_layout/vector_class.h"

struct HouseClass;       // opaque — only ever held/returned as a pointer
struct TeamTypeClass;    // forward (TeamClass::Type points back to it)

// ---------------------------------------------------------------------------
// GetHouse fallback callees (GAMEMD).  When the team has no cached Owner it
// resolves its country index: 0x510F60 reports whether the index names a real
// country (bool), and 0x510ED0 maps the index to the owning HouseClass*.  Both
// take the single int index in ECX (one-arg __fastcall reproduces the retail
// `MOV ECX,idx / CALL`).  Body-less so cl emits reloc-normalised direct calls.
// ---------------------------------------------------------------------------
bool        __fastcall IsCountryIndex(int idxHouse);          // GAMEMD 0x510F60
HouseClass* __fastcall FindHouseByCountryIndex(int idxHouse); // GAMEMD 0x510ED0

// ---------------------------------------------------------------------------
// TeamClass — minimal instance model for DestroyAllInstances.  The walk reads
// the team's vtable (offset 0) and dispatches the deleting/remove virtual at
// vtable+0x20 with flag 1 (MOV EDX,[ECX] / PUSH 1 / CALL [EDX+0x20]); Type@0x24
// is matched against `this`.  Modelled as a standalone polymorphic class so cl
// reproduces the indirect call faithfully: nine virtuals put Remove at slot 8
// (vtable+0x20), and the vptr@0 + Type@0x24 placement matches the retail object.
// Never instantiated, so no vtable/RTTI is emitted for it.
// ---------------------------------------------------------------------------
struct TeamClass
{
    virtual void vf00() = 0;   // vtable+0x00
    virtual void vf04() = 0;   // vtable+0x04
    virtual void vf08() = 0;   // vtable+0x08
    virtual void vf0C() = 0;   // vtable+0x0C
    virtual void vf10() = 0;   // vtable+0x10
    virtual void vf14() = 0;   // vtable+0x14
    virtual void vf18() = 0;   // vtable+0x18
    virtual void vf1C() = 0;   // vtable+0x1C
    virtual void Remove(int free) = 0;   // vtable+0x20

    char           _pad_04[0x24 - 0x04];   // +0x04..0x23 (AbstractClass base, P2)
    TeamTypeClass* Type;                   // +0x24
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TeamClass, Type) == 0x24);
#endif

// ---------------------------------------------------------------------------
// TeamTypeClass — AbstractTypeClass base + the two members GetHouse touches.
// The full layout is P2; only Owner@0xC4 and idxHouse@0xC8 are pinned here.
// ProcessTaskForce is the per-element callee fired by ProcessAllTaskforces.
// ---------------------------------------------------------------------------
struct TeamTypeClass : AbstractTypeClass
{
    char        _pad_98[0xC4 - 0x98];   // +0x98..0xC3 (P2)
    HouseClass* Owner;                  // +0xC4
    int         idxHouse;               // +0xC8

    HouseClass* GetHouse() const;
    void        DestroyAllInstances();
    static void ProcessAllTaskforces();

    void        ProcessTaskForce();     // GAMEMD 0x6F1FA0 (callee, body-less)
};

GG_STATIC_ASSERT(offsetof(TeamTypeClass, Owner)    == 0xC4);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, idxHouse) == 0xC8);

// Global type/instance arrays (DynamicVectorClass of pointers).
extern DynamicVectorClassLayout TeamTypeArray;       // GAMEMD 0xA8ECA0
extern DynamicVectorClassLayout TeamInstanceArray;   // GAMEMD 0x8B40E8 (TeamClass::Array)

#endif  // GG_MATCH_AI_TEAM_TYPE_CLASS_HOUSE_METHODS_H
