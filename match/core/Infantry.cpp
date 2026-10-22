// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Infantry.CPP. The name is the source-file string at 0x825560
//   in retail gamemd.exe v1.001, passed by the assert at 0x51f2d2 inside this object's
//   code range (0x517840-0x52348f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// Retail IPersist::GetClassID (slot 3 of each class's primary vtable) copies a
// 16-byte CLSID global to the caller and returns E_POINTER for a null pointer.
// The owning class of each address is read from the RTTI-named vtable that holds
// it in slot 3. Each class is declared here only as far as this one virtual
// (no layout is claimed); the bodies move into the canonical class once it exists.

#include "deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include <objidl.h>
#include "../_layout/side_class.h"
#include "../_layout/wave_class.h"

// GLOBAL: GAMEMD 0x007E9660 -- CLSID of AircraftClass.
extern const CLSID DAT_007E9660;
// GLOBAL: GAMEMD 0x007E95B0 -- CLSID of AircraftTypeClass.
extern const CLSID DAT_007E95B0;
// GLOBAL: GAMEMD 0x007E98E0 -- CLSID of AirstrikeClass.
extern const CLSID DAT_007E98E0;
// GLOBAL: GAMEMD 0x007E9960 -- CLSID of AITriggerTypeClass.
extern const CLSID DAT_007E9960;
// GLOBAL: GAMEMD 0x007E99A0 -- CLSID of AlphaShapeClass.
extern const CLSID DAT_007E99A0;
// GLOBAL: GAMEMD 0x007E9670 -- CLSID of AnimClass.
extern const CLSID DAT_007E9670;
// GLOBAL: GAMEMD 0x007E9620 -- CLSID of AnimTypeClass.
extern const CLSID DAT_007E9620;
// GLOBAL: GAMEMD 0x007E9980 -- CLSID of NeuronClass.
extern const CLSID DAT_007E9980;
// GLOBAL: GAMEMD 0x007E96E0 -- CLSID of BulletClass.
extern const CLSID DAT_007E96E0;
// GLOBAL: GAMEMD 0x007E95D0 -- CLSID of BulletTypeClass.
extern const CLSID DAT_007E95D0;
// GLOBAL: GAMEMD 0x007E9900 -- CLSID of CampaignClass.
extern const CLSID DAT_007E9900;
// GLOBAL: GAMEMD 0x007E9930 -- CLSID of CellClass.
extern const CLSID DAT_007E9930;
// GLOBAL: GAMEMD 0x007E9890 -- CLSID of DiskLaserClass.
extern const CLSID DAT_007E9890;
// GLOBAL: GAMEMD 0x007E9A30 -- CLSID of DriveLocomotionClass.
extern const CLSID DAT_007E9A30;
// GLOBAL: GAMEMD 0x007E9940 -- CLSID of EMPulseClass.
extern const CLSID DAT_007E9940;
// GLOBAL: GAMEMD 0x007E9820 -- CLSID of FactoryClass.
extern const CLSID DAT_007E9820;
// GLOBAL: GAMEMD 0x007E9990 -- CLSID of FoggedObjectClass.
extern const CLSID DAT_007E9990;
// GLOBAL: GAMEMD 0x007E9680 -- CLSID of InfantryClass.
extern const CLSID DAT_007E9680;
// GLOBAL: GAMEMD 0x007E95A0 -- CLSID of InfantryTypeClass.
extern const CLSID DAT_007E95A0;
// GLOBAL: GAMEMD 0x007E9640 -- CLSID of IsometricTileClass.
extern const CLSID DAT_007E9640;
// GLOBAL: GAMEMD 0x007E95F0 -- CLSID of IsometricTileTypeClass.
extern const CLSID DAT_007E95F0;
// GLOBAL: GAMEMD 0x007E9AC0 -- CLSID of JumpjetLocomotionClass.
extern const CLSID DAT_007E9AC0;
// GLOBAL: GAMEMD 0x007E98F0 -- CLSID of LightSourceClass.
extern const CLSID DAT_007E98F0;
// GLOBAL: GAMEMD 0x007E98A0 -- CLSID of ParasiteClass.
extern const CLSID DAT_007E98A0;
// GLOBAL: GAMEMD 0x007E98C0 -- CLSID of RadSiteClass.
extern const CLSID DAT_007E98C0;
// GLOBAL: GAMEMD 0x007E97A0 -- CLSID of ScriptClass.
extern const CLSID DAT_007E97A0;
// GLOBAL: GAMEMD 0x007E97B0 -- CLSID of ScriptTypeClass.
extern const CLSID DAT_007E97B0;
// GLOBAL: GAMEMD 0x007E9AB0 -- CLSID of ShipLocomotionClass.
extern const CLSID DAT_007E9AB0;
// GLOBAL: GAMEMD 0x007E9910 -- CLSID of SideClass.
extern const CLSID DAT_007E9910;
// GLOBAL: GAMEMD 0x007E9870 -- CLSID of SlaveManagerClass.
extern const CLSID DAT_007E9870;
// GLOBAL: GAMEMD 0x007E9860 -- CLSID of SpawnManagerClass.
extern const CLSID DAT_007E9860;
// GLOBAL: GAMEMD 0x007E9580 -- CLSID of SuperClass.
extern const CLSID DAT_007E9580;
// GLOBAL: GAMEMD 0x007E9570 -- CLSID of SuperWeaponTypeClass.
extern const CLSID DAT_007E9570;
// GLOBAL: GAMEMD 0x007E9950 -- CLSID of Tactical.
extern const CLSID DAT_007E9950;
// GLOBAL: GAMEMD 0x007E9800 -- CLSID of TActionClass.
extern const CLSID DAT_007E9800;
// GLOBAL: GAMEMD 0x007E97C0 -- CLSID of TagClass.
extern const CLSID DAT_007E97C0;
// GLOBAL: GAMEMD 0x007E97D0 -- CLSID of TagTypeClass.
extern const CLSID DAT_007E97D0;
// GLOBAL: GAMEMD 0x007E9770 -- CLSID of TaskForceClass.
extern const CLSID DAT_007E9770;
// GLOBAL: GAMEMD 0x007E9760 -- CLSID of TeamClass.
extern const CLSID DAT_007E9760;
// GLOBAL: GAMEMD 0x007E9780 -- CLSID of TeamTypeClass.
extern const CLSID DAT_007E9780;
// GLOBAL: GAMEMD 0x007E9A90 -- CLSID of TeleportLocomotionClass.
extern const CLSID DAT_007E9A90;
// GLOBAL: GAMEMD 0x007E98D0 -- CLSID of TemporalClass.
extern const CLSID DAT_007E98D0;
// GLOBAL: GAMEMD 0x007E9810 -- CLSID of TEventClass.
extern const CLSID DAT_007E9810;
// GLOBAL: GAMEMD 0x007E9920 -- CLSID of TiberiumClass.
extern const CLSID DAT_007E9920;
// GLOBAL: GAMEMD 0x007E97E0 -- CLSID of TriggerClass.
extern const CLSID DAT_007E97E0;
// GLOBAL: GAMEMD 0x007E97F0 -- CLSID of TriggerTypeClass.
extern const CLSID DAT_007E97F0;
// GLOBAL: GAMEMD 0x007E9750 -- CLSID of TubeClass.
extern const CLSID DAT_007E9750;
// GLOBAL: GAMEMD 0x007E9A50 -- CLSID of TunnelLocomotionClass.
extern const CLSID DAT_007E9A50;
// GLOBAL: GAMEMD 0x007E96F0 -- CLSID of UnitClass.
extern const CLSID DAT_007E96F0;
// GLOBAL: GAMEMD 0x007E9590 -- CLSID of UnitTypeClass.
extern const CLSID DAT_007E9590;
// GLOBAL: GAMEMD 0x007E9650 -- CLSID of VoxelAnimClass.
extern const CLSID DAT_007E9650;
// GLOBAL: GAMEMD 0x007E9790 -- CLSID of VoxelAnimTypeClass.
extern const CLSID DAT_007E9790;
// GLOBAL: GAMEMD 0x007E99B0 -- CLSID of VeinholeMonsterClass.
extern const CLSID DAT_007E99B0;
// GLOBAL: GAMEMD 0x007E9A60 -- CLSID of WalkLocomotionClass.
extern const CLSID DAT_007E9A60;
// GLOBAL: GAMEMD 0x007E9840 -- CLSID of WarheadTypeClass.
extern const CLSID DAT_007E9840;
// GLOBAL: GAMEMD 0x007E9720 -- CLSID of WaveClass.
extern const CLSID DAT_007E9720;
// GLOBAL: GAMEMD 0x007E9850 -- CLSID of WaypointPathClass.
extern const CLSID DAT_007E9850;
// GLOBAL: GAMEMD 0x007E9830 -- CLSID of WeaponTypeClass.
extern const CLSID DAT_007E9830;

class AircraftClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class AircraftTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class AirstrikeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class AITriggerTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class AlphaShapeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class AnimClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class AnimTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class NeuronClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class BulletClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class BulletTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class CampaignClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class CellClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class DiskLaserClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class DriveLocomotionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class EMPulseClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class FactoryClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class FoggedObjectClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class InfantryClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class InfantryTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class IsometricTileClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class IsometricTileTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class JumpjetLocomotionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class LightSourceClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class ParasiteClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class RadSiteClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class ScriptClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class ScriptTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class ShipLocomotionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class SlaveManagerClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class SpawnManagerClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class SuperClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class SuperWeaponTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class Tactical {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TActionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TagClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TagTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TaskForceClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TeamClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TeamTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TeleportLocomotionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TemporalClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TEventClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TiberiumClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TriggerClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TriggerTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TubeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TunnelLocomotionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class UnitClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class UnitTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class VoxelAnimClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class VoxelAnimTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class VeinholeMonsterClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class WalkLocomotionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class WarheadTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class WaypointPathClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class WeaponTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};

#include "trivial_tu099_b_methods.h"

#include "trivial_tu099_methods.h"

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

// FUNCTION: GAMEMD 0x517870
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00517870()
{
    DAT_00A8F238 = DAT_00A8F1E8 / DAT_007EAEE8;
}

// FUNCTION: GAMEMD 0x517890
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00517890()
{
    DAT_00A8F220 = DAT_007E1718 / DAT_00A8F238;
}

// FUNCTION: GAMEMD 0x517A10
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00517A10()
{
    DAT_00A8F230 = 0;
    DAT_00A8F228 = 0x80;
    DAT_00A8F22C = 0x80;
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x51FAF0
// Member getter (dword). Vtable slot 34 of InfantryClass (RTTI).
int Obj_0051FAF0::FUN_0051FAF0() const
{
    return unknown_6C0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5216C0
// Tail-forwards to another function. Vtable slot 27 of InfantryClass (RTTI).
void FUN_005216C0(Obj_005216C0* a1, int a2)
{
    FUN_004DED70(a1, a2);
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x522540
// Member getter (byte).
unsigned char Obj_00522540::FUN_00522540() const
{
    return unknown_6C0->unknown_6AC;
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x522A50
// Empty function that pops its stack arguments.
void __stdcall FUN_00522A50(int a1)
{
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x523350
void* Obj_523350::FUN_523350(unsigned int flags)
{
    FUN_00517D90(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}
