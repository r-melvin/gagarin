// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// ObjectClass bodies for primary-table (0x7EF060) slots in the block
// 0x5F3E30..0x5F4352, in retail address order. Slot numbers come from the
// RTTI-located table; names are placeholders (object_class.h).
#include "../_layout/object_class.h"
#include "../_layout/anim_class.h"
#include "../_layout/anim_type_class.h"
#include "frame_counter.h"


// The map cell (read-only here).
#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"
class Point2D;

// The map object at 0x87F7E8 (only the entry points used here).

// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) -- plays a sound at a coordinate
// through an audio controller (__fastcall, sound in ECX, coordinate in EDX).
void* FUN_007509E0(int sound, CoordStruct* coord, AudioController* controller);
// GLOBAL: GAMEMD 0x8871E0
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;

// Descriptive local helpers for code retail has inlined; no original names
// are attested. A timer temporary started now (its middle word is never
// written), and a coordinate raised by `dz`.
static inline CDTimerClass TimerStarted(int delay)
{
    CDTimerClass timer;
    timer.StartTime = CurrentFrame;
    timer.TimeLeft = delay;
    return timer;
}

static inline CoordStruct CoordRaised(const CoordStruct& coord, int dz)
{
    CoordStruct raised = coord;
    raised.Z += dz;
    return raised;
}

// FUNCTION: GAMEMD 0x5F3E30
void* ObjectClass::vf_27()
{
    return vf_34()->vf_39();
}

// FUNCTION: GAMEMD 0x5F3E50
// True when the object's type has the given ID text.
bool ObjectClass::FUN_005F3E50(const char* name)
{
    return vf_34()->FUN_00410A40(name);
}

// FUNCTION: GAMEMD 0x5F3E70
// PARTIAL 68.9%: retail's frame is 0x10 (one 12-byte slot shared by every
// coordinate temporary plus the damage word); cl gives the raised landing
// coordinate its own slot (0x1C), which shifts every ESP offset, and
// allocates EDI/EDX differently in the flaming-guy tail. Tried a flat
// early-return layout (41.4%), retail's nesting (68.0%) and inline
// temporaries for the timer and the raised coordinate (68.9%).
// The per-frame update every object runs: ambient and custom sounds while on
// the map, then the falling step (slot 116 height plus FallRate), landing, the
// fall-rate update and, for a falling bomb or a flaming-guy animation, the
// landing effects. WhatAmI (slot 11) value 4 is the animation class.
void ObjectClass::vf_23()
{
    if (!InLimbo) {
        if (vf_34() != 0 && vf_34()->AmbientSound != -1) {
            CoordStruct coord = Location;
            FUN_007509E0(vf_34()->AmbientSound, &coord, &AmbientSoundController);
        }
        if (CustomSound != -1) {
            CoordStruct coord = Location;
            FUN_007509E0(CustomSound, &coord, &CustomSoundController);
        }
    }

    if (IsFallingDown) {
        int layer = vf_30();
        int height = FUN_005F5F30() + FallRate;
        if (IsOnMap) {
            vf_73(0);
            Location.Z = height;
            vf_73(1);
        } else {
            Location.Z = height;
        }

        if (vf_114() <= 0) {
            vf_115(0);
            IsFallingDown = 0;
            vf_99(2);
            if (Parachute != 0) {
                Parachute->RemainingIterations = 0;
            }
        }

        if (!InLimbo) {
            if (HasParachute) {
                FallRate--;
                int floor = DAT_008871E0->ParachuteMaxFallRate;
                FallRate = (FallRate > floor) ? FallRate : floor;
            } else {
                FallRate = (int)(FallRate - 1.4);
                int floor = DAT_008871E0->NoParachuteMaxFallRate;
                FallRate = (FallRate > floor) ? FallRate : floor;
            }

            if (layer != vf_30()) {
                DAT_0087F7E8.FUN_004A9720(this);
            }

            if (!IsFallingDown) {
                if (IsABomb && Health > 0) {
                    int damage = Health;
                    vf_91(&damage, 0, DAT_008871E0->C4Warhead, 0, true, true, 0);
                }

                if (vf_11() == 4) {
                    AnimClass* anim = (AnimClass*)this;
                    if (((AnimTypeClass*)anim->Type)->IsFlamingGuy) {
                        anim->FlamingGuyExpire = 1;
                        anim->Rate = 1;
                        anim->Timer = TimerStarted(1);
                        anim->Value = ((AnimTypeClass*)anim->Type)->RunningFrames * 8 + 1;
                        CoordStruct coord = anim->Location;
                        if (DAT_0087F7E8.FUN_00565730(&coord)->LandType == 2) {
                            new AnimClass(const_cast<AnimTypeClass*>(DAT_008871E0->list_0BC0.Items[0]), CoordRaised(anim->Location, 3), 0, 1, 0x600, 0, false);
                        }
                    }
                }
            }
        } else {
            DAT_0087F7E8.FUN_004A9770(this);
        }
    }
}

// FUNCTION: GAMEMD 0x5F4240
int ObjectClass::vf_29(ObjectClass* target, char flag)
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F4250
int ObjectClass::vf_28(CellStruct* cell, char a, char b)
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F4260
int ObjectClass::vf_30()
{
    if (!IsInAir()) {
        return 2;
    }
    return (vf_114() >= DAT_008871E0->unknown_420) + 3;
}

// FUNCTION: GAMEMD 0x5F42A0
int ObjectClass::vf_35()
{
    return 0x7FFFFFFF;
}

// FUNCTION: GAMEMD 0x5F42B0
bool ObjectClass::vf_37()
{
    return false;
}

// FUNCTION: GAMEMD 0x5F42C0
bool ObjectClass::vf_38()
{
    return false;
}

// FUNCTION: GAMEMD 0x5F42D0
bool ObjectClass::vf_39()
{
    return false;
}

// FUNCTION: GAMEMD 0x5F42E0
bool ObjectClass::vf_40()
{
    return false;
}

// FUNCTION: GAMEMD 0x5F42F0
void ObjectClass::vf_56(void* source)
{
}

// FUNCTION: GAMEMD 0x5F4300
void ObjectClass::vf_57(void* house)
{
}

// FUNCTION: GAMEMD 0x5F4310
void ObjectClass::vf_63()
{
}

// FUNCTION: GAMEMD 0x5F4320
int ObjectClass::vf_64(int a1, int a2)
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F4330
void ObjectClass::vf_71()
{
}

// FUNCTION: GAMEMD 0x5F4340
void ObjectClass::vf_72(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x5F4350
bool ObjectClass::vf_81(int a1, ObjectClass* a2, int a3)
{
    return false;
}
