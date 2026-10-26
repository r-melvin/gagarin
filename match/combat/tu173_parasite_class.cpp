// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU173 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x628f80-0x62b3cf,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x008365D8 and 0x00836608 identify
// VectorClass<ParasiteClass*> and DynamicVectorClass<ParasiteClass*>; COLs
// 0x00807A80 and 0x00807A50 point at them, and the dynamic hierarchy (CHD
// 0x00807A40, two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EF844 and DynamicVectorClass<T> address
// point 0x007EF824 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete ParasiteClass layout claim.
//
// Retail IPersist::GetClassID (slot 3 of each class's primary vtable) copies a
// 16-byte CLSID global to the caller and returns E_POINTER for a null pointer.
// The owning class of each address is read from the RTTI-named vtable that holds
// it in slot 3. Each class is declared here only as far as this one virtual
// (no layout is claimed); the bodies move into the canonical class once it exists.
//
// File-scope DynamicVectorClass<T> objects whose exit-time destructors were
// emitted as stand-alone stubs: each stub restores the VectorClass<T> vtable,
// frees the array when it is owned, and clears the flag and capacity. T is the
// element type of the vector's RTTI TypeDescriptor, read through the vptr stored by the
// matching initialiser. The initialisers (the __xc table entries, which also
// register these stubs with atexit) are left to the translation-unit migration;
// they compile here as a by-product and are not claimed. The globals' retail
// addresses are bound for verification through the per-TU symbol map.

#include "../core/vector_class_operations.h"

class ParasiteClass;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

template class DynamicVectorClass<ParasiteClass*>;

// VTABLE: GAMEMD 0x007EF844 -- VectorClass<ParasiteClass*>.
// VTABLE: GAMEMD 0x007EF824 -- DynamicVectorClass<ParasiteClass*>.

typedef VectorClass<ParasiteClass*> GgParasiteClassVector;
typedef DynamicVectorClass<ParasiteClass*> GgParasiteClassDynamicVector;
GG_STATIC_ASSERT(sizeof(ParasiteClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgParasiteClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgParasiteClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParasiteClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParasiteClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParasiteClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgParasiteClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgParasiteClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, CapacityIncrement) == 0x14);

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00629710;
struct Obj_0062AF50;
struct Obj_0062AF60;

struct Obj_00629710
{
    char unknown_00[0x4C];
    int unknown_4C;   // +0x004C
    int unknown_50;   // +0x0050
    // FUNCTION: GAMEMD 0x629710
    void FUN_00629710();
};
GG_STATIC_ASSERT(offsetof(Obj_00629710, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_00629710, unknown_50) == 0x50);

struct Obj_0062AF50
{
    // FUNCTION: GAMEMD 0x62AF50
    int FUN_0062AF50() const;
};

struct Obj_0062AF60
{
    // FUNCTION: GAMEMD 0x62AF60
    int FUN_0062AF60() const;
};




#include "parasite_class_grapple_methods.h"

#include "parasite_class_infect_methods.h"

#define INFECT_VT(p) ((p)->Vtbl)

#include "parasite_class_victim_cell_methods.h"

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

#include "../core/vector_class_operations.h"

class AITriggerTypeClass;
class AbstractClass;
class AbstractTypeClass;
class AircraftClass;
class AircraftTypeClass;
class AirstrikeClass;
class AlphaShapeClass;
class AnimClass;
class AnimTypeClass;
class BuildingClass;
class BuildingLightClass;
class BuildingTypeClass;
class BulletClass;
class BulletTypeClass;
class CampaignClass;
class CaptureManagerClass;
class ColorScheme;
class CommandClass;
class DiskLaserClass;
class EBolt;
class EgoClass;
class FactoryClass;
class FootClass;
class HouseClass;
class HouseTypeClass;
class InfantryClass;
class InfantryTypeClass;
class IsometricTileClass;
class IsometricTileTypeClass;
class LightConvertClass;
class LightSourceClass;
class LineTrail;
class MixFileClass;
class MovieHandle;
class ObjectClass;
class OverlayClass;
class OverlayTypeClass;
class ParasiteClass;
class ParticleClass;
class ParticleSystemClass;
class ParticleSystemTypeClass;
class ParticleTypeClass;
class RadBeam;
class RadSiteClass;
class ScriptClass;
class ScriptTypeClass;
class SideClass;
class SlaveManagerClass;
class SmudgeClass;
class SmudgeTypeClass;
class SpawnManagerClass;
class SpotLightClass;
class SuperClass;
class SuperWeaponTypeClass;
class TActionClass;
class TEventClass;
class TagClass;
class TaskForceClass;
class TeamClass;
class TeamTypeClass;
class TechnoClass;
class TechnoTypeClass;
class TemporalClass;
class TerrainClass;
class TerrainTypeClass;
class TiberiumClass;
class TriggerClass;
class TriggerTypeClass;
class TubeClass;
class UnitClass;
class UnitTypeClass;
class VocClass;
class VoxClass;
class VoxelAnimClass;
class VoxelAnimTypeClass;
class WarheadTypeClass;
class WaveClass;
class WaypointPathClass;
class WeaponTypeClass;
struct HWND__;

// GLOBAL: GAMEMD 0x0087F658

#include "../movement/foot_class_wakes_methods.h"

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EF810
extern const double DAT_007EF810;
// GLOBAL: GAMEMD 0xAC4930
extern double DAT_00AC4930;

// SYNTHETIC: GAMEMD 0x628FB0
// GLOBAL: GAMEMD 0xAC4980
double DAT_00AC4980 = DAT_00AC4930 / DAT_007EF810;

// SYNTHETIC: GAMEMD 0x628FD0
// GLOBAL: GAMEMD 0xAC4968
double DAT_00AC4968 = DAT_007E1718 / DAT_00AC4980;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x006291D0 -- exit-time destructor stub of DAT_00AC4910
DynamicVectorClass<ParasiteClass*> DAT_00AC4910;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006296D0
HRESULT __stdcall ParasiteClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E98A0;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x629710
// Stores several members.
void Obj_00629710::FUN_00629710()
{
    unknown_50 = 0;
    unknown_4C = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x629720
//
// One tick of the grapple animation. The grapple state picks a base frame and
// a per-frame delay (states 0 and 1: base 0, delay 3; state 2: base 80, delay
// 4; anything else: base 160, delay 4). Every `delay` ticks the frame counter
// advances; once it reaches 10 the grapple is over (true). Otherwise the
// grapple anim, if any, is pointed at the frame for the victim's current
// facing and re-timed.
bool ParasiteClass_00629720::UpdateGrapple()
{
    Dir_00629720 dir = this->Victim->PrimaryFacing.Current();
    int base;
    int delay;

    switch (this->GrappleState) {
    case 0:
    case 1:
        base = 0;
        delay = 3;
        break;
    case 2:
        base = 80;
        delay = 4;
        break;
    default:
        base = 160;
        delay = 4;
        break;
    }

    if (++this->GrappleAnimDelay >= delay) {
        this->GrappleAnimDelay = 0;
        if (++this->GrappleAnimFrame >= 10) {
            return true;
        }
        Anim_00629720* anim = this->GrappleAnim;
        if (anim != 0) {
            anim->Timer = CDTimer_00629720(0x80);
            anim->At_C0 = 0x80;
            this->GrappleAnim->At_AC =
                this->GrappleAnimFrame + (int)(((dir.Raw >> 12) + 1 >> 1) & 7) * 10 + base;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x629E90
//
// Drop three wake animations behind a moving unit. The unit's current facing is
// turned into an angle, and each wake is placed at a random offset (+/-0xB4
// along the hull, +/-0x40 across it) rotated into world space by that angle and
// added to the passed-in coordinate. Each wake is an AnimClass built directly
// at the resulting spot.
//
// Phrasing notes (load-bearing):
//   * The sin/cos pair is declared as plain `extern "C" double __cdecl`
//     functions under placeholder names, so cl calls them the retail way
//     (`MOV ESI,[angle+4]; MOV EDI,[angle]; PUSH ESI; PUSH EDI; CALL`) with the
//     two stack cleanups merged into one `ADD ESP,0x10`, instead of
//     substituting an x87 intrinsic.
//   * 0x4CAD00 is cos and 0x4CACB0 is sin: the first result multiplies `along`
//     in the X term and `across` in the Y term, which is the standard rotation.
//   * The AnimClass allocation is written out by hand as operator new / null
//     test / constructor call (a real `new T(...)` adds a /GX EH frame retail
//     does not have, as at 0x641DB0), and there is no else-arm because retail
//     never stores the result.
//
// PARTIAL (31.2%, 29/93). The prologue, the facing read, the angle
// computation and both trig calls are byte-exact through 0x4C. Three residual
// deltas:
//   1. Frame size 0x3C against retail's 0x34. Retail merges the 4-byte facing
//      out-buffer with the 8-byte angle slot at [ESP+0x10] even though its
//      address was taken; cl 8804 will not merge an address-taken local, so it
//      spends a separate 8-byte slot. Forcing the merge with a
//      `union { double; DirStruct; }` does produce SUB ESP,0x34, but it also
//      moves the union above the int conversion slot and every later
//      displacement then differs (23.7%).
//   2. Retail caches only the Y and Z arguments in EDI/EBX and re-reads X from
//      [EBP+8] inside the loop, keeping ESI for the first `_ftol` result; cl
//      caches all three and stores coord.X as soon as the first `_ftol`
//      returns instead of after the second.
//   3. Retail converts `along` to double (`FILD`/`FSTP`) before the second
//      randomizer call; cl defers both conversions until after it.
// Variants tried: the coordinate terms written inline in the member stores
// (31.2%, kept); named `dx`/`dy` locals computed before the stores plus an
// 8-byte out-buffer (29.0%); a `double` out-buffer with a cast (29.0%); the
// union-shared slot, with and without the named deltas (23.7% both).
// Lift pass 2 (2026-09-18): one more rejected - `double dalong = along;`
// between the two randomizer calls to force retail's early FILD/FSTP (delta 3).
// It does move the conversion, but costs the `MOV` and `FXCH` retail has and
// drops to 28.0%; the kept form is still the inline-terms one at 31.2%.
// Delta 1 (the unmergeable address-taken frame slot) is the banked
// 8447-vs-8804 class and dominates the positional score.
void FootClass::CreateWakes(int x, int y, int z)
{
    DirStruct tmp;
    DirStruct* facing = this->PrimaryFacing.FUN_004C93D0(&tmp);
    double angle = -((double)((short)facing->Raw - 0x3FFF) * DAT_007E2810);
    double c = FUN_004CAD00(angle);
    double s = FUN_004CACB0(angle);

    int i = 3;
    do {
        int along  = DAT_00A8B230->Random.RandomRanged(-0xB4, 0xB4);
        int across = DAT_00A8B230->Random.RandomRanged(-0x40, 0x40);

        CoordStruct_00629E90 coord;
        coord.X = x + (int)(along * c - across * s);
        coord.Y = y + (int)(along * s + across * c);
        coord.Z = z;

        AnimClass_00629E90* anim =
            (AnimClass_00629E90*)FUN_007C8E17(sizeof(AnimClass_00629E90));
        if (anim != 0) {
            anim->FUN_00421EA0(DAT_008871E0->At_94, coord, 0, 1, 0x600, 0, 0);
        }
    } while (--i != 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62A8E0
//
// Can this parasite latch onto `target`? The target must exist, be on the map,
// alive, have health, not already carry a parasite, be of a parasite-able type
// and not be bunkered. A naval parasite (its owner's type is Naval) additionally
// needs the target's cell to be a water tile. Every refusal shares the one
// `XOR AL,AL` tail; the acceptances share the `MOV AL,1` tail ahead of it.
bool ParasiteClass_0062A8E0::CanInfect(FootInfect* target)
{
    // Every refusal shares the one `XOR AL,AL` tail at 0x62A976, so the
    // acceptance conditions nest down to a single trailing `return false`;
    // written as seven early returns VC6 emits seven epilogues (12.2%).
    if (target != 0
        && !target->InLimbo
        && target->IsAlive
        && target->Health != 0
        && target->ParasiteEatingMe == 0
        && (target->*INFECT_VT(target)->GetTechnoType)()->At_D38
        && target->BunkerLinkedItem == 0) {
        FootInfect* owner = this->Owner;
        if (owner == 0
            || !(owner->*INFECT_VT(owner)->GetTechnoType)()->Naval
            || (target->*INFECT_VT(target)->GetCell)() == 0
            || (target->*INFECT_VT(target)->GetCell)()->Tile_Is_Water()) {
            return true;
        }
    }

    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62AB40  ParasiteClass::CanExistOnVictimCell
//
// Could the parasite survive where its victim now stands. Nothing without a
// victim, nothing in the air. A non-naval parasite riding a unit is rejected
// if the cell holds an object of kind 0; on the water-ish land types (2, 3, 6)
// it is rejected unless a bridge or a shore overlay (the two overlay bands)
// carries it. Finally the cell must be free of buildings.
bool Parasite_0062AB40::CanExistOnVictimCell()
{
    Obj_0062AB40* victim = Victim;
    if (victim == 0)
        return false;
    if ((victim->*victim->Vptr->IsInAir)())
        return false;

    if ((Owner->*Owner->Vptr->GetTechnoType)()->Naval == 0) {
        if (Owner != 0 && (Owner->*Owner->Vptr->WhatAmI)() == 1) {
            if ((Victim->*Victim->Vptr->GetCell)()->FUN_0047C550(0) != 0)
                return false;
        }

        int land = (Victim->*Victim->Vptr->GetCell)()->LandType;
        if (land == 2 || land == 6 || land == 3) {
            bool blocked = true;
            if ((Victim->*Victim->Vptr->GetCell)()->Flags & 0x100)
                blocked = false;
            int overlay = (Victim->*Victim->Vptr->GetCell)()->OverlayTypeIndex;
            if (overlay >= 0x4A && overlay <= 0x63)
                blocked = false;
            if ((overlay < 0xCD || overlay > 0xE6) && blocked)
                return false;
        }
    }

    // A named bool gives retail's TEST/SETZ; returning the compare directly
    // materialises it as NEG/SBB/INC.
    bool clear = (Victim->*Victim->Vptr->GetCell)()->FUN_0047C520() == 0;
    return clear;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62AF50
// Returns a constant. Vtable slot 12 of ParasiteClass (RTTI).
int Obj_0062AF50::FUN_0062AF50() const
{
    return 0x58;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x62AF60
// Returns a constant. Vtable slot 11 of ParasiteClass (RTTI).
int Obj_0062AF60::FUN_0062AF60() const
{
    return 0x43;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0062B070
// FUNCTION: GAMEMD 0x0062B0A0
// FUNCTION: GAMEMD 0x0062B0C0
// FUNCTION: GAMEMD 0x0062B0D0
// FUNCTION: GAMEMD 0x0062B110
// FUNCTION: GAMEMD 0x0062B1C0
// FUNCTION: GAMEMD 0x0062B1F0
// FUNCTION: GAMEMD 0x0062B230
// FUNCTION: GAMEMD 0x0062B250
// FUNCTION: GAMEMD 0x0062B300
// FUNCTION: GAMEMD 0x0062B330
// FUNCTION: GAMEMD 0x0062B380
template class VectorClass<ParasiteClass*>;
