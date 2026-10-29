// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small UnitClass virtual overrides read off retail gamemd.exe v1.001 (vtable 0x7F5C70).
//   Functions are in ascending retail address order.

#include "../_layout/unit_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/house_class.h"
#include "../core/frame_counter.h"

// EBolt: the electric-bolt effect object held at UnitClass+0x6DC.
struct EBolt
{
    void FUN_004C2C10();   // 0x4C2C10, releases the bolt
};

#include "../_layout/player_ptr_00a83d4c.h"
// GLOBAL: GAMEMD 0x7E2800 -- 0.0, read from memory rather than FLDZ.
extern const double DAT_007E2800;

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

// FUNCTION: GAMEMD 0x744180
// True while the unload timer is in none of its three active states.
bool UnitClass::vf_167()
{
    if (UnloadTimer.FUN_004A5110() || UnloadTimer.FUN_004A5130() || UnloadTimer.FUN_004A51B0()) {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x746C90
// Counts as EMP-disabled while dying, otherwise defers to TechnoClass.
bool UnitClass::IsUnderEMP()
{
    return DeathFrameCounter != -1 || TechnoClass::IsUnderEMP();
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

// FUNCTION: GAMEMD 0x746E30
DirStruct UnitClass::vf_170()
{
    UnitTypeClass* type = static_cast<UnitTypeClass*>(this->Type);
    if (type->bools_C8C[0x15]) {
        return SecondaryFacing.FUN_004C93D0();
    }
    return PrimaryFacing.FUN_004C93D0();
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

// FUNCTION: GAMEMD 0x740B10
int UnitClass::vf_151()
{
    IsHarvesting = 0;
    if (!UnloadTimer.FUN_004A51D0()) {
        UnloadTimer.FUN_004A5240(static_cast<UnitTypeClass*>(this->Type)->DeployTime);
    }
    return FootClass::vf_151();
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

// FUNCTION: GAMEMD 0x746DB0
// True while the unit is in the middle of deploying or undeploying.
bool UnitClass::FUN_00746DB0()
{
    return Deploying || Undeploying;
}

// FUNCTION: GAMEMD 0x744600
// Free the attached electric bolt, then save as a FootClass.
HRESULT __stdcall UnitClass::Save(IStream* pStm, BOOL fClearDirty)
{
    if (ElectricBolt) {
        static_cast<EBolt*>(ElectricBolt)->FUN_004C2C10();
        ElectricBolt = 0;
    }
    return FootClass::Save(pStm, fClearDirty);
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

// FUNCTION: GAMEMD 0x7438B0
// Stored tiberium value scaled by the owner's multiplier.
int UnitClass::FUN_007438B0()
{
    float value = (float)Tiberium.GetTotalValue();
    return (int)(Owner->FUN_0050C160() * value);
}

// FUNCTION: GAMEMD 0x740E60
void UnitClass::FUN_00740E60()
{
    UnloadTimer.FUN_004A5240(static_cast<UnitTypeClass*>(this->Type)->DeployTime);
}
