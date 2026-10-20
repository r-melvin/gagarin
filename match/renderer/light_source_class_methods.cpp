// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp LightSourceClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x554A60  LightSourceClass::Activate   (__thiscall)
//   FUNCTION: GAMEMD 0x554A80  LightSourceClass::Deactivate (__thiscall)
//   FUNCTION: GAMEMD 0x554AF0  LightSourceClass::Calculate  (referenced; matched elsewhere)

#include "light_source_class_methods.h"

// FUNCTION: GAMEMD 0x554A60  (__thiscall)
// Start lighting: if not already active, raise the Activated flag and recompute.
void LightSourceClass::Activate(unsigned long dwZero)
{
    if (!Activated)
    {
        Activated = 1;
        Calculate(dwZero);
    }
}

// FUNCTION: GAMEMD 0x554A80  (__thiscall)
// Stop lighting: if currently active, lower the Activated flag and recompute.
void LightSourceClass::Deactivate(unsigned long dwZero)
{
    if (Activated)
    {
        Activated = 0;
        Calculate(dwZero);
    }
}
