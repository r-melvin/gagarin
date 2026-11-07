// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 disassembly at the entry below (AircraftClass
//   primary vtable 0x7E22A4, slot 54; slot 144 at 0x419C80), read with the Ghidra CLI from the entry point.
#include "_layout/aircraft_class.h"
#include "_layout/aircraft_type_class.h"
#include "_layout/house_class.h"
#include "_layout/house_type_class.h"
#include "_layout/gbl_0087f7e8.h"
#include "_layout/building_class.h"
#include "_layout/techno_type_class.h"
#include "_layout/cell_class.h"
#include "loco_com.h"
#include "scenario_class_methods.h"
#include "_layout/session_class.h"
#include "mission_class_methods.h"
#include "_layout/bullet_class.h"
#include "rules_class.h"
#include "_layout/team_class.h"
#include "_layout/team_type_class.h"
#include "weapon_type_class.h"

// FUNCTION: GAMEMD 0x413F80
// Slot 9: after the techno start-up the aircraft takes a veteran promotion when its house lists the type, aims
// both facings at the type's turn rate, sets the height from the type, and takes the type's starting ammo and
// strength; the owning house is then told about it.
void AircraftClass::vf_9()
{
    TechnoClass::vf_9();
    if (Type) {
        if (Owner) {
            TypeList<const AircraftTypeClass*>& list = Owner->Type->VeteranAircraft;
            for (int i = 0; i < list.Count; i++) {
                if (list.Items[i] == Type) {
                    Veterancy.FUN_00750090(1);
                    break;
                }
            }
        }
        PrimaryFacing.FUN_004C9680(Type->ROT);
        SecondaryFacing.FUN_004C9680(Type->ROT);
        DirStruct dir;
        SecondaryFacing.FUN_004C9300(PrimaryFacing.FUN_004C93D0(&dir));
        vf_115(Type->vf_47());
        int ammo = Type->InitialAmmo;
        Ammo = ammo == -1 ? Type->Ammo : ammo;
        int strength = Type->Strength;
        Health = strength;
        EstimatedHealth = strength;
    }
    if (Owner)
        Owner->FUN_004FF700(this);
}

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

// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
extern ScenarioClass* DAT_00A8B230;

// FUNCTION: GAMEMD 0x414A80
// Slot 138: an aircraft with no ammo left leaves its team, goes idle and waits out a mission rate delay plus a
// small random one. With ammo it looks for a target around itself (strong threats first when the game is not a
// campaign), and with none found it goes idle, else it takes the guard mission.
int AircraftClass::vf_138()
{
    if (Ammo == 0) {
        if (Team)
            Team->LiberateMember(this, -1, 0);
        EnterIdleMode(false, true);
        int delay = (int)(FUN_005B3A00()->Rate * 900.0);
        return delay + DAT_00A8B230->unknown_0218.RandomRanged(0, 2);
    }
    if (!Target) {
        if (Session_00A8B238.GameMode != 0) {
            CoordStruct where = Location;
            vf_242(vf_241(0x40, &where, false));
        }
        if (!Target) {
            CoordStruct where = Location;
            vf_242(vf_241(0, &where, false));
        }
        if (!Target) {
            EnterIdleMode(false, true);
            return 1;
        }
    }
    vf_122(1, false);
    return 1;
}


// FUNCTION: GAMEMD 0x4176F0
// Slot 289, entering idle mode. A suspended mission is resumed instead. Otherwise the foot body runs and the
// aircraft picks the mission to queue: guard (or hunt, when a computer-owned team-less armed one), sent to its dock,
// or held depending on ammo, passengers, whether it is on the map and the dock it can reach; at the end the mission
// is queued and a pending queued one started.
bool AircraftClass::EnterIdleMode(bool initial, bool a2)
{
    // The dock-send block (SetDestination(FUN_0041A160(), true); mission 2) is one block in retail, at 0x417A1A,
    // entered by jumps from 0x417814, 0x4179F5 and by falling out of 0x417A0C.
    if (vf_127()) {
        vf_126();
        if (CurrentMission == 0x19) {
            MissionStatus = 0;
            IsLocked = 0;
            return false;
        }
        return false;
    }
    switch (CurrentMission) {
    case 4:
    case 0x1A:
    case 0x1B:
    case 0x1E:
    case 0x1F:
        if (Airstrike == 0)
            return false;
    }
    if (QueuedMission == 0x1A || QueuedMission == 0x1E) {
        vf_123();
        return false;
    }
    bool result = FootClass::EnterIdleMode(initial, a2);
    int mission;
    if (!Owner->IsControlledByHuman() && !Team && IsArmed())
        mission = 0xB;
    else
        mission = 5;
    int altitude = vf_03();
    if (vf_30() != 2 && vf_114() > altitude && !Type->MissileSpawn) {
        bool sendDock = false;
        if (Passengers.FirstPassenger) {
            if (!Spawned) {
                sendDock = true;
            } else if (Team) {
                mission = 5;
            } else {
                mission = 0x10;
                SetDestination(FUN_0041A160(), true);
            }
        } else {
            if ((Spawned && Owner->IsControlledByHuman()) || (!Owner->IsControlledByHuman() && Type->Ammo == 0)) {
                if (Team && Team->FUN_006EC370())
                    Team->LiberateMember(this, -1, 0);
            }
            if (vf_254(0)->WeaponType) {
                if (Spawned) {
                    if (Ammo == 0) {
                        if (Team)
                            Team->LiberateMember(this, -1, 0);
                        vf_242(0);
                        SetDestination(0, true);
                        mission = 4;
                    } else if (!Team) {
                        mission = 0xF;
                    }
                } else if ((Ammo != 0 && Target && vf_97() == 1) || QueuedMission == 1) {
                    mission = 1;
                } else if (IsInAir()) {
                    if (!(Destination && CurrentMission == 7) && Type->Dock.Count > 0 && (IsInPlayfield || !Team)) {
                        void* dock = vf_330(reinterpret_cast<DynamicVectorClass<AbstractClass*>*>(&Type->Dock), 0, 0);
                        SetDestination(0, true);
                        if (dock && vf_158(2, static_cast<RadioClass*>(dock)) == 1) {
                            SetDestination(static_cast<AbstractClass*>(dock), true);
                            mission = 7;
                        } else {
                            if (Type->AirportBound) {
                                vf_247(0);
                                return false;
                            }
                            sendDock = true;
                        }
                    }
                }
            } else {
                if (Team)
                    return false;
                sendDock = true;
            }
        }
        if (sendDock) {
            SetDestination(FUN_0041A160(), true);
            mission = 2;
        }
    } else if (Spawned) {
        if (Passengers.FirstPassenger) {
            mission = Team ? 5 : 0x10;
        } else if (!Team) {
            vf_242(0);
            SetDestination(0, true);
            mission = 4;
        }
    } else {
        SetDestination(0, true);
        vf_242(0);
        if (!Owner->IsControlledByHuman() && !Team && IsArmed())
            mission = 0xB;
        else
            mission = 5;
    }
    if (Ammo == 0 && IsArmed() && !HasAnyLink()) {
        void* dock = vf_330(reinterpret_cast<DynamicVectorClass<AbstractClass*>*>(&Type->Dock), 0, 0);
        if (dock) {
            SetDestination(static_cast<AbstractClass*>(dock), true);
            vf_242(0);
            mission = 7;
        } else if (Type->AirportBound) {
            vf_247(0);
            return false;
        }
    }
    if (HasAnyLink())
        mission = 7;
    vf_122(mission, false);
    if (vf_128())
        vf_123();
    return result;
}

// FUNCTION: GAMEMD 0x417BD0
// Slot 81: the slot 29 answer for the target decides. 2 is refused, 3 and 17 raise the slot 222 event with codes 7 and
// 2 for the target, 4 raises 0x10 with no target, and anything else is the foot body's with that answer in place
// of the first argument.
bool AircraftClass::vf_81(int a1, ObjectClass* a2, int a3)
{
    int answer = vf_29(a2, (char)a3);
    switch (answer) {
    case 17:
        return vf_222(2, 0, a2, 0);
    case 2:
        return false;
    case 3:
        return vf_222(7, 0, a2, 0);
    case 4:
        return vf_222(0x10, 0, 0, 0);
    }
    return FootClass::vf_81(answer, a2, a3);
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

// GLOBAL: GAMEMD 0xA8E7AC -- nonzero while the scenario is being set up.
extern int DAT_00A8E7AC;

// FUNCTION: GAMEMD 0x4196B0
// Slot 107, whether the cell is out of bounds for the aircraft (7) or usable (0). A team that is cut off by the usable
// area refuses cells outside it. An enemy occupant the aircraft cannot see past, or a cell that cannot be moved
// into, gives 7, and so does a shrouded cell for the local player's aircraft that is not placed yet outside
// multiplayer-style sessions.
int AircraftClass::vf_107(CellClass* cell, int a2, int a3, int a4, bool a5)
{
    if (Team && Team->FUN_006EC300() && !DAT_0087F7E8.FUN_00578540(cell, true))
        return 0;
    TechnoClass* occupant = static_cast<TechnoClass*>(cell->FirstObject);
    bool isTechno = occupant ? occupant->Flags.IsTechno : false;
    if (!occupant || !isTechno || occupant->Owner->IsAlliedWith(Owner)
        || (occupant->CloakState != 2 && !DAT_00A8E7AC
            && (occupant->vf_11() != 6 || !static_cast<BuildingClass*>(occupant)->Type->Invisible))) {
        if (!cell->IsClearToMove(4, false, false, -1, 0, -1, true))
            return 7;
    }
    if (Session_00A8B238.GameMode == 0 && IsOwnedByCurrentPlayer && !Spawned) {
        if (DAT_0087F7E8.IsLocationShrouded(cell->vf_18()))
            return 7;
    }
    return 0;
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

// FUNCTION: GAMEMD 0x41ADF0
// Slot 72, revealing the map around the aircraft. A grounded one sees one cell; a type with no sight of its own in
// a fogged game reveals (twice, the second time as the lower layer) the rules' aircraft radius, with a flag set
// when it is below half the flight level; otherwise its own sight is revealed twice, by the caller's flags.
void AircraftClass::vf_72(int a1, int a2)
{
    int sight = Type->Sight;
    if (vf_114() == 0)
        sight = 1;
    if (sight) {
        CoordStruct where = Location;
        DAT_0087F7E8.FUN_005678E0(&where, sight, Owner, a1, a2, 0, 1, 0);
        where = Location;
        DAT_0087F7E8.FUN_005678E0(&where, sight, Owner, a1, a2, 0, 1, 1);
        return;
    }
    if (DAT_00A8B230->unknown_0000 & 0x1000) {
        sight = RulesInstance->AircraftFogReveal;
        CoordStruct where = Location;
        DAT_0087F7E8.FUN_005678E0(&where, sight, Owner, 0, 0, 1, vf_114() < RulesInstance->FlightLevel / 2, 0);
        where = Location;
        DAT_0087F7E8.FUN_005678E0(&where, sight, Owner, 0, 0, 1, vf_114() < RulesInstance->FlightLevel / 2, 1);
    }
}

// FUNCTION: GAMEMD 0x46B050 (decl; reloc) -- creates a bullet: projectile in ECX, target in EDX, then owner, damage,
// warhead, speed and the bright flag on the stack.
BulletClass* FUN_0046B050(BulletTypeClass* projectile, AbstractClass* target, TechnoClass* owner, int damage,
                          WarheadTypeClass* warhead, int speed, char bright);

// FUNCTION: GAMEMD 0x41BC30
// INoticeSink slot 0 (the +0x08 table). An aircraft that a locomotor is attacking crashes: two death-weapon bullets go
// off at its position (the second at the position of its ground track), the manipulator or house that held it is
// told, and it is removed.
bool AircraftClass::Notice(int id, int arg)
{
    if (IsAttackedByLocomotor) {
        RulesClass* rules = RulesInstance;
        int damage = (int)((rules->CurrentStrengthDamage ? Health : Type->Strength) * rules->FallingDamageMultiplier);
        if (damage < 0)
            damage = 0;
        TechnoClass* owner = this;
        if (BeingManipulatedBy)
            owner = static_cast<TechnoClass*>(BeingManipulatedBy);
        BulletClass* bullet = FUN_0046B050(rules->DeathWeapon->Projectile, this, owner, damage, rules->C4Warhead, 0, 1);
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
        bullet = FUN_0046B050(RulesInstance->DeathWeapon->Projectile, this, owner, damage, RulesInstance->C4Warhead, 0, 1);
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

