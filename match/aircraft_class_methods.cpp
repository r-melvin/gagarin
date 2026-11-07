// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 disassembly at the entry below (AircraftClass
//   primary vtable 0x7E22A4, slot 54; slot 144 at 0x419C80), read with the Ghidra CLI from the entry point.
#include "_layout/aircraft_class.h"
#include "_layout/aircraft_type_class.h"
#include "_layout/gbl_0087f7e8.h"
#include "_layout/building_class.h"
#include "_layout/techno_type_class.h"
#include "_layout/cell_class.h"
#include "loco_com.h"
#include "weapon_type_class.h"

// FUNCTION: GAMEMD 0x414310
// Slot 54: a flying type is raised by its height above the ground unless it is a missile or already on the usable
// map; once the base accepts the placement the turret is set to the facing, the stage timer restarts and slot 337
// is told whether the type's slot 47 value equals slot 114.
bool AircraftClass::vf_54(const CoordStruct& coord, int a2)
{
    CoordStruct loc = coord;
    if (!Type->MissileSpawn) {
        if (!Spawned && DAT_0087F7E8.FUN_005785F0(coord))
            loc.Z = DAT_0087F7E8.FUN_00578080(coord);
        else
            loc.Z = DAT_0087F7E8.FUN_00578080(coord) + Type->vf_47();
    }
    if (FootClass::vf_54(loc, a2)) {
        if (!Type->Selectable || !Type->Landable
            || (vf_254(0)->WeaponType && vf_254(0)->WeaponType->Camera))
            Spawned = 1;
        if (Passengers.FirstPassenger)
            HasPassengers = 1;
        DirStruct dir;
        dir.Raw = (a2 & 0xFF) << 8;
        SecondaryFacing.FUN_004C9300(&dir);
        SetRate(1);
        StageClass::Value = 0;
        if (vf_114() == Type->vf_47())
            vf_337(1.0);
        else
            vf_337(0.0);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x417C80
// Slot 80 forwards its four arguments to the foot body.
bool AircraftClass::vf_80(int mode, CellStruct* cell, int a3, int a4)
{
    return FootClass::vf_80(mode, cell, a3, a4);
}

// The carryall hands its first passenger over to its radio link. Retail saves EBP only around this block (a local
// PUSH/POP EBP in the arm and at each of its exits) where a body in the function proper saves it in the prologue, so
// it is kept as an inline function.
static inline int TransferCargo(AircraftClass* self)
{
    TechnoClass* link = self->FUN_0065AD30(0);
    FootClass* passenger = self->Passengers.RemoveFirstPassenger();
    self->vf_157(3);
    if (passenger->vf_158(2, link) == 1) {
        self->Passengers.AddPassenger(passenger);
        self->vf_73(0);
        self->FUN_00416AF0();
        self->vf_73(1);
        self->vf_122(2, false);
        return 1;
    }
    self->SetDestination(self->FUN_0041A160(), true);
    self->vf_122(2, false);
    return 1;
}

// FUNCTION: GAMEMD 0x419C80
// Slot 144, the airport-bound landing mission step. The step number in MissionStatus picks the stage; the result is
// the delay until the next step.
int AircraftClass::vf_144()
{
    if (!vf_114() && Type->AirportBound && Destination) {
        if (Destination != vf_111()->GetBuilding()) {
            DockNowHeadingTo = Destination->KindCast_00459F40(6);
            vf_157(3);
            vf_122(2, true);
            return 1;
        }
    }
    if (vf_114() > 0 && DockNowHeadingTo != Destination && Destination && Destination->vf_11() == 6)
        DockNowHeadingTo = Destination->KindCast_00459F40(6);
    if (!Destination && vf_30() != 2 && vf_157(0xE) != 1 && !FUN_0070D8F0()) {
        EnterIdleMode(false, true);
        return 1;
    }
    switch (MissionStatus) {
    case 0:
        MissionStatus = 6;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        IsCarryallNotLanding = 1;
        return 1;
    case 6:
        if (Type->AirportBound && vf_114())
            vf_157(0xE);
        if (!HasAnyLink()) {
            if (!FUN_0070D8F0()) {
                if (Locomotor->GetStatus() == 1) {
                    MissionStatus = 7;
                    IsCarryallNotLanding = 1;
                }
                if (QueuedMission == -1) {
                    SetDestination(0, true);
                    EnterIdleMode(false, true);
                    IsCarryallNotLanding = 1;
                    return 1;
                }
                IsCarryallNotLanding = 1;
            }
            IsCarryallNotLanding = 1;
            return 1;
        }
        if (Locomotor->GetStatus() == 1 || (Type->AirportBound && !vf_114())) {
            MissionStatus = 7;
            IsCarryallNotLanding = 0;
        }
        return 3;
    case 7:
        if (Locomotor->GetStatus() == 1) {
            AbstractClass* dest = Destination;
            if (dest) {
                CoordStruct goal = dest->vf_11() == 6 ? static_cast<BuildingClass*>(dest)->vf_42(this) : Destination->vf_18();
                CoordStruct next = Location;
                int dx = goal.X - next.X;
                int dy = goal.Y - next.Y;
                if (dx > 0) {
                    if (dx > 5)
                        dx = 5;
                } else if (dx < -5)
                    dx = -5;
                if (dy > 0) {
                    if (dy > 5)
                        dy = 5;
                } else if (dy < -5)
                    dy = -5;
                next.X += dx;
                next.Y += dy;
                vf_109(next);
            }
            IsCarryallNotLanding = 1;
            return 1;
        }
        IsCarryallNotLanding = 1;
        switch (vf_157(0x15)) {
        case 1:
            if (Type->Carryall && Passengers.FirstPassenger)
                return TransferCargo(this);
            vf_122(5, false);
            break;
        case 5:
            vf_53();
            FUN_0065AD30(0)->Passengers.AddPassenger(this);
            return 1;
        default:
            EnterIdleMode(false, true);
            return 1;
        }
    }
    return 1;
}
