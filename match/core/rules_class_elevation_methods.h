// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x66D150:
//     0x007F0C8C  char* section-name global -> "ElevationModel" (string at 0x839E70)
//     0x0083B370  "ElevationIncrement"
//     0x0083B358  "ElevationIncrementBonus"
//     0x0083B344  "ElevationBonusCap"
//     0x00526810  INIClass::GetSection(const char*)
//     0x005276D0  INIClass::ReadInteger(section, key, int def)
//     0x005283D0  INIClass::ReadDouble(section, key, double def)
//   Members: `[ESI+0x1838]` int, `FSTP qword [ESI+0x1840]`, `FSTP qword
//   [ESI+0x1848]`. Names cross-checked against YRpp RulesClass.h
//   (consult-only, no LICENSE).
#ifndef GG_MATCH_CORE_RULES_CLASS_ELEVATION_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_ELEVATION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class CCINIClass
{
public:
    // FUNCTION: GAMEMD 0x526810 (decl; reloc)
    void*  GetSection(const char* pSection);
    // FUNCTION: GAMEMD 0x526B10 (decl; reloc)
    void*  GetEntry(const char* pSection, const char* pKey);
    // FUNCTION: GAMEMD 0x5276D0 (decl; reloc)
    int    ReadInteger(const char* pSection, const char* pKey, int defaultValue);
    // FUNCTION: GAMEMD 0x5283D0 (decl; reloc)
    double ReadDouble(const char* pSection, const char* pKey, double defaultValue);

    // FUNCTION: GAMEMD 0x679F40 — CCINIClass::Exists, matched out of line in
    // match/platform/ccini_class_methods.cpp. Here it is the header inline
    // that VC6 expands at the section test: with the key defaulted to null
    // the entry branch folds away, and the section probe survives as
    // `TEST EAX,EAX; SETNZ AL; TEST AL,AL`, which is retail's shape.
    bool Exists(const char* pSection, const char* pKey = 0)
    {
        if (pKey == 0) {
            return GetSection(pSection) != 0;
        }
        return GetEntry(pSection, pKey) != 0;
    }
};

// GLOBAL: GAMEMD 0x7F0C8C — holds the "ElevationModel" section name.
extern char* ElevationModelSection;

struct RulesClass
{
    char   _pad0000[0x1838];          // +0x0000
    int    ElevationIncrement;        // +0x1838
    char   _pad183C[0x4];             // +0x183C
    double ElevationIncrementBonus;   // +0x1840
    double ElevationBonusCap;         // +0x1848

    // FUNCTION: GAMEMD 0x66D150
    bool Read_ElevationModel(CCINIClass* pINI);
};
GG_STATIC_ASSERT(offsetof(RulesClass, ElevationIncrement)      == 0x1838);
GG_STATIC_ASSERT(offsetof(RulesClass, ElevationIncrementBonus) == 0x1840);
GG_STATIC_ASSERT(offsetof(RulesClass, ElevationBonusCap)       == 0x1848);

#endif  // GG_MATCH_CORE_RULES_CLASS_ELEVATION_METHODS_H
