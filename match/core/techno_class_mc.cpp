// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x70E360  TechnoClass::GetEffectTintIntensity (__thiscall)
//   FUNCTION: GAMEMD 0x7105E0  TechnoClass::IsMindControlled       (__thiscall)

#include "techno_class_mc.h"

// FUNCTION: GAMEMD 0x70E360  (__thiscall)
// The total effect tint is the invulnerability tint folded through the
// airstrike tint helper:
//   GetAirstrikeTintIntensity(GetInvulnerabilityTintIntensity(current)).
// Retail passes `current` on the stack to the first helper, then the result on
// to the second (both __thiscall on `this`); neither helper is matched here.
int TechnoClass::GetEffectTintIntensity(int currentIntensity) const
{
    return GetAirstrikeTintIntensity(GetInvulnerabilityTintIntensity(currentIntensity));
}

// FUNCTION: GAMEMD 0x7105E0  (__thiscall)
// Mind-controlled iff a controller object is attached OR the "by a unit" flag
// is set. Retail short-circuits: `MOV EAX,[+0x2C0] / JNZ ret1` then tests the
// +0x2C4 byte, converging on `MOV EAX,1` / `XOR EAX,EAX`.
bool TechnoClass::IsMindControlled() const
{
    return MindControlledBy != NULL || MindControlledByAUnit;
}
