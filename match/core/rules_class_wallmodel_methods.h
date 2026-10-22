// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x66D1F0.
//
//   0x007F0C90  char* section-name global -> "WallModel" (string at 0x839E64)
//   0x0083B39C  "AlliedWallTransparency"
//   0x0083B384  "WallPenetratorThreshold"
//   0x00526810  INIClass::GetSection(const char*)
//   0x005295F0  INIClass::ReadBool(section, key, bool def)
//   0x005283D0  INIClass::ReadDouble(section, key, double def)
//
// A third INI-reader shape beside the two list-parser TUs: this one reads
// scalars out of a single section instead of enumerating keys.
#ifndef GG_MATCH_CORE_RULES_CLASS_WALLMODEL_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_WALLMODEL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class CCINIClass
{
public:
    // FUNCTION: GAMEMD 0x526810 (decl; reloc)
    void*  GetSection(const char* pSection);
    // FUNCTION: GAMEMD 0x526B10 (decl; reloc)
    void*  GetEntry(const char* pSection, const char* pKey);

    // FUNCTION: GAMEMD 0x679F40 — CCINIClass::Exists, matched out of line in
    // match/platform/ccini_class_methods.cpp. Read_WallModel expands this body
    // at the call site in flag form (caller-scope `bool ok = false`, assigned
    // in both arms of the `pKey == 0` chain, tested after it): with the key
    // defaulted to null the entry arm folds away and the section probe
    // survives as `TEST EAX,EAX; SETNZ AL; TEST AL,AL`, retail's shape. Kept
    // here as the model of what is being expanded; calling it directly keeps
    // EAX free for the following argument loads and scores 73.7%.
    bool Exists(const char* pSection, const char* pKey = 0)
    {
        if (pKey == 0) {
            return GetSection(pSection) != 0;
        }
        return GetEntry(pSection, pKey) != 0;
    }
    bool   ReadBool(const char* pSection, const char* pKey, bool defaultValue);
    double ReadDouble(const char* pSection, const char* pKey, double defaultValue);
};

// GLOBAL: GAMEMD 0x007F0C90 — holds the "WallModel" section name.
extern char* WallModelSection;

struct RulesClass
{
    char   _pad0000[0x1850];   // +0x0000
    bool   AlliedWallTransparency;      // +0x1850
    char   _pad1851[0x1858 - 0x1851];   // +0x1851
    double WallPenetratorThreshold;     // +0x1858  (default pushed as two dwords)

    bool Read_WallModel(CCINIClass* pINI);   // GAMEMD 0x66D1F0 __thiscall
};
GG_STATIC_ASSERT(offsetof(RulesClass, AlliedWallTransparency)  == 0x1850);
GG_STATIC_ASSERT(offsetof(RulesClass, WallPenetratorThreshold) == 0x1858);

#endif  // GG_MATCH_CORE_RULES_CLASS_WALLMODEL_METHODS_H
