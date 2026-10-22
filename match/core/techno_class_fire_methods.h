// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly of 0x70ECE0), cross-checked
//   against YRpp (consult-only; every offset
//   reconfirmed numerically from the 0x70ECE0 disassembly below).
//
// NOTE ON NAMING: the orchestrator tasked this TU as "TechnoClass-fire", but the
// symbol that actually lives at retail 0x70ECE0 is RecoilData::Fire (name
// cross-checked against YRpp). The function tests
// [ECX] (== Turret.Travel, an int) for zero and uses it as a float-division
// numerator, which a real TechnoClass (vtable @ +0) could never do. We therefore
// model the small RecoilData/TurretControl helper structs the function genuinely
// touches.
#ifndef GG_MATCH_CORE_TECHNO_CLASS_FIRE_METHODS_H
#define GG_MATCH_CORE_TECHNO_CLASS_FIRE_METHODS_H

#include <stddef.h>  // offsetof  (VC6-compatible)
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// TurretControl  (sizeof = 0x10).
// Fire() reads Travel (+0x00) and CompressFrames (+0x04).
// ---------------------------------------------------------------------------
struct TurretControl
{
    int Travel;          // +0x00
    int CompressFrames;  // +0x04
    int RecoverFrames;   // +0x08
    int HoldFrames;      // +0x0C
};

// ---------------------------------------------------------------------------
// RecoilData  (sizeof = 0x20).
//
// Confirmed from 0x70ECE0 (RecoilData::Fire):
//   [ECX]      Turret.Travel      (int, numerator, tested for 0)
//   [ECX+0x04] Turret.CompressFrames (int)
//   [ECX+0x10] TravelPerFrame     (float, written = Travel / TravelFramesLeft)
//   [ECX+0x18] State              (uint, written 1 == Compressing)
//   [ECX+0x1c] TravelFramesLeft   (int, set to CompressFrames, floored to 1)
// ---------------------------------------------------------------------------
struct RecoilData
{
    void Fire();  // GAMEMD 0x70ECE0  __thiscall

    TurretControl Turret;          // +0x00
    float         TravelPerFrame;  // +0x10
    float         TravelSoFar;     // +0x14
    unsigned int  State;           // +0x18  (RecoilState)
    int           TravelFramesLeft;// +0x1c
};

GG_STATIC_ASSERT(offsetof(TurretControl, Travel) == 0x00);
GG_STATIC_ASSERT(offsetof(TurretControl, CompressFrames) == 0x04);
GG_STATIC_ASSERT(sizeof(TurretControl) == 0x10);

GG_STATIC_ASSERT(offsetof(RecoilData, Turret) == 0x00);
GG_STATIC_ASSERT(offsetof(RecoilData, TravelPerFrame) == 0x10);
GG_STATIC_ASSERT(offsetof(RecoilData, TravelSoFar) == 0x14);
GG_STATIC_ASSERT(offsetof(RecoilData, State) == 0x18);
GG_STATIC_ASSERT(offsetof(RecoilData, TravelFramesLeft) == 0x1c);
GG_STATIC_ASSERT(sizeof(RecoilData) == 0x20);

#endif  // GG_MATCH_CORE_TECHNO_CLASS_FIRE_METHODS_H
