// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   SuperWeaponTypeClass construction for loading, destruction and stream loading, read off
//   retail gamemd.exe v1.001 (vtable 0x7F4090). /Ob2: the scalar deleting destructor
//   carries the destructor body inline.
//   Address index: 0x6CE700 no-init ctor, 0x6CE740 dtor, 0x6CE800 Load, 0x6CEFE0 deleting dtor.

#include "FUNCTION.H"
#include "shared_constants_globals.h"

// GLOBAL: GAMEMD 0xA8E330 -- the super weapon type registry.
extern DynamicVectorClass<SuperWeaponTypeClass*> DAT_00A8E330;
// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;
// STRING: GAMEMD 0x8204FC -- "XXICON.SHP".
extern const char STR_DEFAULT_ICON[];

// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) -- loads a shape file by path.
void* __fastcall FUN_005B40B0(const char* name, bool flag);

// FUNCTION: GAMEMD 0x6CE5B0
SuperWeaponTypeClass::SuperWeaponTypeClass(const char* id)
    : AbstractTypeClass(id), WeaponType(0), RechargeVoice(-1), ChargingVoice(-1), ImpatientVoice(-1),
      SuspendVoice(-1), RechargeTime(0x1194), Type(-1), SidebarImage(0), Action(0), SpecialSound(-1),
      StartSound(-1), AuxBuilding(0), FlashSidebarTabFrames(-1), PreDependent(-1), UseChargeDrain(false),
      IsPowered(true), DisableableFromShell(false), AIDefendAgainst(false), PreClick(false),
      PostClick(false), ShowTimer(false), ManualControl(false), Range(0), LineMultiplier(0)
{
    vf_rtti_5();
    ArrayIndex = DAT_00A8E330.Count;
    DAT_00A8E330.AddItem(this);
    ID.CopyTo(CameoFile);
}

// FUNCTION: GAMEMD 0x6CE700
SuperWeaponTypeClass::SuperWeaponTypeClass(const AbstractNoInit& noInit)
    : AbstractTypeClass(noInit), SidebarImage(0), CameoFile(noInit)
{
}

// FUNCTION: GAMEMD 0x6CE740
SuperWeaponTypeClass::~SuperWeaponTypeClass()
{
    DAT_00A8E330.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x6CE800
// Reads the stream, rebuilds the object in place and reloads the cameo shape.
HRESULT __stdcall SuperWeaponTypeClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) SuperWeaponTypeClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&WeaponType);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&AuxBuilding);
    char path[0x200];
    _makepath(path, 0, 0, CameoFile, TypesShpExtension);
    SidebarImage = FUN_005B40B0(path, false);
    if (SidebarImage == 0) {
        SidebarImage = FUN_005B40B0(STR_DEFAULT_ICON, false);
    }
    return 0;
}

// SYNTHETIC: GAMEMD 0x6CEFE0
// SuperWeaponTypeClass scalar deleting destructor (primary slot 8), the destructor expanded in place.
