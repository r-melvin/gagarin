// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The TemporalClass block of retail .text (0x71A1F0..0x71B233): three of the
// unit's run-time initialisers, the constructors and destructor, Load, the
// per-frame update and the link helpers, and the primary-table slots 8, 11
// and 12, in retail address order. TemporalClass is declared in
// _layout/temporal_class.h. Rows of this block outside this partition are
// declared and bound by address only (the other initialisers, the Array
// initialiser 0x71A3D0 and its atexit 0x71A410, slot 13 0x71A650, Save
// 0x71A700, GetClassID 0x71A720, GetWarpPerStep 0x71AB10, 0x71ABC0, JustLetGo
// 0x71AD40, Detach 0x71ADE0 and 0x71AE50).

#include "FUNCTION.H"
#include "header_tuning_globals.h"
#include "temporal_cell.h"
#include "weapon_type_class.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new (CRT), called by the new-expressions.
// LIBRARY: GAMEMD 0x7C5F00 -- _ftol (CRT), the double-to-int conversions.
// GLOBAL: GAMEMD 0x7E1718 -- the shared double 1.0 the compiler's literal binds to.

// ---- run-time initialised copies of the shared tuning globals -------------

// GLOBAL: GAMEMD 0xB0EC78
extern double DAT_00B0EC78;
// GLOBAL: GAMEMD 0x7F5100
const double DAT_007F5100 = 60.0;

// GLOBAL: GAMEMD 0xB0ECC8
extern double DAT_00B0ECC8;
// GLOBAL: GAMEMD 0xB0ECB0
extern double DAT_00B0ECB0;
// GLOBAL: GAMEMD 0xB0ECB8
extern TuningCoordInit DAT_00B0ECB8;

// The append to TemporalClass::Array, the inlined DynamicVectorClass::AddItem
// in the same free-function shape as EMPulse_AddItem (combat/empulse_class.cpp).
static inline bool Temporal_AddItem(DynamicVectorClass<TemporalClass*>& v, TemporalClass* item)
{
    if (v.Count >= v.Capacity)
    {
        if (!v.IsAllocated && v.Capacity != 0)
            return false;
        if (v.CapacityIncrement <= 0)
            return false;
        if (!v.SetCapacity(v.Capacity + v.CapacityIncrement, 0))
            return false;
    }
    int i = v.Count++;
    v.Items[i] = item;
    return true;
}

// GLOBAL: GAMEMD 0x8871E0
extern RulesClass* DAT_008871E0;
// GLOBAL: GAMEMD 0xA83D4C
extern HouseClass* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xA8E7AC
extern int DAT_00A8E7AC;

// The 0x1C8-byte object 0x71A760 allocates and constructs with 0x421EA0
// (type, coordinate, then five scalars; RET 0x1C).
struct TemporalAnimView
{
    // FUNCTION: GAMEMD 0x421EA0 (decl; reloc)
    TemporalAnimView(void* type, const CoordStruct& where, int a, int b, int c, int d, char e);
    char opaque[0x1C8];
};
GG_STATIC_ASSERT(sizeof(TemporalAnimView) == 0x1C8);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- the square root of a double.
double __cdecl FUN_004CAC40(double value);

// The cell of a coordinate (lepton / 256 per axis), read through the reference.
inline TemporalCell TemporalCellOf(const CoordStruct& where)
{
    TemporalCell cell;
    cell.X = (short)(where.X / 256);
    cell.Y = (short)(where.Y / 256);
    return cell;
}

// FUNCTION: GAMEMD 0x65FA70 (decl; reloc) -- __fastcall (type in ECX, the cell by value).
bool FUN_0065FA70(int type, TemporalCell cell);
// FUNCTION: GAMEMD 0x752700 (decl; reloc) -- __fastcall (name, two ints).
void FUN_00752700(const char* name, int a, int b);

// Coordinate difference, read through the two references.
inline CoordStruct operator-(const CoordStruct& a, const CoordStruct& b)
{
    CoordStruct d;
    d.X = a.X - b.X;
    d.Y = a.Y - b.Y;
    d.Z = a.Z - b.Z;
    return d;
}

// The length of a coordinate, truncated to leptons.
inline int TemporalLength(const CoordStruct& c)
{
    return (int)FUN_004CAC40((double)c.X * c.X + (double)c.Y * c.Y + (double)c.Z * c.Z);
}

// The target as a unit, or null (`DEC; NEG; SBB; NOT; AND` on WhatAmI() == 1).
inline UnitClass* TemporalAsUnit(TechnoClass* p)
{
    if (p == 0)
        return 0;
    return (p->vf_11() == 1) ? static_cast<UnitClass*>(p) : 0;
}

// The target as a building, or null (`SUB 6; NEG; SBB; NOT; AND`).
inline BuildingClass* TemporalAsBuilding(TechnoClass* p)
{
    if (p == 0)
        return 0;
    return (p->vf_11() == 6) ? static_cast<BuildingClass*>(p) : 0;
}

// FUNCTION: GAMEMD 0x71A450
TemporalClass::TemporalClass()
{
    Temporal_AddItem(Array, this);
}

// FUNCTION: GAMEMD 0x71A4E0
TemporalClass::TemporalClass(TechnoClass* owner)
{
    Owner = owner;
    Target = 0;
    unknown_2C = TemporalTimer();
    unknown_40 = 0;
    unknown_44 = 0;
    Temporal_AddItem(Array, this);
    unknown_48 = 0;
    unknown_4C = 0;
    unknown_38 = 0;
    unknown_3C = 0;
}

// FUNCTION: GAMEMD 0x71A5A0
TemporalClass::TemporalClass(const AbstractNoInit& noInit)
    : AbstractClass(noInit), unknown_2C(noInit)
{
}

// FUNCTION: GAMEMD 0x71A5D0
TemporalClass::~TemporalClass()
{
    Array.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x71A660
HRESULT __stdcall TemporalClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr >= 0) {
        new (this) TemporalClass(AbstractNoInit());
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Owner);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Target);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_40);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_44);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_38);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_3C);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x71A700
HRESULT __stdcall TemporalClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x71A760
void TemporalClass::vf_23()
{
    if (Target && Target->TemporalTargetingMe == this && unknown_40) {
        Target->TemporalTargetingMe = 0;
        Target->BeingWarpedOut = 0;
        Detach();
        return;
    }
    if (Owner && Owner->InOpenToppedTransport && Target) {
        CoordStruct delta = Owner->vf_18() - Target->vf_18();
        if (TemporalLength(delta) > DAT_008871E0->OpenToppedWarpDistance << 8) {
            FUN_0071ABC0();
            return;
        }
    }
    int helper = 0;
    if (unknown_44)
        helper = unknown_44->GetWarpPerStep(1);
    unknown_4C = Owner->vf_254(Owner->vf_185(0))->WeaponType->Damage;
    unknown_48 -= unknown_4C + helper;
    if (unknown_48 > 0)
        return;
    if (!Target)
        FUN_0071ADB0();
    else
        new TemporalAnimView(DAT_008871E0->WarpAway, CoordStruct(Target->Location), 0, 1, 0x600, 0, 0);
    if (Target) {
        if (Owner->vf_33()->Trainable) {
            TechnoTypeClass* targetType = Target->vf_33();
            TechnoTypeClass* ownerType = Owner->vf_33();
            Owner->Veterancy.FUN_0074FF50(ownerType->vf_33(Owner->Owner),
                                          targetType->vf_33(Target->Owner));
        }
        if (Target->vf_11() == 6) {
            BuildingClass* building = static_cast<BuildingClass*>(Target);
            if (building) {
                if (building->vf_258() > 0)
                    building->FUN_004585C0(0);
                if (DAT_00A8E7AC == 0) {
                    while (building->Passengers.FirstPassenger) {
                        FootClass* passenger = building->Passengers.RemoveFirstPassenger();
                        if (passenger)
                            delete passenger;
                    }
                }
            }
            if (unknown_3C) {
                unknown_3C->SetOnHold(0);
                unknown_3C = 0;
            }
            if (Target->BunkerLinkedItem)
                TemporalAsBuilding(Target)->FUN_004593A0();
            if (Target->SlaveManager)
                static_cast<SlaveManagerClass*>(Target->SlaveManager)->FUN_006B0AE0(Owner, 0);
            Target->vf_238(Owner);
            Target->vf_56(Owner);
            Target->vf_62();
            building->Owner->RecheckTechTree = 1;
        } else {
            if (Target->BunkerLinkedItem)
                TemporalAsBuilding(Target->BunkerLinkedItem)->ClearBunker();
            if (Target->SlaveManager)
                static_cast<SlaveManagerClass*>(Target->SlaveManager)->FUN_006B0AE0(Owner, 0);
            Target->vf_238(Owner);
            Target->vf_56(Owner);
            Target->vf_62();
        }
        if (Owner)
            Owner->EnterIdleMode(0, 1);
    }
    FUN_0071ADB0();
}

// FUNCTION: GAMEMD 0x71AB60
void TemporalClass::FUN_0071AB60(void* object)
{
    if (object == Owner) {
        if (Target) {
            FUN_0071ABC0();
            Target = 0;
        }
    } else if (object == Target) {
        FUN_0071ADB0();
    }
}

// FUNCTION: GAMEMD 0x71ACB0
void TemporalClass::FUN_0071ACB0()
{
    if (Target) {
        Target->TemporalTargetingMe = 0;
        Target->BeingWarpedOut = 0;
        Target = 0;
    }
}

// FUNCTION: GAMEMD 0x71ACD0
void TemporalClass::FUN_0071ACD0()
{
    if (Target) {
        Target->TemporalTargetingMe = 0;
        Target->BeingWarpedOut = 0;
        if (Target->vf_11() == 6) {
            BuildingClass* building = static_cast<BuildingClass*>(Target);
            building->Owner->RecheckPower = 1;
            building->EnableTemporal();
            building->Owner->RecheckTechTree = 1;
        }
        Target->vf_73(2);
    }
}

// FUNCTION: GAMEMD 0x71AD30
void TemporalClass::FUN_0071AD30()
{
}

// FUNCTION: GAMEMD 0x71ADB0
void TemporalClass::FUN_0071ADB0()
{
    Target = 0;
    unknown_44 = 0;
    unknown_40 = 0;
    unknown_3C = 0;
    unknown_38 = 0;
    if (Owner)
        Owner->EnterIdleMode(0, 1);
}

// FUNCTION: GAMEMD 0x71AF20
// PARTIAL 99.0% (one register). After the chain insertion retail reloads the
// target into ECX, cl into EAX. Tried: the insertion branch first (18.2%),
// an explicit != 0 test, and the original order (kept).
void TemporalClass::FUN_0071AF20(TechnoClass* target)
{
    if (target) {
        if (target->SpawnManager)
            static_cast<SpawnManagerClass*>(target->SpawnManager)->KillNodes();
        if (target->CaptureManager)
            static_cast<CaptureManagerClass*>(target->CaptureManager)->FreeAll();
    }
    TemporalClass* own = Owner->TemporalImUsing;
    if (own && own->Target)
        own->FUN_0071ABC0();
    if (!FUN_0071AE50(target) || Owner->TemporalTargetingMe)
        return;
    Target = target;
    TemporalClass* head = target->TemporalTargetingMe;
    if (head == 0) {
        target->TemporalTargetingMe = this;
        unknown_48 = Target->vf_33()->Strength * 10;
        if (Target && Target->vf_11() == 1 && static_cast<UnitTypeClass*>(TemporalAsUnit(Target)->Type)->Harvester
            && Target->Owner == DAT_00A83D4C) {
            TemporalCell cell = TemporalCellOf(Target->vf_19(0));
            if (FUN_0065FA70(4, cell)) {
                // STRING: GAMEMD 0x824784
                FUN_00752700("EVA_OreMinerUnderAttack", -1, -1);
            }
        }
        if (Target->vf_11() == 6 && !Target->vf_33()->Insignificant && !Target->vf_32())
            Target->Owner->FUN_004F93E0(TemporalAsBuilding(Target));
    } else {
        unknown_40 = head;
        unknown_44 = head->unknown_44;
        head->unknown_44 = this;
        if (unknown_44)
            unknown_44->unknown_40 = this;
    }
    Target->BeingWarpedOut = 1;
    if (Target->vf_33()->IsGattling)
        Target->FUN_0070E000(1);
    if (Target->vf_11() == 6) {
        BuildingClass* building = static_cast<BuildingClass*>(Target);
        building->Owner->RecheckPower = 1;
        building->DisableTemporal();
        building->Owner->RecheckTechTree = 1;
    }
    Target->vf_73(2);
    TemporalClass* other = Target->TemporalImUsing;
    if (other && other->Target)
        other->FUN_0071ABC0();
    if (DAT_00A83D4C)
        Target->vf_84();
}

// FUNCTION: GAMEMD 0x71B190
int TemporalClass::vf_12()
{
    return sizeof(TemporalClass);
}

// FUNCTION: GAMEMD 0x71B1A0
int TemporalClass::vf_11()
{
    return 0x46;
}

// FUNCTION: GAMEMD 0x71B1B0
// The scalar deleting destructor the compiler emits for ~TemporalClass (slot 8).
