// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x41D830.

#include "airstrike_class_methods.h"

// FUNCTION: GAMEMD 0x41D830  AirstrikeClass::StartMission (__thiscall, ret 0x4)
// A fresh airstrike starts its run; one already in progress only re-targets, and
// only when the target actually changed. Retail hoists the argument load between
// the flag TEST and its JNZ, which is what putting the flag test first produces.
void AirstrikeClass::StartMission(ObjectClass* target)
{
    if (!unknown_3C) {
        BeginMission(target);
        return;
    }

    if (target != Target)
        ResetTarget(target);
}
