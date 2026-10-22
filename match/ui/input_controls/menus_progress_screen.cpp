// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// ProgressScreenClass entry (layout and evidence: menus_progress_screen.h).

#include "menus_progress_screen.h"

// FUNCTION: GAMEMD 0x643E80
void ProgressScreenClass::Slot0(int value)
{
    Field04 = value;
}
