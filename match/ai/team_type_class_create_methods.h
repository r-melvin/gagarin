// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6F09C0: `[ESI+0xC4]` (Owner, the fallback house),
//   `[ESI+0xC8]` (the country index handed to 0x510F60 / 0x510ED0 in ECX),
//   `[ESI+0xB8]` (Max, sign-tested and compared twice), `[ESI+0xDC]` (the
//   live-instance count compared against Max in campaign mode),
//   `LEA EAX,[ESI+0x64]` (the Name array passed to the log), the dword
//   globals `[0xA8E7AC]` (ScenarioInit) and `[0xA8B238]`
//   (SessionClass::Instance.GameMode), the house call `CALL 0x5095D0` with
//   `this` pushed, `PUSH 0xA0; CALL 0x7C8E17` (operator new, the TeamClass
//   size) and the constructor `CALL 0x6E8A90` with (this, house, 0). Names
//   cross-checked against YRpp;
//   the Owner/idxHouse pair repeats match/ai/team_type_class_house_methods.h.
#ifndef GG_MATCH_AI_TEAM_TYPE_CLASS_CREATE_METHODS_H
#define GG_MATCH_AI_TEAM_TYPE_CLASS_CREATE_METHODS_H

#include <stddef.h>
#include "../_layout/session_class.h"
#include "../_rt/gg_static_assert.h"
#include "../_layout/house_class.h"
#include "../_layout/team_class.h"
#include "../_layout/team_type_class.h"

// FUNCTION: GAMEMD 0x510F60 (decl; reloc) — does the index name a country.
bool        FUN_00510F60(int idxHouse);
// FUNCTION: GAMEMD 0x510ED0 (decl; reloc) — HouseClass::FindByCountryIndex.
HouseClass* FindHouseByCountryIndex(int idxHouse);
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);
// LIBRARY: GAMEMD 0x7C8E17 (decl; reloc) — operator new (CRT).
void* __cdecl operator new(unsigned int size);

// GLOBAL: GAMEMD 0xA8E7AC — nonzero while the scenario is being set up.
extern int ScenarioInit_00A8E7AC;

#endif  // GG_MATCH_AI_TEAM_TYPE_CLASS_CREATE_METHODS_H
