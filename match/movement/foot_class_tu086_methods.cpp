// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of the FootClass methods between 0x4D31E0 and 0x4E0100 in retail gamemd.exe v1.001
//   (vtable 0x7E8C94 and direct callers), matched against the VC6 toolchain.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4D3780  FootClass::vf_73 (__thiscall)
//   FUNCTION: GAMEMD 0x4D4B20  FootClass::vf_133 (__thiscall)
//   FUNCTION: GAMEMD 0x4D4CB0  FootClass::vf_134 (__thiscall)
//   FUNCTION: GAMEMD 0x4D7170  FootClass::vf_54 (__thiscall)
//   FUNCTION: GAMEMD 0x4D9720  FootClass::vf_55 (__thiscall)
//   FUNCTION: GAMEMD 0x4D97A0  FootClass::FUN_004D97A0 (__thiscall)
//   FUNCTION: GAMEMD 0x4D98C0  FootClass::vf_238 (__thiscall)
//   FUNCTION: GAMEMD 0x4D9E70  FootClass::vf_38 (__thiscall)
//   FUNCTION: GAMEMD 0x4DBA50  FootClass::FUN_004DBA50 (__thiscall)
//   FUNCTION: GAMEMD 0x4DBED0  FootClass::vf_245 (__thiscall)
//   FUNCTION: GAMEMD 0x4DDDE0  FootClass::vf_28 (__thiscall)
//   FUNCTION: GAMEMD 0x4DE670  FootClass::FUN_004DE670 (__thiscall)
//   FUNCTION: GAMEMD 0x4DE7B0  FootClass::vf_314 (__thiscall)
//   FUNCTION: GAMEMD 0x4DE940  FootClass::vf_315 (__thiscall)
//   FUNCTION: GAMEMD 0x4DF320  FootClass::vf_306 (__thiscall)
//   FUNCTION: GAMEMD 0x4DF3A0  FootClass::vf_307 (__thiscall)
//   FUNCTION: GAMEMD 0x4DFA70  FootClass::vf_207 (__thiscall)
//   FUNCTION: GAMEMD 0x4DFB70  FootClass::vf_208 (__thiscall)
//   FUNCTION: GAMEMD 0x4DFCB0  FootClass::vf_210 (__thiscall)
//   FUNCTION: GAMEMD 0x4DFE00  FootClass::vf_211 (__thiscall)
//   FUNCTION: GAMEMD 0x4DFF40  FootClass::vf_209 (__thiscall)

#include "../_layout/foot_class.h"
#include "../_layout/house_class.h"
#include "../_layout/team_class.h"
#include "../_layout/team_type_class.h"
#include "../_layout/techno_type_class.h"
#include "../audio/vox_class_play_methods.h"
#include "loco_com.h"
#include "../_layout/aircraft_tracker_class.h"
#include "../_layout/coord_struct.h"
#include "../network/event_class_ctors.h"
#include "../_layout/building_class.h"
#include "../_layout/building_array.h"
#include "../_layout/infantry_class.h"
#include "../core/mission_class_methods.h"
#include "../core/scenario_class_methods.h"
#include "../_layout/house_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"
#include "../core/cell_step_tables.h"
#include "../_layout/player_ptr_00a83d4c.h"

// GLOBAL: GAMEMD 0x8B3D88 -- the "no cell" sentinel.
extern CellStruct DAT_008B3D88;

// GLOBAL: GAMEMD 0x8B3DF4
extern int DAT_008B3DF4;

// GLOBAL: GAMEMD 0x8B3DA8 -- the "no coordinate" sentinel.
extern CoordStruct DAT_008B3DA8;

// GLOBAL: GAMEMD 0x887888
extern AircraftTrackerClass AircraftTracker;

// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
extern ScenarioClass* DAT_00A8B230;

// GLOBAL: GAMEMD 0xA8E7AC -- nonzero while the scenario is being set up.
extern int DAT_00A8E7AC;

// FUNCTION: GAMEMD 0x65FA70 (decl; reloc) -- RadarEventClass::Create: event type in ECX, the cell by value.
bool __fastcall FUN_0065FA70(int type, CellStruct cell);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- the square root.
double __cdecl FUN_004CAC40(double value);

// The whole-lepton distance between two coordinates.
inline int Distance3D(const CoordStruct& a, const CoordStruct& b)
{
    CoordStruct d;
    d.X = a.X - b.X;
    d.Y = a.Y - b.Y;
    d.Z = a.Z - b.Z;
    double fy = (double)d.Y;
    double fz = (double)d.Z;
    double fx = (double)d.X;
    return (int)FUN_004CAC40(fy * fy + fz * fz + fx * fx);
}

// The same distance with the squares written in x, z, y order, as the slot 38 and slot 210 bodies emit it.
inline int Distance3DXZY(const CoordStruct& a, const CoordStruct& b)
{
    CoordStruct d;
    d.X = a.X - b.X;
    d.Y = a.Y - b.Y;
    d.Z = a.Z - b.Z;
    return (int)FUN_004CAC40((double)d.X * (double)d.X + (double)d.Z * (double)d.Z + (double)d.Y * (double)d.Y);
}

// The cell holding a lepton coordinate.
inline CellStruct CoordToCell(const CoordStruct& where)
{
    CellStruct result;
    result.X = where.X / 256;
    result.Y = where.Y / 256;
    return result;
}

// The object as an infantryman when it is one (RTTI 0xF), else 0.
inline InfantryClass* CastToInfantry(FootClass* object)
{
    return object == 0 ? 0 : (object->vf_11() == 0xF ? (InfantryClass*)object : 0);
}

// ---- functions ----
// FUNCTION: GAMEMD 0x4D3780
// Slot 73. Mode 2 is accepted outright. Otherwise the base slot decides, and an object on the ground layer
// (2) takes its footprint off (mode 0) or puts it on (mode 1 or 3) the cell map under its own cell.
bool FootClass::vf_73(int mode)
{
    if (mode == 2) {
        return true;
    }
    if (TechnoClass::vf_73(mode)) {
        if (vf_30() == 2) {
            CellStruct cell = vf_110();
            switch (mode) {
            case 0:
                DAT_0087F7E8.FUN_005687F0(&cell, this);
                break;
            case 1:
            case 3:
                DAT_0087F7E8.FUN_005683C0(&cell, this);
                return true;
            }
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4D4B20
// Slot 133 (mission handler). Like slot 134, but any infantry role that can use a building (C4, the ability
// 0xE, engineer, occupier, assaulter, infiltrator) sends him to it; without a target a non-human owner's
// unit stands down (unless an occupier infantryman) and goes to mission 0xF.
int FootClass::vf_133()
{
    InfantryClass* infantry = CastToInfantry(this);
    if (Target != 0 && Target->vf_11() == 6) {
        if (Destination != 0) {
            goto idle;
        }
        if (infantry != 0) {
            if (infantry->Type->C4 || infantry->FUN_0070D0D0(0xE) || infantry->Type->Engineer
                || infantry->Type->Occupier || infantry->Type->Assaulter || infantry->Type->Infiltrate) {
                SetDestination(Target, true);
            }
        }
    }
    if (Destination == 0) {
        EnterIdleMode(false, true);
        if (DAT_0087F7E8.FUN_00565730(&vf_18())->FUN_0047C520() != 0) {
            vf_93(DAT_008B3DA8, true, false);
        }
    }
idle:
    if (Target == 0) {
        if (!Owner->FUN_0050B730()) {
            if (vf_11() != 0xF || !((InfantryClass*)this)->Type->Occupier) {
                vf_242(0);
                SetDestination(0, true);
                vf_122(0xF, false);
            }
        }
    }
    int base = (int)(FUN_005B3A00()->Rate * 900.0);
    return base + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
}

// FUNCTION: GAMEMD 0x4D4CB0
// Slot 134 (mission handler). An infantryman holding a building target with no destination enters it when
// he can occupy it (C4, the ability 0xE or an engineer); with no destination, idle, and look for a
// building on the spot; then wait the mission rate plus a random 0..2 frames.
int FootClass::vf_134()
{
    InfantryClass* infantry = CastToInfantry(this);
    if (Target != 0 && Target->vf_11() == 6) {
        if (Destination != 0) {
            goto wait;
        }
        if (infantry != 0) {
            if (infantry->Type->C4 || infantry->FUN_0070D0D0(0xE) || infantry->Type->Engineer) {
                SetDestination(Target, true);
            }
        }
    }
    if (Destination == 0) {
        EnterIdleMode(false, true);
        if (DAT_0087F7E8.FUN_00565730(&vf_18())->FUN_0047C520() != 0) {
            vf_93(DAT_008B3DA8, true, false);
        }
    }
wait:
    int base = (int)(FUN_005B3A00()->Rate * 900.0);
    return base + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
}

// FUNCTION: GAMEMD 0x4D7170
// Slot 54. Places the object on the map through the base slot, then unlimbos the locomotor and powers it
// down for an ion-sensitive one while the owner's ion sensitives are offline (up otherwise), clears the
// first path direction and raises the blocked counter of the eight cells around its own. A ground object
// records the cell; an aircraft type joins the tracker. The speed bias and the sensor disc follow.
bool FootClass::vf_54(const CoordStruct& coord, int a2)
{
    if (TechnoClass::vf_54(coord, a2)) {
        (*(ILocomotionPtr*)&Locomotor)->Unlimbo();
        if (Owner->IonSensitivesShouldBeOffline() && (*(ILocomotionPtr*)&Locomotor)->IsIonSensitive()) {
            (*(ILocomotionPtr*)&Locomotor)->PowerOff();
        } else {
            (*(ILocomotionPtr*)&Locomotor)->PowerOn();
        }
        vf_102(Owner);
        PathDirections[0] = -1;
        CellStruct base = vf_110();
        for (int i = 0; i < 8; i++) {
            CellStruct neighbour = base + DAT_0089F688[i & 7];
            CellClass* around = DAT_0087F7E8.FUN_005657A0(&neighbour);
            around->BlockedNeighbours++;
        }
        if (!IsInAir()) {
            LastMapCoords = base;
        } else if (vf_33()->ConsideredAircraft) {
            AircraftTracker.Add(this);
        }
        double coefficient = vf_33()->ThreatAvoidanceCoefficient;
        unknown_530 = coefficient;
        if (vf_33()->SensorsSight != 0) {
            vf_314(DAT_008B3D88);
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4D9720
// Slot 55. Leaving the map (flag set) lets go of the team first unless the scenario is still loading;
// putting it back (flag clear) skips the slot-157 call for an allied radio link. Both end in the base slot.
void FootClass::vf_55(bool removed)
{
    if (removed) {
        if (Team != 0 && !DAT_00A8E7AC) {
            Team->LiberateMember(this, -1, 0);
        }
        vf_157(3);
    } else {
        TechnoClass* link = FUN_0065AD30(0);
        if (link != 0 && !Owner->IsAlliedWith(link)) {
            vf_157(3);
        }
    }
    TechnoClass::vf_55(removed);
}

// FUNCTION: GAMEMD 0x4D97A0
// A score for attacking `target`. Zero without a target, with an armed current target, when the team's type
// forbids it, in mission 10 or without firepower. The current target scores minus its firepower; any other
// scores the firepower (times 1024) over the turns needed to get within weapon range.
int FootClass::FUN_004D97A0(AbstractClass* target)
{
    if (target != 0) {
        if (Target == target) {
            return -vf_176();
        }
        if (Target == 0 || !Target->Flags.IsTechno || !((TechnoClass*)Target)->IsArmed()) {
            bool teamAllows;
            if (Team != 0 && Team->Type->Flag_F6) {
                teamAllows = true;
            } else {
                teamAllows = false;
            }
            if (Team == 0 || teamAllows) {
                if (vf_97() != 10) {
                    if (vf_176() != 0) {
                        int distance = FUN_005F6360(target) - vf_90(0);
                        int power = vf_176() << 10;
                        if (distance > 0) {
                            int divisor;
                            if ((unsigned int)vf_227() > 1) {
                                divisor = vf_227();
                            } else {
                                divisor = 1;
                            }
                            int turns;
                            if (divisor > 0) {
                                int quotient = distance / divisor;
                                if (quotient > 1) {
                                    turns = quotient;
                                } else {
                                    turns = 1;
                                }
                            } else {
                                turns = 1;
                            }
                            int score = power / turns;
                            if (score > 1) {
                                power = score;
                            } else {
                                power = 1;
                            }
                        }
                        return power;
                    }
                }
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4D98C0
// Slot 238. When the local player owns a type that is not a spawned one, play the lost-unit voice if the
// radar event for its cell is accepted.
void FootClass::vf_238(void* a1)
{
    if (Owner->IsControlledByCurrentPlayer() && !vf_33()->Spawned) {
        if (FUN_0065FA70(7, vf_110())) {
            VoxClass::Play("EVA_UnitLost", -1, -1);
        }
    }
}

// FUNCTION: GAMEMD 0x4D9E70
// Slot 38. Ground and infantry objects (kinds 1 and 2) linked to a building whose type sets the flag at
// +0x16A9 answer true while that building is closer than 0x80 leptons; everything else defers to the base.
bool FootClass::vf_38()
{
    int kind = vf_11();
    if (kind > 0 && kind <= 2 && HasAnyLink()) {
        if (FUN_0065AD40(0)->vf_11() == 6 && ((BuildingClass*)FUN_0065AD40(0))->Type->bools_16A4[5]) {
            if (Distance3DXZY(vf_18(), FUN_0065AD40(0)->vf_18()) < 0x80) {
                return true;
            }
        }
    }
    return TechnoClass::vf_38();
}

// FUNCTION: GAMEMD 0x4DBA50
// Slot 177 (the retail table entry). The cell under the source's slot-19 coordinate for this object,
// reduced to its centre point at height 0, goes to slot 179.
void FootClass::FUN_004DBA50(TechnoClass* from)
{
    CellStruct cell = CoordToCell(from->vf_19(this));
    CoordStruct centre;
    centre.X = (cell.X << 8) + 0x80;
    centre.Y = (cell.Y << 8) + 0x80;
    centre.Z = 0;
    vf_179(&centre);
}

// FUNCTION: GAMEMD 0x4DBED0
// Slot 245. The sensor disc of the old spot comes off before the base slot runs and the disc of the new
// spot goes on after it (also when the base refuses). When it accepts, a human-owned team member leaves
// its team, and an object that slot 21 does not hold gets its last cell refreshed.
bool FootClass::vf_245(HouseClass* house, bool a2)
{
    if (vf_33()->SensorsSight != 0) {
        vf_315(vf_110());
    }
    if (TechnoClass::vf_245(house, true)) {
        if (Owner->IsHumanPlayer && Team != 0) {
            Team->LiberateMember(this, -1, 0);
        }
        if (!IsInAir()) {
            LastMapCoords = vf_110();
        }
        if (vf_33()->SensorsSight != 0) {
            vf_314(vf_110());
        }
        return true;
    }
    if (vf_33()->SensorsSight != 0) {
        vf_314(vf_110());
    }
    return false;
}

// FUNCTION: GAMEMD 0x4DDDE0
// Slot 28. The base answer for the cell, kept as is unless the cell centre is shrouded and the answer is
// nonzero: then a type with the flag at +0xC8D and a cell the map accepts answers 1 (0x33 stays 0x33), and
// any other answers 2.
int FootClass::vf_28(CellStruct* cell, char a2, char a3)
{
    int action = TechnoClass::vf_28(cell, a2, a3);
    CoordStruct coord;
    coord.X = cell->X * 256 + 128;
    coord.Y = cell->Y * 256 + 128;
    coord.Z = 0;
    coord.Z = DAT_0087F7E8.FUN_00578080(&coord);
    if (DAT_0087F7E8.FUN_00565730(&coord)->Flags & 0x100) {
        coord.Z += DAT_008B3DF4;
    }
    if (DAT_0087F7E8.IsLocationShrouded(coord) && action != 0) {
        if (vf_33()->bools_C8C[1] && DAT_0087F7E8.FUN_00578460(cell, 1)) {
            if (action != 0x33) {
                return 1;
            }
        } else {
            return 2;
        }
    }
    return action;
}

// FUNCTION: GAMEMD 0x4DE670
// Takes the passenger off the cargo list. When one was given and the type has a leave sound, that sound
// plays at the current location. A gunner type whose cargo is now empty runs slot 310 on the passenger.
void FootClass::FUN_004DE670(FootClass* passenger)
{
    Passengers.RemovePassenger(passenger);
    if (passenger != 0 && vf_33()->LeaveTransportSound != -1) {
        CoordStruct where = Location;
        VoxClass::PlayAtPos(vf_33()->LeaveTransportSound, &where, 0);
    }
    if (vf_33()->Gunner && Passengers.NumPassengers == 0) {
        vf_310(passenger);
    }
}

// FUNCTION: GAMEMD 0x4DE7B0
// Slot 314. Adds the sensor disc of the type's sensor radius, centred on `center` (this object's own cell
// for the sentinel), to the cells in range; the units on those cells are refreshed and a foreign building
// there is flagged for redraw.
void FootClass::vf_314(CellStruct center)
{
    int radius = vf_33()->SensorsSight;
    int radiusSquared = radius * radius;
    int house = Owner->ArrayIndex;
    if (center.X == DAT_008B3D88.X && center.Y == DAT_008B3D88.Y) {
        center = CoordToCell(vf_18());
    }
    CellStruct at;
    for (int dy = -radius; dy < radius; dy++) {
        for (int dx = -radius; dx < radius; dx++) {
            CellStruct delta;
            delta.X = dx;
            delta.Y = dy;
            at = center + delta;
            if (dx * dx + dy * dy < radiusSquared) {
                CellClass* cell = DAT_0087F7E8.FUN_005657A0(&at);
                cell->IncreaseSensorsOfHouse(house);
                for (ObjectClass* object = (ObjectClass*)cell->FirstObject; object != 0;
                     object = (ObjectClass*)object->NextObject) {
                    int kind = object->vf_11();
                    if (kind == 1 || kind == 0xF || kind == 2) {
                        ((TechnoClass*)object)->vf_264();
                    }
                }
                BuildingClass* building = cell->FUN_0047C520();
                if (building != 0 && building->Owner != DAT_00A83D4C && building->vf_26(0, 0) != 0) {
                    building->NeedsRedraw = 1;
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x4DE940
// Slot 315. Takes the sensor disc of the type's sensor radius, centred on `center` (this object's own cell
// for the sentinel), off the cells that carry this house's coverage; the units on those cells are refreshed
// and a foreign building there is flagged for redraw.
void FootClass::vf_315(CellStruct center)
{
    int radius = vf_33()->SensorsSight;
    int radiusSquared = radius * radius;
    int house = Owner->ArrayIndex;
    if (center.X == DAT_008B3D88.X && center.Y == DAT_008B3D88.Y) {
        center = CoordToCell(vf_18());
    }
    CellStruct at;
    for (int dy = -radius; dy < radius; dy++) {
        for (int dx = -radius; dx < radius; dx++) {
            CellStruct delta;
            delta.X = dx;
            delta.Y = dy;
            at = center + delta;
            if (dx * dx + dy * dy < radiusSquared) {
                CellClass* cell = DAT_0087F7E8.FUN_005657A0(&at);
                if (cell->FUN_004870D0(house)) {
                    cell->DecreaseSensorsOfHouse(house);
                    for (ObjectClass* object = (ObjectClass*)cell->FirstObject; object != 0;
                         object = (ObjectClass*)object->NextObject) {
                        int kind = object->vf_11();
                        if (kind == 1 || kind == 0xF || kind == 2) {
                            ((TechnoClass*)object)->vf_264();
                        }
                    }
                    BuildingClass* building = cell->FUN_0047C520();
                    if (building != 0 && building->Owner != DAT_00A83D4C && building->vf_26(0, 0) != 0) {
                        building->NeedsRedraw = 1;
                    }
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x4DF320
// Slot 306. Clears the attack-move flag, then follows the mega destination (mission 2) or the mega
// target (mission 1) when there is one; with neither it runs slot 298 and answers false.
bool FootClass::vf_306()
{
    bool handled = true;
    HaveAttackMoveTarget = 0;
    if (MegaDestination != 0) {
        vf_122(2, true);
        SetDestination((AbstractClass*)MegaDestination, true);
    } else if (MegaTarget != 0) {
        vf_122(1, true);
        vf_242((AbstractClass*)MegaTarget);
    } else {
        vf_298();
        handled = false;
    }
    return handled;
}

// FUNCTION: GAMEMD 0x4DF3A0
// Slot 307. Re-aims the attack-move: with a mega destination the current target is dropped when slot 237
// refuses it, and the move is accepted only if slot 231 takes the current spot; without one the mega target
// is tried first and restored as the target when slot 231 refuses. A taken move sets mission 1 and the flag.
void FootClass::vf_307()
{
    if (MegaDestination != 0) {
        if (HaveAttackMoveTarget) {
            if (vf_237(Target)) {
                return;
            }
            Target = 0;
        }
        CoordStruct here = Location;
        if (vf_231(here, 1)) {
            vf_122(1, true);
            HaveAttackMoveTarget = 1;
        }
    } else {
        if (MegaTarget != 0 && vf_237((AbstractClass*)MegaTarget)) {
            return;
        }
        if (HaveAttackMoveTarget && vf_237(Target)) {
            return;
        }
        Target = 0;
        CoordStruct here = Location;
        if (vf_231(here, 1)) {
            vf_122(1, true);
            HaveAttackMoveTarget = 1;
        } else {
            Target = (AbstractClass*)MegaTarget;
        }
    }
}

// FUNCTION: GAMEMD 0x4DFA70
// Slot 207. Heads for the nearest of the owner's grinders (mission 9) and answers true when there is one.
bool FootClass::vf_207()
{
    BuildingClass* nearest = 0;
    int nearestDistance = 0x7FFFFFFF;
    for (int i = Owner->Grinders.Count - 1; i >= 0; i--) {
        BuildingClass* grinder = Owner->Grinders.Items[i];
        int distance = Distance3D(vf_18(), grinder->vf_18());
        if (distance < nearestDistance) {
            nearestDistance = distance;
            nearest = grinder;
        }
    }
    if (nearest == 0) {
        return false;
    }
    SetDestination(nearest, true);
    vf_122(9, false);
    return true;
}

// FUNCTION: GAMEMD 0x4DFB70
// Slot 208. Looks for the nearest of the owner's absorbers that answers the radio command 0xF positively;
// finding one sets the enter-absorber flag and, unless already linked or queued there, heads for it
// (mission 7); finding none clears the flag.
bool FootClass::vf_208()
{
    BuildingClass* nearest = 0;
    int nearestDistance = 0x7FFFFFFF;
    for (int i = Owner->Absorbers.Count - 1; i >= 0; i--) {
        BuildingClass* absorber = Owner->Absorbers.Items[i];
        if (vf_158(0xF, absorber) == 1) {
            int distance = Distance3D(vf_18(), absorber->vf_18());
            if (distance < nearestDistance) {
                nearestDistance = distance;
                nearest = absorber;
            }
        }
    }
    if (nearest == 0) {
        ShouldEnterAbsorber = 0;
        return false;
    }
    ShouldEnterAbsorber = 1;
    if (FUN_0065AD30(0) != nearest && QueueUpToEnter != nearest) {
        vf_122(7, false);
        SetDestination(nearest, true);
    }
    return true;
}

// FUNCTION: GAMEMD 0x4DFCB0
// Slot 210. Heads for the nearest of the owner's occupiable buildings that this object, as an infantryman,
// can occupy (mission 8) and answers true when there is one; with none the occupy flag is cleared.
bool FootClass::vf_210()
{
    BuildingClass* nearest = 0;
    int nearestDistance = 0x7FFFFFFF;
    for (int i = Owner->Occupiables.Count - 1; i >= 0; i--) {
        BuildingClass* building = Owner->Occupiables.Items[i];
        int distance = Distance3DXZY(vf_18(), building->vf_18());
        if (distance < nearestDistance) {
            if (building->CanBeOccupiedBy(CastToInfantry(this))) {
                nearestDistance = distance;
                nearest = building;
            }
        }
    }
    if (nearest == 0) {
        ShouldEnterOccupiable = 0;
        return false;
    }
    ShouldEnterOccupiable = 1;
    if (Destination != nearest || CurrentMission != 8) {
        SetDestination(nearest, true);
        vf_122(8, true);
    }
    return true;
}

// FUNCTION: GAMEMD 0x4DFE00
// Slot 211. The same search over every building on the map for one this infantryman can garrison.
bool FootClass::vf_211()
{
    BuildingClass* nearest = 0;
    int nearestDistance = 0x7FFFFFFF;
    for (int i = DAT_00A8EB40.Count - 1; i >= 0; i--) {
        BuildingClass* building = DAT_00A8EB40.Items[i];
        if (building->CanBeOccupiedBy(CastToInfantry(this))) {
            int distance = Distance3D(vf_18(), building->vf_18());
            if (distance < nearestDistance) {
                nearestDistance = distance;
                nearest = building;
            }
        }
    }
    if (nearest == 0) {
        ShouldGarrisonStructure = 0;
        return false;
    }
    ShouldGarrisonStructure = 1;
    if (Destination != nearest || CurrentMission != 8) {
        SetDestination(nearest, true);
        vf_122(8, true);
    }
    return true;
}

// FUNCTION: GAMEMD 0x4DFF40
// Slot 209. When 0x70FB50 allows it, heads for the nearest of the owner's bunkers that has neither a radio
// link nor a linked item (radio command 2, then mission 7) and answers true when there is one.
bool FootClass::vf_209()
{
    if (!FUN_0070FB50()) {
        return false;
    }
    BuildingClass* nearest = 0;
    int nearestDistance = 0x7FFFFFFF;
    for (int i = Owner->Bunkers.Count - 1; i >= 0; i--) {
        BuildingClass* bunker = Owner->Bunkers.Items[i];
        int distance = Distance3D(vf_18(), bunker->vf_18());
        if (distance < nearestDistance) {
            if (bunker->FUN_0065AD30(0) == 0 && bunker->BunkerLinkedItem == 0) {
                nearestDistance = distance;
                nearest = bunker;
            }
        }
    }
    if (nearest == 0) {
        return false;
    }
    SetDestination(nearest, true);
    vf_158(2, nearest);
    vf_122(7, true);
    return true;
}
