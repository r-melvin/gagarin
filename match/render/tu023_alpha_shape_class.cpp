// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit TU023 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x4206f0-0x421caf,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
// Retail RTTI TypeDescriptors 0x818238 and 0x818270 identify
// VectorClass<AlphaShapeClass*> and DynamicVectorClass<AlphaShapeClass*>; the latter's
// CHD names the former as its zero-offset base.
// Complete entry spans bind these methods. Original TUs and standalone
// constructors are unestablished; the derived deleting body needs GX off.
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
class AlphaShapeClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// VTABLE: GAMEMD 0x7E3258 -- VectorClass<AlphaShapeClass*>.
template class VectorClass<AlphaShapeClass*>;
// VTABLE: GAMEMD 0x7E3238 -- DynamicVectorClass<AlphaShapeClass*>.
template class DynamicVectorClass<AlphaShapeClass*>;

typedef VectorClass<AlphaShapeClass*> GgAlphaShapeVector;
typedef DynamicVectorClass<AlphaShapeClass*> GgAlphaShapeDynamicVector;
GG_STATIC_ASSERT(sizeof(AlphaShapeClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgAlphaShapeVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgAlphaShapeDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAlphaShapeDynamicVector, CapacityIncrement) == 0x14);

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

// GLOBAL: GAMEMD 0x0088A0F0

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x00420920 -- exit-time destructor stub of DAT_0088A0F0
// SYNTHETIC: GAMEMD 0x004208E0 -- initialiser of DAT_0088A0F0
DynamicVectorClass<AlphaShapeClass*> DAT_0088A0F0;

#include "../_layout/alpha_shape_class.h"

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00420D40
HRESULT __stdcall AlphaShapeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E99A0;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x421800
// DynamicVectorClass<AlphaShapeClass*>::Clear
// FUNCTION: GAMEMD 0x421830
// DynamicVectorClass<AlphaShapeClass*>::Slot5
// FUNCTION: GAMEMD 0x421850
// VectorClass<AlphaShapeClass*>::Slot6
// FUNCTION: GAMEMD 0x421860
// VectorClass<AlphaShapeClass*>::operator==
// FUNCTION: GAMEMD 0x4218A0
// VectorClass<AlphaShapeClass*>::SetCapacity
// FUNCTION: GAMEMD 0x421950
// VectorClass<AlphaShapeClass*>::Clear
// FUNCTION: GAMEMD 0x421980
// VectorClass<AlphaShapeClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x4219C0
// VectorClass<AlphaShapeClass*>::Slot5
// FUNCTION: GAMEMD 0x4219E0
// DynamicVectorClass<AlphaShapeClass*>::SetCapacity
// FUNCTION: GAMEMD 0x421A90
// DynamicVectorClass<AlphaShapeClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x421AC0
// VectorClass<AlphaShapeClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x421B10
// DynamicVectorClass<AlphaShapeClass*>::scalar deleting destructor
