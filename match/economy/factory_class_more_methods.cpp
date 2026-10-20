// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp FactoryClass.h / TechnoClass.h (consult-only, no
//   LICENSE; every offset reconfirmed against the binary in the header).
//
// Translation unit: FactoryClass production-state methods (Suspend +
// GetBuildTimeFrames).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4C9E60   FactoryClass::Suspend             (__thiscall)
//   FUNCTION: GAMEMD 0x4C9FB0   FactoryClass::GetBuildTimeFrames  (__thiscall)

#include "factory_class_more_methods.h"

// FUNCTION: GAMEMD 0x4C9E60  (__thiscall)
// Mark production as suspended (no-op if already suspended) and reset the
// progress timer.  Resetting goes Rate = 0 first, then a CDTimerClass(0)
// temporary copied into Production.Timer; the temporary's uninitialised
// CurrentTime slot is carried through as the MOV [ECX+0x30],<garbage> store.
bool FactoryClass::Suspend(bool manual)
{
    if (!this->IsSuspended) {
        this->IsManual = manual;
        this->IsSuspended = true;
        this->Production.Start(0);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4C9FB0  (__thiscall)
// Build time in frames: the produced object's TimeToBuild() (0 when none) scaled
// down by 54 (signed IMUL+SAR), then clamped to [1, 255].
int FactoryClass::GetBuildTimeFrames() const
{
    int cost = 0;
    if (this->Object)
        cost = this->Object->TimeToBuild();

    int frames = cost / 54;
    if (frames < 1)
        return 1;
    if (frames > 255)
        frames = 255;
    return frames;
}
