// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Shapes read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x476EB0: a 0x80-byte stack buffer handed to the
//   string reader at 0x528A10 with the "<none>" literal (0x817474) as the
//   default; four name lookups (0x523C90, 0x747370, 0x41CAA0, 0x45E7B0), each
//   taking the buffer in ECX and answering -1 for a miss; the hit is indexed
//   into the matching pointer array `[0xA8E34C]`, `[0xA83CE4]`, `[0xA8B21C]`,
//   `[0xA83C6C]` (`MOV EAX,[ECX+EAX*4]`). Method name from YRpp
//   (name only, no text copied).
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_TECHNO_TYPE_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_TECHNO_TYPE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "ccini_class_methods.h"

class TechnoTypeClass;   // opaque, handled by pointer only

// The four type arrays (DynamicVectorClass::Items of the per-kind type lists).
// GLOBAL: GAMEMD 0xA8E34C -- AircraftTypeClass array items.
extern TechnoTypeClass** DAT_00A8E34C;
// GLOBAL: GAMEMD 0xA83CE4 -- BuildingTypeClass array items.
extern TechnoTypeClass** DAT_00A83CE4;
// GLOBAL: GAMEMD 0xA8B21C -- InfantryTypeClass array items.
extern TechnoTypeClass** DAT_00A8B21C;
// GLOBAL: GAMEMD 0xA83C6C -- UnitTypeClass array items.
extern TechnoTypeClass** DAT_00A83C6C;

// The per-kind FindIndex lookups: name in ECX, index or -1 back.
// FUNCTION: GAMEMD 0x523C90 (decl; reloc) -- AircraftTypeClass::FindIndex.
int FUN_00523C90(const char* name);
// FUNCTION: GAMEMD 0x747370 (decl; reloc) -- BuildingTypeClass::FindIndex.
int FUN_00747370(const char* name);
// FUNCTION: GAMEMD 0x41CAA0 (decl; reloc) -- InfantryTypeClass::FindIndex.
int FUN_0041CAA0(const char* name);
// FUNCTION: GAMEMD 0x45E7B0 (decl; reloc) -- UnitTypeClass::FindIndex.
int FUN_0045E7B0(const char* name);


#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_TECHNO_TYPE_METHODS_H
