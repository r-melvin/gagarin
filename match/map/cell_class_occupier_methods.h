// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 via the local Ghidra CLI
//   (member-access + virtual-call disassembly at 0x47EBA0 / 0x47EBF0 /
//   0x47EC40). Signatures cross-checked against YRpp
//   (every offset reconfirmed numerically below).
//
// Three CellClass occupier-type accessors. Each is gated by a global byte flag
// (MOV AL,[0x00A8E9A0]) then walks the cell occupier linked list, calling the
// occupier's WhatAmI() virtual (primary-vtable slot +0x2C) and filtering by a
// hard-coded AbstractType discriminant (Unit=1 / Aircraft=2 / Infantry=15).
// The occupier list starts at FirstObject@0xE4 (ground) or AltObject@0xE8
// (on the bridge), threaded through ObjectClass::NextObject@0x30. These mirror
// the FindObjectOfType family in cell_class_query_methods.h.
#ifndef GG_MATCH_MAP_CELL_CLASS_OCCUPIER_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_OCCUPIER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_class.h"   // ObjectClass: NextObject@0x30

// Re-assert the spine member the loop strides on (self-guards the TU).
GG_STATIC_ASSERT(offsetof(ObjectClass, NextObject) == 0x30);

// Opaque returns: codegen returns the matched occupier pointer in EAX; the
// concrete leaf type only documents intent and never alters the bytes.
struct UnitClass;
struct AircraftClass;
struct InfantryClass;

// GLOBAL: GAMEMD 0x00A8E9A0  the byte the queries test before touching the cell
// occupier list (MOV AL,[0x00A8E9A0]; TEST AL,AL). Reloc-normalised.
extern unsigned char CellOccupiersValid;

// WhatAmI() — virtual at primary-vtable slot +0x2C (CALL [vtbl+0x2C]). Modelled
// as a __fastcall fn-pointer through the vtable so VC6 reproduces the indirect
// __thiscall (ECX = this, no stack args) exactly, matching
// `MOV EAX,[ESI]; MOV ECX,ESI; CALL [EAX+0x2C]`. Returns the AbstractType (the
// full dword loaded into EAX; modelled int to keep the CMP integer-typed).
typedef int (__fastcall* WhatAmIFunc)(const ObjectClass*);

// CellClass — a single map cell. This TU models only the two occupier-list
// heads the queries dereference; the unknown base is padded to 0xE4.
struct CellClass
{
    char         _pad00[0xE4];   // +0x00  AbstractClass base + cell bookkeeping
    ObjectClass* FirstObject;    // +0xE4  ground occupier list head
    ObjectClass* AltObject;      // +0xE8  on-bridge occupier list head

    // FUNCTION: GAMEMD 0x47EBA0  CellClass::GetUnit      (__thiscall)
    UnitClass*     GetUnit(bool alt) const;
    // FUNCTION: GAMEMD 0x47EBF0  CellClass::GetAircraft  (__thiscall)
    AircraftClass* GetAircraft(bool alt) const;
    // FUNCTION: GAMEMD 0x47EC40  CellClass::GetInfantry  (__thiscall)
    InfantryClass* GetInfantry(bool alt) const;
};

GG_STATIC_ASSERT(offsetof(CellClass, FirstObject) == 0xE4);
GG_STATIC_ASSERT(offsetof(CellClass, AltObject)   == 0xE8);

#endif  // GG_MATCH_MAP_CELL_CLASS_OCCUPIER_METHODS_H
