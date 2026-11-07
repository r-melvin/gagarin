// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   EBolt members read off the user's retail gamemd.exe v1.001: constructor
//   0x4C1E10 (allocation site 0x6FD460, size 0x30), owner coordinate query
//   0x4C2B40 (UnitClass slot 44 = 0x6F3AD0, three-dword base coordinate), owner
//   latch 0x4C2BD0 and detach 0x4C2C10.

#include "_layout/ebolt_class.h"
#include "_layout/unit_class.h"
#include "header_init_shapes.h"
#include "vector_class_operations.h"
#include "_layout/tactical.h"
#include "_layout/tactical_viewport.h"
#include "wwlib/surface/surface_class.h"

void __cdecl operator delete(void*);

// FUNCTION: GAMEMD 0x4C1E10
//
// A fresh bolt: both end points at the origin, no owner, and the two trailing
// state fields at their start values.
EBolt::EBolt()
{
    CoordStruct z = { 0, 0, 0 };
    Point1 = z;
    Color = 0;
    At_28 = 0x10000;
    At_2C = false;
    Phase = 0;
    Owner = 0;
    Point2 = z;
    WeaponSlot = 0;
}

// Draw one bolt when its end points fall on screen, count its phase and halve its life counter.
static inline void DrawBolt(EBolt* bolt)
{
    if (bolt->At_28 != 0) {
        Point2D a;
        Point2D b;
        DAT_00887324->CoordsToClient(&bolt->Point1, &a);
        DAT_00887324->CoordsToClient(&bolt->Point2, &b);
        if (ClipLine(&a, &b, &Viewport_00886FA0)) {
            bolt->FUN_004C1F20(bolt->Point1, bolt->Point2, bolt->At_2C ? 5 : 10);
        }
        bolt->Phase++;
    }
    bolt->At_28 >>= 1;
}

// FUNCTION: GAMEMD 0x4C2830
//
// Step every live bolt, last to first: take the start point from the owner when it reports one, draw
// it, and free it once its life counter reaches zero.
void FUN_004C2830()
{
    for (int i = DAT_008A0E88.Count - 1; i >= 0; i--) {
        EBolt* bolt = DAT_008A0E88.Items[i];
        if (bolt->Owner != 0) {
            CoordStruct start = bolt->Owner->vf_44(bolt->WeaponSlot, CoordStructInit(0, 0, 0));
            if (start.X != DAT_008A0E50.X || start.Y != DAT_008A0E50.Y || start.Z != DAT_008A0E50.Z)
                bolt->Point1 = start;
        }
        DrawBolt(bolt);
        if (bolt->At_28 == 0) {
            DAT_008A0E88.RemoveItem(bolt);
            delete bolt;
        }
    }
}

// FUNCTION: GAMEMD 0x4C2B40
//
// The bolt's start position: the owner's slot-44 coordinate for the latched
// weapon, or the zero coordinate when the bolt has no owner.
CoordStruct* EBolt::GetOwnerCoords(CoordStruct* out)
{
    if (Owner != 0) {
        CoordStruct zero = { 0, 0, 0 };
        *out = Owner->vf_44(WeaponSlot, zero);
    } else {
        *out = DAT_008A0E50;
    }
    return out;
}

// FUNCTION: GAMEMD 0x4C2BD0
//
// Latch the firing unit and its weapon slot, but only when the candidate owner
// is a live, non-limbo UnitClass (WhatAmI() == AbstractType::Unit).
void EBolt::SetOwner(UnitClass* pOwner, int idxWeapon)
{
    if (pOwner != 0) {
        if (pOwner->vf_11() == 1 && pOwner->IsAlive && !pOwner->InLimbo) {
            Owner = pOwner;
            WeaponSlot = idxWeapon;
        }
    }
}

// FUNCTION: GAMEMD 0x4C2C10
//
// Unlink from the owner: clear the owner's pointer back at this bolt, then drop
// the owner.
void EBolt::DetachOwner()
{
    if (Owner != 0) {
        Owner->ElectricBolt = 0;
        Owner = 0;
    }
}
