// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TAction.CPP. The name is the source-file string at 0x842bf8
//   in retail gamemd.exe v1.001, passed by the assert at 0x6de10c inside this object's
//   code range (0x6dcd70-0x6e4b4f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The six ID-resolving commands, ordered ascending by retail address.
//
// Two phrasing points carry the whole body. The three failure exits have to be
// one shared `goto`, not three `return false` statements: written as returns cl
// duplicates the two-instruction failure tail at each site and the layout
// diverges from the first branch (14.3%). And the predicate arm has to be a
// ternary feeding one assignment rather than an if/else assigning in both arms,
// which is what keeps retail's shared `MOV ECX,ESI` ahead of the test.
//
// Nine small guarded predicates across three shapes: a flag-gated
// out-parameter copy, a bool-selected float constant, and a null-guarded relay.
// Within a shape the bodies are byte-identical apart from the member offset,
// the float constant or the relayed call displacement, so each is written once
// as a macro and expanded per instantiation. Ordered ascending by retail
// address.
//
// Retail IPersist::GetClassID (slot 3 of each class's primary vtable) copies a
// 16-byte CLSID global to the caller and returns E_POINTER for a null pointer.
// The owning class of each address is read from the RTTI-named vtable that holds
// it in slot 3. Each class is declared here only as far as this one virtual
// (no layout is claimed); the bodies move into the canonical class once it exists.

#include "../ai/taction_class_mode_methods.h"

#include "id_resolve_command_sweep.h"

#include "leftover_predicate_sweep.h"

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

#include "trivial_tu230_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F43B8
extern const double DAT_007F43B8;
// GLOBAL: GAMEMD 0xB0E688
extern double DAT_00B0E688;
// GLOBAL: GAMEMD 0xB0E6C0
extern double DAT_00B0E6C0;
// GLOBAL: GAMEMD 0xB0E6C8
extern int DAT_00B0E6C8;
// GLOBAL: GAMEMD 0xB0E6CC
extern int DAT_00B0E6CC;
// GLOBAL: GAMEMD 0xB0E6D0
extern int DAT_00B0E6D0;
// GLOBAL: GAMEMD 0xB0E6D8
extern double DAT_00B0E6D8;

// FUNCTION: GAMEMD 0x6DCDA0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006DCDA0()
{
    DAT_00B0E6D8 = DAT_00B0E688 / DAT_007F43B8;
}

// FUNCTION: GAMEMD 0x6DCDC0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006DCDC0()
{
    DAT_00B0E6C0 = DAT_007E1718 / DAT_00B0E6D8;
}

// FUNCTION: GAMEMD 0x6DCF40
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_006DCF40()
{
    DAT_00B0E6D0 = 0;
    DAT_00B0E6C8 = 0x80;
    DAT_00B0E6CC = 0x80;
}

// FUNCTION: GAMEMD 0x6E0040
// Returns a constant boolean; pops its stack arguments.
bool __stdcall FUN_006E0040(int a1, int a2, int a3, int a4)
{
    return true;
}

// FUNCTION: GAMEMD 0x6E0250
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E0250::FUN_006E0250(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->unknown_34A7 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E0270
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E0270::FUN_006E0270(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->unknown_34A6 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E0290
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E0290::FUN_006E0290(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->unknown_34A8 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E0ED0
// Branching.
unsigned char Obj_006E0ED0::FUN_006E0ED0(Arg1_006E0ED0* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_54EC = unknown_90;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x6E0FA0
// Calls other functions.
bool Obj_006E0FA0::FUN_006E0FA0(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->FUN_00689670(unknown_90, 1);
    return true;
}

// FUNCTION: GAMEMD 0x6E0FC0
// Calls other functions.
bool Obj_006E0FC0::FUN_006E0FC0(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->FUN_00689670(unknown_90, 0);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1720
// Calls other functions.
bool Obj_006E1720::FUN_006E1720(int a1, int a2, int a3, int a4)
{
    FUN_005BF390(unknown_90, false);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1740
// Calls other functions.
bool Obj_006E1740::FUN_006E1740(int a1, int a2, int a3, int a4)
{
    FUN_005BF390(unknown_90, true);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1B90
// Calls other functions.
bool FUN_006E1B90(Obj_006E1B90* a1, int a2, int a3, int a4, int a5, int a6)
{
    FUN_00720B20(DAT_00A83D10, a2, a1->unknown_90);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1BB0
// Calls other functions.
bool Obj_006E1BB0::FUN_006E1BB0(int a1, int a2, int a3, int a4)
{
    FUN_00752480(unknown_90, 2, -1);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1F90
// Branching.
unsigned char Obj_006E1F90::FUN_006E1F90(int a1, int a2, int a3, int a4)
{
    if (unknown_30 != 0)
    {
        unknown_30->FUN_006F0A70();
        return 1;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1FB0
// Branching.
unsigned char FUN_006E1FB0(Obj_006E1FB0* a1, int a2, int a3, int a4, int a5, int a6)
{
    if (a1->unknown_30 != 0)
    {
        return FUN_0065D8E0(a1->unknown_30, -1);
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E1FD0
// Branching.
unsigned char Obj_006E1FD0::FUN_006E1FD0(int a1, int a2, int a3, int a4)
{
    if (unknown_30 != 0)
    {
        if (unknown_44 != -1)
        {
            return FUN_0065D8E0(unknown_30, unknown_44);
        }
        return 0;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E21D0
// Returns a constant boolean; pops its stack arguments.
bool __stdcall FUN_006E21D0(int a1, int a2, int a3, int a4)
{
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E2950
// Calls other functions.
bool FUN_006E2950(int a1, int a2, int a3, int a4, int a5, int a6)
{
    FUN_00577C90(DAT_0087F7E8, a2, a3);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E2BE0
// Calls other functions.
bool Obj_006E2BE0::FUN_006E2BE0(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->FUN_00689910(unknown_90, 1);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E2C00
// Calls other functions.
bool Obj_006E2C00::FUN_006E2C00(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->FUN_00689910(unknown_90, 0);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E2E20
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E2E20::FUN_006E2E20(int a1, int a2, int a3, int a4)
{
    DAT_008871E0->unknown_1670 = unknown_90;
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E2E40
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E2E40::FUN_006E2E40(int a1, int a2, int a3, int a4)
{
    DAT_008871E0->unknown_1668 = unknown_90;
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E30C0
bool __fastcall IdCommandOwner::FUN_006E30C0(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_0050D440(obj);
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3120
bool __fastcall IdCommandOwner::FUN_006E3120(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_0050D320(obj);
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3180
bool __fastcall IdCommandOwner::FUN_006E3180(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_004FC6D0(obj);
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E31E0
bool __fastcall IdCommandOwner::FUN_006E31E0(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_004FC790(obj);
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3240
bool __fastcall IdCommandOwner::FUN_006E3240(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_004FC820(obj);
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E32A0
bool __fastcall IdCommandOwner::FUN_006E32A0(int, int, int, void* handle, int)
{
    int id = this->StoredId;
    void* obj;

    if (handle == 0) goto fail;

    if (id == 0x2325) {
        obj = FUN_00726910(handle);
    } else {
        if (id == -1) goto fail;

        obj = FUN_00510F60(id) ? FUN_00510ED0(id) : FUN_00502D30(id);
    }

    if (obj == 0) goto fail;

    FUN_004FC8D0(obj);
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3300
// Branching.
unsigned char Obj_006E3300::FUN_006E3300(Arg1_006E3300* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_565C = unknown_90;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3320
// Branching.
unsigned char Obj_006E3320::FUN_006E3320(Arg1_006E3320* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_5660 = unknown_90;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3340
// Branching.
unsigned char Obj_006E3340::FUN_006E3340(Arg1_006E3340* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_5664 = unknown_90;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3360
// Branching.
unsigned char Obj_006E3360::FUN_006E3360(Arg1_006E3360* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_5668 = unknown_90;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3890
// Branching.
unsigned char Obj_006E3890::FUN_006E3890(int a1, int a2, int a3, int a4)
{
    if (unknown_30 != 0)
    {
        if (unknown_44 != -1)
        {
            return FUN_0065EC30(unknown_30, unknown_44);
        }
        return 0;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3B20
// Stores its argument in a member; pops its stack arguments.
bool __stdcall FUN_006E3B20(int a1, int a2, int a3, int a4)
{
    bool t1 = DAT_00A8B230->unknown_34A5;
    DAT_00A8B230->unknown_34A5 = DAT_00A8B230->unknown_34A5 == 0;
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3B40
// Branching.
unsigned char Obj_006E3B40::FUN_006E3B40(Arg1_006E3B40* a1, int a2, int a3, int a4)
{
    if (a1 == 0)
    {
        return 0;
    }
    a1->FUN_0050BCD0(unknown_90);
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E3B60  TActionClass::GetMode
//
// Which parameter-editing mode a trigger action kind uses. The cases are
// written in the order of their result blocks in the retail image.
int __fastcall TActionClass_006E3B60::GetMode(int kind)
{
    switch (kind) {
    case 0x0B: case 0x67:
        return 0x27;
    case 0x21: case 0x22: case 0x86:
        return 0x11;
    case 0x01: case 0x02: case 0x03: case 0x06: case 0x09: case 0x0D: case 0x0E:
    case 0x24: case 0x25: case 0x26: case 0x4A: case 0x4B: case 0x71: case 0x77:
    case 0x78: case 0x79: case 0x7A: case 0x7B: case 0x7C: case 0x7E: case 0x82:
        return 0x0D;
    case 0x1E: case 0x55: case 0x56: case 0x57:
        return 0x10;
    case 0x04: case 0x05: case 0x07: case 0x69:
        return 0x0C;
    case 0x68:
        return 0x28;
    case 0x50: case 0x6B:
        return 0x22;
    case 0x58:
        return 0x23;
    case 0x0C: case 0x16: case 0x35: case 0x36:
        return 0x0B;
    case 0x14:
        return 0x01;
    case 0x0A: case 0x64: case 0x75:
        return 0x02;
    case 0x13: case 0x62:
        return 0x03;
    case 0x15:
        return 0x04;
    case 0x46:
        return 0x1A;
    case 0x6A: case 0x73:
        return 0x2B;
    case 0x81: case 0x84: case 0x85:
        return 0x2E;
    case 0x1C: case 0x1D:
        return 0x16;
    case 0x38: case 0x39:
        return 0x1D;
    case 0x23:
        return 0x0F;
    case 0x28:
        return 0x15;
    case 0x29:
        return 0x17;
    case 0x63:
        return 0x26;
    case 0x08: case 0x11: case 0x12: case 0x3B: case 0x3F: case 0x40: case 0x41:
    case 0x42: case 0x59: case 0x5A: case 0x5E: case 0x5F: case 0x60: case 0x65:
    case 0x66: case 0x6D: case 0x70: case 0x74: case 0x80: case 0x87: case 0x89:
    case 0x8C:
        return 0x09;
    case 0x2A:
        return 0x18;
    case 0x2B:
        return 0x1B;
    case 0x30:
        return 0x1E;
    case 0x19: case 0x1A: case 0x1B: case 0x27: case 0x2C: case 0x49: case 0x4C:
    case 0x4D: case 0x4E: case 0x4F: case 0x54: case 0x6E: case 0x72: case 0x7F:
    case 0x8B: case 0x8E: case 0x8F: case 0x90:
        return 0x0A;
    case 0x34:
        return 0x19;
    case 0x37:
        return 0x1C;
    case 0x3A:
        return 0x1F;
    case 0x47: case 0x48:
        return 0x21;
    case 0x6C:
        return 0x2C;
    case 0x7D:
        return 0x2D;
    case 0x83:
        return 0x2F;
    default:
        return 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006E3D70
HRESULT __stdcall TActionClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9800;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E4020
// Branching.
unsigned char FUN_006E4020(Obj_006E4020* a1, int a2, int a3, int a4, int a5, int a6)
{
    if (a1->unknown_30 != 0)
    {
        FUN_006F1F30(a1->unknown_30, a2, a1->unknown_90);
        return 1;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006E44C0
bool __stdcall FUN_006E44C0(void* p, int, int, int)
{
    if (p == 0) {
        return false;
    }
    FUN_0050DA50(p);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006E4540
bool __stdcall FUN_006E4540(void* p, int, int, int)
{
    if (p == 0) {
        return false;
    }
    FUN_0050DFF0(p);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E4630
// Returns a constant. Vtable slot 12 of TActionClass (RTTI).
int Obj_006E4630::FUN_006E4630() const
{
    return 0x94;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E4640
// Returns a constant. Vtable slot 11 of TActionClass (RTTI).
int Obj_006E4640::FUN_006E4640() const
{
    return 0x2F;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E4650
// Member getter (dword). Vtable slot 16 of TActionClass (RTTI).
int Obj_006E4650::FUN_006E4650() const
{
    return unknown_24;
}
