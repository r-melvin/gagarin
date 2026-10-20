// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x554AA0).
//   Names cross-checked against YRpp LightSourceClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x554AA0  LightSourceClass::ChangeLevels (__thiscall)
//   FUNCTION: GAMEMD 0x554AF0  LightSourceClass::Calculate    (referenced)

#include "light_source_class_more_methods.h"

// FUNCTION: GAMEMD 0x554AA0  (__thiscall)
// Re-tint / re-level the light. If the intensity or tint actually changed,
// store the new values and, if currently lit, recompute the light converts.
void LightSourceClass::ChangeLevels(int nIntensity, TintStruct Tint, unsigned long mode)
{
    if (LightIntensity != nIntensity ||
        LightTint.Red != Tint.Red ||
        LightTint.Red != Tint.Blue)
    {
        LightIntensity = nIntensity;
        LightTint.Red = Tint.Red;
        LightTint.Green = Tint.Green;
        LightTint.Blue = Tint.Blue;
        if (Activated)
            Calculate(mode);
    }
}
