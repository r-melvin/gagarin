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

// FUNCTION: GAMEMD 0x0046C750
HRESULT __stdcall BulletTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E95D0;
    return S_OK;
}

// FUNCTION: GAMEMD 0x0046CF80
HRESULT __stdcall CampaignClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9900;
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

// FUNCTION: GAMEMD 0x004B4830
HRESULT __stdcall DriveLocomotionClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9A30;
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

