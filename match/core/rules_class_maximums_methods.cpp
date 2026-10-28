// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x672230: the section-name pointer at
//   0x7F0CA4 ("Maximums"), the key "Players" (0x83A0BC) and the RulesClass member at +0x14D0.
//
// Address index: 0x672230

#include "rules_class_jumpjet_methods.h"

// GLOBAL: GAMEMD 0x7F0CA4 -- pointer to the "Maximums" section name.
extern char* MaximumsSection_00672230;

// RulesClass view: only the member this reader fills.
struct Rules_00672230
{
    char unknown_0000[0x14D0];
    int  Players;    // +0x14D0
    // FUNCTION: GAMEMD 0x672230 -- RulesClass::Read_Maximums.
    bool Read_Maximums(CCINI_006743D0* pINI);
};
GG_STATIC_ASSERT(offsetof(Rules_00672230, Players) == 0x14D0);

// FUNCTION: GAMEMD 0x672230
// Reads the player limit from the [Maximums] section when the section exists.
bool Rules_00672230::Read_Maximums(CCINI_006743D0* pINI)
{
    bool        ok  = false;
    const char* key = 0;

    if (key == 0) {
        ok = pINI->GetSection(MaximumsSection_00672230) != 0;
    } else {
        ok = pINI->GetEntry(MaximumsSection_00672230, key) != 0;
    }

    if (ok)
        Players = pINI->ReadInteger(MaximumsSection_00672230, "Players", Players);
    return true;
}
