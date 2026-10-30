// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail IPersist::GetClassID (slot 3 of each class's primary vtable) copies a
// 16-byte CLSID global to the caller and returns E_POINTER for a null pointer.
// The owning class of each address is read from the RTTI-named vtable that holds
// it in slot 3. Each class is declared here only as far as this one virtual
// (no layout is claimed); the bodies move into the canonical class once it exists.
#include <objidl.h>
#include "../_layout/side_class.h"
#include "../_layout/wave_class.h"
#include "../_layout/unit_class.h"
#include "../_layout/anim_type_class.h"
#include "../_layout/bullet_class.h"
#include "../_layout/script_class.h"
#include "../_layout/script_type_class.h"
#include "../ai/taction_class_methods.h"
#include "../_layout/tag_type_class.h"
#include "../_layout/task_force_class.h"
#include "../_layout/team_class.h"
#include "../_layout/team_type_class.h"
#include "../ai/tevent_class_methods.h"
#include "../_layout/trigger_class.h"
#include "../_layout/voxel_anim_type_class.h"
#include "../_layout/warhead_type_class.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/fogged_object_class.h"
#include "../_layout/aircraft_type_class.h"
#include "../_layout/anim_class.h"
#include "../_layout/infantry_class.h"
#include "../_layout/infantry_type_class.h"
#include "../_layout/jumpjet_locomotion_class.h"
#include "../_layout/ship_locomotion_class.h"
#include "../_layout/teleport_locomotion_class.h"
#include "../_layout/tunnel_locomotion_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/voxel_anim_class.h"
#include "../combat/weapon_type_class.h"
#include "../movement/walk_locomotion_class.h"
#include "../_layout/ai_trigger_type_class.h"
#include "../_layout/alpha_shape_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/empulse_class.h"
#include "../_layout/light_source_class.h"
#include "../_layout/rad_site_class.h"
#include "../_layout/tactical.h"
#include "../_layout/tag_class.h"
#include "../_layout/trigger_type_class.h"
#include "../_layout/veinhole_monster_class.h"
#include "../_layout/airstrike_class.h"
#include "../_layout/neuron_class.h"
#include "../_layout/disk_laser_class.h"
#include "../_layout/factory_class.h"
#include "../_layout/slave_manager_class.h"
#include "../_layout/spawn_manager_class.h"
#include "../_layout/temporal_class.h"
#include "../_layout/tiberium_class.h"
#include "../_layout/tube_class.h"

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
// GLOBAL: GAMEMD 0x007E9930 -- CLSID of CellClass.
extern const CLSID DAT_007E9930;
// GLOBAL: GAMEMD 0x007E9890 -- CLSID of DiskLaserClass.
extern const CLSID DAT_007E9890;
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

class ParasiteClass {
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
class WaypointPathClass {
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


// FUNCTION: GAMEMD 0x0041C190
HRESULT __stdcall AircraftClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9660;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0041CEB0
HRESULT __stdcall AircraftTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E95B0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0041D7A0
HRESULT __stdcall AirstrikeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E98E0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0041E500
HRESULT __stdcall AITriggerTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9960;
    return S_OK;
}


// FUNCTION: GAMEMD 0x00426540
HRESULT __stdcall AnimClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9670;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00428990
HRESULT __stdcall AnimTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9620;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0043A500
HRESULT __stdcall NeuronClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9980;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0046B560
HRESULT __stdcall BulletClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E96E0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00485200
HRESULT __stdcall CellClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9930;
    return S_OK;
}

// FUNCTION: GAMEMD 0x004A7C30
HRESULT __stdcall DiskLaserClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9890;
    return S_OK;
}

// FUNCTION: GAMEMD 0x004C59F0
HRESULT __stdcall EMPulseClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9940;
    return S_OK;
}

// FUNCTION: GAMEMD 0x004CA230
HRESULT __stdcall FactoryClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9820;
    return S_OK;
}

// FUNCTION: GAMEMD 0x004D27D0
HRESULT __stdcall FoggedObjectClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9990;
    return S_OK;
}


// FUNCTION: GAMEMD 0x00524C70
HRESULT __stdcall InfantryTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E95A0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00543AB0
HRESULT __stdcall IsometricTileClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9640;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00549D90
HRESULT __stdcall IsometricTileTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E95F0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0054B710
HRESULT __stdcall JumpjetLocomotionClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9AC0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00555080
HRESULT __stdcall LightSourceClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E98F0;
    return S_OK;
}


// FUNCTION: GAMEMD 0x0065B470
HRESULT __stdcall RadSiteClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E98C0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x006915F0
HRESULT __stdcall ScriptClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E97A0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00691D50
HRESULT __stdcall ScriptTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E97B0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x006A3E60
HRESULT __stdcall ShipLocomotionClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9AB0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x006A4740
HRESULT __stdcall SideClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9910;
    return S_OK;
}

// FUNCTION: GAMEMD 0x006B1130
HRESULT __stdcall SlaveManagerClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9870;
    return S_OK;
}

// FUNCTION: GAMEMD 0x006B7ED0
HRESULT __stdcall SpawnManagerClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9860;
    return S_OK;
}

// FUNCTION: GAMEMD 0x006CDEB0
HRESULT __stdcall SuperClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9580;
    return S_OK;
}

// FUNCTION: GAMEMD 0x006CE7C0
HRESULT __stdcall SuperWeaponTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9570;
    return S_OK;
}


// FUNCTION: GAMEMD 0x006E56A0
HRESULT __stdcall TagClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E97C0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x006E63A0
HRESULT __stdcall TagTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E97D0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x006E8710
HRESULT __stdcall TaskForceClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9770;
    return S_OK;
}

// FUNCTION: GAMEMD 0x006EC560
HRESULT __stdcall TeamClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9760;
    return S_OK;
}

// FUNCTION: GAMEMD 0x006F1C40
HRESULT __stdcall TeamTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9780;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00719C60
HRESULT __stdcall TeleportLocomotionClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9A90;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0071A720
HRESULT __stdcall TemporalClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E98D0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0071F880
HRESULT __stdcall TEventClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9810;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00721E40
HRESULT __stdcall TiberiumClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9920;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00726820
HRESULT __stdcall TriggerClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E97E0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00727BB0
HRESULT __stdcall TriggerTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E97F0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x007286D0
HRESULT __stdcall TubeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9750;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0072A110
HRESULT __stdcall TunnelLocomotionClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9A50;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00746DE0
HRESULT __stdcall UnitClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E96F0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00747F30
HRESULT __stdcall UnitTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9590;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0074AAD0
HRESULT __stdcall VoxelAnimClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9650;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0074B7D0
HRESULT __stdcall VoxelAnimTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9790;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0074F2D0
HRESULT __stdcall VeinholeMonsterClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E99B0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0075C640
HRESULT __stdcall WalkLocomotionClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9A60;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0075E080
HRESULT __stdcall WarheadTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9840;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0075F840
HRESULT __stdcall WaveClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9720;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00763C30
HRESULT __stdcall WaypointPathClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9850;
    return S_OK;
}

// FUNCTION: GAMEMD 0x00772C90
HRESULT __stdcall WeaponTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9830;
    return S_OK;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E9570
extern const CLSID DAT_007E9570 = {0x0CF2BCE7, 0x36E4, 0x11D2, {0xB8, 0xD8, 0x00, 0x60, 0x08, 0xC8, 0x09, 0xED}};
// GLOBAL: GAMEMD 0x7E9580
extern const CLSID DAT_007E9580 = {0xD7F754C6, 0x391C, 0x11D2, {0x9B, 0x64, 0x00, 0x10, 0x4B, 0x97, 0x2F, 0xE8}};
// GLOBAL: GAMEMD 0x7E9590
extern const CLSID DAT_007E9590 = {0xDCBD42EA, 0x0546, 0x11D2, {0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E95A0
extern const CLSID DAT_007E95A0 = {0xAE8B33D8, 0x061C, 0x11D2, {0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E95B0
extern const CLSID DAT_007E95B0 = {0xAE8B33D9, 0x061C, 0x11D2, {0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E95F0
extern const CLSID DAT_007E95F0 = {0x5AF2CE7A, 0x0634, 0x11D2, {0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9620
extern const CLSID DAT_007E9620 = {0xAE8B33DA, 0x061C, 0x11D2, {0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9640
extern const CLSID DAT_007E9640 = {0x0E272DC0, 0x9C0F, 0x11D1, {0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7E9650
extern const CLSID DAT_007E9650 = {0x0E272DC1, 0x9C0F, 0x11D1, {0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7E9660
extern const CLSID DAT_007E9660 = {0x0E272DC2, 0x9C0F, 0x11D1, {0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7E9670
extern const CLSID DAT_007E9670 = {0x0E272DC3, 0x9C0F, 0x11D1, {0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7E96F0
extern const CLSID DAT_007E96F0 = {0x0E272DCA, 0x9C0F, 0x11D1, {0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7E9720
extern const CLSID DAT_007E9720 = {0x0E272DCD, 0x9C0F, 0x11D1, {0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7E9750
extern const CLSID DAT_007E9750 = {0x0B4CA41C, 0xB3A7, 0x11D1, {0xB4, 0x57, 0x00, 0x60, 0x97, 0xC6, 0xA9, 0x79}};
// GLOBAL: GAMEMD 0x7E9760
extern const CLSID DAT_007E9760 = {0x0E272DCF, 0x9C0F, 0x11D1, {0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7E9770
extern const CLSID DAT_007E9770 = {0x61DE341E, 0x0774, 0x11D2, {0xAC, 0xA5, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9780
extern const CLSID DAT_007E9780 = {0xD1DBA64E, 0x0778, 0x11D2, {0xAC, 0xA5, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9790
extern const CLSID DAT_007E9790 = {0x2EBB6D66, 0x0D4D, 0x11D2, {0x81, 0x72, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E97A0
extern const CLSID DAT_007E97A0 = {0x42F3A646, 0x0789, 0x11D2, {0xAC, 0xA5, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E97B0
extern const CLSID DAT_007E97B0 = {0x42F3A647, 0x0789, 0x11D2, {0xAC, 0xA5, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E97C0
extern const CLSID DAT_007E97C0 = {0x54F6E432, 0x09ED, 0x11D2, {0xAC, 0xA5, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E97D0
extern const CLSID DAT_007E97D0 = {0x54F6E433, 0x09ED, 0x11D2, {0xAC, 0xA5, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E97E0
extern const CLSID DAT_007E97E0 = {0xC02D1590, 0x0A2A, 0x11D2, {0xAC, 0xA7, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E97F0
extern const CLSID DAT_007E97F0 = {0xC02D1591, 0x0A2A, 0x11D2, {0xAC, 0xA7, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9810
extern const CLSID DAT_007E9810 = {0x4F0EC393, 0x0A55, 0x11D2, {0xAC, 0xA7, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9820
extern const CLSID DAT_007E9820 = {0x34ECD9A8, 0x0AB0, 0x11D2, {0xAC, 0xA7, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9830
extern const CLSID DAT_007E9830 = {0x9FD219CA, 0x0F7B, 0x11D2, {0x81, 0x72, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9840
extern const CLSID DAT_007E9840 = {0xA8C54DA4, 0x0F7B, 0x11D2, {0x81, 0x72, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9850
extern const CLSID DAT_007E9850 = {0xF73125BA, 0x1054, 0x11D2, {0x81, 0x72, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9860
extern const CLSID DAT_007E9860 = {0x0679E981, 0xAD9D, 0x11D3, {0xBE, 0x16, 0x00, 0x10, 0x4B, 0x62, 0xA1, 0x6C}};
// GLOBAL: GAMEMD 0x7E9870
extern const CLSID DAT_007E9870 = {0x335AAFE4, 0x2DA6, 0x11D5, {0xBE, 0x22, 0x00, 0x10, 0x4B, 0x62, 0xA1, 0x6C}};
// GLOBAL: GAMEMD 0x7E9890
extern const CLSID DAT_007E9890 = {0x5230C9A8, 0x846A, 0x47EC, {0xBD, 0xA2, 0x7E, 0x95, 0x44, 0x5E, 0x1D, 0x49}};
// GLOBAL: GAMEMD 0x7E98C0
extern const CLSID DAT_007E98C0 = {0x4104D740, 0xD507, 0x11D3, {0x8C, 0x38, 0x00, 0xA0, 0xC9, 0x33, 0xBE, 0x44}};
// GLOBAL: GAMEMD 0x7E98D0
extern const CLSID DAT_007E98D0 = {0x94112424, 0xE403, 0x11D3, {0x8E, 0x6E, 0x00, 0x50, 0x04, 0xAA, 0xB2, 0xFB}};
// GLOBAL: GAMEMD 0x7E98E0
extern const CLSID DAT_007E98E0 = {0x70DE3921, 0x1E26, 0x11D5, {0x8F, 0x95, 0x00, 0xA0, 0x24, 0x83, 0x4B, 0x9C}};
// GLOBAL: GAMEMD 0x7E98F0
extern const CLSID DAT_007E98F0 = {0x6F9C48F0, 0x1207, 0x11D2, {0x81, 0x74, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9910
extern const CLSID DAT_007E9910 = {0xC53DD372, 0x151E, 0x11D2, {0x81, 0x75, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9920
extern const CLSID DAT_007E9920 = {0xC53DD373, 0x151E, 0x11D2, {0x81, 0x75, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9930
extern const CLSID DAT_007E9930 = {0xC1BF99CE, 0x1A8C, 0x11D2, {0x81, 0x75, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5}};
// GLOBAL: GAMEMD 0x7E9940
extern const CLSID DAT_007E9940 = {0xB825CB22, 0x200E, 0x11D2, {0x9F, 0xA9, 0x00, 0x60, 0x08, 0x9A, 0xD4, 0x58}};
// GLOBAL: GAMEMD 0x7E9960
extern const CLSID DAT_007E9960 = {0xBA093524, 0x4CF4, 0x11D2, {0xBC, 0x26, 0x00, 0x10, 0x4B, 0x8F, 0xB0, 0x4D}};
// GLOBAL: GAMEMD 0x7E9980
extern const CLSID DAT_007E9980 = {0x241AB316, 0x4CF5, 0x11D2, {0xBC, 0x26, 0x00, 0x10, 0x4B, 0x8F, 0xB0, 0x4D}};
// GLOBAL: GAMEMD 0x7E9990
extern const CLSID DAT_007E9990 = {0x1C470B0E, 0x69D7, 0x11D2, {0xB8, 0xF2, 0x00, 0x60, 0x08, 0xC8, 0x09, 0xED}};
// GLOBAL: GAMEMD 0x7E99B0
extern const CLSID DAT_007E99B0 = {0x5192D06A, 0xC632, 0x11D2, {0xB9, 0x0B, 0x00, 0x60, 0x08, 0xC8, 0x09, 0xED}};
// GLOBAL: GAMEMD 0x7E9A50
extern const CLSID DAT_007E9A50 = {0x4A582743, 0x9839, 0x11D1, {0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7E9A60
extern const CLSID DAT_007E9A60 = {0x4A582744, 0x9839, 0x11D1, {0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7E9A90
extern const CLSID DAT_007E9A90 = {0x4A582747, 0x9839, 0x11D1, {0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1}};
// GLOBAL: GAMEMD 0x7E9AB0
extern const CLSID DAT_007E9AB0 = {0x2BEA74E1, 0x7CCA, 0x11D3, {0xBE, 0x14, 0x00, 0x10, 0x4B, 0x62, 0xA1, 0x6C}};
// END defined globals
