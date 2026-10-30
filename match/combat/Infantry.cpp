// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Infantry.CPP. The name is the source-file string at 0x825560
//   in retail gamemd.exe v1.001, passed by the assert at 0x51f2d2 inside this object's
//   code range (0x517840-0x52348f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.

#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include <objidl.h>
#include "../_layout/side_class.h"
#include "../_layout/wave_class.h"

// GLOBAL: GAMEMD 0x007E9680 -- CLSID of InfantryClass.
extern const CLSID DAT_007E9680;

#include "../core/trivial_tu099_b_methods.h"

#include "../core/trivial_tu099_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EAEE8
extern const double DAT_007EAEE8;
// GLOBAL: GAMEMD 0xA8F1E8
extern double DAT_00A8F1E8;
// GLOBAL: GAMEMD 0xA8F220
extern double DAT_00A8F220;
// GLOBAL: GAMEMD 0xA8F228
extern int DAT_00A8F228;
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

#include "../_layout/infantry_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../core/frame_counter.h"
#include "../_layout/house_class.h"
#include "../movement/loco_interfaces.h"
#include "../_layout/building_class.h"
#include "../_layout/cell_class.h"
#include "../core/rules_class.h"
#include "../_layout/map_0087f7e8.h"
#include "../_layout/team_class.h"

// Offsets this TU relies on, each read from an instruction in the matched bodies.
GG_STATIC_ASSERT(offsetof(CellClass, OccupationFlags)    == 0x124);  // 0x5217C0
GG_STATIC_ASSERT(offsetof(CellClass, AltOccupationFlags) == 0x128);  // 0x5217C0
GG_STATIC_ASSERT(offsetof(CellClass, Flags)              == 0x140);  // 0x5217C0
GG_STATIC_ASSERT(offsetof(InfantryClass, Type)              == 0x6C0);  // 0x51AA10
GG_STATIC_ASSERT(offsetof(InfantryClass, SequenceAnim)      == 0x6C4);  // 0x522510
GG_STATIC_ASSERT(offsetof(InfantryClass, PanicDurationLeft) == 0x6D4);  // 0x521C10
GG_STATIC_ASSERT(offsetof(InfantryClass, Technician)        == 0x6D9);  // 0x521C90
GG_STATIC_ASSERT(offsetof(InfantryTypeClass, Fearless)      == 0xEBC);  // 0x521C10

// The FootClass locomotor is an ILocomotion COM smart pointer. Dereferencing it
// checks for null and raises E_POINTER through the library helper (retail 0x7DC720),
// then reloads the interface pointer; the check is inlined at every use.
extern void __stdcall _com_issue_error(long hr);
struct ILocomotionPtr
{
    ILocomotion* m_pInterface;
    ILocomotion* operator->() const
    {
        if (m_pInterface == 0) {
            _com_issue_error(0x80004003);
        }
        return m_pInterface;
    }
};
GG_STATIC_ASSERT(offsetof(InfantryClass, Locomotor) == 0x674);
static inline ILocomotionPtr* LocomotorOf(InfantryClass* unit)
{
    return reinterpret_cast<ILocomotionPtr*>(&unit->Locomotor);
}

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
// GLOBAL: GAMEMD 0xA8F234 -- the height added to the floor before the bridge test.
extern int DAT_00A8F234;

// FUNCTION: GAMEMD 0x4810A0 (decl; reloc) -- the sub-cell slot a coordinate falls in.
int FUN_004810A0(CoordStruct* coord);

// The elapsed-time arithmetic of a CDTimerClass read, as retail inlines it (0x521C90).
static inline int TimerRemaining(const CDTimerClass& timer)
{
    int timeLeft = timer.TimeLeft;
    if (timer.StartTime != -1) {
        int elapsed = CurrentFrame - timer.StartTime;
        if (elapsed < timeLeft) {
            return timeLeft - elapsed;
        }
        return 0;
    }
    return timeLeft;
}

// GLOBAL: GAMEMD 0x8871E0
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;
// GLOBAL: GAMEMD 0xA83D4C -- the local player's house.
extern HouseClass* CurrentPlayer;

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- resolve a label to its localised text; the
// last two arguments are the assert file and line.
const wchar_t* FUN_00734E60(const char* label, int flags, const char* file, int line);

// GLOBAL: GAMEMD 0x825560 -- "D:\\ra2mdpost\\Infantry.CPP"
extern const char DAT_00825560[];

// FUNCTION: GAMEMD 0x51AA10
void InfantryClass::vf_10(void* a1, bool a2)
{
    FootClass::vf_10(a1, a2);
    if (this->Type == a1) {
        this->Type = 0;
    }
}

// FUNCTION: GAMEMD 0x51DF10
bool InfantryClass::vf_53()
{
    (*LocomotorOf(this))->StopMovementAnimation();
    this->unknown_int_6E8 = 2;
    this->Crawling = false;
    this->SequenceAnim = 0;
    return FootClass::vf_53();
}

// FUNCTION: GAMEMD 0x51DF60
int InfantryClass::vf_243(AbstractClass* a1, int a2)
{
    this->IsFiring = 0;
    int result = TechnoClass::vf_243(a1, a2);
    if (result && !this->InLimbo && this->Type->Fraidycat && this->Ammo == 0) {
        this->PanicDurationLeft = 300;
        if (this->vf_97() == 1 || this->vf_97() == 15) {
            this->vf_122(5, false);
        }
    }
    return result;
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x51FAF0
// Member getter (dword). Vtable slot 34 of InfantryClass (RTTI).
int Obj_0051FAF0::FUN_0051FAF0() const
{
    return unknown_6C0;
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
    if (DAT_00A8F234 + MapClass_Instance.GetCellFloorHeight(*coord) <= coord->Z) {
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
// Branching. Vtable slot 338 of InfantryClass (RTTI).
void Obj_00521B20::FUN_00521B20()
{
    int t1 = unknown_6C4;
    if (t1 == 6)
    {
        unknown_6C4 = -1;
    }
    if (t1 == 3)
    {
        unknown_6C4 = -1;
    }
    if (t1 == 0x11)
    {
        unknown_6C4 = -1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x521B40
// Branching. Vtable slot 339 of InfantryClass (RTTI).
void Obj_00521B40::FUN_00521B40()
{
    if (unknown_6E4 != 0)
    {
        unknown_6E4 = 0;
        vf_342(0x1B, 0, 0);
    }
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
    crc->FUN_004A1D50(TimerRemaining(this->unknown_Timer_6C8));
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
// Stores its argument in a member. Vtable slot 325 of InfantryClass (RTTI).
void Obj_005220F0::FUN_005220F0()
{
    unknown_6D8 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5224D0
// Member getter (byte). Vtable slot 204 of InfantryClass (RTTI).
unsigned char Obj_005224D0::FUN_005224D0() const
{
    return unknown_6C0->unknown_EC3;
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
int InfantryClass::FUN_00522510()
{
    int s = this->SequenceAnim;
    if (s == 0x1B || s == 0x1C || s == 0x1D || s == 0x1E) {
        return 1;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x522540
// Member getter (byte).
unsigned char Obj_00522540::FUN_00522540() const
{
    return unknown_6C0->unknown_6AC;
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x522A50
// Empty function that pops its stack arguments.
void __stdcall FUN_00522A50(int a1)
{
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
int InfantryClass::FUN_00522CB0()
{
    int s = this->SequenceAnim;
    if (s == 11 || s == 12 || s == 13 || s == 14 || s == 15
        || s == 0x22 || s == 0x23 || s == 0x24 || s == 0x14 || s == 0x15) {
        return 1;
    }
    return 0;
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

// FUNCTION: GAMEMD 0x522FC0
bool InfantryClass::FUN_00522FC0()
{
    return this->vf_97() == 10;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5232F0
// Returns a constant. Vtable slot 12 of InfantryClass (RTTI).
int Obj_005232F0::FUN_005232F0() const
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
// Returns a constant. Vtable slot 11 of InfantryClass (RTTI).
int Obj_00523340::FUN_00523340() const
{
    return 0xF;
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
