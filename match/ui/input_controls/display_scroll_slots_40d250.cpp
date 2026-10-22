// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Two display-chain slot bodies emitted at 0x40D250 / 0x40D270: DisplayClass
// slot 43 (inherited down to MouseClass, table 0x7E1964) and ScrollClass slot 8
// (table 0x7F1094), which hands straight to TabClass's slot 8 (0x6D03A0).
#include "ui_display_chain.h"

// FUNCTION: GAMEMD 0x40D250
void DisplayClass::vf_43(int a1)
{
}

// FUNCTION: GAMEMD 0x40D270
void ScrollClass::vf_08()
{
    TabClass::vf_08();
}
