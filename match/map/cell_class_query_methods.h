// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 via the local Ghidra CLI
//   (member-access + virtual-call disassembly at 0x47C4D0 / 0x47C520 /
//   0x47C550). Signatures cross-checked against YRpp CellClass.h (consult-only,
//   no LICENSE; every offset reconfirmed numerically below).
//
// Three CellClass content-query accessors. Each one is gated by a global byte
// flag (MOV AL,[0x00A8E9A0]) then walks the cell occupier linked list, calling
// the occupier's WhatAmI() virtual (primary-vtable slot +0x2C) and filtering by
// AbstractType. The occupier list starts at FirstObject@0xE4 (ground) or
// AltObject@0xE8 (on the bridge), threaded through ObjectClass::NextObject@0x30.
#ifndef GG_MATCH_MAP_CELL_CLASS_QUERY_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_QUERY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_class.h"   // ObjectClass: NextObject@0x30

// Re-assert the spine member the loop strides on (self-guards the TU).
GG_STATIC_ASSERT(offsetof(ObjectClass, NextObject) == 0x30);

// Opaque returns: codegen returns the matched occupier pointer in EAX; the
// concrete leaf type only documents intent and never alters the bytes.
struct BuildingClass;
class TerrainClass;
struct TunnelClass;

// Reveal() — virtual at primary-vtable slot +0xFC, dispatched exactly like
// WhatAmI below (`MOV EAX,[ESI]; MOV ECX,ESI; CALL [EAX+0xFC]`).
typedef void (__fastcall* RevealFunc)(ObjectClass*);

// TunnelClass::Array — GetTunnel reads the element count from 0x008B4148 and
// the Items base from 0x008B413C (the vector object sits at 0x008B4138).
extern int           TunnelArrayCount;    // GLOBAL: GAMEMD 0x008B4148
extern TunnelClass** TunnelArrayItems;    // GLOBAL: GAMEMD 0x008B413C

// GLOBAL: GAMEMD 0x00A8E9A0  the byte the three queries test before touching the
// cell occupier list (MOV AL,[0x00A8E9A0]; TEST AL,AL). Reloc-normalised.
extern unsigned char CellOccupiersValid;

// WhatAmI() — virtual at primary-vtable slot +0x2C (CALL [vtbl+0x2C]). Modelled
// as a __fastcall fn-pointer through the vtable so VC6 reproduces the indirect
// __thiscall (ECX = this, no stack args) exactly, matching
// `MOV EAX,[ESI]; MOV ECX,ESI; CALL [EAX+0x2C]`. Returns the AbstractType (the
// full dword loaded into EAX; modelled int to keep the CMP integer-typed).
typedef int (__fastcall* WhatAmIFunc)(const ObjectClass*);

// CellClass — a single map cell. This TU models only the two occupier-list
// heads the three queries dereference; the unknown base is padded to 0xE4.
struct CellClass
{
    char         _pad00[0xE4];        // +0x00  AbstractClass base + cell bookkeeping
    ObjectClass* FirstObject;         // +0xE4  ground occupier list head
    ObjectClass* AltObject;           // +0xE8  on-bridge occupier list head
    char         _padEC[0x116 - 0xEC];// +0xEC
    short        TunnelIndex;         // +0x116 (signed; -1 == no tunnel)

    // FUNCTION: GAMEMD 0x483480  CellClass::RevealCellObjects (__thiscall)
    void RevealCellObjects();
    // FUNCTION: GAMEMD 0x484F20  CellClass::GetTunnel (__thiscall)
    TunnelClass* GetTunnel() const;
    // FUNCTION: GAMEMD 0x47C4D0  CellClass::FindObjectOfType (__thiscall)
    ObjectClass* FindObjectOfType(int abs, bool alt) const;
    // FUNCTION: GAMEMD 0x47C520  CellClass::GetBuilding (__thiscall)
    BuildingClass* GetBuilding() const;
    // FUNCTION: GAMEMD 0x47C550  CellClass::GetTerrain (__thiscall)
    TerrainClass* GetTerrain(bool alt) const;
    // FUNCTION: GAMEMD 0x47C5A0  CellClass::GetSomeObject (__thiscall)
    ObjectClass* GetSomeObject(int a, int b);
    // 0x47C3D0 — retail callee, declared only (relocation-normalised).
    ObjectClass* FindObjectAt(int a, int b, bool alt);
};

GG_STATIC_ASSERT(offsetof(CellClass, FirstObject) == 0xE4);
GG_STATIC_ASSERT(offsetof(CellClass, AltObject)   == 0xE8);
GG_STATIC_ASSERT(offsetof(CellClass, TunnelIndex) == 0x116);

#endif  // GG_MATCH_MAP_CELL_CLASS_QUERY_METHODS_H
