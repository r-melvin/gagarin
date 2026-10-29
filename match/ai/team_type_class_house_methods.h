// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/convention derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x6F0A70 / 0x6F2040 /
//   0x6F2070), cross-checked against YRpp
//   (every offset/global/call target
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
#include "../_layout/team_class.h"
#include "../_layout/team_type_class.h"

class HouseClass;       // opaque — only ever held/returned as a pointer

// ---------------------------------------------------------------------------
// GetHouse fallback callees (GAMEMD).  When the team has no cached Owner it
// resolves its country index: 0x510F60 reports whether the index names a real
// country (bool), and 0x510ED0 maps the index to the owning HouseClass*.  Both
// take the single int index in ECX (one-arg __fastcall reproduces the retail
// `MOV ECX,idx / CALL`).  Body-less so cl emits reloc-normalised direct calls.
// ---------------------------------------------------------------------------
bool        FUN_00510F60(int idxHouse);          // GAMEMD 0x510F60
HouseClass* FindHouseByCountryIndex(int idxHouse); // GAMEMD 0x510ED0

// Global type/instance arrays (DynamicVectorClass of pointers).
extern DynamicVectorClassLayout TeamTypeArray;       // GAMEMD 0xA8ECA0
extern DynamicVectorClassLayout TeamInstanceArray;   // GAMEMD 0x8B40E8 (TeamClass::Array)

#endif  // GG_MATCH_AI_TEAM_TYPE_CLASS_HOUSE_METHODS_H
