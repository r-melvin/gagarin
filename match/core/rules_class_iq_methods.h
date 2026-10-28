// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read off the user's retail gamemd.exe v1.001 at 0x674240: section
//   name pointer at 0x7F0CDC, INIClass calls 0x526810 (GetSection) and
//   0x5276D0 (ReadInteger), and the eleven IQ thresholds at [this+0x1434..0x145C].
#ifndef GG_MATCH_CORE_RULES_CLASS_IQ_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_IQ_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class CCINI_00674240
{
public:
    // FUNCTION: GAMEMD 0x526810 (decl; reloc) -- INIClass::GetSection.
    void* GetSection(const char* pSection);
    // FUNCTION: GAMEMD 0x5276D0 (decl; reloc) -- INIClass::ReadInteger.
    // FUNCTION: GAMEMD 0x526B10 (decl; reloc) -- INIClass::GetEntry.
    void* GetEntry(const char* pSection, const char* pKey);
    int   ReadInteger(const char* pSection, const char* pKey, int defaultValue);
};

// GLOBAL: GAMEMD 0x7F0CDC -- holds the "IQ" section name.
extern char* IQSection_00674240;

struct Rules_00674240
{
    char _pad000[0x1434];  // +0x0000
    int  MaxIQLevels;      // +0x1434
    int  SuperWeapons;     // +0x1438
    int  Production;       // +0x143C
    int  GuardArea;        // +0x1440
    int  RepairSell;       // +0x1444
    int  AutoCrush;        // +0x1448
    int  Scatter;          // +0x144C
    int  ContentScan;      // +0x1450
    int  Aircraft;         // +0x1454
    int  Harvester;        // +0x1458
    int  SellBack;         // +0x145C

    // FUNCTION: GAMEMD 0x674240 -- RulesClass::Read_IQ.
    bool Read_IQ(CCINI_00674240* pINI);
};
GG_STATIC_ASSERT(offsetof(Rules_00674240, MaxIQLevels) == 0x1434);
GG_STATIC_ASSERT(offsetof(Rules_00674240, SuperWeapons) == 0x1438);
GG_STATIC_ASSERT(offsetof(Rules_00674240, Production) == 0x143C);
GG_STATIC_ASSERT(offsetof(Rules_00674240, GuardArea) == 0x1440);
GG_STATIC_ASSERT(offsetof(Rules_00674240, RepairSell) == 0x1444);
GG_STATIC_ASSERT(offsetof(Rules_00674240, AutoCrush) == 0x1448);
GG_STATIC_ASSERT(offsetof(Rules_00674240, Scatter) == 0x144C);
GG_STATIC_ASSERT(offsetof(Rules_00674240, ContentScan) == 0x1450);
GG_STATIC_ASSERT(offsetof(Rules_00674240, Aircraft) == 0x1454);
GG_STATIC_ASSERT(offsetof(Rules_00674240, Harvester) == 0x1458);
GG_STATIC_ASSERT(offsetof(Rules_00674240, SellBack) == 0x145C);

#endif  // GG_MATCH_CORE_RULES_CLASS_IQ_METHODS_H
