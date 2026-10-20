// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x70ED10: `[ECX]` (Travel), `[ECX+0x8]` (RecoverFrames),
//   `[ECX+0xC]` (HoldFrames), `[ECX+0x10]` (TravelPerFrame, float),
//   `[ECX+0x14]` (TravelSoFar, float), `[ECX+0x18]` (State), `[ECX+0x1C]`
//   (TravelFramesLeft). All agree with RecoilData in the committed spine
//   match/_layout/techno_class.h (TurretRecoil @0x3D8 / BarrelRecoil @0x3F8).
//   YRpp lists 0x70ED10 as RecoilData::Update (nested in struct RecoilData;
//   the flat method map mis-files it as TechnoClass::Update).
#ifndef GG_MATCH_COMBAT_TECHNO_CLASS_UPDATE_METHODS_H
#define GG_MATCH_COMBAT_TECHNO_CLASS_UPDATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/techno_class.h"   // RecoilData / TurretControl (sizeof 0x20 / 0x10)

// The spine's RecoilData is data-only; this view adds the matched method on the
// identical layout (single inheritance at offset 0, no adjustment).
struct RecoilData_0070ED10 : RecoilData
{
    // FUNCTION: GAMEMD 0x70ED10 — RecoilData::Update
    void Update();
};
GG_STATIC_ASSERT(offsetof(RecoilData_0070ED10, Turret)           == 0x00);
GG_STATIC_ASSERT(offsetof(RecoilData_0070ED10, TravelPerFrame)   == 0x10);
GG_STATIC_ASSERT(offsetof(RecoilData_0070ED10, TravelSoFar)      == 0x14);
GG_STATIC_ASSERT(offsetof(RecoilData_0070ED10, State)            == 0x18);
GG_STATIC_ASSERT(offsetof(RecoilData_0070ED10, TravelFramesLeft) == 0x1C);
GG_STATIC_ASSERT(offsetof(TurretControl, RecoverFrames)          == 0x08);
GG_STATIC_ASSERT(offsetof(TurretControl, HoldFrames)             == 0x0C);
GG_STATIC_ASSERT(sizeof(RecoilData_0070ED10)                     == 0x20);

#endif  // GG_MATCH_COMBAT_TECHNO_CLASS_UPDATE_METHODS_H
