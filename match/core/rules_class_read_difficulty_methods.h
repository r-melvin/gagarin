// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x66D270: the receiver is ECX (CCINIClass, passed on
//   as `this` of 0x526810 / 0x5283D0 / 0x5295F0), the output struct is EDX
//   (`MOV EDI,EDX`, stores `[EDI]` .. `[EDI+0x4A]`) and the section name is
//   the one stack argument (`MOV EBX,[ESP+8]`, `RET 4`). The twelve members
//   follow the FSTP / byte-store offsets: doubles at +0x00 FirePower
//   (0x83B3F8), +0x08 Groundspeed (0x825488), +0x10 Airspeed (0x82547C),
//   +0x18 Armor (0x81D9D4), +0x20 ROF (0x825478), +0x28 Cost (0x825470),
//   +0x30 BuildTime (0x825464), +0x38 RepairDelay (0x83B3EC), +0x40
//   BuildDelay (0x83B3E0); bools at +0x48 BuildSlowdown (0x83B3D0), +0x49
//   DestroyWalls (0x83B3C0), +0x4A ContentScan (0x83B3B4). Names
//   cross-checked against YRpp RulesClass.h / GeneralStructures.h
//   (consult-only; NO LICENSE).
#ifndef GG_MATCH_CORE_RULES_CLASS_READ_DIFFICULTY_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_READ_DIFFICULTY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class CCINI_0066D270
{
public:
    // FUNCTION: GAMEMD 0x526810 (decl; reloc) — INIClass::GetSection.
    void*  GetSection(const char* pSection);
    // FUNCTION: GAMEMD 0x526B10 (decl; reloc) — INIClass::GetEntry.
    void*  GetEntry(const char* pSection, const char* pKey);
    // FUNCTION: GAMEMD 0x5283D0 (decl; reloc) — INIClass::ReadDouble.
    double ReadDouble(const char* pSection, const char* pKey, double defaultValue);
    // FUNCTION: GAMEMD 0x5295F0 (decl; reloc) — INIClass::ReadBool.
    bool   ReadBool(const char* pSection, const char* pKey, bool defaultValue);
};

// One difficulty level's multipliers ([Easy] / [Normal] / [Difficult]),
// 0x4B bytes used, 0x50 apart inside RulesClass.
struct Difficulty_0066D270
{
    double FirePower;       // +0x0000
    double Groundspeed;     // +0x0008
    double Airspeed;        // +0x0010
    double Armor;           // +0x0018
    double ROF;             // +0x0020
    double Cost;            // +0x0028
    double BuildTime;       // +0x0030
    double RepairDelay;     // +0x0038
    double BuildDelay;      // +0x0040
    bool   BuildSlowdown;   // +0x0048
    bool   DestroyWalls;    // +0x0049
    bool   ContentScan;     // +0x004A
};
GG_STATIC_ASSERT(offsetof(Difficulty_0066D270, FirePower)     == 0x00);
GG_STATIC_ASSERT(offsetof(Difficulty_0066D270, Groundspeed)   == 0x08);
GG_STATIC_ASSERT(offsetof(Difficulty_0066D270, Airspeed)      == 0x10);
GG_STATIC_ASSERT(offsetof(Difficulty_0066D270, Armor)         == 0x18);
GG_STATIC_ASSERT(offsetof(Difficulty_0066D270, ROF)           == 0x20);
GG_STATIC_ASSERT(offsetof(Difficulty_0066D270, Cost)          == 0x28);
GG_STATIC_ASSERT(offsetof(Difficulty_0066D270, BuildTime)     == 0x30);
GG_STATIC_ASSERT(offsetof(Difficulty_0066D270, RepairDelay)   == 0x38);
GG_STATIC_ASSERT(offsetof(Difficulty_0066D270, BuildDelay)    == 0x40);
GG_STATIC_ASSERT(offsetof(Difficulty_0066D270, BuildSlowdown) == 0x48);
GG_STATIC_ASSERT(offsetof(Difficulty_0066D270, DestroyWalls)  == 0x49);
GG_STATIC_ASSERT(offsetof(Difficulty_0066D270, ContentScan)   == 0x4A);

// FUNCTION: GAMEMD 0x66D270 — RulesClass::Read_Difficulty. Retail is
// __fastcall (ini in ECX, output struct in EDX, section name on the stack,
// RET 4); YRpp's __thiscall(CCINIClass*) spelling is a naming fact only.
void __fastcall Read_Difficulty_0066D270(CCINI_0066D270* pINI,
                                         Difficulty_0066D270* pOut,
                                         const char* pSection);

#endif  // GG_MATCH_CORE_RULES_CLASS_READ_DIFFICULTY_METHODS_H
