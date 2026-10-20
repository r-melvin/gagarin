// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x53AB50.

#include "lightning_storm_methods.h"

// FUNCTION: GAMEMD 0x53AB50  LightningStorm::Init (__fastcall, static)
// Re-light the map for the storm, then raise the local player's flag. The
// lighting call takes no arguments, so retail issues it before touching the
// global at all.
void LightningStorm::Init()
{
    ScenarioClass::UpdateLighting();
    CurrentPlayer->unknown_5779 = true;
}
