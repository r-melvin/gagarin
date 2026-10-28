// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x674500: three calls to 0x66D270 with the
//   section names "Easy" (0x818134), "Normal" (0x81BB60) and "Difficult" (0x83A0C4), filling the
//   0x50-byte blocks at RulesClass+0x1538, +0x1588 and +0x15D8.
//
// Address index: 0x674500

#include "rules_class_read_difficulty_methods.h"

// RulesClass view: only the three difficulty blocks this reader fills.
struct Rules_00674500
{
    char                 unknown_0000[0x1538];
    Difficulty_0066D270  Easy;       // +0x1538
    Difficulty_0066D270  Normal;     // +0x1588
    Difficulty_0066D270  Difficult;  // +0x15D8

    // FUNCTION: GAMEMD 0x674500 -- RulesClass::Read_Difficulties.
    bool Read_Difficulties(CCINI_0066D270* pINI);
};
GG_STATIC_ASSERT(sizeof(Difficulty_0066D270) == 0x50);
GG_STATIC_ASSERT(offsetof(Rules_00674500, Easy) == 0x1538);
GG_STATIC_ASSERT(offsetof(Rules_00674500, Normal) == 0x1588);
GG_STATIC_ASSERT(offsetof(Rules_00674500, Difficult) == 0x15D8);

// FUNCTION: GAMEMD 0x674500
// Reads the three difficulty sections into their blocks.
bool Rules_00674500::Read_Difficulties(CCINI_0066D270* pINI)
{
    Read_Difficulty_0066D270(pINI, &Easy, "Easy");
    Read_Difficulty_0066D270(pINI, &Normal, "Normal");
    Read_Difficulty_0066D270(pINI, &Difficult, "Difficult");
    return true;
}
