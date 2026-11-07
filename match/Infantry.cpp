// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Infantry.CPP. The name is the source-file string at 0x825560
//   in retail gamemd.exe v1.001, passed by the assert at 0x51f2d2 inside this object's
//   code range (0x517840-0x52348f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.

#include "deleting_dtor_sweep.h"
#include "winsock_interface_class.h"
#include "_layout/pipe.h"
#include "_layout/straw.h"
#include <math.h>
#include "header_init_shapes.h"
#include "mathtbl_init_shapes.h"

#include <objidl.h>
#include "_layout/side_class.h"
#include "_layout/wave_class.h"

// GLOBAL: GAMEMD 0x007E9680 -- CLSID of InfantryClass.
extern const CLSID DAT_007E9680;

#include "trivial_tu099_b_methods.h"

#include "trivial_tu099_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E2AC8 -- the cap on one visit's intake.
extern const float DAT_007E2AC8;
// GLOBAL: GAMEMD 0x7EAEE8
extern const double DAT_007EAEE8;
// GLOBAL: GAMEMD 0xA8F1E8
extern double DAT_00A8F1E8;
// GLOBAL: GAMEMD 0xA8F220
extern double DAT_00A8F220;
// GLOBAL: GAMEMD 0xA8F228
extern HeaderCoordInit DAT_00A8F228;
// GLOBAL: GAMEMD 0xA8F22C
extern int DAT_00A8F22C;
// GLOBAL: GAMEMD 0xA8F230
extern int DAT_00A8F230;
// GLOBAL: GAMEMD 0xA8F238
extern double DAT_00A8F238;


// ---- from the former Infantry.cpp ----
//   CLI (disasm from each entry point). Original TU: Infantry.CPP, attested by the
//   __FILE__ assert string at 0x825560 ("...\Infantry.CPP"); the TU spans
//   0x517840-0x52348F. Class layout comes from the committed spine
//   match/_layout/infantry_class.h. Slot numbers are RTTI-derived (InfantryClass
//   vtable 0x7EB058); the vf_N and FUN_ names are placeholders.

#include "_layout/infantry_class.h"
#include "_layout/house_type_class.h"
#include "abstract_index_cast_sweep.h"
#include "vector_class_mutation.h"
#include "_layout/obj_004a1d30.h"
#include "frame_counter.h"
#include "_layout/house_class.h"
#include "loco_interfaces.h"
#include "loco_com.h"
#include "_layout/building_class.h"
#include "_layout/cell_class.h"
#include "rules_class.h"
#include "_layout/map_0087f7e8.h"
#include "_layout/team_class.h"
#include "weapon_type_class.h"
#include "_layout/vox_class.h"

// Offsets this TU relies on, each read from an instruction in the matched bodies.
GG_STATIC_ASSERT(offsetof(CellClass, OccupationFlags)    == 0x124);  // 0x5217C0
GG_STATIC_ASSERT(offsetof(CellClass, AltOccupationFlags) == 0x128);  // 0x5217C0
GG_STATIC_ASSERT(offsetof(CellClass, Flags)              == 0x140);  // 0x5217C0
GG_STATIC_ASSERT(offsetof(InfantryClass, Type)              == 0x6C0);  // 0x51AA10
GG_STATIC_ASSERT(offsetof(InfantryClass, SequenceAnim)      == 0x6C4);  // 0x522510
GG_STATIC_ASSERT(offsetof(InfantryClass, PanicDurationLeft) == 0x6D4);  // 0x521C10
GG_STATIC_ASSERT(offsetof(InfantryClass, Technician)        == 0x6D9);  // 0x521C90
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, Fearless)      == 0xEBC);  // 0x521C10

// The map singleton (GAMEMD 0x87F7E8): the two lookups the occupation methods use.
class MapView_565730
{
public:
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) -- the cell under a coordinate.
    CellClass* GetTargetCell(const CoordStruct& where);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) -- the floor height under a coordinate.
    int GetCellFloorHeight(const CoordStruct& where);
};
// GLOBAL: GAMEMD 0x87F7E8
extern MapView_565730 MapClass_Instance;
// GLOBAL: GAMEMD 0xA8E7AC -- nonzero suppresses the EVA line.
extern int DAT_00A8E7AC;
// GLOBAL: GAMEMD 0xA8F234 -- the height added to the floor before the bridge test.
extern int DAT_00A8F234;

// FUNCTION: GAMEMD 0x4810A0 (decl; reloc) -- the sub-cell slot a coordinate falls in.
int FUN_004810A0(CoordStruct* coord);

// GLOBAL: GAMEMD 0x8871E0
#include "_layout/rules_class.h"
#include "_layout/techno_class.h"
#include "mission_class_methods.h"
#include "randomizer.h"
#include "scenario_class_methods.h"
#include "_layout/geometry2d.h"
extern RulesClass* DAT_008871E0;
// GLOBAL: GAMEMD 0xA83D4C -- the local player's house.
extern HouseClass* CurrentPlayer;

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- resolve a label to its localised text; the
// last two arguments are the assert file and line.
const wchar_t* FUN_00734E60(const char* label, int flags, const char* file, int line);

// GLOBAL: GAMEMD 0x825560 -- "D:\\ra2mdpost\\Infantry.CPP"
extern const char DAT_00825560[];

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);
// GLOBAL: GAMEMD 0x7E1708
extern const double DAT_007E1708;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// GLOBAL: GAMEMD 0x7EAEE8
const double DAT_007EAEE8 = 60.0;
// GLOBAL: GAMEMD 0x7EAEF0
const double DAT_007EAEF0 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x517840
// GLOBAL: GAMEMD 0xA8F1E8
double DAT_00A8F1E8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));

// SYNTHETIC: GAMEMD 0x517870
// GLOBAL: GAMEMD 0xA8F238
double DAT_00A8F238 = DAT_00A8F1E8 / DAT_007EAEE8;

// SYNTHETIC: GAMEMD 0x517890
// GLOBAL: GAMEMD 0xA8F220
double DAT_00A8F220 = 1.0 / DAT_00A8F238;

// SYNTHETIC: GAMEMD 0x5178B0
// GLOBAL: GAMEMD 0xA8F218
double DAT_00A8F218 = DAT_007EAEF0 * 45.0;

// SYNTHETIC: GAMEMD 0x5178D0
// GLOBAL: GAMEMD 0xA8F1F0
double DAT_00A8F1F0 = DAT_007EAEF0 * 60.0;

// SYNTHETIC: GAMEMD 0x5178F0
// GLOBAL: GAMEMD 0xA8F1C8
double DAT_00A8F1C8 = DAT_007EAEF0 * 90.0;

// SYNTHETIC: GAMEMD 0x517910
// GLOBAL: GAMEMD 0xA8F240
int DAT_00A8F240 = (int)(FUN_004CAD50(DAT_00A8F1C8 - DAT_00A8F1F0) * DAT_00A8F1E8 * 0.5);

// SYNTHETIC: GAMEMD 0x517950
// GLOBAL: GAMEMD 0xA8F1F8
double DAT_00A8F1F8 = FUN_004CADE0(DAT_00A8F240 * 0.00390625);

// SYNTHETIC: GAMEMD 0x517980
// GLOBAL: GAMEMD 0xA8F210
double DAT_00A8F210 = FUN_004CADE0((DAT_00A8F240 * 2) / DAT_00A8F1E8);

// SYNTHETIC: GAMEMD 0x5179B0
// GLOBAL: GAMEMD 0xA8F234
int DAT_00A8F234 = (int)(DAT_00A8F240 * 4 + 0.5);

// SYNTHETIC: GAMEMD 0x5179E0
// GLOBAL: GAMEMD 0xA8F1E0
HeaderCellInit DAT_00A8F1E0(0, 0);

// SYNTHETIC: GAMEMD 0x5179F0
// GLOBAL: GAMEMD 0xA8F200
HeaderCoordInit DAT_00A8F200(0, 0, 0);

// SYNTHETIC: GAMEMD 0x517A10
// GLOBAL: GAMEMD 0xA8F228
HeaderCoordInit DAT_00A8F228(128, 128, 0);

// SYNTHETIC: GAMEMD 0x517A30
// GLOBAL: GAMEMD 0xA8F1D0
MathTblZero4 DAT_00A8F1D0;

// Kept after the static initialisers: at the top of the file this header alone costs all 14 initialiser rows their
// `_$E` numbers (measured: 73 matched, 0 regressed here; 59 matched, 14 regressed there). The two other new includes of
// this wave, weapon_type_class.h and vox_class.h, move nothing and sit with the rest.
#include "_layout/voc_class.h"
#include "_layout/astar_00746000.h"

// GLOBAL: GAMEMD 0xA83DE8 -- every InfantryClass joins this list.
extern DynamicVectorClass<InfantryClass*> DAT_00A83DE8;

// FUNCTION: GAMEMD 0x517A50
InfantryClass::InfantryClass(InfantryTypeClass* type, HouseClass* owner)
    : FootClass(owner),
      Type(type),
      SequenceAnim(-1),
      unknown_Timer_6C8(0),
      PanicDurationLeft(0),
      PermanentBerzerk(false),
      Technician(false),
      unknown_bool_6DA(false),
      Crawling(false),
      unknown_bool_6DC(false),
      unknown_bool_6DD(false),
      unknown_6E0(0),
      ShouldDeploy(false),
      unknown_int_6E8(2)
{
    vf_rtti_5();
    DAT_00A83DE8.AddItem(this);
    vf_9();
    if (Type) {
        Locomotor.CreateInstance(Type->Locomotor, 0, 7);
        Locomotor->LinkToObject(this);
    }
    PrimaryFacing.FUN_004C9680(0x7F);
    AbstractIndex.AddIndex(vf_rtti_4(), this);
}

// FUNCTION: GAMEMD 0x517CC0
void InfantryClass::vf_9()
{
    TechnoClass::vf_9();
    if (Owner) {
        Owner->FUN_004FF700(this);
    }
    if (Type) {
        if (Owner) {
            TypeList<const InfantryTypeClass*>& list = Owner->Type->VeteranInfantry;
            for (int i = 0; i < list.Count; i++) {
                if (list.Items[i] == Type) {
                    Veterancy.FUN_00750090(1);
                    break;
                }
            }
        }
        if (Owner && Owner->BarracksInfiltrated && Type->bools_C8C[2]) {
            Veterancy.FUN_00750090(1);
        }
        Health = Type->Strength;
        EstimatedHealth = Type->Strength;
        int ammo = Type->InitialAmmo;
        if (ammo == -1) {
            ammo = Type->Ammo;
        }
        Ammo = ammo;
        Cloakable = Type->Cloakable;
    }
}

// FUNCTION: GAMEMD 0x51AA10
void InfantryClass::vf_10(void* a1, bool a2)
{
    FootClass::vf_10(a1, a2);
    if (this->Type == a1) {
        this->Type = 0;
    }
}

// FUNCTION: GAMEMD 0x51B1F0
// Slot 242: a new target stops the current action (the deploy kinds undeploy, a crawler stands up, else idle);
// the rocker link is dropped, then TechnoClass takes the target. An infiltrator that was given a building it
// may capture (or spy on, for agents) is sent to it.
void InfantryClass::vf_242(AbstractClass* target)
{
    if (target != Target) {
        if (Health > 0) {
            int s = SequenceAnim;
            IsFiring = 0;
            bool deploying = s == 0x1B || s == 0x1C || s == 0x1D || s == 0x1E;
            if (deploying) {
                this->vf_342(0x1C, 0, 0);
            } else if (Crawling) {
                this->vf_342(2, 0, 0);
            } else {
                this->vf_342(0, 0, 0);
            }
        }
        if (target != Target) {
            if (DirectRockerLinkedUnit) {
                static_cast<TechnoClass*>(DirectRockerLinkedUnit)->DirectRockerLinkedUnit = 0;
                DirectRockerLinkedUnit = 0;
            }
        }
    }
    int s = SequenceAnim;
    if ((s == 0x1B || s == 0x1C || s == 0x1D || s == 0x1E) && !Type->DeployFire) {
        return;
    }
    PathDirections[0] = -1;
    TechnoClass::vf_242(target);
    if (!Destination && Type->Infiltrate) {
        BuildingClass* building = target && target->vf_11() == 6 ? static_cast<BuildingClass*>(target) : 0;
        if (!Type->Agent && building && building->Type->Capturable) {
            this->SetDestination(target, true);
            unknown_bool_68E = 0;
            return;
        }
        if (Type->Agent && building && building->Type->Spyable) {
            this->SetDestination(target, true);
        }
    }
    unknown_bool_68E = 0;
}

// FUNCTION: GAMEMD 0x51CBA0
// Slot 289 (EnterIdleMode): after FootClass's pass, an infantryman with nothing queued picks a
// mission from its target, destination, owner and team, and switches to it.
bool InfantryClass::EnterIdleMode(bool initial, bool a2)
{
    bool result = FootClass::EnterIdleMode(initial, a2);
    if (this->vf_299()) {
        return result;
    }
    if (this->vf_97() == 0x1C) {
        return result;
    }
    int mission;
    if (this->Target) {
        mission = 1;
        if (this->vf_97() == 0x11) {
            mission = 0x11;
        }
        if (this->vf_97() == 8) {
            mission = 8;
        }
    } else {
        this->FUN_004DA030();
        if (this->Destination) {
            mission = 2;
            if (this->vf_97() == 8) {
                mission = 8;
            }
            if (this->vf_97() == 0x11) {
                mission = 0x11;
            }
        } else {
            if (this->vf_97() == 5 || this->vf_97() == 0xB) {
                return false;
            }
            if (this->vf_97() != -1) {
                if (this->FUN_005B3A00()->Zombie || this->FUN_005B3A00()->Paralyzed) {
                    return false;
                }
            }
            if (!this->Owner->IsControlledByHuman() && !this->Team) {
                if (this->Owner->IQLevel2 < DAT_008871E0->unknown_1440 && this->CurrentMission != 0xB) {
                    mission = 5;
                } else if (this->SlaveOwner) {
                    mission = 5;
                } else if (!this->IsArmed() && !this->Type->Engineer && !this->Type->VehicleThief) {
                    mission = 5;
                } else {
                    mission = 0xB;
                }
            } else if (this->CurrentMission != 0xB
                       && (!(this->FUN_0070D0D0(0x10) || this->Type->DefaultToGuardArea) || this->Team)) {
                mission = 5;
            } else {
                mission = 0xB;
            }
        }
    }
    if (this->CurrentMission != 0x19 && this->CurrentMission != 0xB && mission != -1) {
        this->vf_122(mission, false);
    }
    return result;
}

// FUNCTION: GAMEMD 0x51DAF0
// Slot 320: the sequence slot (deploy kinds 0x1C, crawling 2, else 0) is selected, then whether the cell
// ahead (the facing rounded to eight ways) can be entered is recorded before FootClass runs.
bool InfantryClass::vf_320()
{
    int s = this->SequenceAnim;
    bool deploying = s == 0x1B || s == 0x1C || s == 0x1D || s == 0x1E;
    if (deploying) {
        this->vf_342(0x1C, 0, 0);
    } else if (this->Crawling) {
        this->vf_342(2, 0, 0);
    } else {
        this->vf_342(0, 0, 0);
    }
    DirStruct facing;
    int ahead = (((this->PrimaryFacing.FUN_004C93D0(&facing)->Whole >> 12) + 1) >> 1) & 7;
    CoordStruct where = this->Location;
    if (!this->vf_107(DAT_0087F7E8.FUN_00565730(where), ahead, this->GetCellLevel(), 0, true)) {
        this->unknown_bool_6DC = false;
    } else {
        this->unknown_bool_6DC = true;
    }
    return FootClass::vf_320();
}

// FUNCTION: GAMEMD 0x51DF10
bool InfantryClass::vf_53()
{
    Locomotor->StopMovementAnimation();
    this->unknown_int_6E8 = 2;
    this->Crawling = false;
    this->SequenceAnim = 0;
    return FootClass::vf_53();
}

// FUNCTION: GAMEMD 0x51DF60
BulletClass* InfantryClass::vf_243(AbstractClass* a1, int a2)
{
    this->IsFiring = 0;
    BulletClass* result = TechnoClass::vf_243(a1, a2);
    if (result && !this->InLimbo && this->Type->Fraidycat && this->Ammo == 0) {
        this->PanicDurationLeft = 300;
        if (this->vf_97() == 1 || this->vf_97() == 15) {
            this->vf_122(5, false);
        }
    }
    return result;
}

inline CellStruct CoordToCell_005227F0(const CoordStruct& where)
{
    CellStruct result;
    result.X = where.X / 256;
    result.Y = where.Y / 256;
    return result;
}

// FUNCTION: GAMEMD 0x51DFF0
// PARTIAL: 96.3% - identical instruction multiset; the two stores of the snapped X and Y into the local
// coordinate are scheduled after the Z load here and between the loads in retail (3 instructions out of place).
// Slot 54 (place on the map): a coordinate resting on the floor is snapped to the cell's sub-cell
// position first. FootClass runs on the result; a position at or below the cell's floor level is then
// registered through slot 60.
bool InfantryClass::vf_54(const CoordStruct& coord, int a2)
{
    int floor = DAT_0087F7E8.FUN_00578080(coord);
    CoordStruct where = coord;
    bool ok = true;
    if (where.Z == floor) {
        CoordStruct snapped = DAT_0087F7E8.FUN_00565730(coord)->FindInfantrySubposition(coord,
            DAT_00A8E7AC || !DAT_0087F7E8.FUN_00578460(CoordToCell_005227F0(coord), 1), false, false);
        where.Y = snapped.Y;
        where.X = snapped.X;
        if (where.X == DAT_00A8F200.X && where.Y == DAT_00A8F200.Y && snapped.Z == DAT_00A8F200.Z) {
            ok = false;
        } else {
            where.Z = floor;
        }
    }
    if (ok && FootClass::vf_54(where, a2)) {
        if (this->Type->Sight == 0) {
            this->DiscoveredByCurrentPlayer = 0;
        }
        if (where.Z <= DAT_00A8F234 + floor) {
            this->vf_60(&where);
        }
        this->unknown_int_6E8 = 2;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x51F190
// PARTIAL: 95.6% - retail's jump table also spans labels 1/5/0x10/0x1A that share the join block
// (range 1..0x39); VC6 drops empty labels so the compiled table starts at 9 (2 instructions differ).
// Re-derives the action the target would get (vf_29): the 0x1C/0x1D kinds fold into 9 and
// 0x1B/0x39 into 5. An infantryman never takes action 5 on itself and does nothing while
// berzerk; otherwise the folded action is handed to FootClass.
bool InfantryClass::vf_81(int a1, ObjectClass* a2, int a3)
{
    int action = this->vf_29(a2, a3);
    switch (action) {
    case 9:
    case 0x1C:
    case 0x1D:
        action = 9;
        break;
    case 0x1B:
    case 0x39:
        action = 5;
    }
    if (a2 == this && action == 5) {
        return false;
    }
    if (this->Berzerk) {
        return false;
    }
    return FootClass::vf_81(action, a2, a3);
}

// FUNCTION: GAMEMD 0x51F250
// PARTIAL: 87.5% - ebx/edi hold a2/a4 swapped (6 instructions differ, same multiset).
// Refuses while berzerk, or while in a 0x1B-0x1E sequence when vf_28 reports 2; otherwise defers to FootClass.
bool InfantryClass::vf_80(int mode, CellStruct* cell, int a3, int a4)
{
    int s = this->SequenceAnim;
    if (s == 0x1B || s == 0x1C || s == 0x1D || s == 0x1E) {
        if (this->vf_28(cell, 0, a4) == 2) {
            return false;
        }
    }
    if (this->Berzerk) {
        return false;
    }
    return FootClass::vf_80(mode, cell, a3, a4);
}

// STRING: GAMEMD 0x825550 "TXT_TECHNICIAN"
// FUNCTION: GAMEMD 0x51F2C0
const wchar_t* InfantryClass::vf_36()
{
    if (this->Technician) {
        return FUN_00734E60("TXT_TECHNICIAN", 0, DAT_00825560, 0x121C);
    }
    if (this->vf_49() && !this->Owner->IsAlliedWith(CurrentPlayer)) {
        return this->vf_51(true)->UIName;
    }
    return this->Type->UIName;
}


// GLOBAL: GAMEMD 0xA8B230
extern ScenarioClass* DAT_00A8B230;

// GLOBAL: GAMEMD 0x7E9AC0 -- CLSID of JumpjetLocomotionClass.
extern const CLSID DAT_007E9AC0;

// GLOBAL: GAMEMD 0x7EAF7C -- per-sequence table, 4 bytes an entry; the first byte is the one read.
extern const unsigned char DAT_007EAF7C[][4];


// FUNCTION: GAMEMD 0x51F330
// Slot 266: re-pick a target for this infantry. Keep the current target if it is still valid for
// the chosen weapon, else scan for a new one, and finally fall back to idle mode.
void InfantryClass::vf_266()
{
    int weapon = vf_185(0);
    if (Target && vf_234(Target, weapon))
        return;
    CoordStruct where = Location;
    AbstractClass* found = vf_241(1, &where, false);
    if ((Target || found) && (vf_242(found), found))
        return;
    if (CurrentMission != 5 && !vf_33()->bools_D94[0])
        EnterIdleMode(false, true);
}

// FUNCTION: GAMEMD 0x51F3E0
// Slot 132: an infantryman that can demolish (or any computer-owned one that can occupy or infiltrate)
// heads for a building target it can act on; a human-owned deployer mid-deploy waits out a random extra
// delay. Everything else is FootClass's.
int InfantryClass::vf_132()
{
    if ((this->Type->C4 || this->FUN_0070D0D0(0xE)) && this->Target && this->Target->vf_11() == 6
        && static_cast<BuildingClass*>(this->Target)->Type->CanC4
        && !static_cast<BuildingClass*>(this->Target)->Type->InvisibleInGame) {
        this->SetDestination(this->Target, true);
        this->vf_122(0x11, false);
        return 1;
    }
    if (!this->Owner->IsControlledByHuman() && this->Target && this->Target->vf_11() == 6
        && (this->Type->Infiltrate
            || ((this->Type->Occupier || this->Type->Assaulter)
                && static_cast<BuildingClass*>(this->Target)->CanBeOccupiedBy(this)))) {
        this->SetDestination(this->Target, true);
        this->vf_124(8);
        return 1;
    }
    if (this->Owner->IsControlledByHuman()) {
        int s = this->SequenceAnim;
        if (s == 0x1B || s == 0x1C || s == 0x1D || s == 0x1E) {
            this->vf_266();
            int delay = (int)(this->FUN_005B3A00()->Rate * 900.0);
            return delay + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
        }
    }
    return FootClass::vf_132();
}

// FUNCTION: GAMEMD 0x51F540
int InfantryClass::vf_138()
{
    if (!this->Owner->IsControlledByHuman() && this->Target && this->Target->vf_11() == 6
        && (this->Type->Infiltrate
            || ((this->Type->Occupier || this->Type->Assaulter)
                && static_cast<BuildingClass*>(this->Target)->CanBeOccupiedBy(this)))) {
        this->SetDestination(this->Target, true);
        this->vf_124(8);
        return 1;
    }
    if (!this->Owner->IsControlledByHuman()) {
        int s = this->SequenceAnim;
        if ((s == 0x1B || s == 0x1C || s == 0x1D || s == 0x1E) && !this->Target) {
            this->vf_342(0x1F, 0, 0);
            return 1;
        }
    }
    return FootClass::vf_138();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x51F620
// Branching. Vtable slot 135 of InfantryClass (RTTI).
void FUN_0051F620(Obj_0051F620* a1, int a2)
{
    int c0 = FUN_00521320(a1, a2);
    if (c0 == -1)
    {
        a1->FUN_004D5070();
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x51F640
// Branching. Vtable slot 136 of InfantryClass (RTTI).
void FUN_0051F640(Obj_0051F640* a1, int a2)
{
    int c0 = FUN_00521320(a1, a2);
    if (c0 == -1)
    {
        a1->FUN_004D6AA0();
    }
}

// FUNCTION: GAMEMD 0x51F660
int InfantryClass::vf_139()
{
    int s = this->SequenceAnim;
    if (s == 0x1B || s == 0x1C || s == 0x1D || s == 0x1E) {
        if (this->vf_15()->IsControlledByHuman()) {
            this->SetDestination(0, true);
            return 1;
        }
        if (this->Type->UndeployDelay <= -1) {
            this->vf_342(0x1F, 0, 0);
            return this->Type->Sequence[0x1F].unknown_04;
        }
    }
    return FootClass::vf_139();
}

// FUNCTION: GAMEMD 0x51F6E0
// Slot 143: a deployer plays its undeploy or deploy sequence, drops its destination and reports how long
// that takes; FootClass answers when it is not a deployer or no delay came out.
int InfantryClass::vf_143()
{
    if (this->Type->Deployer) {
        int result = -1;
        int s = this->SequenceAnim;
        bool deploying = s == 0x1B || s == 0x1C || s == 0x1D || s == 0x1E;
        if (deploying) {
            if (this->Type->UndeployDelay <= -1) {
                this->vf_342(0x1F, 1, 0);
            }
        } else {
            this->vf_342(0x1B, 1, 0);
            WeaponStruct* weapon = this->vf_252();
            if (this->FUN_0070E240(weapon) && weapon->WeaponType->AreaFire) {
                if (this->FUN_005F3E50("DESO")) {
                    result = this->Type->Sequence[0x1B].unknown_04 + 1;
                } else {
                    this->vf_242(DAT_0087F7E8.FUN_005657A0(this->vf_110()));
                }
            }
            if (this->Type->UndeployDelay > -1) {
                result = this->Type->UndeployDelay;
            }
        }
        this->vf_124(5);
        this->SetDestination(0, true);
        if (result > -1) {
            return result;
        }
    }
    return FootClass::vf_143();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x51FAF0
// Vtable slot 34 of InfantryClass (RTTI). Member getter (dword).
ObjectTypeClass* InfantryClass::vf_34()
{
    return Type;
}

// FUNCTION: GAMEMD 0x520260
bool InfantryClass::FUN_00520260()
{
    if (this->Team && this->IsInPlayfield) {
        this->Team->Flag82 = true;
    }
    if (!this->Team && vf_97() == 5) {
        CoordStruct where = this->Location;
        if (!DAT_0087F7E8.FUN_00568350(where)) {
            vf_232();
            vf_62();
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5216C0
// Tail-forwards to another function. Vtable slot 27 of InfantryClass (RTTI).
void FUN_005216C0(Obj_005216C0* a1, int a2)
{
    FUN_004DED70(a1, a2);
}

// FUNCTION: GAMEMD 0x521760
bool InfantryClass::vf_58(const CoordStruct& coord)
{
    if (ObjectClass::vf_58(coord)) {
        if (this->Owner->IsControlledByHuman()) {
            this->vf_122(5, false);
        } else {
            this->vf_122(15, false);
        }
        this->vf_342(0x21, 1, 0);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5217C0
void InfantryClass::vf_60(CoordStruct* coord)
{
    int slot = FUN_004810A0(coord);
    CellClass* cell = MapClass_Instance.GetTargetCell(*coord);
    int floor = MapClass_Instance.GetCellFloorHeight(*coord) + DAT_00A8F234;
    if (floor <= coord->Z && (cell->Flags & 0x100)) {
        cell->AltOccupationBits |= (1 << slot);
        cell->AltInfantryOwnerIndex = this->vf_14();
    } else {
        cell->OccupationBits |= (1 << slot);
        cell->InfantryOwnerIndex = this->vf_14();
    }
}

// FUNCTION: GAMEMD 0x521850
void InfantryClass::vf_61(CoordStruct* coord)
{
    int slot = FUN_004810A0(coord);
    CellClass* cell = MapClass_Instance.GetTargetCell(*coord);
    int level = MapClass_Instance.GetCellFloorHeight(*coord);
    level += DAT_00A8F234;
    if (level <= coord->Z) {
        cell->AltOccupationBits &= ~(1 << slot);
        if (!(cell->AltOccupationBits & 0x1C)) {
            cell->AltInfantryOwnerIndex = -1;
        }
    } else {
        cell->OccupationBits &= ~(1 << slot);
        if (!(cell->OccupationBits & 0x1C)) {
            cell->InfantryOwnerIndex = -1;
        }
    }
}

// FUNCTION: GAMEMD 0x5218E0
int InfantryClass::vf_185(AbstractClass* target)
{
    InfantryTypeClass* type = this->Type;
    if (type->DeployFire) {
        int s = this->SequenceAnim;
        if (s == 0x1B || s == 0x1C || s == 0x1D || s == 0x1E) {
            return type->DeployFireWeapon;
        }
        if (this->InOpenToppedTransport) {
            if (this->vf_33()->OpenTransportWeapon != -1) {
                return this->vf_33()->OpenTransportWeapon;
            }
        }
        return 0;
    }
    return TechnoClass::vf_185(target);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x521B20
// Vtable slot 338 of InfantryClass (RTTI). Branching.
void InfantryClass::vf_338()
{
    int t1 = SequenceAnim;
    if (t1 == 6)
    {
        SequenceAnim = -1;
    }
    if (t1 == 3)
    {
        SequenceAnim = -1;
    }
    if (t1 == 0x11)
    {
        SequenceAnim = -1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x521B40
// Vtable slot 339 of InfantryClass (RTTI). Branching.
void InfantryClass::vf_339()
{
    if (ShouldDeploy != 0)
    {
        ShouldDeploy = 0;
        vf_342(0x1B, 0, 0);
    }
}

// FUNCTION: GAMEMD 0x521B60
// Slot 128: true when the infantry is idle enough to be ordered about. Not while in mission 6 or
// 0x15, firing or falling; while moving, only in certain states; finally gated by its sequence's flag.
bool InfantryClass::vf_128()
{
    if (CurrentMission != 6 && CurrentMission != 0x15 && !IsFiring && !IsFallingDown) {
        if (Locomotor->IsMovingNow()
            && vf_97() != 5 && vf_97() != 0xF && (vf_97() != 1 || Target))
            return false;
        if (SequenceAnim == -1 || DAT_007EAF7C[SequenceAnim][0])
            return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x521C10
void InfantryClass::vf_326()
{
    if (!this->Type->Fearless && !this->FUN_0070D0D0(13)) {
        this->PanicDurationLeft = 300;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x521C40
// Branching. Vtable slot 327 of InfantryClass (RTTI).
Obj_00521C40_6C0* Obj_00521C40::FUN_00521C40()
{
    if (unknown_6C0->unknown_EBC == 0)
    {
        unknown_6D4 = 0;
    }
    return unknown_6C0;
}

// FUNCTION: GAMEMD 0x521C60
void InfantryClass::vf_328(int a1)
{
    switch (a1) {
    case 1:
        this->vf_342(10, 0, 0);
        break;
    default:
        this->vf_342(9, 0, 0);
        break;
    }
}

// FUNCTION: GAMEMD 0x521C90
void InfantryClass::vf_13(Obj_004A1D30* crc)
{
    FootClass::vf_13(crc);
    crc->FUN_004A1D50(this->SequenceAnim);
    crc->FUN_004A1D50(this->unknown_Timer_6C8.GetTimeLeft());
    crc->FUN_004A1D50(this->PanicDurationLeft);
    crc->FUN_004A1CA0(this->Technician);
    crc->FUN_004A1CA0(this->unknown_bool_6DA);
    crc->FUN_004A1CA0(this->Crawling);
    crc->FUN_004A1CA0(this->unknown_bool_6DC);
    crc->FUN_004A1CA0(this->unknown_bool_6DD);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// The infantry seen as a bare vtable pointer; slot 44 takes the argument and a
// coordinate by value.
struct Vtbl_00521D30;
struct InfantryView_00521D30
{
    Vtbl_00521D30* Vtbl;
};
typedef CoordStruct (InfantryView_00521D30::*Slot44_00521D30)(int, CoordStruct);
struct Vtbl_00521D30
{
    char             _pad000[0xB0];
    Slot44_00521D30  At_B0;     // +0xB0
};

// FUNCTION: GAMEMD 0x521D30
// Ask slot 44 for the position, passing the origin as the coordinate.
CoordStruct InfantryClass::vf_192(int a1)
{
    CoordStruct zero = { 0, 0, 0 };
    InfantryView_00521D30* self = (InfantryView_00521D30*)this;
    return (self->*self->Vtbl->At_B0)(a1, zero);
}

// FUNCTION: GAMEMD 0x5220F0
// Vtable slot 325 of InfantryClass (RTTI). Stores a constant in a member.
void InfantryClass::vf_325()
{
    PermanentBerzerk = 1;
}

// FUNCTION: GAMEMD 0x522100
// True when the type is a jumpjet type and its locomotor reports the jumpjet locomotor's class ID.
bool InfantryClass::FUN_00522100()
{
    if (!Type->bools_D94[0])
        return false;
    IPersistPtr persist(Locomotor);
    CLSID id;
    persist->GetClassID(&id);
    return IsEqualCLSID(id, DAT_007E9AC0);
}

// FUNCTION: GAMEMD 0x5221D0
// Should a short hop between two cells be handed to the path search? An airborne infantryman (height above
// zero), a failed pre-check, a far hop or an off-map endpoint all say yes; a house that cannot see ahead, a
// blocked start cell, the same cell or an adjacent one say no. In between the search is run and only a
// long result counts.
bool InfantryClass::FUN_005221D0(CellStruct* from, CellStruct* to)
{
    // Retail makes this call first and drops the result (the second call below is the one tested).
    this->vf_114();
    if (Owner->IonSensitivesShouldBeOffline()) {
        return false;
    }
    if (this->vf_114() > 0) {
        return true;
    }
    if (Owner->IsControlledByHuman()) {
        CellClass* cell = DAT_0087F7E8.FUN_005657A0(*from);
        if (cell && cell->FUN_00484AE0()) {
            return false;
        }
    }
    if (DAT_0087F7E8.FUN_0056D100(from, to, 7, OnBridge, (DAT_0087F7E8.FUN_005657A0(*to)->Flags >> 8) & 1, 0)) {
        if (from->X == to->X && from->Y == to->Y) {
            return false;
        }
        int dy = abs(to->Y - from->Y);
        int dx = abs(to->X - from->X);
        int dist = dx > dy ? dx : dy;
        if (dist == 1) {
            return false;
        }
        if (dist < 4
            && DAT_0087F7E8.FUN_00578460(from, true)
            && DAT_0087F7E8.FUN_00578460(to, true)) {
            int steps = DAT_0087E8B8.AttemptPath(
                from, to, this, OnBridge, (DAT_0087F7E8.FUN_005657A0(*to)->Flags >> 8) & 1, 7);
            return steps > 7;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x522340
// Slot 335: while deploying toward a target with a deploy-fire weapon the target is out of range of, the
// infantryman undeploys (sequence 0x1F); while standing and the target is in range, it starts to deploy.
// The delay FUN_00522550 reports is dropped. Anything else is FootClass's with the flag cleared.
int InfantryClass::vf_335(bool a1)
{
    if (this->Target) {
        int s = this->SequenceAnim;
        bool deploying = s == 0x1B || s == 0x1C || s == 0x1D || s == 0x1E;
        if (!deploying) {
            return FootClass::vf_335(false);
        }
        if (!this->vf_15()->IsControlledByHuman() && this->Type->Deployer && this->Type->DeployFire) {
            int weapon = this->Type->DeployFireWeapon;
            bool inRange = this->vf_234(this->Target, weapon);
            WeaponTypeClass* type = this->vf_254(weapon)->WeaponType;
            if (type && !type->AreaFire) {
                int now = this->SequenceAnim;
                bool deployingNow = now == 0x1B || now == 0x1C || now == 0x1D || now == 0x1E;
                if (deployingNow) {
                    if (!inRange && !a1) {
                        this->vf_342(0x1F, 0, 0);
                        return 0;
                    }
                } else if (inRange && !a1) {
                    this->FUN_00522550();
                    return 0;
                }
            }
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5224D0
// Vtable slot 204 of InfantryClass (RTTI). Member getter (byte) of the type.
bool InfantryClass::vf_204()
{
    return Type->Engineer;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5224E0
// Member getter (byte).
unsigned char Obj_005224E0::FUN_005224E0() const
{
    return unknown_6C0->unknown_EC8;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5224F0
// Returns a comparison result.
unsigned char Obj_005224F0::FUN_005224F0() const
{
    return unknown_6C0->unknown_6C4 > -1;
}

// FUNCTION: GAMEMD 0x522510
bool InfantryClass::FUN_00522510()
{
    int s = this->SequenceAnim;
    return s == 0x1B || s == 0x1C || s == 0x1D || s == 0x1E;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x522540
// Member getter (byte).
unsigned char Obj_00522540::FUN_00522540() const
{
    return unknown_6C0->unknown_6AC;
}

// FUNCTION: GAMEMD 0x522550
// Start deploying: a stationary infantry plays the deploy sequence and reports that sequence's second
// field; a moving one stops, flags itself to deploy and returns a delay from its mission rate plus a
// random 0-2.
int InfantryClass::FUN_00522550()
{
    if (!Locomotor->IsMoving()) {
        vf_342(0x1B, 0, 0);
        return Type->Sequence[0x1B].unknown_04;
    }
    Locomotor->StopMoving();
    ShouldDeploy = true;
    MissionControlClass* control = FUN_005B3A00();
    int delay = (int)(control->Rate * 900.0);
    return delay + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
}

// FUNCTION: GAMEMD 0x522600
// Applies the type's full strength as C4 warhead damage; the second argument is the house.
void InfantryClass::vf_85(int a1, int a2, bool a3)
{
    int damage = this->Type->Strength;
    this->vf_91(&damage, 0, RulesInstance->C4Warhead, 0, true, false, (void*)a2);
}

// FUNCTION: GAMEMD 0x522640
ObjectTypeClass* InfantryClass::vf_51(bool a1)
{
    if (this->Owner->IsAlliedWith(CurrentPlayer) && !a1) {
        return this->Type;
    }
    if (this->Disguise) {
        return this->Disguise;
    }
    if (CurrentPlayer) {
        int side = CurrentPlayer->SideIndex;
        if (side == 0) {
            return DAT_008871E0->AlliedDisguise;
        }
        if (side == 1) {
            return DAT_008871E0->SovietDisguise;
        }
    }
    return DAT_008871E0->ThirdDisguise;
}

// FUNCTION: GAMEMD 0x5226C0
HouseClass* InfantryClass::vf_52(bool a1)
{
    if (this->Owner->IsAlliedWith(CurrentPlayer) && !a1) {
        return this->Owner;
    }
    if (this->DisguisedAsHouse) {
        return this->DisguisedAsHouse;
    }
    return CurrentPlayer;
}

// FUNCTION: GAMEMD 0x522700
// Disguise as another infantryman: take on his type and house. Retail leaves
// the return value unset.
#pragma warning(disable : 4716)
unsigned long InfantryClass::DisguiseAs(AbstractClass* target)
{
    TechnoClass* other = (TechnoClass*)target;
    if (other && other->vf_11() == 15) {
        TechnoClass::DisguiseAs(target);
        if (other->vf_49()) {
            this->Disguise = other->vf_51(true);
            this->DisguisedAsHouse = other->vf_52(true);
        } else {
            this->Disguise = other->vf_34();
            this->DisguisedAsHouse = other->vf_15();
        }
    }
}
#pragma warning(default : 4716)

// FUNCTION: GAMEMD 0x522780
void InfantryClass::vf_284()
{
    if (this->Type->bools_D20[0x10]) {
        this->Disguised = true;
        this->DisguisedAsHouse = this->Owner;
        int side = this->Owner->SideIndex;
        if (side == 0) {
            this->Disguise = DAT_008871E0->AlliedDisguise;
        } else if (side == 1) {
            this->Disguise = DAT_008871E0->SovietDisguise;
        } else {
            this->Disguise = DAT_008871E0->ThirdDisguise;
        }
    } else {
        this->Disguised = false;
    }
}



// A house, as far as its alliance test.
struct HouseView_005227F0
{
    // FUNCTION: GAMEMD 0x4F9A50 (decl; reloc)
    bool FUN_004F9A50(HouseClass* other);
};


// FUNCTION: GAMEMD 0x5227F0
// Whether the house is fooled by this infantryman's disguise at its current cell.
bool InfantryClass::vf_50(HouseClass* house)
{
    if (vf_49()) {
        CellStruct cell = CoordToCell_005227F0(vf_18());
        CellClass* cellRecord = DAT_0087F7E8.FUN_005657A0(&cell);
        if (!reinterpret_cast<HouseView_005227F0*>(Owner)->FUN_004F9A50(house) &&
            !cellRecord->FUN_004870F0(house->ArrayIndex)) {
            HouseClass* disguised = DisguisedAsHouse;
            if (disguised == house || !disguised ||
                reinterpret_cast<HouseView_005227F0*>(house)->FUN_004F9A50(disguised))
                return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5228B0
// Tail-forwards to another function. Vtable slot 303 of InfantryClass (RTTI).
void FUN_005228B0(Obj_005228B0* a1, int a2)
{
    FUN_0070F070(a1, a2);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5228C0
// Tail-forwards to another function. Vtable slot 304 of InfantryClass (RTTI).
void FUN_005228C0(Obj_005228C0* a1, int a2)
{
    FUN_0070F090(a1, a2);
}

// FUNCTION: GAMEMD 0x5228D0
int InfantryClass::vf_341()
{
    if (this->Type->Deployer) {
        int s = this->SequenceAnim;
        if (s == 0x1B || s == 0x1C || s == 0x1D || s == 0x1E) {
            return 1;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x522910
// Enter a building: an occupier joins its occupants (announced once, for the first one, to the local
// player); an assaulter instead clears the occupants out and takes the building's position.
void InfantryClass::FUN_00522910(BuildingClass* building)
{
    if (this->Type->Occupier) {
        this->vf_53();
        building->Occupants.AddItem(this);
        building->UpdateThreatInCell(building->vf_111());
        if (building->Occupants.Count == 1) {
            building->vf_73(2);
            if (this->Owner->IsControlledByCurrentPlayer()) {
                VoxClass::Play("EVA_StructureGarrisoned", -1, -1);
                VocClass::PlayAt(DAT_008871E0->BuildingGarrisonedSound, this->vf_18(), 0);
            }
        }
        if (this->Owner->IsHumanPlayer) {
            this->ShouldGarrisonStructure = 0;
            this->ShouldEnterOccupiable = 0;
        }
    } else if (this->Type->Assaulter) {
        building->FUN_004585C0(this);
        this->SetDestination(0, true);
        this->vf_93(building->vf_18(), true, true);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x522A50
// Empty function that pops its stack arguments.
void __stdcall FUN_00522A50(int a1)
{
}

// FUNCTION: GAMEMD 0x522A60
// INoticeSink slot 0 (the +0x08 table). Notice 0x117B hands a jumpjet or balloon-hover infantryman
// that is linked to something over to its archived target, or stops it; notice 0x117C drops a
// crashable one to the cell's height and starts sequence 0x24.
bool InfantryClass::Notice(int id, int arg)
{
    if ((this->Type->BalloonHover || this->Type->JumpJet) && id == 0x117B && this->HasAnyLink()) {
        this->vf_157(8);
        if (this->ArchiveTarget && this->ArchiveTarget != this->Destination) {
            this->SetDestination(this->ArchiveTarget, true);
            return true;
        }
        this->AbortMotion();
        this->vf_93(DAT_00A8F200, true, false);
        return true;
    }
    if (this->Type->Crashable && id == 0x117C) {
        CellClass* cell = DAT_0087F7E8.FUN_005657A0(CoordToCell_005227F0(this->vf_18()));
        if (cell->Flags & 0x100) {
            this->vf_115(DAT_00A8F234);
        } else {
            this->vf_115(0);
        }
        this->vf_342(0x24, 1, 0);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x522BC0
bool InfantryClass::vf_225()
{
    if (this->vf_97() == 5 || this->vf_97() == 11) {
        int s = this->SequenceAnim;
        if (s == 0 || s == 9 || s == 10 || s == 0x20) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x522C00
// Starts sequence 0x20 when the argument is set or vf_225() holds.
void InfantryClass::vf_226(int a1)
{
    if ((unsigned char)a1 || this->vf_225()) {
        this->vf_342(0x20, 0, 0);
    }
}

// FUNCTION: GAMEMD 0x522C30
bool InfantryClass::FUN_00522C30(int sequence)
{
    if (sequence == 9 || sequence == 10 || sequence == 0x12 || sequence == 0x13 || sequence == 0x17 || sequence == 0x20) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x522C60
int InfantryClass::FUN_00522C60(int sequence)
{
    if (sequence == 11 || sequence == 12 || sequence == 13 || sequence == 14 || sequence == 15
        || sequence == 0x22 || sequence == 0x23 || sequence == 0x24 || sequence == 0x14 || sequence == 0x15) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x522CB0
bool InfantryClass::FUN_00522CB0()
{
    int s = this->SequenceAnim;
    return s == 11 || s == 12 || s == 13 || s == 14 || s == 15
        || s == 0x22 || s == 0x23 || s == 0x24 || s == 0x14 || s == 0x15;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x522D00
// Branching.
void Obj_00522D00::FUN_00522D00()
{
    if (unknown_AC != 0xA)
    {
        vf_122(0xA, 0);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x522D20
// Calls other functions.
void Obj_00522D20::FUN_00522D20()
{
    vf_122(5, 0);
}

// FUNCTION: GAMEMD 0x522D30
// True when vf_173() equals the constant at 0x7E1718.
bool InfantryClass::FUN_00522D30()
{
    if (this->vf_173() == DAT_007E1718) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x522E70
// Slot 137: a harvesting infantryman standing on tiberium takes up as much as its storage has room for
// (the amount per visit is capped), reports the type's harvest rate, and keeps harvesting. With no
// storage, or off the ore, it stands down and goes back to mission 5.
int InfantryClass::vf_137()
{
    if (this->Type->Storage == 0) {
        this->vf_342(0, 0, 0);
        this->vf_122(5, false);
        return 1;
    }
    CellClass* cell = this->vf_111();
    if (cell->IsLandType5() && this->vf_173() != DAT_007E1718) {
        if (this->SequenceAnim != 0x26) {
            this->vf_342(0x26, 0, 0);
        }
        int index = cell->GetContainedTiberiumIndex();
        int taken = cell->FUN_00480A80((int)(((float)this->Type->Storage - this->Tiberium.GetTotalAmount()) > DAT_007E2AC8
                                                 ? DAT_007E2AC8
                                                 : ((float)this->Type->Storage - this->Tiberium.GetTotalAmount())));
        if (taken > 0) {
            this->Tiberium.AddAmount((float)taken, index);
        }
        return this->Type->HarvestRate;
    }
    this->vf_342(0, 0, 0);
    this->vf_122(5, false);
    return 1;
}

// FUNCTION: GAMEMD 0x522FC0
bool InfantryClass::FUN_00522FC0()
{
    return this->vf_97() == 10;
}

// GLOBAL: GAMEMD 0x007E9A90 -- CLSID of TeleportLocomotionClass.
extern const CLSID DAT_007E9A90;

// FUNCTION: GAMEMD 0x522FE0
// Slot 322: the infantryman is moved to a coordinate by a teleport locomotor that piggybacks the current one.
bool InfantryClass::vf_322(CoordStruct where)
{
    if (IsInAir() || vf_88() || IsImmobilized || vf_117() || vf_118()) {
        return false;
    }
    Locomotor->MarkAllOccupationBits(0);
    vf_61(&where);
    FrozenStill = true;
    SetDestination(DAT_0087F7E8.FUN_00565730(&where), true);
    LocoCoord to = where;
    Locomotor->ForceImmediateDestination(to);
    LocomotorPtr teleport(DAT_007E9A90, 0, 7);
    IPiggybackPtr piggyback(teleport);
    if (DAT_0087F7E8.FUN_00565730(&where)->Flags & 0x100) {
        where.Z += DAT_00A8F234;
    }
    teleport->LinkToObject(this);
    piggyback->BeginPiggyback(Locomotor);
    Locomotor = teleport;
    IsImmobilized = true;
    ChronoDestCoords = where;
    SetDestination(DAT_0087F7E8.FUN_00565730(&where), true);
    Locomotor->MarkAllOccupationBits(0);
    return true;
}

// FUNCTION: GAMEMD 0x523250
// Slot 44: while riding in an open-topped transport, take the transporter's coordinate offset by this
// passenger's (negated) position in its cargo list; otherwise use the base TechnoClass answer.
CoordStruct InfantryClass::vf_44(int a1, CoordStruct a2)
{
    if (InOpenToppedTransport && Transporter) {
        int index = ((TechnoClass*)Transporter)->Passengers.IndexOf((FootClass*)this);
        if (index) {
            CoordStruct zero = { 0, 0, 0 };
            return ((TechnoClass*)Transporter)->vf_44(-index, zero);
        }
    }
    CoordStruct zero = { 0, 0, 0 };
    return TechnoClass::vf_44(a1, zero);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5232F0
// Vtable slot 12 of InfantryClass (RTTI). Returns a constant.
int InfantryClass::vf_12()
{
    return 0x6F0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00523300
HRESULT __stdcall InfantryClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9680;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x523340
// Vtable slot 11 of InfantryClass (RTTI). Returns a constant.
int InfantryClass::vf_11()
{
    return 0xF;
}

// The infantry as the receiver of its scalar deleting destructor (slot 8, 0x523350).
struct Obj_00523350
{
    // FUNCTION: GAMEMD 0x517D90 (decl; reloc) -- the real destructor.
    void FUN_00517D90();
    // FUNCTION: GAMEMD 0x523350
    void* FUN_00523350(unsigned int flags);
};

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x523350
// Scalar deleting destructor: run the destructor, then free when bit 0 is set.
void* Obj_00523350::FUN_00523350(unsigned int flags)
{
    FUN_00517D90();
    if (flags & 1) {
        FUN_007C8B3D(this);
    }
    return this;
}

struct Obj_00523370 {
    IUnknown* unknown_00;
    Obj_00523370* FUN_00523370(IUnknown* p);
    Obj_00523370* FUN_005233A0(IUnknown* p);
};
// FUNCTION: GAMEMD 0x00523370
Obj_00523370* Obj_00523370::FUN_00523370(IUnknown* p)
{
    IUnknown* old = unknown_00;
    if (old != p) {
        unknown_00 = p;
        if (p)
            p->AddRef();
        if (old)
            old->Release();
    }
    return this;
}
// FUNCTION: GAMEMD 0x005233A0
Obj_00523370* Obj_00523370::FUN_005233A0(IUnknown* p)
{
    IUnknown* old = unknown_00;
    if (old != p) {
        unknown_00 = p;
        if (p)
            p->AddRef();
        if (old)
            old->Release();
    }
    return this;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x825560
extern const char DAT_00825560[] = "D:\\ra2mdpost\\Infantry.CPP";
// GLOBAL: GAMEMD 0x7E9680
extern const CLSID DAT_007E9680 = {0x0E272DC4, 0x9C0F, 0x11D1, {0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// END defined globals



// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E9AC0
extern const CLSID DAT_007E9AC0 = {0x92612C46, 0xF71F, 0x11D1, {0xAC, 0x9F, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// END defined globals
