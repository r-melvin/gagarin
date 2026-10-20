// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x48ACF0.

#include "unsorted_rules_methods.h"

// FUNCTION: GAMEMD 0x48ACF0  Unsorted::GetFloaterGravity (__fastcall)
// The integer rule is loaded straight onto the x87 stack (FILD) and halved by
// the shared 0.5 constant at 0x007E1738; no register work at all.
double __fastcall Unsorted_GetFloaterGravity()
{
    return RulesGlobalPtr->Gravity * 0.5;
}
