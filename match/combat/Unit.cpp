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

#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "../core/same_object_test_sweep.h"

#include "../movement/trivial_tu258_methods.h"

#include <stdlib.h>
#include "../movement/unit_class_astar_attempt_methods.h"

#include "../core/scenario_class_methods.h"
#include "../movement/unit_class_occupation_methods.h"
#include "../ui/input_controls/ui_display_chain.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

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
// GLOBAL: GAMEMD 0xB1D0B0
extern double DAT_00B1D0B0;



#include "../_layout/unit_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../_layout/cell_class.h"
#include "../_layout/house_class.h"
#include "../core/frame_counter.h"
#include "../_layout/ebolt_class.h"
#include "../_layout/player_ptr_00a83d4c.h"
#include "../_layout/tag_class.h"
#include "../core/randomizer.h"
#include "../_layout/rules_class.h"
#include "../_layout/temporal_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../_layout/object_type_class.h"
#include "../_layout/team_class.h"

// Native error helper at 0x7DC720; the Unit call passes 0x80004003.
void __stdcall FUN_007DC720(unsigned int hr);

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
        if (!this->Locomotor) {
            FUN_007DC720(0x80004003u);
        }

        ILocomotion* locomotor = static_cast<ILocomotion*>(this->Locomotor);
        if (locomotor->IsMoving()) {
            const int remaining = this->ReloadTimer.GetTimeLeft();
            if (remaining > 0) {
                this->ReloadTimer = CDTimerClass(remaining + 1);
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
    if (!deploysInto || deploysInto->bools_16A4[0x20]) {
        return false;
    }

    if (this->Owner->FUN_0050B730()) {
        return false;
    }

    AbstractClass* target = this->Target;
    if (!target) {
        return false;
    }

    IRTTITypeInfo* typeInfo = static_cast<IRTTITypeInfo*>(target);
    const int targetType = typeInfo->vf_rtti_3();
    if (targetType != 1 && targetType != 6 && targetType != 15) {
        return false;
    }

    CoordStruct location = this->Location;
    CellClass* cell = Map_0087F7E8.FUN_00565730(location);
    return cell->FUN_00487C10();
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


// The unit's slave manager, as far as the two calls the mission delay makes.
struct UnitSlaveManagerView
{
    // FUNCTION: GAMEMD 0x6B1020 (decl; reloc) -- whether the manager should wake now.
    bool FUN_006B1020();
    // FUNCTION: GAMEMD 0x6B0CC0 (decl; reloc) -- wakes the manager.
    void FUN_006B0CC0();
};

// GLOBAL: GAMEMD 0x8871E0 -- the rules.
extern RulesClass* DAT_008871E0;

// GLOBAL: GAMEMD 0xA8B230 -- the scenario.
extern ScenarioClass* DAT_00A8B230;

// The mission control record (canonical view).
#include "../core/mission_class_methods.h"

// GLOBAL: GAMEMD 0xB1CFB8 -- the cell passed with tag events when there is none.
extern CellStruct DAT_00B1CFB8;


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



// GLOBAL: GAMEMD 0x7E2800 -- 0.0, read from memory rather than FLDZ.
extern const double DAT_007E2800;


// FUNCTION: GAMEMD 0x740A90
int UnitClass::vf_139()
{
    IsHarvesting = 0;
    if (Deployed || Deploying || Undeploying) {
        vf_122(5, false);
        return 1;
    }
    if (!UnloadTimer.FUN_004A51D0()) {
        UnloadTimer.FUN_004A5240(static_cast<UnitTypeClass*>(this->Type)->DeployTime);
    }
    return FootClass::vf_139();
}

// FUNCTION: GAMEMD 0x740B10
int UnitClass::vf_151()
{
    IsHarvesting = 0;
    if (!UnloadTimer.FUN_004A51D0()) {
        UnloadTimer.FUN_004A5240(static_cast<UnitTypeClass*>(this->Type)->DeployTime);
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
    UnloadTimer.FUN_004A5240(static_cast<UnitTypeClass*>(this->Type)->DeployTime);
}

// FUNCTION: GAMEMD 0x740E80  (__thiscall)
// If the unit is not in motion (per its locomotor) and the door-pending flag is
// clear, begin the door transition by handing the unit type's door-open angle to
// the unload timer. The locomotor is a COM smart pointer, so the dereference
// carries the inlined NULL-guard that raises E_POINTER.
void UnitClass::APCOpenDoor()
{
    ILocomotionPtr* loco = reinterpret_cast<ILocomotionPtr*>(&this->Locomotor);
    if (!(*loco)->IsMoving() && !this->unknown_bool_6AF)
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
    void* contact = vf_330(reinterpret_cast<DynamicVectorClassLayout*>((char*)DAT_008871E0 + 0x850), 0, 0);
    IsHarvesting = false;
    if (contact == 0) {
        if (vf_330(reinterpret_cast<DynamicVectorClassLayout*>((char*)DAT_008871E0 + 0x850), 0, 1)) {
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

// FUNCTION: GAMEMD 0x741490
// Member getter (dword). Vtable slot 34 of UnitClass (RTTI).
int Obj_00741490::FUN_00741490() const
{
    return unknown_6C4;
}

// FUNCTION: GAMEMD 0x7414A0
// Fraction of the harvester's capacity that is full; zero for non-harvesters.
double UnitClass::vf_173()
{
    UnitTypeClass* type = static_cast<UnitTypeClass*>(this->Type);
    if (!type->Harvester && !type->Weeder) {
        return DAT_007E2800;
    }
    return (double)Tiberium.GetTotalAmount() / static_cast<UnitTypeClass*>(this->Type)->Storage;
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
    crc->FUN_004A1D50(static_cast<UnitKindView_r16*>(Type)->vf_11());
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
        temporal->Owner = reinterpret_cast<TemporalTechnoView*>(this);
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
        TemporalImUsing->Owner = reinterpret_cast<TemporalTechnoView*>(passenger);
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
int Obj_00746D90::FUN_00746D90()
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
int Obj_00746DD0::FUN_00746DD0() const
{
    return 0x8E8;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746E20
// Returns a constant. Vtable slot 11 of UnitClass (RTTI).
int Obj_00746E20::FUN_00746E20() const
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
// GLOBAL: GAMEMD 0xB1CFB8
CellStruct DAT_00B1CFB8;
// GLOBAL: GAMEMD 0x87E8B8
AStar_00746000 DAT_0087E8B8;
// GLOBAL: GAMEMD 0x7F5C28
extern const double DAT_007F5C28 = 60.0;
// END defined globals
