// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6743D0: the section name pointer at 0x7F0CE0, the
//   INIClass calls 0x526810 (GetSection), 0x5276D0 (ReadInteger) and
//   0x5283D0 (ReadDouble, default pushed as two dwords, result via FSTP),
//   and the rules members `[ESI+0x40C]` .. `[ESI+0x438]` (JumpjetControls:
//   TurnRate, Speed, Climb, CruiseHeight, Acceleration, WobblesPerSecond,
//   WobbleDeviation) with the key strings at 0x83D554, 0x81D9CC, 0x83D54C,
//   0x83D53C, 0x81B140, 0x83D528, 0x83D518. Names cross-checked against
//   YRpp (consult-only; NO LICENSE).
#ifndef GG_MATCH_CORE_RULES_CLASS_JUMPJET_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_JUMPJET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class CCINI_006743D0
{
public:
    // FUNCTION: GAMEMD 0x526810 (decl; reloc) — INIClass::GetSection.
    void*  GetSection(const char* pSection);
    // FUNCTION: GAMEMD 0x526B10 (decl; reloc) — INIClass::GetEntry.
    void*  GetEntry(const char* pSection, const char* pKey);
    // FUNCTION: GAMEMD 0x5276D0 (decl; reloc) — INIClass::ReadInteger.
    int    ReadInteger(const char* pSection, const char* pKey, int defaultValue);
    // FUNCTION: GAMEMD 0x5283D0 (decl; reloc) — INIClass::ReadDouble.
    double ReadDouble(const char* pSection, const char* pKey, double defaultValue);
};

// GLOBAL: GAMEMD 0x7F0CE0 — holds the "JumpjetControls" section name.
extern char* JumpjetSection_006743D0;

// RulesClass — the seven JumpjetControls members.
struct Rules_006743D0
{
    char   _pad000[0x40C];          // +0x0000
    int    JumpjetTurnRate;         // +0x040C
    int    JumpjetSpeed;            // +0x0410
    char   _pad414[4];              // +0x0414
    double JumpjetClimb;            // +0x0418
    int    JumpjetCruiseHeight;     // +0x0420
    char   _pad424[4];              // +0x0424
    double JumpjetAcceleration;     // +0x0428
    double JumpjetWobblesPerSecond; // +0x0430
    int    JumpjetWobbleDeviation;  // +0x0438

    // FUNCTION: GAMEMD 0x6743D0 — RulesClass::Read_JumpjetControls.
    bool Read_JumpjetControls(CCINI_006743D0* pINI);
};
GG_STATIC_ASSERT(offsetof(Rules_006743D0, JumpjetTurnRate)         == 0x40C);
GG_STATIC_ASSERT(offsetof(Rules_006743D0, JumpjetSpeed)            == 0x410);
GG_STATIC_ASSERT(offsetof(Rules_006743D0, JumpjetClimb)            == 0x418);
GG_STATIC_ASSERT(offsetof(Rules_006743D0, JumpjetCruiseHeight)     == 0x420);
GG_STATIC_ASSERT(offsetof(Rules_006743D0, JumpjetAcceleration)     == 0x428);
GG_STATIC_ASSERT(offsetof(Rules_006743D0, JumpjetWobblesPerSecond) == 0x430);
GG_STATIC_ASSERT(offsetof(Rules_006743D0, JumpjetWobbleDeviation)  == 0x438);

#endif  // GG_MATCH_CORE_RULES_CLASS_JUMPJET_METHODS_H
