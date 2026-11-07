// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of the FootClass methods between 0x4D31E0 and 0x4E0100 in retail gamemd.exe v1.001
//   (vtable 0x7E8C94 and direct callers), matched against the VC6 toolchain.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4D3780  FootClass::vf_73 (__thiscall)
//   FUNCTION: GAMEMD 0x4D3810  FootClass::vf_179 (__thiscall)
//   FUNCTION: GAMEMD 0x4D4B20  FootClass::vf_133 (__thiscall)
//   FUNCTION: GAMEMD 0x4D4CB0  FootClass::vf_134 (__thiscall)
//   FUNCTION: GAMEMD 0x4D4FC0  FootClass::FUN_004D4FC0 (__thiscall)
//   FUNCTION: GAMEMD 0x4D5070  FootClass::vf_135 (__thiscall)
//   FUNCTION: GAMEMD 0x4D5350  FootClass::vf_138 (__thiscall)
//   FUNCTION: GAMEMD 0x4D7170  FootClass::vf_54 (__thiscall)
//   FUNCTION: GAMEMD 0x4D7330  FootClass::vf_91 (__thiscall)
//   FUNCTION: GAMEMD 0x4D94B0  FootClass::SetDestination (__thiscall)
//   FUNCTION: GAMEMD 0x4D9720  FootClass::vf_55 (__thiscall)
//   FUNCTION: GAMEMD 0x4D97A0  FootClass::FUN_004D97A0 (__thiscall)
//   FUNCTION: GAMEMD 0x4D98C0  FootClass::vf_238 (__thiscall)
//   FUNCTION: GAMEMD 0x4D9E70  FootClass::vf_38 (__thiscall)
//   FUNCTION: GAMEMD 0x4D9F70  FootClass::vf_104 (__thiscall)
//   FUNCTION: GAMEMD 0x4DA030  FootClass::FUN_004DA030 (__thiscall)
//   FUNCTION: GAMEMD 0x4DA2C0  FootClass::vf_140 (__thiscall)
//   FUNCTION: GAMEMD 0x4DAFC0  FootClass::vf_187 (__thiscall)
//   FUNCTION: GAMEMD 0x4DB810  FootClass::vf_109 (__thiscall)
//   FUNCTION: GAMEMD 0x4DBA50  FootClass::FUN_004DBA50 (__thiscall)
//   FUNCTION: GAMEMD 0x4DBAD0  FootClass::vf_13 (__thiscall)
//   FUNCTION: GAMEMD 0x4DBED0  FootClass::vf_245 (__thiscall)
//   FUNCTION: GAMEMD 0x4DCE80  FootClass::FUN_004DCE80 (__thiscall)
//   FUNCTION: GAMEMD 0x4DD0A0  FootClass::vf_206 (__thiscall)
//   FUNCTION: GAMEMD 0x4DD9F0  FootClass::FUN_004DD9F0 (__thiscall)
//   FUNCTION: GAMEMD 0x4DDC60  FootClass::vf_340 (__thiscall)
//   FUNCTION: GAMEMD 0x4DDDE0  FootClass::vf_28 (__thiscall)
//   FUNCTION: GAMEMD 0x4DDF90  FootClass::vf_150 (__thiscall)
//   FUNCTION: GAMEMD 0x4DE670  FootClass::FUN_004DE670 (__thiscall)
//   FUNCTION: GAMEMD 0x4DE7B0  FootClass::vf_314 (__thiscall)
//   FUNCTION: GAMEMD 0x4DE940  FootClass::vf_315 (__thiscall)
//   FUNCTION: GAMEMD 0x4DEAE0  FootClass::vf_85 (__thiscall)
//   FUNCTION: GAMEMD 0x4DEBB0  FootClass::vf_247 (__thiscall)
//   FUNCTION: GAMEMD 0x4DED70  FootClass::vf_27 (__thiscall)
//   FUNCTION: GAMEMD 0x4DEE80  FootClass::vf_331 (__thiscall)
//   FUNCTION: GAMEMD 0x4DF320  FootClass::vf_306 (__thiscall)
//   FUNCTION: GAMEMD 0x4DF3A0  FootClass::vf_307 (__thiscall)
//   FUNCTION: GAMEMD 0x4DF4B0  FootClass::vf_308 (__thiscall)
//   FUNCTION: GAMEMD 0x4DF7F0  FootClass::vf_322 (__thiscall)
//   FUNCTION: GAMEMD 0x4DFA70  FootClass::vf_207 (__thiscall)
//   FUNCTION: GAMEMD 0x4DFB70  FootClass::vf_208 (__thiscall)
//   FUNCTION: GAMEMD 0x4DFCB0  FootClass::vf_210 (__thiscall)
//   FUNCTION: GAMEMD 0x4DFE00  FootClass::vf_211 (__thiscall)
//   FUNCTION: GAMEMD 0x4DFF40  FootClass::vf_209 (__thiscall)

#include "_layout/voc_class.h"
#include "_layout/rules_class.h"
#include "_layout/foot_class.h"
#include "_layout/house_class.h"
#include "_layout/team_class.h"
#include "_layout/team_type_class.h"
#include "_layout/techno_type_class.h"
#include "vox_class_play_methods.h"
#include "loco_com.h"
#include "_layout/aircraft_tracker_class.h"
#include "_layout/coord_struct.h"
#include "event_class_ctors.h"
#include "_layout/building_class.h"
#include "_layout/building_array.h"
#include "_layout/infantry_class.h"
#include "mission_class_methods.h"
#include "scenario_class_methods.h"
#include "_layout/house_class.h"
#include "_layout/building_type_class_layout.h"
#include "_layout/cell_class.h"
#include "_layout/map_0087f7e8.h"
#include "cell_step_tables.h"
#include "foot_class_nav_list_methods.h"
#include "_layout/player_ptr_00a83d4c.h"

#include "_layout/session_class.h"
#include "_layout/parasite_class.h"
#include "_layout/aircraft_class.h"
#include "_layout/tag_class.h"
#include "weapon_type_class.h"
#include "_layout/warhead_type_class.h"
#include "slave_manager_class_methods.h"
#include "map_class_area_methods.h"

// GLOBAL: GAMEMD 0x8B3D88 -- the "no cell" sentinel.
extern CellStruct DAT_008B3D88;

// TEMPLATE: GAMEMD 0x45AEA0
// _com_ptr_t<IPersist>::_QueryInterface from a FootClass::LocomotorPtr (comip.h; SetDestination, slot 288).
// TEMPLATE: GAMEMD 0x45AF20
// _com_ptr_t<IPiggyback>::_QueryInterface from a FootClass::LocomotorPtr (comip.h; slot 322).

// GLOBAL: GAMEMD 0x7E9A40 -- CLSID of a locomotion class.
extern const CLSID DAT_007E9A40;

// GLOBAL: GAMEMD 0x7E9A90 -- CLSID of TeleportLocomotionClass.
extern const CLSID DAT_007E9A90;

// GLOBAL: GAMEMD 0x8B3DF4
extern int DAT_008B3DF4;

// GLOBAL: GAMEMD 0x8B3DA8 -- the "no coordinate" sentinel.
extern CoordStruct DAT_008B3DA8;

// GLOBAL: GAMEMD 0x887888
extern AircraftTrackerClass AircraftTracker;

// GLOBAL: GAMEMD 0xA8E390 -- the aircraft registry.
extern DynamicVectorClass<AircraftClass*> DAT_00A8E390;

// GLOBAL: GAMEMD 0x7E3570 -- one over the largest random draw.
extern const double DAT_007E3570;

// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
extern ScenarioClass* DAT_00A8B230;

// GLOBAL: GAMEMD 0xA8E7AC -- nonzero while the scenario is being set up.
extern int DAT_00A8E7AC;

// FUNCTION: GAMEMD 0x65FA70 (decl; reloc) -- RadarEventClass::Create: event type in ECX, the cell by value.
bool __fastcall FUN_0065FA70(int type, CellStruct cell);

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) -- operator delete.
extern "C" void __cdecl FUN_007C8B3D(void* block);

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

// Whether two coordinates differ.
inline bool CoordsDiffer(const CoordStruct& a, CoordStruct b)
{
    return a.X != b.X || a.Y != b.Y || a.Z != b.Z;
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

// FUNCTION: GAMEMD 0x4D3810
// Slot 179. True outright for a type with no movement zone. False for the "no cell" sentinel; otherwise
// whether the cell holding this object reaches the cell holding the coordinate, the bridge flag of the
// target cell and the slot 200 answer qualifying the check.
bool FootClass::vf_179(CoordStruct* where)
{
    int zone = vf_33()->MovementZone;
    if (zone == -1) {
        return true;
    }
    CellStruct to = CoordToCell(*where);
    if (to == DAT_008B3D88) {
        return false;
    }
    CellStruct from = CoordToCell(vf_19(0));
    return DAT_0087F7E8.FUN_0056D100(&from, &to, zone, vf_47(0), (DAT_0087F7E8.FUN_005657A0(&to)->Flags >> 8) & 1, vf_200());
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
        if (DAT_0087F7E8.FUN_00565730(vf_18())->GetBuilding() != 0) {
            vf_93(DAT_008B3DA8, true, false);
        }
    }
idle:
    if (Target == 0) {
        if (!Owner->IsControlledByHuman()) {
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
        if (DAT_0087F7E8.FUN_00565730(vf_18())->GetBuilding() != 0) {
            vf_93(DAT_008B3DA8, true, false);
        }
    }
wait:
    int base = (int)(FUN_005B3A00()->Rate * 900.0);
    return base + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
}

static inline CellStruct FootStepCell(const CellStruct& here, int facing)
{
    CellStruct cell;
    const CellStruct& step = DAT_0089F688[facing];
    cell.X = step.X + here.X;
    cell.Y = here.Y + step.Y;
    return cell;
}

// FUNCTION: GAMEMD 0x4D4FC0
// Of the eight cells around this object's cell, the first with a building of the same owner whose
// type has the flag at +0x1575; null when none.
BuildingClass* FootClass::FUN_004D4FC0()
{
    for (int i = 0; i < 8; i++) {
        CellStruct cell = FootStepCell(vf_110(), i & 7);
        BuildingClass* building = DAT_0087F7E8.FUN_005657A0(&cell)->GetBuilding();
        if (building && building->Type->Overpowerable) {
            if (building->vf_15() == vf_15()) {
                return building;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4D5070
// Slot 135 (mission handler). A pending absorber, occupiable or garrison entry runs its slot (208, 210,
// 211) and waits the mission rate. Otherwise without a target an object whose primary weapon has an
// electric-assault warhead looks for a friendly building around it and attacks it, else it stands down;
// with a target a hover type that has no hold on slot 114 heads for the nearby cell. Then an unmanned
// C4 or ability-0xE infantryman that is not already in mission 0x11 and holds a building target goes to
// mission 0x11. The wait is the rearm timer while it runs; a distributed-fire type with targets waits
// none, any other the mission rate plus a random 0..2 frames.
int FootClass::vf_135()
{
    if (ShouldEnterAbsorber) {
        vf_208();
        return (int)(FUN_005B3A00()->Rate * 900.0);
    }
    if (ShouldEnterOccupiable) {
        vf_210();
        return (int)(FUN_005B3A00()->Rate * 900.0);
    }
    if (ShouldGarrisonStructure) {
        vf_211();
        return (int)(FUN_005B3A00()->Rate * 900.0);
    }
    if (Target == 0) {
        if (vf_254(1)->WeaponType != 0 && vf_254(1)->WeaponType->Warhead->ElectricAssault) {
            BuildingClass* building = 0;
            for (int i = 0; i < 8; i++) {
                CellStruct cell = FootStepCell(vf_110(), i & 7);
                building = DAT_0087F7E8.FUN_005657A0(&cell)->GetBuilding();
                if (building && building->Type->Overpowerable) {
                    if (building->vf_15() == vf_15()) {
                        break;
                    }
                }
                building = 0;
            }
            if (building != 0) {
                vf_242(building);
                unknown_bool_68E = 1;
                vf_122(1, false);
            } else {
                vf_286();
            }
        } else {
            vf_286();
        }
    } else if (vf_33()->HoverAttack) {
        if (vf_114() == 0) {
            SetDestination(DAT_0087F7E8.FUN_005657A0(NearbyLocation(this)), true);
        }
    }
    int base = (int)(FUN_005B3A00()->Rate * 900.0);
    // Retail tests this (0x4D523A, TEST ESI,ESI) and then compares the kind with a plain CMP EAX,0xF / JNE
    // (0x4D5247), a branch the mask-form helper cannot produce: KindCast_00459F40 was tried first and scored 60.4%.
    // THISNULL: GAMEMD 0x459F40
    if (this != 0 && vf_11() == 0xF && !Owner->IsControlledByHuman()
        && (((InfantryClass*)this)->Type->C4 || FUN_0070D0D0(0xE)) && vf_97() != 0x11
        && Target != 0 && Target->vf_11() == 6) {
        vf_122(0x11, false);
    }
    int result = 0;
    if (RearmTimer.GetTimeLeft() != 0) {
        result = RearmTimer.GetTimeLeft();
    } else if (!(vf_33()->DistributedFire && CurrentTargets.Count > 0)) {
        result = DAT_00A8B230->unknown_0218.RandomRanged(0, 2) + base;
    }
    return result;
}

// FUNCTION: GAMEMD 0x4D5350
// Slot 138 (mission handler). A type that is not a hunter with a place to stand: an infantryman who can
// enter a building goes after the target (an engineer-only one takes it outright, a C4 or ability-0xE one
// only when it is a building, a vehicle thief takes anything), others stand down; a non-infantry object
// does the same. A hunter type or a spot refused by slot 231 sends a computer-run object in a campaign to
// the player's start cell, guarding with its slaves first. Then wait the mission rate plus a random 0..2 frames.
int FootClass::vf_138()
{
    bool spot = false;
    if (!vf_33()->StupidHunt) {
        CoordStruct here = Location;
        if (vf_231(here, 0)) {
            InfantryClass* infantry = vf_11() == 0xF ? (InfantryClass*)this : 0;
            if (infantry != 0) {
                if (infantry->Type->Engineer && !infantry->Type->C4 && !infantry->FUN_0070D0D0(0xE)) {
                    SetDestination(Target, true);
                    goto enter;   // retail 0x4D53F4: JMP 0x4D548F, the shared enter tail
                }
                if ((infantry->Type->C4 || infantry->FUN_0070D0D0(0xE)) && Target != 0 && Target->vf_11() == 6) {
                    SetDestination(Target, true);
                    vf_122(0x11, false);
                    if (vf_128()) {
                        vf_123();
                    }
                } else if (infantry->Type->VehicleThief) {
                    SetDestination(Target, true);
                  enter:
                    vf_122(8, false);
                    if (vf_128()) {
                        vf_123();
                    }
                } else {
                    SetDestination(0, true);
                    vf_335(0);
                }
            } else {
                vf_335(0);
            }
            spot = true;
        }
    }
    if (!spot) {
        if (!Owner->IsControlledByHuman() && Session_00A8B238.GameMode == 0) {
            CellStruct spot = DAT_008B3D88;
            spot = DAT_00A83D4C->FUN_0050DEF0();
            if (spot.X != DAT_008B3D88.X || spot.Y != DAT_008B3D88.Y) {
                if (SlaveManager != 0) {
                    ((SlaveManagerView_006B0A20*)SlaveManager)->AllGuard();
                }
                SetDestination(DAT_0087F7E8.FUN_005657A0(&spot), true);
                vf_122(2, true);
            }
        } else {
            vf_286();
        }
    }
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
        Locomotor->Unlimbo();
        if (Owner->IonSensitivesShouldBeOffline() && Locomotor->IsIonSensitive()) {
            Locomotor->PowerOff();
        } else {
            Locomotor->PowerOn();
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

// FUNCTION: GAMEMD 0x4D7330
// Slot 91, ReceiveDamage. A hit by a warhead with the sonic flag lets go of the parasite on this object and
// has the attacker (slot 242, argument 0) react. A hit harder than the host's suppression threshold, or any
// healing, restarts the parasite's timer. The TechnoClass body decides the result: 5 is returned as is; a
// team learns of a nonzero result; otherwise (not 0 or 4) a team whose type has the whiner flag and whose
// owner is not human controlled switches to the attacker, and an attacker whose mission is a no-threat,
// non-zombie one sends this object back to idle mode.
int FootClass::vf_91(int* damage, int distance, void* warhead, void* source, bool a5, bool a6, void* house)
{
    WarheadTypeClass* hit = static_cast<WarheadTypeClass*>(warhead);
    TechnoClass* attacker = static_cast<TechnoClass*>(source);
    if (hit != 0 && hit->Sonic && ParasiteEatingMe != 0) {
        ParasiteEatingMe->ParasiteImUsing->FUN_0062A4A0();
        if (attacker != 0) {
            attacker->vf_242(0);
        }
    }
    if (ParasiteEatingMe != 0 && attacker != ParasiteEatingMe) {
        if (*damage > ParasiteEatingMe->vf_33()->SuppressionThreshold) {
            ParasiteEatingMe->ParasiteImUsing->TimerA = CDTimerClass(*damage * 2 - ParasiteEatingMe->vf_33()->SuppressionThreshold);
        }
    }
    if (ParasiteEatingMe != 0 && *damage < 0) {
        ParasiteEatingMe->ParasiteImUsing->TimerA = CDTimerClass(0x32);
        ParasiteEatingMe->ParasiteImUsing->FUN_0062A4A0();
    }
    int result = FUN_00701900(damage, distance, warhead, source, a5, a6, house);
    if (result == 5) {
        return result;
    }
    if (result != 0 && Team != 0) {
        Team->FUN_006EB380(this, result, attacker);
        return result;
    }
    if (result != 4 && result != 0) {
        if (Team != 0 && Team->Type->Whiner && !Owner->IsControlledByHuman()) {
            if (attacker == 0) {
                return result;
            }
            FUN_00708080(attacker);
        }
        if (attacker != 0 && FUN_005B3A00()->NoThreat && !FUN_005B3A00()->Zombie) {
            EnterIdleMode(false, true);
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x4D8FB0
// Slot 101, the radio message handler of the foot layer; the sender is a1 and a3 points at the in/out object.
// 0x11 is taken once a mission of 7 is current or queued; 0x12 (move here) answers 0x14 when the sender's cell is
// already ours, else heads for it; 0x13 reports the destination and refuses (10) while the locomotor is moving;
// 0x17 drops a destination shared with the linked object and falls back to a guard-style mission; 0x1c refuses
// while a destination is held; 0x23 asks whether the building under this cell is the sender.
int FootClass::vf_101(int a1, int event, int a3)
{
    AbstractClass** param = reinterpret_cast<AbstractClass**>(a3);
    switch (event) {
    case 0x23:
        if (DAT_0087F7E8.FUN_00565730(vf_18())->GetBuilding() != reinterpret_cast<BuildingClass*>(a1)) {
            return 10;
        }
        return 1;
    case 0x1c:
        if (Destination) {
            return 10;
        }
        break;
    case 0x17:
        if (HasAnyLink() && Destination == FUN_0065AD30(0)) {
            SetDestination(0, true);
        }
        if (vf_97() == 0) {
            vf_122(5, false);
            if (vf_128()) {
                vf_123();
            }
        }
        if (vf_97() == 7) {
            vf_122(5, false);
        }
        if (!unknown_bool_6AF && !Destination) {
            vf_93(DAT_008B3DA8, true, true);
        }
        break;
    case 0x13:
        *param = Destination;
        if (Destination) {
            if (Locomotor->IsMoving()) {
                return 10;
            }
        }
        return 1;
    case 0x12:
        if (*param) {
            CellStruct goal = Coord2Cell((*param)->vf_18());
            if (vf_110() == goal) {
                return 0x14;
            }
        }
        if (vf_97() == 5 && QueuedMission == -1) {
            vf_122(2, false);
        }
        if (QueuedMission == 7 && vf_128()) {
            vf_123();
        }
        SetDestination(*param, true);
        UpdateTimer = CDTimerClass(0);
        return 1;
    case 0x11:
        if (vf_97() == 7 || QueuedMission == 7) {
            TechnoClass::vf_101(a1, event, a3);
            return 1;
        }
        break;
    }
    return TechnoClass::vf_101(a1, event, a3);
}

// FUNCTION: GAMEMD 0x4D94B0
// Slot 288. Drops the pending step and refuses a destination while a locomotor holds this object, it rides an
// open-topped transport or it is linked to a bunker. Otherwise it takes the destination (releasing a
// locomotor that carries it, and the particle system when there is one), and a drive-class locomotor whose
// path delay ran out restarts it. A destination sends the locomotor there; none stops it unless an
// aircraft with an attack mission still has a target. The blockage and path timers restart.
void FootClass::SetDestination(AbstractClass* target, bool a2)
{
    unknown_5A0 = 0;
    if (IsAttackedByLocomotor && target != 0) {
        return;
    }
    if (InOpenToppedTransport && target != 0) {
        return;
    }
    if (BunkerLinkedItem != 0 && target != 0) {
        return;
    }
    if (LocomotorTarget != 0 && target != 0) {
        FUN_0070FEE0(true);
    }
    Destination = target;
    if (target == 0 && IsAttackedByLocomotor && LocomotorSource != 0) {
        static_cast<TechnoClass*>(LocomotorSource)->LocomotorTarget = 0;
        LocomotorSource = 0;
        IsLetGoByLocomotor = 1;
    }
    if (Destination != 0) {
        if (ParticleSystems[0] != 0) {
            static_cast<ObjectClass*>(ParticleSystems[0])->vf_62();
            ParticleSystems[0] = 0;
        }
        IPersistPtr persist(Locomotor);
        CLSID id;
        persist->GetClassID(&id);
        if (IsEqualCLSID(id, DAT_007E9A40)) {
            if (PathDelayTimer.GetTimeLeft() == 0) {
                PathDelayTimer = CDTimerClass(1);
            }
        }
        if (unknown_bool_6AC) {
            unknown_bool_6AC = 0;
        } else {
            LocoCoord to = Destination->vf_19(this);
            Locomotor->MoveTo(to);
        }
    } else {
        if (!(vf_11() == 2 && (CurrentMission == 1 || QueuedMission == 1) && Target != 0)) {
            Locomotor->StopMoving();
            Destination = target;
        }
    }
    IsWaitingBlockagePath = 0;
    BlockagePathTimer = CDTimerClass(Rules->BlockagePathDelay);
    PathDelayTimer = CDTimerClass(0);
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
            if (Team != 0 && Team->Type->IsBaseDefense) {
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
        if (FUN_0065AD40(0)->vf_11() == 6 && ((BuildingClass*)FUN_0065AD40(0))->Type->UnitRepair) {
            if (Distance3DXZY(vf_18(), FUN_0065AD40(0)->vf_18()) < 0x80) {
                return true;
            }
        }
    }
    return TechnoClass::vf_38();
}

// FUNCTION: GAMEMD 0x4D9F70
// Slot 104. Given a non-null argument: announce the sale to the local player, pay out the refund, then run
// slots 232, 53 and 62.
void FootClass::vf_104(int a1)
{
    if (a1) {
        if (Owner->IsControlledByCurrentPlayer()) {
            VoxClass::Play("EVA_UnitSold", -1, -1);
            VocClass::PlayGlobal(RulesInstance->SellSound, 1.0f, 0x2000, 0);
        }
        Owner->GiveMoney(vf_175());
        vf_232();
        vf_53();
        vf_62();
    }
}

// FUNCTION: GAMEMD 0x4DA030
// With no destination and a queued waypoint, make the first waypoint the destination and take it off
// the queue; with the loop flag set it goes back on the end.
void FootClass::FUN_004DA030()
{
    if (Destination == 0 && NavQueue.Count != 0) {
        AbstractClass* next = NavQueue.Items[0];
        if (next) {
            SetDestination(next, 1);
            NavQueue.Delete(0);
            if (unknown_bool_6B1) {
                NavQueue.AddItem(next);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x4DA2C0
// Slot 140 (mission handler). Status 0 with no destination picks a cell: with a team whose type names a
// waypoint, the map-edge search from the team's waypoint; failing that, the same search with no waypoint.
// The pick becomes the destination and status 1; a standing destination moves status 0 to 1 and status 1
// with none back to 0. Then wait the mission rate plus a random 0..2 frames.
int FootClass::vf_140()
{
    switch (MissionStatus) {
    case 0:
        if (Destination != 0) {
            MissionStatus = 1;
            break;
        }
        {
            CellStruct pick;
            pick.X = 0;
            pick.Y = 0;
            CellStruct here1;
            CellStruct here2;
            CellStruct buffer1;
            CellStruct buffer2;
            CellStruct scratch1;
            CellStruct scratch2;
            if (Team != 0) {
                CellStruct* waypoint = Team->Type->GetWaypoint(&buffer1);
                if (waypoint->X != DAT_008B3D88.X || waypoint->Y != DAT_008B3D88.Y) {
                    here1 = CoordToCell(vf_18());
                    pick = *DAT_0087F7E8.FUN_004AA440(&scratch1, Owner->FUN_0050DAA0(),
                                                      Team->Type->GetWaypoint(&buffer2), &here1, vf_33()->SpeedType, 1, 0);
                }
            }
            if (pick.X == DAT_008B3D88.X && pick.Y == DAT_008B3D88.Y) {
                here2 = CoordToCell(vf_18());
                pick = *DAT_0087F7E8.FUN_004AA440(&scratch2, Owner->FUN_0050DAA0(), &DAT_008B3D88, &here2,
                                                  vf_33()->SpeedType, 1, 0);
            }
            SetDestination(DAT_0087F7E8.FUN_005657A0(&pick), true);
            MissionStatus = 1;
        }
        break;
    case 1:
        if (Destination == 0) {
            MissionStatus = 0;
        }
        break;
    }
    int base = (int)(FUN_005B3A00()->Rate * 900.0);
    return base + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
}

// FUNCTION: GAMEMD 0x4DAFC0
// Slot 187. The base slot's value plus the largest of the type's four Z fudge terms, each scaled by its
// measure of the cell around the object (bridge only when that cell flag is set), plus the locomotor's Z adjust.
int FootClass::vf_187()
{
    int adjust = 0;
    if (Locomotor != 0) {
        adjust = Locomotor->ZAdjust();
    }
    int column = vf_33()->ZFudgeColumn * FUN_00703E70();
    int tunnel = vf_33()->ZFudgeTunnel * FUN_00704000();
    int cliff = vf_33()->ZFudgeCliff * FUN_00704240();
    int bridge = 0;
    if (FUN_00703B10()) {
        bridge = vf_33()->ZFudgeBridge;
    }
    int most = column;
    if (!(most > tunnel)) {
        most = tunnel;
    }
    if (!(most > cliff)) {
        most = cliff;
    }
    if (!(most > bridge)) {
        most = bridge;
    }
    return TechnoClass::vf_187() + most + adjust;
}

// FUNCTION: GAMEMD 0x4DB810
// Slot 109. Moves the object to the coordinate through the base slot (footprint off the cell map first and on
// again after when it is on the map). An open-topped type whose position changed carries its passengers along.
void FootClass::vf_109(const CoordStruct& coord)
{
    bool moved;
    if (CoordsDiffer(coord, Location)) {
        moved = true;
    } else {
        moved = false;
    }
    if (IsOnMap) {
        vf_73(0);
        ObjectClass::vf_109(coord);
        vf_73(1);
    } else {
        ObjectClass::vf_109(coord);
    }
    if (moved && vf_33()->OpenTopped) {
        UpdatePassengerCoords();
    }
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

// FUNCTION: GAMEMD 0x4DBAD0
// Slot 13. Feeds the synchronised movement state to the checksum after the base slot: the threat
// multiplier, the cell distance from the map origin, the tunnel distance, the speed pair, the ids of the
// destination, the last destination, the team and the next team member, the two timers as the frames
// they still have to run, the path wait time, the planning-point distance and a run of movement flags.
void FootClass::vf_13(Obj_004A1D30* crc)
{
    TechnoClass::vf_13(crc);
    crc->FUN_004A1D90(unknown_530);
    double cellY = CurrentMapCoords.Y;
    double cellX = CurrentMapCoords.X;
    crc->FUN_004A1D30((int)FUN_004CAC40(cellY * cellY + cellX * cellX));
    double tunnelZ = CurrentTunnelCoords.Z;
    double tunnelY = CurrentTunnelCoords.Y;
    double tunnelX = CurrentTunnelCoords.X;
    crc->FUN_004A1D50((int)FUN_004CAC40(tunnelX * tunnelX + tunnelY * tunnelY + tunnelZ * tunnelZ));
    crc->FUN_004A1D90(SpeedPercentage);
    crc->FUN_004A1D90(SpeedMultiplier);
    if (Destination != 0) {
        crc->FUN_004A1D50(Destination->vf_rtti_4());
    }
    if (LastDestination != 0) {
        crc->FUN_004A1D50(((AbstractClass*)LastDestination)->vf_rtti_4());
    }
    if (Team != 0) {
        crc->FUN_004A1D50(Team->vf_rtti_4());
    }
    if (NextTeamMember != 0) {
        crc->FUN_004A1D50(NextTeamMember->vf_rtti_4());
    }
    crc->FUN_004A1D50(PathDelayTimer.GetTimeLeft());
    crc->FUN_004A1D50(PathWaitTimes);
    crc->FUN_004A1D50(unknown_timer_650.GetTimeLeft());
    double pointZ = unknown_point3d_678.Z;
    double pointY = unknown_point3d_678.Y;
    double pointX = unknown_point3d_678.X;
    crc->FUN_004A1D50((int)FUN_004CAC40(pointX * pointX + pointY * pointY + pointZ * pointZ));
    crc->FUN_004A1C10(TubeIndex);
    crc->FUN_004A1C10(TubeFaceIndex);
    crc->FUN_004A1CA0(IsScanLimited);
    crc->FUN_004A1CA0(IsInitiated);
    crc->FUN_004A1CA0(ShouldScanForTarget);
    crc->FUN_004A1CA0(unknown_bool_68B);
    crc->FUN_004A1CA0(IsDeploying);
    crc->FUN_004A1CA0(IsFiring);
    crc->FUN_004A1CA0(unknown_bool_6AF);
    crc->FUN_004A1CA0(unknown_bool_6B0);
    crc->FUN_004A1CA0(unknown_bool_6B1);
    crc->FUN_004A1CA0(unknown_bool_6B2);
    crc->FUN_004A1CA0(unknown_bool_6B3);
    crc->FUN_004A1C10(unknown_bool_6B4);
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

// FUNCTION: GAMEMD 0x4DCE80
// True when the cell is inside the usable map, not shrouded (outside a campaign an owned object only looks),
// reachable from the cell holding this object, and of land type 5 with this object allowed to enter it.
bool FootClass::FUN_004DCE80(CellStruct* cell)
{
    if (DAT_0087F7E8.FUN_00578460(cell, 1)) {
        if (Session_00A8B238.GameMode == 0 && IsOwnedByCurrentPlayer) {
            CoordStruct where;
            where.X = cell->X * 256 + 128;
            where.Y = cell->Y * 256 + 128;
            where.Z = 0;
            int ground = DAT_0087F7E8.FUN_00578080(&where);
            CoordStruct shroud;
            shroud.X = cell->X * 256 + 128;
            shroud.Y = cell->Y * 256 + 128;
            shroud.Z = ground;
            if (DAT_0087F7E8.IsLocationShrouded(shroud)) {
                return false;
            }
        }
        CellStruct here = CoordToCell(vf_19(0));
        if (DAT_0087F7E8.FUN_0056D100(&here, cell, vf_33()->MovementZone, vf_47(0), 0, 0)) {
            CellClass* target = DAT_0087F7E8.FUN_005657A0(cell);
            if (target->LandType == 5) {
                if (vf_107(target, -1, -1, 0, true) == 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

// PARTIAL: 98.3% (identical instruction multiset, 179 of 179). Remaining delta: the epilogue stores the best cell
// through EAX = out / EDX = best where retail has EDX = out / EAX = best (two moves swapped, one store operand).
// FUNCTION: GAMEMD 0x4DD0A0
// Slot 206. The cell holding this object when it is of land type 5; otherwise a search over square rings
// of growing radius (up to but not including `radius`) for the usable cell with the most tiberium, stopping
// at the first ring that has any.
void FootClass::vf_206(CellStruct* out, int radius, int a3)
{
    CellStruct best = DAT_008B3D88;
    CellStruct center = CoordToCell(vf_18());
    if (DAT_0087F7E8.FUN_005657A0(&center)->LandType == 5) {
        *out = center;
        return;
    }
    int bestValue = -1;
    for (int r = 1; r < radius; ++r) {
        for (int d = -r; d <= r; ++d) {
            CellStruct probe;
            CellStruct above;
            above.X = d;
            above.Y = -r;
            probe = center + above;
            if (FUN_004DCE80(&probe)) {
                int value = DAT_0087F7E8.FUN_005657A0(&probe)->GetContainedTiberiumValue();
                if (value > bestValue) {
                    bestValue = value;
                    best = probe;
                }
            }
            probe = center + CellStructInit(d, r);
            if (FUN_004DCE80(&probe)) {
                int value = DAT_0087F7E8.FUN_005657A0(&probe)->GetContainedTiberiumValue();
                if (value > bestValue) {
                    bestValue = value;
                    best = probe;
                }
            }
            probe = center + CellStructInit(-r, d);
            if (FUN_004DCE80(&probe)) {
                int value = DAT_0087F7E8.FUN_005657A0(&probe)->GetContainedTiberiumValue();
                if (value > bestValue) {
                    bestValue = value;
                    best = probe;
                }
            }
            probe = center + CellStructInit(r, d);
            if (FUN_004DCE80(&probe)) {
                int value = DAT_0087F7E8.FUN_005657A0(&probe)->GetContainedTiberiumValue();
                if (value > bestValue) {
                    bestValue = value;
                    best = probe;
                }
            }
        }
        if (bestValue != -1) {
            break;
        }
    }
    *out = best;
}

// FUNCTION: GAMEMD 0x4DD9F0
// Steps the cell by (dx, dy) when the step stays inside the usable map; true when the stepped cell is
// visible (outside a campaign an owned object only looks), reachable from the cell holding this object, and
// enterable ground of land type 0xB (weed) with overlay data of at least 0x30. The cell takes the step as soon
// as it is usable.
bool FootClass::FUN_004DD9F0(CellStruct* cell, short dx, short dy)
{
    CellStruct delta;
    delta.X = dx;
    delta.Y = dy;
    CellStruct stepped = *cell + delta;
    if (DAT_0087F7E8.FUN_00578460(&stepped, 1)) {
        *cell = stepped;
        if (Session_00A8B238.GameMode == 0 && IsOwnedByCurrentPlayer) {
            CoordStruct where;
            where.X = cell->X * 256 + 128;
            where.Y = cell->Y * 256 + 128;
            where.Z = 0;
            int ground = DAT_0087F7E8.FUN_00578080(&where);
            CoordStruct shroud;
            shroud.X = cell->X * 256 + 128;
            shroud.Y = cell->Y * 256 + 128;
            shroud.Z = ground;
            if (DAT_0087F7E8.IsLocationShrouded(shroud)) {
                return false;
            }
        }
        CellStruct here = CoordToCell(vf_19(0));
        if (DAT_0087F7E8.FUN_0056D100(&here, cell, vf_33()->MovementZone, vf_47(0), 0, 0)) {
            CellClass* target = DAT_0087F7E8.FUN_005657A0(cell);
            if (vf_107(target, -1, -1, 0, true) == 0 && target->LandType == 0xB && target->OverlayData >= 0x30) {
                return true;
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x4DDC60
// Slot 340. False for no target or a spot outside the usable map. With an object standing on the target's cell
// it is acceptable when it is this object, this object's first radio link, or both this and that object are of
// the spawned kind (or that one carries a spawn manager). On an empty cell the spot must be clear to move and
// no other living, on-map object may already be heading for the target.
bool FootClass::vf_340(AbstractClass* target)
{
    if (target == 0) {
        return false;
    }
    CellStruct cell = CoordToCell(target->vf_18());
    if (!DAT_0087F7E8.FUN_00578460(&cell, 1)) {
        return false;
    }
    ObjectClass* found;
    {
        Point2D offset;
        offset.X = 0;
        offset.Y = 0;
        found = DAT_0087F7E8.FUN_005657A0(&cell)->FindTechnoNearestTo(&offset, false, 0);
    }
    if (found) {
        if (this != found && FUN_0065AD40(0) != found) {
            if (!vf_33()->Spawned || (static_cast<TechnoClass*>(found)->SpawnManager == 0 && !found->vf_33()->Spawned)) {
                return false;
            }
        }
    } else {
        if (!DAT_0087F7E8.FUN_005657A0(&cell)->IsClearToMove(1, false, false, -1, 0, -1, true)) {
            return false;
        }
        for (int i = 0; i < DAT_00A8E390.Count; i++) {
            AircraftClass* other = DAT_00A8E390.Items[i];
            if (other->IsAlive && !other->InLimbo && other->Destination == target && other != this) {
                return false;
            }
        }
    }
    return true;
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

// FUNCTION: GAMEMD 0x4DDF90
// Slot 150 (mission handler). Status 0 with a target stands down; without one it takes the cell under the
// object as the archive target if there is none, looks around the archive target for something to attack
// (and attacks it when it is within a range and a half of the archive target); with a target by then it waits
// one frame; else the owner picks a spot for the object and the object heads there, or stands down when
// there is none, with the archive target cleared. Status 1 with no destination clears the archive target and
// goes to mission 0xB. Then wait the mission rate plus a random 0..2 frames.
int FootClass::vf_150()
{
    CoordStruct here;
    AbstractClass* found;
    switch (MissionStatus) {
    case 0:
        if (Target != 0) {
            vf_335(0);
            break;
        }
        if (ArchiveTarget == 0) {
            here = Location;
            SetArchiveTarget(DAT_0087F7E8.FUN_00565730(&here));
        }
        IsScanLimited = 0;
        // ADDRCALL: GAMEMD 0x4DE051 (the archive target's returned coordinate address is the slot-241 argument)
        found = vf_241(0, &ArchiveTarget->vf_18(), false);
        if (found != 0) {
            double distance = Distance3D(found->vf_18(), ArchiveTarget->vf_18());
            if (vf_199(1) * 1.5 > distance) {
                vf_242(found);
            }
        }
        if (Target != 0) {
            return 1;
        }
        MissionStatus = 1;
        {
            CellStruct spot = Owner->FUN_00500200(this);
            if (spot.X == DAT_008B3D88.X && spot.Y == DAT_008B3D88.Y) {
                SetDestination(0, true);
            } else {
                SetDestination(DAT_0087F7E8.FUN_005657A0(&spot), true);
            }
        }
        SetArchiveTarget(0);
        break;
    case 1:
        if (Destination == 0) {
            SetArchiveTarget(0);
            vf_122(0xB, false);
            vf_123();
        }
        break;
    }
    int base = (int)(FUN_005B3A00()->Rate * 900.0);
    return base + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
}

// FUNCTION: GAMEMD 0x4DE670
// Takes the passenger off the cargo list. When one was given and the type has a leave sound, that sound
// plays at the current location. A gunner type whose cargo is now empty runs slot 310 on the passenger.
void FootClass::FUN_004DE670(FootClass* passenger)
{
    Passengers.RemovePassenger(passenger);
    if (passenger != 0 && vf_33()->LeaveTransportSound != -1) {
        CoordStruct where = Location;
        VocClass::PlayAtPos(vf_33()->LeaveTransportSound, &where, 0);
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
                BuildingClass* building = cell->GetBuilding();
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
                    BuildingClass* building = cell->GetBuilding();
                    if (building != 0 && building->Owner != DAT_00A83D4C && building->vf_26(0, 0) != 0) {
                        building->NeedsRedraw = 1;
                    }
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x4DEAE0
// Slot 85. An organic type takes its full strength as C4 warhead damage. Any other type lets go of the parasite
// on it (restarting the parasite's timer), clears its paralysis timer and passes the arguments to the
// TechnoClass routine.
void FootClass::vf_85(int a1, int a2, bool a3)
{
    if (vf_33()->Organic) {
        int damage = vf_33()->Strength;
        vf_91(&damage, 0, Rules->C4Warhead, 0, false, false, 0);
        return;
    }
    if (ParasiteEatingMe != 0) {
        ParasiteEatingMe->ParasiteImUsing->TimerA = CDTimerClass(0x32);
        ParasiteEatingMe->ParasiteImUsing->FUN_0062A4A0();
    }
    ParalysisTimer = CDTimerClass(0);
    FUN_0070E2B0(a1, a2, a3);
}

// FUNCTION: GAMEMD 0x4DEBB0
// Slot 247. Refused (false) when slot 114 reports nothing to kill. A live object with a tag fires its
// tag events (0x26 and 0x29 for a killer, 0x29 again while still alive); then slot 56 runs, the object
// is set crashing, loses its health unless the locomotor is attacking it, and its passengers die. Outside
// the scenario set-up a non-infantry object gets a random spin, and the pointer is announced as expired.
bool FootClass::vf_247(TechnoClass* killer)
{
    if (vf_114() > 0) {
        if (Health > 0) {
            if (killer != 0 && AttachedTag != 0) {
                AttachedTag->FUN_006E53A0(0x26, this, DAT_008B3D88, false, 0);
            }
            if (AttachedTag != 0 && IsAlive) {
                AttachedTag->FUN_006E53A0(0x29, this, DAT_008B3D88, false, 0);
            }
            if (AttachedTag != 0 && IsAlive && killer != 0) {
                AttachedTag->FUN_006E53A0(0x29, this, DAT_008B3D88, false, (int)killer);
            }
            if (!IsAlive) {
                return true;
            }
            vf_56(killer);
            if (!IsAlive) {
                return true;
            }
            if (!IsAttackedByLocomotor) {
                Health = 0;
            }
        }
        IsCrashing = true;
        vf_157(3);
        vf_232();
        KillPassengers(killer);
        if (vf_11() != 0xF && !DAT_00A8E7AC) {
            RockingSidewaysPerFrame = (float)(DAT_00A8B230->unknown_0218.RandomRanged(0, 0x7FFFFFFE) * DAT_007E3570 * 0.15 + 0.1);
            if (DAT_00A8B230->unknown_0218.RandomRanged(0, 1) == 0) {
                RockingSidewaysPerFrame = -RockingSidewaysPerFrame;
            }
            RockingForwardsPerFrame = (float)(DAT_00A8B230->unknown_0218.RandomRanged(0, 0x7FFFFFFE) * DAT_007E3570 * 0.1);
        }
        AnnounceExpiredPointer(false);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4DED70
// Slot 27. For a viewer who is not allied with the owner, a disguised object on a cell the viewer cannot see
// into shows the type's image for flag 0, and any object that slot 272 hides from the viewer shows flag 1;
// otherwise the base slot answers.
void* FootClass::vf_27()
{
    CellStruct cell = CoordToCell(vf_18());
    CellClass* where = DAT_0087F7E8.FUN_005657A0(&cell);
    if (!Owner->IsAlliedWith(DAT_00A83D4C) && vf_49() && !where->FUN_004870F0(DAT_00A83D4C->ArrayIndex)) {
        return vf_51(false)->Image;
    }
    if (!vf_272(DAT_00A83D4C)) {
        return vf_51(true)->Image;
    }
    return ObjectClass::vf_27();
}

// FUNCTION: GAMEMD 0x4DEE80
// Slot 331. Among the owner's buildings of the given type (the owner must have one), the first live one with
// a free radio link (unless a3 is 1) that slot 158 accepts, and that this object can reach (anything but
// an aircraft needs a path), keeps the nearest: the squared distance goes through a4, and the primary factory
// always wins. Returns that building, or 0.
void* FootClass::vf_331(void* a1, int a2, int a3, int* a4)
{
    BuildingTypeClass* type = static_cast<BuildingTypeClass*>(a1);
    BuildingClass* best = 0;
    if (Owner->OwnedBuildingTypes.FUN_0049FAE0(type->ArrayIndex)) {
        int count = Owner->Buildings.Count;
        for (int i = 0; i < count; i++) {
            BuildingClass* building = Owner->Buildings.Items[i];
            if (building != 0 && !building->InLimbo && building->Type == type &&
                (a3 == 1 || building->HasFreeLinkFor(this))) {
                if (vf_11() != 2) {
                    CellStruct to = CoordToCell(building->vf_18());
                    CellStruct from = CoordToCell(vf_19(0));
                    if (!DAT_0087F7E8.FUN_0056D100(&from, &to, vf_33()->MovementZone, vf_47(0), 0, 0)) {
                        continue;
                    }
                }
                if (vf_158(0xF, building) == 1) {
                    int distance = FUN_005F6500(building);
                    if (*a4 == -1 || distance < *a4 || building->IsPrimaryFactory) {
                        best = building;
                        *a4 = distance;
                    }
                }
            }
        }
    }
    return best;
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

// FUNCTION: GAMEMD 0x4DF4B0
// Slot 308. For the attack-move mega mission (0x1D): with the attack-move target flag set, or a slot-97 value
// of 5, drops the flag and runs slot 306; otherwise runs slot 298 and answers false.
bool FootClass::vf_308()
{
    bool result = false;
    if (MegaMission == 0x1D) {
        result = HaveAttackMoveTarget;
        if (result) {
            HaveAttackMoveTarget = 0;
            result = vf_306();
        } else if (vf_97() == 5 || vf_97() == 5) {
            result = vf_306();
        } else {
            vf_298();
            result = false;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x4DF7F0
// Slot 322, the chrono jump. Refused in the air, while iron-curtained, immobilised or in either of the two
// slot 117 / 118 states. Otherwise a teleport locomotor is created and piggybacked on the current one, which
// is first parked on the target (a bridge cell raises it) when slot 11 answers 1; the teleport locomotor
// replaces the current one, the object is immobilised and heads for the destination cell.
bool FootClass::vf_322(CoordStruct where)
{
    if (IsInAir() || vf_88() || IsImmobilized || vf_117() || vf_118()) {
        return false;
    }
    LocomotorPtr teleport(DAT_007E9A90, 0, 7);
    IPiggybackPtr piggyback(teleport);
    if (DAT_0087F7E8.FUN_00565730(&where)->Flags & 0x100) {
        where.Z += DAT_008B3DF4;
    }
    if (vf_11() == 1) {
        Locomotor->MarkAllOccupationBits(0);
        LocoCoord to = where;
        Locomotor->ForceTrack(-1, to);
        vf_61(&where);
        FrozenStill = true;
    }
    SetDestination(DAT_0087F7E8.FUN_00565730(&where), true);
    SetDestination(0, true);
    teleport->LinkToObject(this);
    piggyback->BeginPiggyback(Locomotor);
    Locomotor = teleport;
    IsImmobilized = true;
    ChronoDestCoords = where;
    SetDestination(DAT_0087F7E8.FUN_00565730(&where), true);
    return true;
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
