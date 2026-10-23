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
#include "../_rt/gg_static_assert.h"

class HouseClass;
class TeamTypeClass;

// TeamClass — only its size (0xA0, the operator-new argument) and the
// constructor are needed. The constructor is declared as a member returning
// `this` so the call is a plain `MOV ECX,EAX; CALL` after the null test,
// without the EH frame a real `new T(...)` would register under /GX.
class TeamClass
{
public:
    char _pad000[0xA0];   // +0x0000

    // FUNCTION: GAMEMD 0x6E8A90 (decl; reloc) — TeamClass::TeamClass.
    TeamClass* Construct(TeamTypeClass* type, HouseClass* house, int arg);
};
GG_STATIC_ASSERT(sizeof(TeamClass) == 0xA0);

// HouseClass — opaque but for the one member call used here.
class HouseClass
{
public:
    // FUNCTION: GAMEMD 0x5095D0 (decl; reloc) — how many live teams of this
    // type the house already fields.
    int FUN_005095D0(TeamTypeClass* type);
};

class TeamTypeClass
{
public:
    char        _pad000[0x64];   // +0x0000
    char        Name[0x31];      // +0x0064
    char        _pad095[0x23];   // +0x0095
    int         Max;             // +0x00B8
    char        _padBC[0x8];     // +0x00BC
    HouseClass* Owner;           // +0x00C4
    int         idxHouse;        // +0x00C8
    char        _padCC[0x10];    // +0x00CC
    int         At_DC;           // +0x00DC

    // FUNCTION: GAMEMD 0x6F09C0
    TeamClass* CreateTeam(HouseClass* house);
};
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Name)     == 0x64);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Max)      == 0xB8);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Owner)    == 0xC4);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, idxHouse) == 0xC8);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, At_DC)    == 0xDC);

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
// GLOBAL: GAMEMD 0xA8B238 — SessionClass::Instance.GameMode (Campaign == 0).
extern int GameMode_00A8B238;

#endif  // GG_MATCH_AI_TEAM_TYPE_CLASS_CREATE_METHODS_H
