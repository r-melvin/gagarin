// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU066 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x4a6a60-0x4a843f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail PAVDiskLaserClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
//
// Classes that override an AbstractClass slot with a body that only forwards to
// the base body: AircraftClass AddRef/Release (slots 1, 2: 0x410300, 0x410310)
// and the checksum slot 13 of Airstrike, DiskLaser, LightSource, RadSite and
// Temporal (0x410410). The owning class of each address is read from the
// RTTI-named vtable that holds it; each class is declared only as far as these
// virtuals (no layout is claimed).
//
// File-scope DynamicVectorClass<T> objects whose exit-time destructors were
// emitted as stand-alone stubs: each stub restores the VectorClass<T> vtable,
// frees the array when it is owned, and clears the flag and capacity. T is the
// element type of the vector's RTTI TypeDescriptor, read through the vptr stored by the
// matching initialiser. The initialisers (the __xc table entries, which also
// register these stubs with atexit) are left to the translation-unit migration;
// they compile here as a by-product and are not claimed. The globals' retail
// addresses are bound for verification through the per-TU symbol map.
//
//   0x732D00 via the local Ghidra disassembly.
//
// Global query leaves, ordered ascending by retail address.

#include "../core/vector_class_operations.h"

class DiskLaserClass;

// VTABLE: GAMEMD 0x7E5EFC -- VectorClass<DiskLaserClass*>.
template class VectorClass<DiskLaserClass*>;
typedef VectorClass<DiskLaserClass*> GgDiskLaserClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E5EDC -- DynamicVectorClass<DiskLaserClass*>.
template class DynamicVectorClass<DiskLaserClass*>;
typedef DynamicVectorClass<DiskLaserClass*> GgDiskLaserClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgDiskLaserClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(DiskLaserClass*) == 4);

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004A7C70;
struct Obj_004A7C80;

struct Obj_004A7C70
{
    // FUNCTION: GAMEMD 0x4A7C70
    int FUN_004A7C70() const;
};

struct Obj_004A7C80
{
    // FUNCTION: GAMEMD 0x4A7C80
    int FUN_004A7C80() const;
};




#include "disk_laser_pointer_methods.h"

#include "../_layout/abstract_class.h"
#include "../_layout/airstrike_class.h"
#include "../_layout/disk_laser_class.h"
#include "../_layout/temporal_class.h"

class AircraftClass : public AbstractClass
{
public:
    virtual ULONG __stdcall AddRef();
    virtual ULONG __stdcall Release();
};

class LightSourceClass : public AbstractClass
{
public:
    virtual void vf_13(Obj_004A1D30* crc);
};

class RadSiteClass : public AbstractClass
{
public:
    virtual void vf_13(Obj_004A1D30* crc);
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


#include "../platform/system_query_methods.h"

// Win32 import reached through the IAT (`CALL dword ptr [0x007E1530]`).
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E5EC8
extern const double DAT_007E5EC8;
// GLOBAL: GAMEMD 0x8A0238
extern double DAT_008A0238;

// SYNTHETIC: GAMEMD 0x004A6A90
// dynamic initializer for DAT_008A0288

// GLOBAL: GAMEMD 0x008A0288
double DAT_008A0288 = DAT_008A0238 / DAT_007E5EC8;

// SYNTHETIC: GAMEMD 0x004A6AB0
// dynamic initializer for DAT_008A0270

// GLOBAL: GAMEMD 0x008A0270
double DAT_008A0270 = DAT_007E1718 / DAT_008A0288;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x004A6CB0 -- exit-time destructor stub of DAT_008A0208
// SYNTHETIC: GAMEMD 0x004A6C70 -- initialiser of DAT_008A0208
DynamicVectorClass<DiskLaserClass*> DAT_008A0208;

// Declarations: GAMEMD 0x4CACB0 (sin) and 0x4CAD00 (cos) -- __cdecl, double in and out.
extern "C" double __cdecl FUN_004CACB0(double angle);
extern "C" double __cdecl FUN_004CAD00(double angle);
// GLOBAL: GAMEMD 0x7E5ED0 -- degrees to radians
extern const double DAT_007E5ED0;

// A pair of integers built from its two arguments.
struct Pair_008A0180
{
    int unknown_0;
    int unknown_4;
    Pair_008A0180(int a, int b)
    {
        unknown_0 = a;
        unknown_4 = b;
    }
};
GG_STATIC_ASSERT(sizeof(Pair_008A0180) == 8);

// SYNTHETIC: GAMEMD 0x4A6CF0 -- table build: sixteen (cosine, sine) pairs scaled by 240, at 15-22 degree steps
// GLOBAL: GAMEMD 0x8A0180
Pair_008A0180 DAT_008A0180[16] = {
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 270.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 270.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 292.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 292.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 315.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 315.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 337.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 337.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 0.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 0.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 22.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 22.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 45.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 45.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 67.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 67.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 90.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 90.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 112.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 112.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 135.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 135.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 157.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 157.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 180.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 180.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 202.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 202.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 235.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 235.0) * 240.0)),
    Pair_008A0180((int)(FUN_004CAD00(DAT_007E5ED0 * 257.0) * 240.0), (int)(FUN_004CACB0(DAT_007E5ED0 * 257.0) * 240.0))
};

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4A7900  DiskLaserClass::PointerGotInvalid (__thiscall, ret 0x4)
// Two independent tests, one per end of the laser: if the expiring pointer is
// the owner, or the target, the +0x30 handle is reset and the laser queues
// itself for deletion. Both can fire on the same call, so the AddItem is
// expanded twice.
void DiskLaser_004A7900::PointerGotInvalid(void* pInvalid)
{
    if (pInvalid == this->Owner)
    {
        this->unknown_30 = -1;
        reinterpret_cast<PendingVector_004A7900*>(&DAT_00B0F698)->AddItem(this);
    }

    if (pInvalid == this->Target)
    {
        this->unknown_30 = -1;
        reinterpret_cast<PendingVector_004A7900*>(&DAT_00B0F698)->AddItem(this);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x004A7AD0
DiskLaserClass::DiskLaserClass(const AbstractNoInit& noInit) : AbstractClass(noInit)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4A7B00
// Removes the laser from the global laser list; ~AbstractClass runs after it.
DiskLaserClass::~DiskLaserClass()
{
    DAT_008A0208.RemoveItem(this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x004A7B80
void DiskLaserClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4A7C70
// Returns a constant. Vtable slot 12 of DiskLaserClass (RTTI).
int Obj_004A7C70::FUN_004A7C70() const
{
    return 0x40;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4A7C80
// Returns a constant. Vtable slot 11 of DiskLaserClass (RTTI).
int Obj_004A7C80::FUN_004A7C80() const
{
    return 0x49;
}

// SYNTHETIC: GAMEMD 0x4A7C90 -- DiskLaserClass scalar deleting destructor (slot 8), emitted with the vtable.

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4A7D20
// DynamicVectorClass<DiskLaserClass*>::Clear

// FUNCTION: GAMEMD 0x4A7D50
// DynamicVectorClass<DiskLaserClass*>::Slot5

// FUNCTION: GAMEMD 0x4A7D70
// VectorClass<DiskLaserClass*>::Slot6

// FUNCTION: GAMEMD 0x4A7D80
// VectorClass<DiskLaserClass*>::operator==

// FUNCTION: GAMEMD 0x4A7DC0
// VectorClass<DiskLaserClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4A7E70
// VectorClass<DiskLaserClass*>::Clear

// FUNCTION: GAMEMD 0x4A7EA0
// VectorClass<DiskLaserClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4A7EE0
// VectorClass<DiskLaserClass*>::Slot5

// FUNCTION: GAMEMD 0x4A7F00
// DynamicVectorClass<DiskLaserClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4A7FB0
// DynamicVectorClass<DiskLaserClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4A8030
// VectorClass<DiskLaserClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4A8080
// DynamicVectorClass<DiskLaserClass*>::scalar deleting destructor

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E5EC8
extern const double DAT_007E5EC8 = 60.0;
// END defined globals
