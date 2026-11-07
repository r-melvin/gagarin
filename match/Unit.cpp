// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Unit.CPP. The name is the source-file string at 0x845964
//   in retail gamemd.exe v1.001, passed by the assert at 0x746bd4 inside this object's
//   code range (0x735180-0x746edf). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// The four remaining identity tests, ordered ascending by retail address.
//
// The two conditions have to sit in one `&&` with the `true` inline: split
// into two early-return `if`s the failure block is duplicated and the score
// drops to 18.2%.
//
//   cross-checked against YRpp.

#include "unit_class_should_crash_methods.h"

#include "deleting_dtor_sweep.h"
#include "winsock_interface_class.h"
#include "_layout/pipe.h"
#include "_layout/straw.h"

#include "same_object_test_sweep.h"

#include "trivial_tu258_methods.h"

#include <stdlib.h>
#include <wchar.h>
#include "unit_class_astar_attempt_methods.h"

#include "scenario_class_methods.h"
#include "unit_class_occupation_methods.h"
#include "_layout/map_0087f7e8.h"
#include "ui_display_chain.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "shared_constants_globals.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F5C28
extern const double DAT_007F5C28;
// GLOBAL: GAMEMD 0xB1CFD0
extern double DAT_00B1CFD0;
// GLOBAL: GAMEMD 0xB1D008
extern double DAT_00B1D008;
// GLOBAL: GAMEMD 0xB1D0A0
extern int DAT_00B1D0A0;
// GLOBAL: GAMEMD 0xB1D0A4
extern int DAT_00B1D0A4;
// GLOBAL: GAMEMD 0xB1D0A8
extern int DAT_00B1D0A8;
// GLOBAL: GAMEMD 0xB1D0AC
extern int DAT_00B1D0AC;
// GLOBAL: GAMEMD 0xB1D0B0
extern double DAT_00B1D0B0;



#include "_layout/unit_class.h"
#include "_layout/unit_type_class.h"
#include "_layout/building_type_class_layout.h"
#include "_layout/cell_class.h"
#include "_layout/house_class.h"
#include "_layout/house_type_class.h"
#include "frame_counter.h"
#include "_layout/ebolt_class.h"
#include "_layout/player_ptr_00a83d4c.h"
#include "_layout/tag_class.h"
#include "randomizer.h"
#include "_layout/rules_class.h"
#include "_layout/temporal_class.h"
#include "_layout/obj_004a1d30.h"
#include "_layout/object_type_class.h"
#include "weapon_type_class.h"
#include "_layout/team_class.h"
#include "_layout/overlay_type_class.h"
#include "_layout/anim_class.h"
#include "_layout/anim_type_class.h"
#include "terrain_type_class.h"
#include "cell_step_tables.h"
#include "_layout/infantry_class.h"
#include "_layout/infantry_type_class.h"
#include "_layout/building_class.h"
#include "_layout/unit_type_class.h"
#include "_layout/techno_type_class.h"
#include "_layout/spawn_manager_class.h"
// The mission control record (canonical view).
#include "mission_class_methods.h"
#include "_layout/fogged_object_class.h"
#include "loco_interfaces.h"
#include "bullet_type_class.h"
#include "_layout/bullet_class.h"
#include "whatami_dispatch_methods.h"
#include "mathtbl_init_shapes.h"
#include "_layout/voc_class.h"
#include "map_class_area_methods.h"
#include "vector_class.h"
#include "vector_class_operations.h"
#include "abstract_index_cast_sweep.h"

// GLOBAL: GAMEMD 0x8458B0 -- the stage of the visceroid animation for each of the eight facings.
extern int DAT_008458B0[8];
// GLOBAL: GAMEMD 0xA83D84 -- OverlayTypeClass::Array.Items.
extern OverlayTypeClass** DAT_00A83D84;
// GLOBAL: GAMEMD 0x8871E0 -- the rules.
extern RulesClass* DAT_008871E0;
// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- localised string lookup, label and flags in registers, file and line on the stack.
wchar_t* FUN_00734E60(const char* label, int flags, const char* file, int line);

// FUNCTION: GAMEMD 0x7DC720 (decl; reloc) -- the missing-pointer report of the smart-pointer dereference (E_POINTER).
void __stdcall FUN_007DC720(unsigned int hr);

// GLOBAL: GAMEMD 0xA8B230 -- the scenario.
extern ScenarioClass* DAT_00A8B230;

// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_007351B0()
{
    DAT_00B1D0B0 = DAT_00B1CFD0 / DAT_007F5C28;
}

// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_007351D0()
{
    DAT_00B1D008 = DAT_007E1718 / DAT_00B1D0B0;
}

// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00735350()
{
    DAT_00B1D0A8 = 0;
    DAT_00B1D0A0 = 0x80;
    DAT_00B1D0A4 = 0x80;
}


// The lookup as 0x735780 expands it: the probe key sits in a stack slot and is compared as the left operand.
template<>
inline IndexClass<int, AbstractClass*>::NodeElement* IndexClass<int, AbstractClass*>::SearchForNode(const int& id)
{
    if (IndexCount == 0) {
        return 0;
    }
    if (!IsSorted) {
        qsort(IndexTable, IndexCount, sizeof(NodeElement), Comparator);
        Archive = 0;
        IsSorted = true;
    }
    NodeElement node;
    node.ID = id;
    NodeElement* base = IndexTable;
    for (int count = IndexCount; count > 0; ) {
        int half = count / 2;
        NodeElement* mid = base + half;
        if (node.ID < mid->ID) {
            count = half;
        } else {
            if (mid->ID == node.ID) {
                return mid;
            }
            base = mid + 1;
            count = count - 1 - half;
        }
    }
    return 0;
}

// The removal shifts whole nodes down.
template<>
inline bool IndexClass<int, AbstractClass*>::RemoveIndex(const int& id)
{
    NodeElement* node = SearchForNode(id);
    if (node != 0) {
        int found = node - IndexTable;
        if (found != -1) {
            for (int i = found + 1; i < IndexCount; i++) {
                IndexTable[i - 1] = IndexTable[i];
            }
            IndexCount--;
            NodeElement zero;
            zero.ID = 0;
            zero.Data = 0;
            IndexTable[IndexCount] = zero;
            Archive = 0;
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x46B050 (decl; reloc) -- creates a bullet: projectile in ECX, target in EDX, then owner, damage,
// warhead, speed and the bright flag on the stack.
BulletClass* FUN_0046B050(BulletTypeClass* projectile, AbstractClass* target, TechnoClass* owner, int damage,
                          WarheadTypeClass* warhead, int speed, char bright);

// GLOBAL: GAMEMD 0xA8E9A0
extern char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0xA8E7AC -- nonzero suppresses the EVA line.
extern int DAT_00A8E7AC;
// GLOBAL: GAMEMD 0x8B4108
extern DynamicVectorClass<UnitClass*> DAT_008B4108;

// FUNCTION: GAMEMD 0x735780
// Releases the electric bolt, hands the house back its bookkeeping, frees the passengers,
// lets go of a carried flag, then leaves the unit list and the abstract index.
UnitClass::~UnitClass()
{
    if (ElectricBolt) {
        ElectricBolt->DetachOwner();
        ElectricBolt = 0;
    }
    if (DAT_00A8E9A0 && Type) {
        if (Owner->FUN_004F7870(Type, false, false) == -1) {
            Owner->RecheckTechTree = 1;
        }
        if (Team) {
            Team->LiberateMember(this, -1, 0);
            Team = 0;
        }
        Owner->RemoveTracking(this);
        if (!DAT_00A8E7AC && Passengers.FirstPassenger) {
            do {
                FootClass* passenger = Passengers.RemoveFirstPassenger();
                if (passenger) {
                    delete passenger;
                }
            } while (Passengers.FirstPassenger);
        }
        vf_53();
    }
    AnnounceExpiredPointer(1);
    DAT_008B4108.RemoveItem(this);
    AbstractIndex.RemoveIndex(vf_rtti_4());
    IsAlive = false;
}

// FUNCTION: GAMEMD 0x736990
// Keeps the turret and body facing in step with the target. A unit that has a target turns its
// turret to it (or to the body facing when the weapon's turret is locked); a turretless unit
// that stands still on the spot turns its body; a spinning turret keeps rotating; otherwise it
// follows the destination (or the body) once the guard delay has passed. Records whether the
// turret is still turning.
void UnitClass::FUN_00736990()
{
    DirStruct dir;
    if (Target && !unknown_bool_6AF) {
        DirStruct scratch;
        dir = *FUN_005F3DB0(&scratch, Target);
        if (Type->Turret) {
            WeaponStruct* weapon = GetPrimaryWeapon();
            if (FUN_0070E240(weapon) && !weapon->WeaponType->OmniFire) {
                if (weapon->TurretLocked) {
                    SecondaryFacing.SetDesired(*PrimaryFacing.FUN_004C93D0(&scratch));
                } else {
                    SecondaryFacing.SetDesired(dir);
                }
            }
        } else if (Type->SpeedType == 1 && !Destination) {
            if (Locomotor == 0) {
                FUN_007DC720(0x80004003);
            }
            if (!static_cast<ILocomotion*>(Locomotor)->IsMoving()) {
                if (PrimaryFacing.FUN_004C93D0(&scratch)->Raw == dir.Raw) {
                    PrimaryFacing.SetDesired(dir);
                }
            }
        }
    }
    if (Type->TurretSpins) {
        DirStruct scratch;
        int index = ((SecondaryFacing.FUN_004C93D0(&scratch)->Whole >> 7) + 1) >> 1 & 0xFF;
        dir.Raw = (unsigned short)((index + 8) << 8);
        SecondaryFacing.SetDesired(dir);
    } else {
        unknown_bool_6AF = 0;
        if (Type->Turret) {
            if (SecondaryFacing.IsRotating()) {
                if (!Type->TurretSpins) {
                    unknown_bool_6AF = SecondaryFacing.IsRotating();
                }
            } else if (!Target) {
                bool ready = true;
                if (CurrentFrame - LastFireBulletFrame < DAT_008871E0->GuardAreaTargetingDelay + 5) {
                    ready = false;
                }
                if (BunkerLinkedItem) {
                    ready = false;
                }
                if (!(static_cast<UnitTypeClass*>(Type)->IsSimpleDeployer && Deployed) && ready) {
                    DirStruct scratch;
                    WeaponStruct* weapon = GetPrimaryWeapon();
                    bool locked = FUN_0070E240(weapon) && weapon->TurretLocked;
                    if (Destination && !locked) {
                        if (!IsAttackedByLocomotor) {
                            SecondaryFacing.SetDesired(*FUN_005F3DB0(&scratch, Destination));
                        }
                    } else {
                        SecondaryFacing.SetDesired(*PrimaryFacing.FUN_004C93D0(&scratch));
                    }
                }
            }
        }
    }
    if (Type->Turret) {
        TurretIsRotating = SecondaryFacing.IsRotating();
    }
}

// The map singleton (GLOBAL 0x87F7E8), as far as the on-map test.
struct MapView_00736C10
{
    // FUNCTION: GAMEMD 0x568350 (decl; reloc) -- is the coordinate inside the map.
    bool FUN_00568350(const CoordStruct* where);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the map.
extern MapView_00736C10 MapInstance_00736C10;


// FUNCTION: GAMEMD 0x736C10
//
// A unit in the mode answered by slot 97 as 5 that has left the map while
// placed in the playfield: flag its team, run slots 232 and 62, and report
// that it was handled.
bool UnitClass::FUN_00736C10()
{
    if (vf_97() == 5) {
        CoordStruct where = this->Location;
        if (!MapInstance_00736C10.FUN_00568350(&where)) {
            if (this->IsInPlayfield) {
                if (this->Team) {
                    this->Team->Flag82 = true;
                }
                vf_232();
                vf_62();
                return true;
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x736CA0
void UnitClass::vf_265()
{
    UnitTypeClass* type = static_cast<UnitTypeClass*>(this->Type);
    if (!type->MobileFire) {
        if (this->Locomotor->IsMoving()) {
            if (this->ReloadTimer.GetTimeLeft() > 0) {
                this->ReloadTimer = CDTimerClass(this->ReloadTimer.GetTimeLeft() + 1);
            }
        }
    }

    TechnoClass::vf_265();
}

// FUNCTION: GAMEMD 0x736D50
bool UnitClass::vf_313()
{
    UnitTypeClass* type = static_cast<UnitTypeClass*>(this->Type);
    if (type->DeployToFire) {
        return true;
    }

    BuildingTypeClass* deploysInto = type->DeploysInto;
    if (!deploysInto || !deploysInto->TickTank) {
        return false;
    }

    if (this->Owner->IsControlledByHuman()) {
        return false;
    }

    AbstractClass* target = this->Target;
    if (!target) {
        return false;
    }

    IRTTITypeInfo* typeInfo = static_cast<IRTTITypeInfo*>(target);
    switch (typeInfo->vf_rtti_3()) {
    case 1:
        break;
    case 6:
    case 15:
        return false;
    default:
        return false;
    }

    CoordStruct location = this->Location;
    CellClass* cell = Map_0087F7E8.FUN_00565730(location);
    return cell->FUN_00487C10() ? true : false;
}

// FUNCTION: GAMEMD 0x736DF0
// Acts on the answer of slot 240 for the current target, then keeps the gattling stage and the turret
// animation frame in step. With nothing to shoot at only the gattling part runs.
void UnitClass::FUN_00736DF0()
{
    if (Target && vf_254(0)->WeaponType) {
        int weaponIndex = vf_185(Target);
        int action = vf_240(Target, weaponIndex, true);
        if ((action == 0 || action == 2) && vf_313()) {
            vf_122(0x10, false);
            return;
        }
        DirStruct scratch;
        DirStruct turretScratch;
        DirStruct bodyScratch;
        DirStruct again;
        switch (action) {
        case 5:
            if (CombatDamage(weaponIndex) < 0) {
                AbstractClass* victim = Target;
                if (victim && victim->Flags.unknown_14_1 && victim->vf_11() == 1) {
                    if (!(static_cast<ObjectClass*>(victim)->GetHealthPercentage() < DAT_008871E0->unknown_16F8)) {
                        vf_242(0);
                    }
                } else {
                    vf_242(0);
                }
            }
            break;
        case 0:
            if (!static_cast<UnitTypeClass*>(Type)->unknown_E10) {
                IsFiring = 0;
            }
            if (static_cast<UnitTypeClass*>(Type)->LargeVisceroid || static_cast<UnitTypeClass*>(Type)->SmallVisceroid) {
                int facing = (((FUN_005F3DB0(&scratch, Target)->Whole >> 12) + 1) >> 1) & 7;
                StageClass::Value = DAT_008458B0[facing];
                SetRate(5);
            }
            vf_243(Target, weaponIndex);
            break;
        case 2:
            if (!static_cast<UnitTypeClass*>(Type)->HasTurret && static_cast<UnitTypeClass*>(Type)->Turret) {
                SecondaryFacing.SetDesired(*FUN_005F3DB0(&turretScratch, Target));
            } else if (!Destination) {
                if (Locomotor == 0) {
                    FUN_007DC720(0x80004003);
                }
                if (!static_cast<ILocomotion*>(Locomotor)->IsMoving()) {
                    PrimaryFacing.SetDesired(*FUN_005F3DB0(&bodyScratch, Target));
                    SecondaryFacing.SetDesired(*PrimaryFacing.FUN_004C9470(&again));
                }
            }
            break;
        case 9:
            IsFiring = 0;
            if (TechnoClass::vf_234(Target, weaponIndex)) {
                vf_279(0);
            }
            break;
        case 8:
        case 11:
            IsFiring = 0;
            break;
        case 6:
            if (SpawnManager) {
                static_cast<SpawnManagerClass*>(SpawnManager)->ResetTarget();
            }
            break;
        }
        if (Type->IsGattling && (action == 0 || action == 3 || action == 2 || action == 4)) {
            FUN_0070DE70(1);
        } else if (vf_33()->IsGattling) {
            GattlingRateDown(1);
        }
        if (vf_33()->IsGattling) {
            if (FUN_0070DDF0() > 0) {
                TurretAnimFrame++;
            }
        } else if (action == 0 || action == 3) {
            TurretAnimFrame++;
        }
    } else {
        if (vf_33()->IsGattling) {
            GattlingRateDown(1);
        }
        if (vf_33()->IsGattling && FUN_0070DDF0() > 0) {
            TurretAnimFrame++;
        }
    }
}

// FUNCTION: GAMEMD 0x737180
// The visceroid's wander. Late in its stage count it re-rolls the stage; a still unit looks for
// a neighbouring small visceroid and calls it over, or else picks a free direction to step
// into, remembering it between calls.
void UnitClass::FUN_00737180()
{
    CellStruct here = vf_110();
    CellStruct ahead;
    if (StageClass::Value >= 0x5A) {
        if (StageClass::Value % 5 == 4) {
            StageClass::Value = DAT_00A8B230->unknown_0218.RandomRanged(0, 2) * 30;
            SetRate(1);
        }
        return;
    }
    if (StageClass::Value % 30 == 29) {
        StageClass::Value = DAT_00A8B230->unknown_0218.RandomRanged(0, 2) * 30;
    }
    SetRate(1);
    if (Locomotor == 0) {
        FUN_007DC720(0x80004003);
    }
    if (static_cast<ILocomotion*>(Locomotor)->IsMoving()) {
        return;
    }
    bool called = false;
    if (static_cast<UnitTypeClass*>(Type)->SmallVisceroid) {
        int dir = 7;
        for (int i = 0; i < 8; i++) {
            dir = (dir + 1) & 7;
            ahead = here + DAT_0089F688[dir & 7];
            ObjectClass* other = DAT_0087F7E8.FUN_005657A0(&ahead)->FirstObject;
            if (other && other->vf_11() == 1 && static_cast<UnitClass*>(other)->Type->SmallVisceroid) {
                if (!static_cast<UnitClass*>(other)->Destination && !static_cast<UnitClass*>(other)->Target) {
                    static_cast<UnitClass*>(other)->SetDestination(this, true);
                }
                called = true;
                break;
            }
        }
    }
    if (!called) {
        if (Destination || Target) {
            return;
        }
        int wander;
        if (unknown_int_6D4 != -1 && DAT_00A8B230->unknown_0218.RandomRanged(0, 2)) {
            wander = unknown_int_6D4;
        } else {
            wander = DAT_00A8B230->unknown_0218.RandomRanged(0, 7);
            unknown_int_6D4 = wander;
        }
        ahead = here + DAT_0089F688[wander & 7];
        CellClass* cell = DAT_0087F7E8.FUN_005657A0(&ahead);
        if (!vf_107(cell, wander, GetCellLevel(), (int)DAT_0087F7E8.FUN_005657A0(&here), true)) {
            SetDestination(cell, true);
            return;
        }
    }
    unknown_int_6D4 = -1;
}

// FUNCTION: GAMEMD 0x737BA0
// Place the unit on the map, face it, then restart its stage timer; a unit that is
// neither small nor large visceroid starts at a random stage.
bool UnitClass::vf_54(const CoordStruct& coord, int a2)
{
    if (FootClass::vf_54(coord, a2)) {
        DirStruct dir;
        dir.Raw = (unsigned short)((a2 & 0xFF) << 8);
        SecondaryFacing.FUN_004C9300(&dir);
        if (Cloakable && !IsInPlayfield) {
            CloakState = 2;
        }
        UnitTypeClass* type = static_cast<UnitTypeClass*>(this->Type);
        if (!type->SmallVisceroid && !type->LargeVisceroid) {
            StageClass::Value = 0;
            SetRate(0);
            return true;
        }
        StageClass::Value = DAT_00A8B230->unknown_0218.RandomRanged(0, 0x1D);
        SetRate(1);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x7393B0
// Empty function.
void __cdecl FUN_007393B0()
{
}


// A house seen only through the dropped-flag handler the unit calls when it lets go of a flag.
struct UnitFlagHouse
{
    // FUNCTION: GAMEMD 0x4FBF60 (decl; reloc) -- put the dropped flag down at a cell.
    void FUN_004FBF60(const CellStruct& cell, int closeTo);
};
// GLOBAL: GAMEMD 0xA8022C -- HouseClass::Array.Items.
extern UnitFlagHouse** DAT_00A8022C;


// FUNCTION: GAMEMD 0x738890
// Maps the object kind in question to a target class, then defers to the foot test unless
// the unit is aimed at itself in a way that makes no sense or is berserk.
bool UnitClass::vf_81(int a1, ObjectClass* a2, int a3)
{
    int type = vf_29(a2, a3);
    int m = a1;
    if (a1 != type) {
        m = type;
        switch (type) {
        case 3:
            m = 1;
            goto done;
        case 9:
        case 0x10:
            goto five;
        }
    }
    if (m == 0x1b || m == 0x1d) {
five:
        m = 5;
    }
done:
    if ((a2 == this) && (m == 2 || m == 5)) {
        return false;
    }
    if (Berzerk) {
        return false;
    }
    return FootClass::vf_81(m, a2, a3);
}

// FUNCTION: GAMEMD 0x738910
// PARTIAL: 85.4% -- identical instruction multiset; retail keeps the third and fourth
// arguments in EBX/EDI the other way round (variants with locals and nested ifs tried).
// Refuses when deployed and the unit's own check says 2, or when berserk.
bool UnitClass::vf_80(int mode, CellStruct* cell, int a3, int a4)
{
    if (Deployed && vf_28(cell, 0, a4) == 2) {
        return false;
    }
    if (Berzerk) {
        return false;
    }
    return FootClass::vf_80(mode, cell, a3, a4);
}


// The centre of a cell on the ground, as retail inlined it for the position test.
inline CoordStruct CellCenter_00738970(const CellStruct& cell)
{
    CoordStruct center;
    center.X = cell.X * 256 + 128;
    center.Y = cell.Y * 256 + 128;
    center.Z = 0;
    return center;
}

// FUNCTION: GAMEMD 0x738970
// Slot 289 (EnterIdleMode): after FootClass's pass, a unit with nothing queued picks a mission from its
// target, destination, type and owner, and switches to it.
bool UnitClass::EnterIdleMode(bool initial, bool a2)
{
    bool result = FootClass::EnterIdleMode(initial, a2);
    if (vf_299()) {
        return result;
    }
    if (vf_97() == 0x1C) {
        return result;
    }
    if (LocomotorTarget) {
        FUN_0070FEE0(true);
    }
    if (vf_97() == 2 && !Destination) {
        CoordStruct center = CellCenter_00738970(vf_110());
        CoordStruct here = Location;
        if (here.X == center.X && here.Y == center.Y && here.Z == center.Z) {
            vf_157(3);
        }
    }
    FUN_004DA030();
    int mission;
    if (Destination) {
        mission = 2;
    } else if (Type->Harvester || Type->Weeder) {
        if (HasAnyLink()) {
            return result;
        }
        if (vf_97() == 0xA) {
            return result;
        }
        if (QueuedMission == 0xA) {
            return result;
        }
        mission = 0xA;
        if (!initial && Owner->IsControlledByHuman()) {
            CoordStruct location = Location;
            int landType = Map_0087F7E8.FUN_00565730(location)->LandType;
            if (landType != (Type->Harvester ? 5 : 0xB)) {
                mission = 5;
            }
        }
        vf_242(0);
        SetDestination(0, true);
    } else if (!IsArmed()) {
        if (Spawned && Type->Passengers > 0 && Passengers.FirstPassenger && !Team) {
            mission = 0x10;
        } else {
            if (IsDeploying) {
                return result;
            }
            if (CurrentMission == 0x10 && Type->DeploysInto) {
                return result;
            }
            if (CurrentMission == 0xB) {
                return result;
            }
            mission = 5;
            vf_242(0);
            SetDestination(0, true);
        }
    } else {
        if (vf_97() == 5) {
            return result;
        }
        if (vf_97() == 0xB) {
            return result;
        }
        if (vf_97() != -1) {
            if (FUN_005B3A00()->Paralyzed) {
                return result;
            }
            if (FUN_005B3A00()->Zombie) {
                return result;
            }
        }
        if (Owner->IQLevel2 < DAT_008871E0->unknown_1440 && !FUN_0070D0D0(0x10) && !Type->DefaultToGuardArea) {
            mission = 5;
        } else if (Team || SlaveOwner || SlaveManager) {
            mission = 5;
        } else {
            mission = 0xB;
        }
    }
    if (mission == 0xB && BunkerLinkedItem) {
        mission = 5;
    }
    TechnoClass* link = FUN_0065AD30(0);
    if (CurrentMission == 7 && link && link->vf_11() == 6
        && ((BuildingClass*)link->KindCast_00459F40(6))->Type->Bunker && vf_111()->GetBuilding() != link) {
        return result;
    }
    if (CurrentMission == 0x19 || CurrentMission == 0xB || CurrentMission == 0x10 || CurrentMission == 9) {
        return result;
    }
    vf_122(mission, false);
    return result;
}

// The unit's slave manager, as far as the two calls the mission delay makes.
struct UnitSlaveManagerView
{
    // FUNCTION: GAMEMD 0x6B1020 (decl; reloc) -- whether the manager should wake now.
    bool FUN_006B1020();
    // FUNCTION: GAMEMD 0x6B0CC0 (decl; reloc) -- wakes the manager.
    void FUN_006B0CC0();
};

// GLOBAL: GAMEMD 0xB1CFB8 -- the cell passed with tag events when there is none.
extern CellStruct DAT_00B1CFB8;


// FUNCTION: GAMEMD 0x739AC0
// Steps a simple deployer through its deploy animation: a grounded unit starts the animation (or
// is deployed at once when its type has none), the running animation is followed to its last
// frame, and the deploy sound is played at the unit's position.
void UnitClass::FUN_00739AC0()
{
    if (Type->IsSimpleDeployer) {
        if (vf_114() > 0 && !vf_33()->DeployToLand) {
            return;
        }
        if (!Deployed) {
            if (!InAir && vf_114() > 0) {
                InAir = true;
            }
            if (Deploying && DeployAnim) {
                AnimTypeClass* animType = static_cast<AnimClass*>(DeployAnim)->Type;
                if (StageClass::Value >= animType->End + animType->Start - 1) {
                    Deployed = true;
                    Deploying = false;
                }
            } else if (!InAir) {
                if (Type->DeployingAnim != 0) {
                    if (DeployAnim == 0) {
                        AnimClass* anim = new AnimClass(Type->DeployingAnim, CoordStruct(Location), 0, 1, 0x600, 0, false);
                        DeployAnim = anim;
                        anim->FUN_00424B50(this);
                        static_cast<AnimClass*>(DeployAnim)->LightConvert = vf_121();
                    }
                    StageClass::Value = static_cast<AnimClass*>(DeployAnim)->Type->Start;
                    SetRate(static_cast<AnimClass*>(DeployAnim)->Type->Rate);
                    Deploying = true;
                } else {
                    Deployed = true;
                }
            }
            if (vf_33()->DeploySound != -1) {
                CoordStruct where = Location;
                VocClass::PlayAt(vf_33()->DeploySound, where, 0);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x739CD0
// Steps a deployed unit through its undeploy animation: the animation is started, followed to
// its last frame, and then the unit leaves its deployed state and (when its type lands) heads for
// the nearest free cell; the undeploy sound is played at the unit's position.
void UnitClass::FUN_00739CD0()
{
    if (Deployed) {
        if (Undeploying && DeployAnim) {
            AnimTypeClass* animType = static_cast<AnimClass*>(DeployAnim)->Type;
            if (StageClass::Value >= animType->End + animType->Start - 2) {
                Deployed = false;
                Undeploying = false;
                if (vf_33()->DeployToLand) {
                    SetDestination(DAT_0087F7E8.FUN_005657A0(NearbyLocation(this)), true);
                }
            }
        } else if (Type->DeployingAnim != 0) {
            if (DeployAnim == 0) {
                AnimClass* anim = new AnimClass(Type->DeployingAnim, CoordStruct(Location), 0, 1, 0x600, 0, true);
                DeployAnim = anim;
                anim->FUN_00424B50(this);
                static_cast<AnimClass*>(DeployAnim)->LightConvert = vf_121();
            }
            StageClass::Value = static_cast<AnimClass*>(DeployAnim)->Type->Start;
            SetRate(static_cast<AnimClass*>(DeployAnim)->Type->Rate);
            Undeploying = true;
        } else {
            Deployed = false;
        }
        if (vf_49()) {
            vf_284();
        }
        if (vf_33()->UndeploySound != -1) {
            CoordStruct where = Location;
            VocClass::PlayAt(vf_33()->UndeploySound, where, 0);
        }
    }
}

// FUNCTION: GAMEMD 0x73B0B0
// Refuses while the tethered contact (a building doing its unload or deploy changes) is busy;
// otherwise the object handling, without the third argument.
bool UnitClass::vf_65(RectangleStruct* rect, bool force, int a3)
{
    if (IsTether) {
        TechnoClass* contact = FUN_0065AD40(0);
        if (contact->vf_11() == 6 && (contact->vf_97() == 0x10 || contact->QueuedMission == 0x10)) {
            if (contact->UnloadTimer.FUN_004A5110() || contact->UnloadTimer.FUN_004A5130() ||
                contact->UnloadTimer.FUN_004A51B0() || contact->UnloadTimer.FUN_004A51D0()) {
                return false;
            }
        }
    }
    return ObjectClass::vf_65(rect, force, 0);
}




// FUNCTION: GAMEMD 0x73D450
// One harvesting step on the cell underfoot: a weeder clears the growth for one unit of
// storage, a harvester takes what fits; either restarts the stage timer at the
// harvest rate. Fails (and rests the timer) when it is not harvesting here.
bool UnitClass::FUN_0073D450()
{
    CoordStruct location = this->Location;
    CellClass* cell = Map_0087F7E8.FUN_00565730(location);
    if (Destination) {
        return true;
    }
    if (Type->Harvester && vf_173() < DAT_007E1718 && cell->LandType == 5) {
        if (Type->Weeder) {
            cell->FUN_00486E30();
            Tiberium.AddAmount(1.0f, 0);
            StageClass::Value = 0;
            SetRate(DAT_008871E0->HarvesterLoadRate * 3);
            return true;
        }
        int index = cell->GetContainedTiberiumIndex();
        int taken = cell->FUN_00480A80((int)((float)Type->Storage - Tiberium.GetTotalAmount() > 1.0f
                                                 ? 1.0f
                                                 : (float)Type->Storage - Tiberium.GetTotalAmount()));
        if (taken > 0) {
            Tiberium.AddAmount((float)taken, index);
            StageClass::Value = 0;
            SetRate(DAT_008871E0->HarvesterLoadRate);
            return true;
        }
        return false;
    }
    StageClass::Value = 0;
    SetRate(0);
    return false;
}

// FUNCTION: GAMEMD 0x73EFC0
// A unit whose type deploys into something waits out the mission rate plus a little random
// time, advancing the deploy step first when the type is a listed one, is aiming at something
// or is player controlled; any other unit takes the foot delay.
int UnitClass::vf_138()
{
    BuildingTypeClass* deploysInto = static_cast<UnitTypeClass*>(this->Type)->DeploysInto;
    if (deploysInto) {
        RulesClass* rules = DAT_008871E0;
        bool listed = false;
        for (int i = 0; i < rules->list_08AC.Count; i++) {
            if (rules->list_08AC.Items[i] == deploysInto) {
                listed = true;
                break;
            }
        }
        if (listed || this->Target || Owner->IsControlledByHuman()) {
            switch (MissionStatus) {
            case 0:
                if (FUN_00738D30() && FUN_007393C0())
                    MissionStatus = 1;
                break;
            case 1:
                if (!IsDeploying)
                    MissionStatus = 0;
                break;
            }
            int delay = (int)(FUN_005B3A00()->Rate * 900.0);
            return delay + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
        }
    }
    return FootClass::vf_138();
}

// FUNCTION: GAMEMD 0x7404B0
// What the player's unit can do at a cell, as an action code: only a unit its house's player
// controls answers. A healing weapon over a friendly occupant turns 5 into 0x3B; a harvester
// or weeder may not enter what it cannot work, ore or gems on a cell with the wrong
// overlay; a deployer standing deployed refuses the rest.
int UnitClass::vf_28(CellStruct* cell, char a2, char a3)
{
    if (!Owner->IsControlledByCurrentPlayer()) {
        return 0;
    }
    CellClass* target = DAT_0087F7E8.FUN_005657A0(cell);
    int action = FootClass::vf_28(cell, a2, a3);
    if (CombatDamage(-1) < 0 && Owner->IsControlledByCurrentPlayer() && action == 5) {
        action = 0x3B;
    }
    int overlay = -1;
    if (a2 && (DAT_00A8B230->unknown_0000 & 0x1000) && target->FoggedObjects) {
        DynamicVectorClass<FoggedObjectClass*>* fogged = target->FoggedObjects;
        for (int i = 0; i < fogged->Count; i++) {
            FoggedObjectClass* object = fogged->Items[i];
            if (object->unknown_74 && object->unknown_30 == 0x14) {
                overlay = object->unknown_24;
            }
        }
    }
    CoordStruct coord;
    coord.X = cell->X * 256 + 128;
    coord.Y = cell->Y * 256 + 128;
    coord.Z = 0;
    coord.Z = DAT_0087F7E8.FUN_00578080(&coord);
    if (DAT_0087F7E8.FUN_00565730(&coord)->Flags & 0x100) {
        coord.Z += DAT_00B1D0AC;
    }
    bool moveCheck = false;
    if (!DAT_0087F7E8.IsLocationShrouded(coord)) {
        if (action == 1) {
            moveCheck = true;
            if (target->LandType == 5
                || (overlay != -1 && DAT_00A83D84[overlay]->Tiberium && a2)) {
                if (static_cast<UnitTypeClass*>(Type)->Harvester) {
                    return 6;
                }
            }
            if (target->LandType == 0xB || (overlay == 0x7E && target->OverlayData >= 0x30 && a2)) {
                if (static_cast<UnitTypeClass*>(Type)->Weeder) {
                    return 6;
                }
            }
            if (target->LandType == 5
                || (overlay != -1 && DAT_00A83D84[overlay]->Tiberium && a2)) {
                if (Type->ResourceDestination && Type->ResourceGatherer) {
                    return 6;
                }
            }
        }
    } else if (action == 1) {
        moveCheck = true;
    }
    if (moveCheck) {
        if (DAT_0087F7E8.FUN_005657A0(cell)->InRange()) {
            return DAT_0087F7E8.FUN_005657A0(cell)->FUN_00484F10(this) ? 0x23 : 0x24;
        }
        if (Deployed || Deploying || Undeploying) {
            action = 0;
        }
    }
    if (Owner->IsControlledByCurrentPlayer() && static_cast<UnitTypeClass*>(Type)->IsSimpleDeployer && Deployed) {
        if (action == 1) {
            action = 2;
        } else if (action == 5) {
            if (Type->DeployFire) {
                CoordStruct at;
                at.X = cell->X * 256 + 128;
                at.Y = cell->Y * 256 + 128;
                at.Z = 0;
                if (vf_89(at, vf_185(0))) {
                    if (!vf_196()) {
                        action = 0;
                    }
                    return action;
                }
            }
            action = 2;
        }
    } else if (action == 5) {
        if (!vf_196()) {
            action = 0;
        }
    }
    return action;
}

// FUNCTION: GAMEMD 0x740810
// Mission rate for a unit that works or serves: wakes a due slave manager, sends a
// harvester or weeder to its work, and lets a deployer that is allowed to build
// deploy; anything else takes the foot delay.
int UnitClass::vf_135()
{
    if (SlaveManager && DAT_008871E0->SlaveMinerKickFrameDelay + CurrentMissionStartTime < CurrentFrame) {
        if (static_cast<UnitSlaveManagerView*>(SlaveManager)->FUN_006B1020()) {
            static_cast<UnitSlaveManagerView*>(SlaveManager)->FUN_006B0CC0();
            int delay = (int)(FUN_005B3A00()->Rate * 900.0);
            return delay + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
        }
    }
    if (Type->Harvester || Type->Weeder) {
        if (!Owner->IsControlledByHuman()) {
            for (int i = 0; i < Type->Dock.Count; i++) {
                if (Owner->OwnedBuildingTypes.FUN_0049FAE0(Type->Dock.Items[i]->ArrayIndex) > 0) {
                    if (Type->Harvester && Owner->IsTiberiumShort) {
                        break;
                    }
                    vf_122(10, false);
                    return 1;
                }
            }
        } else if (Type->Teleporter) {
            CellClass* cell = vf_111();
            for (int i = 0; i < 8; i++) {
                BuildingClass* building = cell->GetNeighbourCell(i)->GetBuilding();
                if (building && building->Type->Refinery && building->Owner == Owner) {
                    vf_122(10, false);
                    return 1;
                }
            }
            if (vf_173() == DAT_007E1718 && Locomotor->IsMoving()) {
                vf_122(10, false);
                return 1;
            }
        }
    }
    BuildingTypeClass* deploysInto = Type->DeploysInto;
    if (deploysInto) {
        RulesClass* rules = DAT_008871E0;
        bool listed = false;
        for (int i = 0; i < rules->list_08AC.Count; i++) {
            if (rules->list_08AC.Items[i] == deploysInto) {
                listed = true;
                break;
            }
        }
        if (listed && Owner->AutoBaseBuilding && !Owner->IsControlledByHuman()) {
            vf_122(0x10, false);
            int delay = (int)(FUN_005B3A00()->Rate * 900.0);
            return delay + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
        }
    }
    if (Type->Weeder && unknown_bool_6B8) {
        unknown_bool_6B8 = 0;
        vf_122(10, false);
    }
    return FootClass::vf_135();
}

// FUNCTION: GAMEMD 0x740A90
int UnitClass::vf_139()
{
    IsHarvesting = 0;
    if (Deployed || Deploying || Undeploying) {
        vf_122(5, false);
        return 1;
    }
    if (!UnloadTimer.FUN_004A51D0()) {
        UnloadTimer.StartTimer10(static_cast<UnitTypeClass*>(this->Type)->DeployTime);
    }
    return FootClass::vf_139();
}

// FUNCTION: GAMEMD 0x740B10
int UnitClass::vf_151()
{
    IsHarvesting = 0;
    if (!UnloadTimer.FUN_004A51D0()) {
        UnloadTimer.StartTimer10(static_cast<UnitTypeClass*>(this->Type)->DeployTime);
    }
    return FootClass::vf_151();
}

// FUNCTION: GAMEMD 0x740DF0  (__thiscall)
// Bind this unit to a house's flag (capture-the-flag). Only succeeds when a real
// house is given and no flag is already attached; then redraw and report true.
bool UnitClass::FlagAttach(int houseIndex)
{
    if (houseIndex != -1 && FlagHouseIndex == -1)
    {
        FlagHouseIndex = houseIndex;
        vf_73(2);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x740E20  (__thiscall)
// Detach the flag this unit was carrying, if any; redraw and report true.
bool UnitClass::FlagRemove()
{
    if (FlagHouseIndex != -1)
    {
        FlagHouseIndex = -1;
        vf_73(2);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x740E50
// Tail-forwards to another function. Vtable slot 174 of UnitClass (RTTI).
void FUN_00740E50(Obj_00740E50* a1, int a2)
{
    FUN_00708C30(a1, a2);
}

// FUNCTION: GAMEMD 0x740E60
void UnitClass::FUN_00740E60()
{
    UnloadTimer.StartTimer10(static_cast<UnitTypeClass*>(this->Type)->DeployTime);
}

// FUNCTION: GAMEMD 0x740E80  (__thiscall)
// If the unit is not in motion (per its locomotor) and the door-pending flag is
// clear, begin the door transition by handing the unit type's door-open angle to
// the unload timer. The locomotor is a COM smart pointer, so the dereference
// carries the inlined NULL-guard that raises E_POINTER.
void UnitClass::APCOpenDoor()
{
    if (!this->Locomotor->IsMoving() && !this->unknown_bool_6AF)
    {
        reinterpret_cast<DoorTimer*>(&this->UnloadTimer)->Start(
            *reinterpret_cast<double*>(reinterpret_cast<char*>(this->Type) + 0x3C8));
    }
}

// FUNCTION: GAMEMD 0x740EE0
// Tail-forwards to another function. Vtable slot 195 of UnitClass (RTTI).
void FUN_00740EE0(Obj_00740EE0* a1, int a2)
{
    FUN_00707D20(a1, a2);
}

// FUNCTION: GAMEMD 0x740EF0
// Drops out of harvesting: asks the radio contact to stand down or goes idle, then waits the
// mission rate.
int UnitClass::vf_147()
{
    void* contact = vf_330(reinterpret_cast<DynamicVectorClass<AbstractClass*>*>((char*)DAT_008871E0 + 0x850), 0, 0);
    IsHarvesting = false;
    if (contact == 0) {
        if (vf_330(reinterpret_cast<DynamicVectorClass<AbstractClass*>*>((char*)DAT_008871E0 + 0x850), 0, 1)) {
            EnterIdleMode(false, true);
        }
    } else if (vf_158(2, static_cast<RadioClass*>(contact)) == 1) {
        vf_122(7, false);
        return 1;
    }
    return (int)(FUN_005B3A00()->Rate * 900.0);
}

// FUNCTION: GAMEMD 0x740F80
// Turret facing when the type has a turret flag, else the base choice.
DirStruct UnitClass::vf_194()
{
    UnitTypeClass* type = static_cast<UnitTypeClass*>(this->Type);
    if (type->bools_C8C[0x15]) {
        return SecondaryFacing.FUN_004C93D0();
    }
    return TechnoClass::vf_194();
}

// FUNCTION: GAMEMD 0x740FD0
// Why this unit cannot use the weapon on the target, as a result code: the foot answer wins
// when non-zero; a dying unit answers 6, one with launching spawns 10, one held by a rocker
// 5, a deployer that has to deploy first 11; a unit that has to stop to fire answers 7,
// and a turret that is not facing the target within half a quadrant (or a full one for a
// homing projectile) answers 2.
int UnitClass::vf_240(AbstractClass* target, int a2, bool a3)
{
    if (DeathFrameCounter >= 0) {
        return 6;
    }
    if (SpawnManager && static_cast<SpawnManagerClass*>(SpawnManager)->CountLaunchingSpawns()) {
        return 10;
    }
    if (DirectRockerLinkedUnit) {
        return 5;
    }
    int result = TechnoClass::vf_240(target, a2, a3);
    if (result == 0 || result == 2) {
        CoordStruct location = this->Location;
        CellClass* cell = Map_0087F7E8.FUN_00565730(location);
        bool flag = cell->FUN_00487C10();
        if (Type->DeployToFire && vf_313() && !flag) {
            return 11;
        }
    }
    if (result == 0) {
        if (IsTether) {
            if (FUN_0065AD40(0)->vf_11() == 6) {
                return 6;
            }
        }
        WeaponTypeClass* weapon = vf_254(a2)->WeaponType;
        if (CombatDamage(-1) < 0) {
            ObjectClass* object = (ObjectClass*)FUN_0040DD20((WhatAmIHolder*)target);
            if (!object || !object->vf_32() || !(object->GetHealthPercentage() < DAT_008871E0->unknown_16F8)) {
                return 5;
            }
        }
        if (!Type->MobileFire && Destination) {
            return 7;
        }
        if (!weapon->FireWhileMoving) {
            if (!Type->BalloonHover && Destination) {
                return 7;
            }
            if (Type->BalloonHover) {
                if (Locomotor == 0) {
                    FUN_007DC720(0x80004003);
                }
                if (static_cast<ILocomotion*>(Locomotor)->IsMovingNow()) {
                    return 7;
                }
            }
        }
        if ((weapon->UseSparkParticles || weapon->UseFireParticles) && Destination) {
            return 7;
        }
        if (TemporalImUsing && Destination) {
            return 7;
        }
        if (!IsFiring && unknown_bool_6AF && !weapon->Projectile->ROT) {
            return 4;
        }
        if (!weapon->OmniFire && !Type->LargeVisceroid && !Type->SmallVisceroid) {
            DirStruct scratch;
            DirStruct* facing;
            if (Type->Turret) {
                facing = SecondaryFacing.FUN_004C93D0(&scratch);
            } else {
                facing = PrimaryFacing.FUN_004C93D0(&scratch);
            }
            DirStruct current = *facing;
            int limit = (weapon->Projectile->ROT != 0 ? 16 : 8);
            DirStruct* toTarget = FUN_005F3DB0(&scratch, target);
            short diff = (short)(current.Raw - toTarget->Raw);
            if (abs((short)(limit << 8)) < abs(diff)) {
                return 2;
            }
        }
        if (Locomotor == 0) {
            FUN_007DC720(0x80004003);
        }
        int fromLocomotor = static_cast<ILocomotion*>(Locomotor)->CanFire();
        if (fromLocomotor != 0) {
            return fromLocomotor;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x741340
// Slot 243 (fire): when the weapon is ready, fires through TechnoClass, then restarts the reload
// timer of a magazine unit, picks the firing-frame countdown and starts a scalable bullet.
BulletClass* UnitClass::vf_243(AbstractClass* target, int a2)
{
    BulletClass* result = 0;
    WeaponTypeClass* weapon = vf_254(a2)->WeaponType;
    if (!weapon) {
        return 0;
    }
    bool synced = false;
    if (a2 == 0) {
        int phase = CurrentBurstIndex % weapon->Burst;
        int syncFrame;
        if (phase < 2) {
            syncFrame = Type->FiringSyncFrame[phase];
        } else {
            syncFrame = -1;
        }
        if (CurrentFiringFrame == -1 || syncFrame == -1) {
            synced = false;
        } else {
            synced = true;
        }
    }
    if (vf_240(target, a2, true) == 0) {
        result = TechnoClass::vf_243(target, a2);
        if (result) {
            int ammo = Type->Ammo;
            if (ammo > 0 && Ammo < ammo && !Type->ManualReload) {
                StartReloading();
            }
            if (!synced && Type->FiringFrames > 0) {
                CurrentFiringFrame = Type->FiringFrames * 2 - 1;
            }
            if (result->Type->Scalable) {
                result->InitScalable();
            }
            if (Type->DisguiseWhenStill) {
                DisguiseBlinkTimer = CDTimerClass(weapon->DisguiseFakeBlinkTime);
            }
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x741490
// Member getter (dword). Vtable slot 34 of UnitClass (RTTI).
ObjectTypeClass* UnitClass::vf_34()
{
    return Type;
}

// FUNCTION: GAMEMD 0x7414A0
// Fraction of the harvester's capacity that is full; zero for non-harvesters.
double UnitClass::vf_173()
{
    UnitTypeClass* type = static_cast<UnitTypeClass*>(this->Type);
    if (!type->Harvester && !type->Weeder) {
        return GG_ZERO;
    }
    return (double)Tiberium.GetTotalAmount() / static_cast<UnitTypeClass*>(this->Type)->Storage;
}

// GLOBAL: GAMEMD 0xB1CFE8 -- the all-zero coordinate.
extern MathTblZero3 DAT_00B1CFE8;

// Null-safe casts of a target pointer, used by slot 335 (0x7414E0). Retail tests the pointer again
// ahead of each flag test; written inline as a ternary the second test folds away (9.4% and 62.3%).
static inline ObjectClass* TestAsTechno(AbstractClass* a)
{
    if (a == 0) {
        return 0;
    }
    return a->Flags.IsTechno ? static_cast<ObjectClass*>(a) : 0;
}

static inline bool TestIsObject(AbstractClass* a)
{
    return a != 0 && a->Flags.unknown_14_1;
}

static inline ObjectClass* TestAsObject(AbstractClass* a)
{
    if (a == 0) {
        return 0;
    }
    return a->Flags.unknown_14_1 ? static_cast<ObjectClass*>(a) : 0;
}

// FUNCTION: GAMEMD 0x7414E0
// PARTIAL: 96.4% - identical instruction multiset; retail keeps the type pointer in EDX and the target in EAX
// across the hover-attack test, this build uses ECX/EAX and ECX (5 instructions differ by register only).
// Slot 335 (the crush check of the idle pass): a unit that can crush the thing it is aiming at,
// and has the range to do so, drives over it instead of firing; otherwise the foot pass runs.
int UnitClass::vf_335(bool a1)
{
    bool crush = false;
    if (!Owner->IsControlledByHuman() && Target && !Destination) {
        ObjectClass* techno = TestAsTechno(Target);
        if (Type->Crusher || FUN_0070D0D0(0x11)) {
            if (FUN_005F6360(Target) < DAT_008871E0->Crush && techno && techno->IsCrushable(this)) {
                if (Type->AutoCrush || !Owner->IsControlledByHuman()) {
                    crush = true;
                }
            }
        }
    }
    if (!crush) {
        if (Type->BalloonHover) {
            WeaponTypeClass* weapon = vf_254(vf_185(Target))->WeaponType;
            if (weapon && weapon->Projectile && weapon->Projectile->Vertical) {
                if (!a1) {
                    SetDestination(Target, true);
                }
                return (int)Target;
            }
        }
        if (Type->OmniCrusher && Target && (!Owner->IsHumanPlayer || !ShouldLoseTargetNow) && TestIsObject(Target)) {
            if (TestAsObject(Target)->IsCrushable(this)) {
                crush = true;
            }
        }
    }
    if (crush) {
        if (!a1) {
            SetDestination(Target, true);
        }
        return (int)Target;
    }
    return FootClass::vf_335(false);
}

// FUNCTION: GAMEMD 0x7416A0
// A crusher driving over a cell: with the cell argument set it only leaves the track marks
// where something occupies the cell; otherwise it crushes what is crushable there, an
// infantry thief aimed at this unit steals it instead, and a crusher that took something
// down wakes up and starts to rock.
void UnitClass::vf_333(int a1, int a2)
{
    CellClass* cell = DAT_0087F7E8.FUN_005657A0((CellStruct*)a1);
    bool onBridge = false;
    if (cell->Flags & 0x100) {
        if (OnBridge) {
            onBridge = true;
        } else {
            CellStruct above = Coord2Cell(vf_18());
            if (DAT_0087F7E8.FUN_005657A0(&above)->Level == cell->Level + 4) {
                onBridge = true;
            }
        }
    }
    if (Type->Crusher || FUN_0070D0D0(0x11)) {
        if ((char)a2) {
            if (onBridge) {
                if (cell->AltOccupationBits & 0x1F) {
                    cell->FUN_00481670(&DAT_00B1CFE8, 1, 0, 1);
                }
            } else if (cell->OccupationBits & 0x1F) {
                cell->FUN_00481670(&DAT_00B1CFE8, 1, 0, 0);
            }
        } else {
            ObjectClass* object = onBridge ? cell->AltObject : cell->FirstObject;
            bool shaken = false;
            bool crushed = false;
            while (object) {
                if (!object->IsCrushable(this) || (Owner->IsAlliedWith(object) && !Type->IsTrain)
                    || FUN_005F6560(object->vf_18()) >= 0x4000 || object->IsFallingDown) {
                    object = (ObjectClass*)object->NextObject;
                } else if (object->vf_11() == 0xF && static_cast<InfantryClass*>(object)->Type->VehicleThief
                           && static_cast<InfantryClass*>(object)->Destination == this && !Type->IsTrain) {
                    ObjectClass* next = (ObjectClass*)object->NextObject;
                    IsOwnedByCurrentPlayer = static_cast<InfantryClass*>(object)->IsOwnedByCurrentPlayer;
                    vf_55(0);
                    vf_245(static_cast<InfantryClass*>(object)->Owner, 1);
                    object->vf_62();
                    object = next;
                } else {
                    ObjectClass* next = (ObjectClass*)object->NextObject;
                    crushed = true;
                    if (object->vf_11() == 1) {
                        shaken = true;
                    }
                    CoordStruct where = Location;
                    VocClass::PlayAt(object->vf_34()->CrushSound, where, 0);
                    object->vf_92();
                    object->vf_56(this);
                    object->vf_73(0);
                    object->vf_53();
                    object->vf_62();
                    object = next;
                }
            }
            if (crushed) {
                vf_279(object);
                if (shaken && RockingForwardsPerFrame == 0.0f) {
                    RockingForwardsPerFrame = -0.05f;
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x743190
// Target scan. A human-run unit that must deploy to fire scans nothing; otherwise
// the threat mask grows by what the weapons in use can hit before the FootClass scan.
AbstractClass* UnitClass::vf_241(unsigned int threat, CoordStruct* coord, bool a3)
{
    if (Owner->IsControlledByHuman() && static_cast<UnitTypeClass*>(Type)->DeployToFire) {
        return 0;
    }
    if ((threat & 0x1B978) == 0) {
        if (FUN_0070DC60() && !static_cast<UnitTypeClass*>(Type)->IsGattling) {
            threat |= vf_254(FUN_0070DD20())->WeaponType->AllowedThreats();
        } else {
            if (vf_254(0)->WeaponType) {
                threat |= vf_254(0)->WeaponType->AllowedThreats();
            }
            if (vf_254(1)->WeaponType) {
                threat |= vf_254(1)->WeaponType->AllowedThreats();
            }
        }
    }
    return FootClass::vf_241(threat, coord, a3);
}

// FUNCTION: GAMEMD 0x7438B0
// Stored tiberium value scaled by the owner's multiplier.
int UnitClass::FUN_007438B0()
{
    float value = (float)Tiberium.GetTotalValue();
    return (int)(Owner->FUN_0050C160() * value);
}

// FUNCTION: GAMEMD 0x7438F0
//
// MATCHED (100.0%, 108/108). Retail's per-operand store/FILD interleave
// (store Y, compute Z, FILD Y, store Z, FILD Z) comes from binding each
// component of the CoordStruct difference to its own `double` local
// immediately after that component's store, and then writing the sum over the
// doubles; writing the casts inside the sum expression lets cl 12.00.8804
// batch both int stores and then both FILDs. Variants tried: the difference as
// three separate ints (84.3%), as a `volatile` CoordStruct (28.7% — volatile
// also breaks the FMUL/FLD duplication), and the casts inline (95.4%). The
// final compare needed the slot-0xC8 result bound to a `char` local and then to
// a named bool: spelled inline as `call(...) == 0` cl emits NEG/SBB/INC instead
// of retail's TEST AL,AL / SETZ AL (84.4%).
//
// UnitClass::ShouldCrashIt — decide whether this unit may run the candidate
// over. The unit's house type must allow crushing outright or the unit must
// answer capability 0x11; the candidate must exist and accept the unit; the
// straight-line distance between the two coordinate triples (taken through the
// by-value coordinate slot 0x48 of each) must be inside the rules limit; and
// the owning house must pass three further checks — a human/AI split crossed
// with the rules flag and the house type's second byte, a house state that is
// not 2, and a minimum count for AI houses. Only then is the candidate's own
// veto slot 0xC8 asked, and its answer is inverted into the result.
bool Obj_007438F0::ShouldCrashIt(Obj_007438F0* victim)
{
    if (this->At_6C4->At_D28 == 0 && !this->FUN_0070D0D0(0x11)) {
        return false;
    }

    if (victim != 0 && victim->FUN_005F6CD0(this)) {
        Coord_007438F0 there;
        Coord_007438F0 here;
        Coord_007438F0* a = (victim->*victim->Vtbl->At_048)(&there);
        Coord_007438F0* b = (this->*this->Vtbl->At_048)(&here);

        Coord_007438F0 d;
        d.X = b->X - a->X;
        d.Y = b->Y - a->Y;
        double dy = (double)d.Y;
        d.Z = b->Z - a->Z;
        double dz = (double)d.Z;
        double dx = (double)d.X;

        double dist = Sqrt_004CAC40(dx * dx + dz * dz + dy * dy);

        if ((int)dist <= RulesInstance_007438F0->At_1728) {
            if (this->At_21C->FUN_0050B730()
                && RulesInstance_007438F0->At_17EB == 0
                && this->At_6C4->At_D2D == 0) {
                return false;
            }
            if (this->At_21C->At_184 == 2) {
                return false;
            }
            if (!this->At_21C->FUN_0050B730()
                && this->At_21C->At_24C < RulesInstance_007438F0->At_1448) {
                return false;
            }
            char veto = (victim->*victim->Vtbl->At_0C8)(this->At_21C);
            bool ok = (veto == 0);
            return ok;
        }
    }

    return false;
}

// FUNCTION: GAMEMD 0x7440B0
// Lets go of a carried flag, dropping it at the unit's cell.
bool UnitClass::vf_53()
{
    if (FootClass::vf_53()) {
        if (FlagHouseIndex != -1) {
            UnitFlagHouse** slot = &DAT_00A8022C[FlagHouseIndex];
            (*slot)->FUN_004FBF60(vf_110(), 0);
            FlagHouseIndex = -1;
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x744100
// A unit with a slave manager that is due to wake it waits the mission rate plus a little
// random time; otherwise the foot delay applies.
int UnitClass::vf_136()
{
    if (SlaveManager && DAT_008871E0->SlaveMinerKickFrameDelay + CurrentMissionStartTime < CurrentFrame) {
        if (static_cast<UnitSlaveManagerView*>(SlaveManager)->FUN_006B1020()) {
            static_cast<UnitSlaveManagerView*>(SlaveManager)->FUN_006B0CC0();
            int delay = (int)(FUN_005B3A00()->Rate * 900.0);
            return delay + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
        }
    }
    return FootClass::vf_136();
}

// FUNCTION: GAMEMD 0x744180
// True while the unload timer is in none of its three active states.
bool UnitClass::vf_167()
{
    if (UnloadTimer.FUN_004A5110() || UnloadTimer.FUN_004A5130() || UnloadTimer.FUN_004A51B0()) {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x7441B0  (__thiscall)
// Set the "Units" occupation bit (0x20) for the cell the coordinate maps to.
// When the coordinate sits at or below the cell floor and the cell is a bridge
// cell, the bit goes into the alternate (on-bridge) occupation set instead.
void UnitClass::MarkAllOccupationBits(CoordStruct const& coords)
{
    OccCellClass* cell = MapInstance->GetTargetCell(coords);
    if (MapInstance->GetCellFloorHeight(coords) + BridgeCellHeight <= coords.Z
        && (cell->Flags & 0x100))
    {
        cell->AltOccupationFlags |= 0x20;
        return;
    }
    cell->OccupationFlags |= 0x20;
}

// FUNCTION: GAMEMD 0x744210  (__thiscall)
// Clear the "Units" occupation bit (0x20) the mirror of MarkAllOccupationBits;
// unlike the mark path the unmark always clears the alternate set on the
// at-or-below-floor branch with no bridge-flag test.
void UnitClass::UnmarkAllOccupationBits(CoordStruct const& coords)
{
    OccCellClass* cell = MapInstance->GetTargetCell(coords);
    if (MapInstance->GetCellFloorHeight(coords) + BridgeCellHeight <= coords.Z)
    {
        cell->AltOccupationFlags &= ~0x20;
        return;
    }
    cell->OccupationFlags &= ~0x20;
}

// The cell a coordinate falls in: the inlined signed divide by 256 of X and Y.
static inline CellStruct CoordToCell_00744270(CoordStruct coord)
{
    CellStruct cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}

// FUNCTION: GAMEMD 0x744270
// Whether the unit is ready to be worked on (for example by a weapons factory): not while it
// is changing shape or unloading, nor while a contact it is tethered to still needs it, and
// not when it waits directly below an untethered weapons factory.
bool UnitClass::vf_128()
{
    if (CurrentMission == 6 || CurrentMission == 0x15 || Deploying || Undeploying || Unloading) {
        return false;
    }
    if (QueuedMission != 7 && Locomotor->IsMovingNow() && vf_114() >= 0 && vf_97() != 5 &&
        (vf_97() != 1 || Target)) {
        if (!unknown_bool_B8) {
            return false;
        }
    }
    if (!UnloadTimer.FUN_004A51D0()) {
        return false;
    }
    TechnoClass* contact = FUN_0065AD40(0);
    if (contact) {
        if (contact->vf_11() == 6 && static_cast<BuildingClass*>(contact)->Type->WeaponsFactory &&
            QueuedMission != 2 && QueuedMission != 7) {
            return false;
        }
    } else {
        CoordStruct location = this->Location;
        BuildingClass* building = Map_0087F7E8.FUN_00565730(location)->GetBuilding();
        if (building && building->Type->WeaponsFactory) {
            CellStruct buildingCell = CoordToCell_00744270(building->Location);
            CellStruct myCell = CoordToCell_00744270(Location);
            CellStruct delta = myCell - buildingCell;
            if (delta.X == 0 && delta.Y == 1) {
                return false;
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x744600
// Free the attached electric bolt, then save as a FootClass.
HRESULT __stdcall UnitClass::Save(IStream* pStm, BOOL fClearDirty)
{
    if (ElectricBolt) {
        ElectricBolt->DetachOwner();
        ElectricBolt = 0;
    }
    return FootClass::Save(pStm, fClearDirty);
}


// A COM-style interface pointer called through its raw table with the pointer on the stack.
struct UnitComObj_r16;
struct UnitComVtbl_r16
{
    void* slots[4];
    int (__stdcall* Slot4)(UnitComObj_r16* self);   // +0x10
};
struct UnitComObj_r16
{
    UnitComVtbl_r16* lpVtbl;
};

// A type or unit object, as far as its primary table slot 11.
struct UnitKindView_r16
{
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual void vf_7();
    virtual void vf_8();
    virtual void vf_9();
    virtual void vf_10();
    virtual int vf_11();
};

// The checksum sink, as far as the raw one-byte add (the byte goes through unchanged).
struct UnitCrcView_r16
{
    // FUNCTION: GAMEMD 0x4A1CA0 (decl; reloc)
    void FUN_004A1CA0(unsigned char value);
};

// A cell record, as far as the one test the disguise check makes.
struct UnitCellView_r16
{
    // FUNCTION: GAMEMD 0x4870F0 (decl; reloc)
    bool FUN_004870F0(int houseIndex);
};

// The map object, as far as the cell lookup.
struct UnitMapView_r16
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    UnitCellView_r16* FUN_005657A0(CellStruct* cell);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
extern UnitMapView_r16 DAT_0087F7E8_r16;

// A house, as far as its alliance test.
struct UnitHouseView_r16
{
    // FUNCTION: GAMEMD 0x4F9A50 (decl; reloc)
    bool FUN_004F9A50(HouseClass* other);
};

inline CellStruct UnitCoordToCell_r16(const CoordStruct& where)
{
    CellStruct result;
    result.X = where.X / 256;
    result.Y = where.Y / 256;
    return result;
}

class UnitView_r16 : public UnitClass
{
public:
    void FUN_00744640(Obj_004A1D30* crc);
    bool FUN_00746750(HouseClass* house);
};


// FUNCTION: GAMEMD 0x744640
// Feeds the unit's type, follower and flag state to the checksum.
void UnitView_r16::FUN_00744640(Obj_004A1D30* crc)
{
    FootClass::vf_13(crc);
    crc->FUN_004A1D50(Type->vf_11());
    UnitComObj_r16* typeIface = reinterpret_cast<UnitComObj_r16*>((char*)Type + 4);
    crc->FUN_004A1D50(typeIface->lpVtbl->Slot4(typeIface));
    if (FollowerCar) {
        UnitComObj_r16* followerIface = reinterpret_cast<UnitComObj_r16*>((char*)FollowerCar + 4);
        crc->FUN_004A1D50(followerIface->lpVtbl->Slot4(followerIface));
    }
    crc->FUN_004A1D50(FlagHouseIndex);
    UnitCrcView_r16* sink = reinterpret_cast<UnitCrcView_r16*>(crc);
    sink->FUN_004A1CA0(IsFollowerCar);
    sink->FUN_004A1CA0(Unloading);
    sink->FUN_004A1CA0(IsHarvesting);
    sink->FUN_004A1CA0(ShouldScatterInNextIdle);
}

// FUNCTION: GAMEMD 0x7446E0
// Drop references to a removed object.
void UnitClass::vf_10(void* target, bool removed)
{
    FootClass::vf_10(target, removed);
    if (FollowerCar == target) {
        FollowerCar = 0;
    }
    if (Type == target) {
        Type = 0;
    }
}

// FUNCTION: GAMEMD 0x744720
// Fires the attached tag's events (6: a source was given; then 0x30 and 0x1d) unless a
// hijacker is aboard and the tag is to be replaced; then the techno handling.
void UnitClass::vf_56(void* source)
{
    if (AttachedTag && (HijackerInfantryType == -1 || !AttachedTag->ShouldReplace())) {
        if (source) {
            AttachedTag->FUN_006E53A0(7, this, DAT_00B1CFB8, false, 0);
        }
        if (AttachedTag) {
            AttachedTag->FUN_006E53A0(0x30, this, DAT_00B1CFB8, false, 0);
        }
        if (AttachedTag) {
            AttachedTag->FUN_006E53A0(0x1d, this, DAT_00B1CFB8, false, 0);
        }
    }
    TechnoClass::vf_56(source);
}

// FUNCTION: GAMEMD 0x7447A0
// Tail-forwards to another function. Vtable slot 132 of UnitClass (RTTI).
void FUN_007447A0(Obj_007447A0* a1, int a2)
{
    FUN_004D4DC0(a1, a2);
}

// FUNCTION: GAMEMD 0x746000
//
// Should a short hop between two cells be handed to the A* search? A unit
// below ground, a failed pre-check, a far hop (twelve cells or more) or an
// off-map endpoint all say yes; the same cell or an adjacent one says no.
// In between, the search is run for real and only a long result counts.
//
// Every `return true` is the one fall-through tail: the guards are nested
// (`&&` chains) rather than early returns, which is what makes retail jump
// forward to a single MOV AL,1 block while the false returns stay inline.
// The flag word is unsigned so the level bit comes out with SHR.
bool UnitClass::AStarAttempt(const CellStruct* from, const CellStruct* to)
{
    if (this->vf_114() >= 0
        && MapInstance_00746000.FUN_0056D100(from, to, 0, 0, 0, 0)) {
        if (from->X == to->X && from->Y == to->Y) {
            return false;
        }

        int dy = abs(to->Y - from->Y);
        int dx = abs(to->X - from->X);
        int dist = dx > dy ? dx : dy;
        if (dist == 1) {
            return false;
        }
        if (dist < 12
            && MapInstance_00746000.IsWithinUsableArea(from, true)
            && MapInstance_00746000.IsWithinUsableArea(to, true)) {
            int steps = DAT_0087E8B8.AttemptPath(
                from, to, this, false,
                (MapInstance_00746000.GetCellAt(to)->Flags >> 8) & 1, 0);
            return steps > 15;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x746100
// PARTIAL: 96.5% - identical instruction multiset; register naming only: the vtable pointer after the
// death-weapon call (EDX in retail, EAX here), the health/strength load and the warhead load in the damage
// computation (8 instructions differ by register only).
// INoticeSink slot 0 (the +0x08 table). Notice 0x117B hands a jumpjet or balloon-hover unit that
// is linked to something over to its archived target, or stops it; notice 0x117C lets a crashable
// unit fall apart; otherwise a unit that is being attacked by a locomotor explodes with the death
// weapon and the C4 warhead.
bool UnitClass::Notice(int id, int arg)
{
    if ((Type->BalloonHover || Type->JumpJet) && id == 0x117B && HasAnyLink()) {
        vf_157(8);
        if (ArchiveTarget && ArchiveTarget != Destination) {
            SetDestination(ArchiveTarget, true);
            return true;
        }
        AbortMotion();
        vf_93(DAT_00B1CFE8, true, false);
        return true;
    }
    if (Type->Crashable && id == 0x117C) {
        vf_115(0);
        if (!Type->BalloonHover) {
            FUN_00738680();
            vf_62();
            return true;
        }
        FUN_0070D690(0);
        vf_62();
        return true;
    }
    if (IsAttackedByLocomotor) {
        RulesClass* rules = DAT_008871E0;
        int damage = (int)((rules->CurrentStrengthDamage ? Health : Type->Strength) * rules->FallingDamageMultiplier);
        if (damage < 0) {
            damage = 0;
        }
        TechnoClass* owner = this;
        if (BeingManipulatedBy) {
            owner = static_cast<TechnoClass*>(BeingManipulatedBy);
        }
        BulletClass* bullet = FUN_0046B050(rules->DeathWeapon->Projectile, this, owner, damage, rules->CrushWarhead, 0, 1);
        CoordStruct coord = vf_18();
        coord.Z -= vf_114();
        if (bullet) {
            bullet->vf_53();
            bullet->FUN_004690B0(&coord);
            bullet->Release();
        }
        if (BeingManipulatedBy) {
            vf_56(BeingManipulatedBy);
        } else if (ChronoWarpedByHouse) {
            vf_57(ChronoWarpedByHouse);
        }
        coord = vf_18();
        bullet = FUN_0046B050(DAT_008871E0->DeathWeapon->Projectile, this, owner, damage, DAT_008871E0->C4Warhead, 0, 1);
        if (bullet) {
            bullet->vf_53();
            bullet->FUN_004690B0(&coord);
            bullet->Release();
        }
        vf_62();
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x7463A0
// Change owner: hand the follower car over too, then do the FootClass change.
bool UnitClass::vf_245(HouseClass* house, bool a2)
{
    if (house != Owner) {
        UnitClass* follower = static_cast<UnitClass*>(FollowerCar);
        IsFollowerCar = false;
        if (follower) {
            follower->vf_245(house, true);
            FollowerCar = follower;
            follower->IsFollowerCar = true;
        }
        return FootClass::vf_245(house, true);
    }
    return false;
}

// FUNCTION: GAMEMD 0x746400
// Returns a comparison result. Vtable slot 32 of UnitClass (RTTI).
unsigned char Obj_00746400::FUN_00746400() const
{
    return unknown_6C4->unknown_E1B == 0;
}

// FUNCTION: GAMEMD 0x746420
// Takes over the temporal link of the given unit (it must be a unit), carrying its
// rearm state across, then adopts that unit's mode.
void UnitClass::vf_309(int a1)
{
    UnitClass* other = reinterpret_cast<UnitClass*>(a1);
    TemporalClass* temporal = other->TemporalImUsing;
    if (temporal) {
        int rearming = 0;
        if (other->RearmTimer.GetTimeLeft()) {
            rearming = 1;
        }
        TemporalImUsing = temporal;
        temporal->Owner = this;
        other->TemporalImUsing = 0;
        FUN_0070DC70(7);
        if (rearming) {
            CurrentBurstIndex++;
            RearmTimer = CDTimerClass(vf_198(7));
        }
    }
    FUN_0070DC70(other->vf_33()->IFVMode);
}

// FUNCTION: GAMEMD 0x7464E0
// Same hand-over for a possibly null foot object.
void UnitClass::vf_310(FootClass* passenger)
{
    if (passenger && TemporalImUsing) {
        TemporalClass* temporal = TemporalImUsing;
        int rearming = 0;
        if (RearmTimer.GetTimeLeft()) {
            rearming = 1;
        }
        passenger->TemporalImUsing = temporal;
        TemporalImUsing->Owner = passenger;
        TemporalImUsing = 0;
        if (passenger->TemporalImUsing && passenger->TemporalImUsing->Target) {
            passenger->TemporalImUsing->FUN_0071ABC0();
        }
        if (rearming) {
            passenger->CurrentBurstIndex++;
            passenger->RearmTimer = CDTimerClass(passenger->vf_198(0));
        }
    }
    FUN_0070DC70(0);
}

// FUNCTION: GAMEMD 0x7465B0
ObjectTypeClass* UnitClass::vf_51(bool a1)
{
    if (Owner->IsAlliedWith(DAT_00A83D4C) && !a1) {
        return static_cast<ObjectTypeClass*>(this->Type);
    }
    return Disguise;
}

// FUNCTION: GAMEMD 0x7465F0
HouseClass* UnitClass::vf_52(bool a1)
{
    if (Owner->IsAlliedWith(DAT_00A83D4C) && !a1) {
        return Owner;
    }
    return DisguisedAsHouse;
}

// FUNCTION: GAMEMD 0x746630
// Start disguising as the given type (does nothing for null).
void UnitClass::FUN_00746630(ObjectTypeClass* type)
{
    if (type) {
        Disguise = type;
        DisguisedAsHouse = 0;
        Disguised = true;
        DisguiseCreationFrame = CurrentFrame;
        vf_295();
    }
}

// FUNCTION: GAMEMD 0x746670
// Disguise as the given object: a unit takes on the type and house it presents, a
// cell takes on its overlay, and a terrain object only its type. Retail leaves the
// return value unset.
#pragma warning(disable : 4716)
unsigned long UnitClass::DisguiseAs(AbstractClass* target)
{
    TechnoClass* other = (TechnoClass*)target;
    if (other) {
        bool apply = false;
        ObjectTypeClass* type;
        switch (other->vf_11()) {
        case 36:
            type = other->vf_34();
            apply = true;
            break;
        case 11:
            if (vf_230(target)) {
                type = DAT_00A83D84[((CellClass*)target)->OverlayTypeIndex];
                apply = true;
            }
            break;
        case 1:
            if (other->vf_49()) {
                Disguise = other->vf_51(true);
                DisguisedAsHouse = other->vf_52(true);
                TechnoClass::DisguiseAs(target);
            }
            break;
        }
        if (apply) {
            Disguise = type;
            DisguisedAsHouse = 0;
            TechnoClass::DisguiseAs(target);
        }
    }
}
#pragma warning(default : 4716)

// FUNCTION: GAMEMD 0x746720
// Drop the disguise.
void UnitClass::vf_284()
{
    Disguised = false;
    vf_295();
    Disguise = 0;
    DisguisedAsHouse = 0;
}

// FUNCTION: GAMEMD 0x746750
// Whether the house is fooled by this unit's disguise at its current cell.
bool UnitView_r16::FUN_00746750(HouseClass* house)
{
    if (vf_49()) {
        CellStruct cell = UnitCoordToCell_r16(vf_18());
        UnitCellView_r16* cellRecord = DAT_0087F7E8_r16.FUN_005657A0(&cell);
        if (!reinterpret_cast<UnitHouseView_r16*>(Owner)->FUN_004F9A50(house) &&
            !cellRecord->FUN_004870F0(house->ArrayIndex)) {
            HouseClass* disguised = DisguisedAsHouse;
            if (disguised == house || !disguised ||
                reinterpret_cast<UnitHouseView_r16*>(house)->FUN_004F9A50(disguised))
                return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x746810
// After the techno start-up, the unit takes a veteran promotion when its house lists the type as
// a veteran unit, or when a trainable land type belongs to a house that has infiltrated a war
// factory, and a gunner type sets up its gunner state.
void UnitClass::vf_9()
{
    TechnoClass::vf_9();
    if (Type) {
        if (Owner) {
            TypeList<const UnitTypeClass*>& list = Owner->Type->VeteranUnits;
            for (int i = 0; i < list.Count; i++) {
                if (list.Items[i] == Type) {
                    Veterancy.FUN_00750090(1);
                    break;
                }
            }
        }
        if (Owner && Owner->WarFactoryInfiltrated && !Type->Naval && Type->Trainable) {
            Veterancy.FUN_00750090(1);
        }
        if (Type->Gunner) {
            FUN_0070DC70(0);
        }
    }
}

// FUNCTION: GAMEMD 0x7468C0
// Keep the disguise in step with what is around: a moving or disturbed unit drops it, a unit
// that stands still with nobody linked to it may pick a fresh one when the blink timer has run
// out, and the mind-control ring is hidden while the disguise is up for other players.
bool UnitClass::FUN_007468C0()
{
    bool canBlink = false;
    if (!vf_49()) {
        if (!Locomotor->IsMoving()) {
            if (Type->DisguiseWhenStill) {
                if (!FUN_0065AD30(0)) {
                    canBlink = true;
                }
            }
        }
    }
    if (Locomotor->IsMoving()) {
        goto drop;
    }
    if (CurrentFrame % 8 != 0) {
        CellStruct cell = vf_110();
        bool onBridge = vf_111()->IsBridgeTile();
        for (int i = 0; i < 8; i++) {
            CellStruct next = cell + DAT_0089F688[i & 7];
            CellClass* neighbour = reinterpret_cast<CellClass*>(Map_0087F7E8.FUN_005657A0(&next));
            InfantryClass* infantry = neighbour->GetInfantry(onBridge);
            if (infantry && !Owner->IsAlliedWith(infantry)) {
                goto found;
            }
        }
    }
    if (canBlink && InfantryBlinkTimer.GetTimeLeft() == 0) {
        int index = DAT_00A8B230->unknown_0218.RandomRanged(0, DAT_008871E0->DefaultMirageDisguises.Count - 1);
        int last = DAT_008871E0->DefaultMirageDisguises.Count - 1;
        if (index >= last) {
            index = last;
        }
        FUN_00746630(const_cast<TerrainTypeClass*>(DAT_008871E0->DefaultMirageDisguises.Items[index]));
    }
done:
    if (MindControlRingAnim) {
        if (vf_49() && !Owner->IsControlledByCurrentPlayer()) {
            static_cast<AnimClass*>(MindControlRingAnim)->Invisible = 1;
            return true;
        }
        static_cast<AnimClass*>(MindControlRingAnim)->Invisible = 0;
    }
    return false;
    // Layout evidence: retail emits this block between the ring's return-true (0x746ADB) and the false arm (0x746B0B),
    // entered by the jumps at 0x746942 (moving) and 0x7469F5 (enemy found) and left by a jump back to 0x746A9C. It
    // cannot be written as a structured arm: nested and flag forms place it mid-function and score 25.3 / 68.4.
found:
    InfantryBlinkTimer = CDTimerClass(DAT_008871E0->InfantryBlinkDisguiseTime);
drop:
    vf_284();
    goto done;
}

// FUNCTION: GAMEMD 0x746B20
// The name shown for the unit. A disguise shows the disguise's name to the local player; a
// turreted unit with an infantryman inside shows the turret's tip (or the rider's own name)
// followed by the unit's name; any other unit shows its own name.
const wchar_t* UnitClass::vf_36()
{
    if (vf_50(DAT_00A83D4C) && vf_51(true)) {
        if (!vf_52(true)) {
            return 0;
        }
        return vf_51(true)->UIName;
    }
    if (FUN_0070DC60() && FUN_0070DC50()) {
        const wchar_t* name = 0;
        FootClass* passenger = Passengers.GetFirstPassenger();
        if (passenger && passenger->vf_11() == 0xF) {
            bool own = false;
            if (static_cast<InfantryClass*>(passenger)->Type->UseOwnName) {
                own = true;
            }
            int turret = GetCurrentTurret();
            if (turret == 0) {
                name = FUN_00734E60("Tip:Rocket", 0, "D:\\ra2mdpost\\Unit.CPP", 0x2C90);
            } else if (turret == 1 && !own) {
                name = FUN_00734E60("Tip:MachineGun", 0, "D:\\ra2mdpost\\Unit.CPP", 0x2C94);
            } else if (turret == 2) {
                name = FUN_00734E60("Tip:Repair", 0, "D:\\ra2mdpost\\Unit.CPP", 0x2C98);
            } else if (turret == 3 || own) {
                name = passenger->vf_34()->UIName;
            }
        }
        if (!name) {
            name = FUN_00734E60("Tip:Rocket", 0, "D:\\ra2mdpost\\Unit.CPP", 0x2CBE);
        }
        swprintf(ToolTipText, L"%s %s", name, Type->UIName);
        return ToolTipText;
    }
    return Type->UIName;
}

// FUNCTION: GAMEMD 0x746C90
// Counts as EMP-disabled while dying, otherwise defers to TechnoClass.
bool UnitClass::IsUnderEMP()
{
    return DeathFrameCounter != -1 || TechnoClass::IsUnderEMP();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746CB0
// Tail-forwards to another function. Vtable slot 303 of UnitClass (RTTI).
void FUN_00746CB0(Obj_00746CB0* a1, int a2)
{
    FUN_0070F070(a1, a2);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746CC0
// Tail-forwards to another function. Vtable slot 304 of UnitClass (RTTI).
void FUN_00746CC0(Obj_00746CC0* a1, int a2)
{
    FUN_0070F090(a1, a2);
}

// FUNCTION: GAMEMD 0x746CD0
// A deployed deploy-fire unit uses its deploy weapon; otherwise the base choice.
int UnitClass::vf_185(AbstractClass* target)
{
    if (Deployed && static_cast<UnitTypeClass*>(this->Type)->DeployFire) {
        return static_cast<UnitTypeClass*>(this->Type)->DeployFireWeapon;
    }
    return TechnoClass::vf_185(target);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746D00
// Member getter (byte).
unsigned char Obj_00746D00::FUN_00746D00() const
{
    return unknown_6C4->unknown_6AC;
}

// FUNCTION: GAMEMD 0x746D10
// Whether a simple-deploy unit is currently allowed to deploy: the type must
// allow it, and when it carries anything it must also be a land-deployer.
bool UnitClass::FUN_00746D10()
{
    if (!static_cast<UnitTypeClass*>(this->Type)->IsSimpleDeployer) {
        return false;
    }
    if (vf_114() > 0 && !vf_33()->DeployToLand) {
        return false;
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746D60
// Calls other functions. Vtable slot 92 of UnitClass (RTTI).
void FUN_00746D60(Obj_00746D60* a1, int a2)
{
    FUN_00738680(a1, a2);
    a1->FUN_00710460();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746D80
// Member getter (byte).
unsigned char Obj_00746D80::FUN_00746D80() const
{
    return unknown_6E0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746D90
// Branching.
bool Obj_00746D90::FUN_00746D90()
{
    return unknown_6E0 != 0 || unknown_6E1 != 0;
}

// FUNCTION: GAMEMD 0x746DB0
// True while the unit is in the middle of deploying or undeploying.
bool UnitClass::FUN_00746DB0()
{
    return Deploying || Undeploying;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746DD0
// Returns a constant. Vtable slot 12 of UnitClass (RTTI).
int UnitClass::vf_12()
{
    return 0x8E8;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746E20
// Returns a constant. Vtable slot 11 of UnitClass (RTTI).
int UnitClass::vf_11()
{
    return 1;
}

// FUNCTION: GAMEMD 0x746E30
DirStruct UnitClass::vf_170()
{
    UnitTypeClass* type = static_cast<UnitTypeClass*>(this->Type);
    if (type->bools_C8C[0x15]) {
        return SecondaryFacing.FUN_004C93D0();
    }
    return PrimaryFacing.FUN_004C93D0();
}

// SYNTHETIC: GAMEMD 0x746E80 -- compiler-generated scalar deleting destructor of ~UnitClass (slot 8).

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746EA0
bool HandleHolder::FUN_00746EA0(void** other)
{
    if (this->Held != 0 && *this->Held == *other) {
        return true;
    }

    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87E8B8
extern AStar_00746000 DAT_0087E8B8;
// GLOBAL: GAMEMD 0x7F5C28
extern const double DAT_007F5C28 = 60.0;
// END defined globals
