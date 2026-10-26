// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU118 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x554430-0x555baf,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail RTTI TypeDescriptors 0x829AF0 and 0x829B28 identify
// VectorClass<LightSourceClass*> and DynamicVectorClass<LightSourceClass*>; the latter's
// CHD names the former as its zero-offset base.
//
// Retail RTTI type descriptors name VectorClass<LightSourceClass::PendingCellClass*> and
// DynamicVectorClass<LightSourceClass::PendingCellClass*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
//   an outside method map).
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
//   Read off retail gamemd.exe v1.001 at 0x554D50: __fastcall (time budget in
//   ECX, a force flag in DL), plain RET. The queue is a dynamic vector object
//   at 0xABCA40 (items 0xABCA44, capacity 0xABCA48, allocated byte 0xABCA4D,
//   count 0xABCA50); cursor 0xABCA7C, pending count 0xABCA80, done flag byte
//   0xABCA84, frame counter 0xABCA74, last-adjust frame 0xABCA78, adjust
//   interval 0x829AE8. The clock is the object at 0x884D88 read through
//   0x5B1E40 (returns a double); cells come from the map object 0x87F7E8 via
//   0x5657A0 (cell coordinates by reference); 0x484050 reads six light values
//   (two dwords, four words) and 0x483E30 writes them back.

#include "../core/vector_class_operations.h"
class LightSourceClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
// This specialization records the vector ABI, not the owning element class layout or original TU.
// No constructors were evidenced here. The size asserts describe these compiled vector models,
// not a complete owner object. Full spans match with /GX off; /GX shortens the dynamic
// scalar-deleting destructor. Vtable checks use conditional weak-default resolution, not final-link proof.

// VTABLE: GAMEMD 0x7ECF9C -- VectorClass<LightSourceClass*>.
template class VectorClass<LightSourceClass*>;
// VTABLE: GAMEMD 0x7ECF7C -- DynamicVectorClass<LightSourceClass*>.
template class DynamicVectorClass<LightSourceClass*>;

typedef VectorClass<LightSourceClass*> GgLightSourceClassVector;
typedef DynamicVectorClass<LightSourceClass*> GgLightSourceClassDynamicVector;
GG_STATIC_ASSERT(sizeof(LightSourceClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgLightSourceClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgLightSourceClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgLightSourceClassDynamicVector, CapacityIncrement) == 0x14);

#include "../core/vector_class_operations.h"

class LightSourceClass {
public:
    class PendingCellClass;
};

template class DynamicVectorClass<LightSourceClass::PendingCellClass*>;

GG_STATIC_ASSERT(sizeof(LightSourceClass::PendingCellClass*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<LightSourceClass::PendingCellClass* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<LightSourceClass::PendingCellClass* >) == 0x18);

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00555130;
struct Obj_00555140;

struct Obj_00555130
{
    // FUNCTION: GAMEMD 0x555130
    int FUN_00555130() const;
};

struct Obj_00555140
{
    // FUNCTION: GAMEMD 0x555140
    int FUN_00555140() const;
};




#include "../core/scenario_class_lighting_methods.h"

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


#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CellStruct_00554D50
{
    short X;   // +0x00
    short Y;   // +0x02
};

// One queued cell: the six saved light values and the cell coordinates.
struct LightQueueItem_00554D50
{
    int            Value0;   // +0x00
    int            Value1;   // +0x04
    unsigned short Value2;   // +0x08
    unsigned short Value3;   // +0x0A
    unsigned short Value4;   // +0x0C
    unsigned short Value5;   // +0x0E
    CellStruct_00554D50 Cell;   // +0x10
};
GG_STATIC_ASSERT(offsetof(LightQueueItem_00554D50, Value2) == 0x08);
GG_STATIC_ASSERT(offsetof(LightQueueItem_00554D50, Value5) == 0x0E);
GG_STATIC_ASSERT(offsetof(LightQueueItem_00554D50, Cell) == 0x10);

struct Cell_00554D50
{
    // FUNCTION: GAMEMD 0x484050 (decl; reloc)
    void GetLight(int* v0, int* v1, int* v2, int* v3, int* v4, int* v5);
    // FUNCTION: GAMEMD 0x483E30 (decl; reloc)
    void SetLight(int v0, int v1, int v2, int v3, int v4, int v5);
};

struct Map_00554D50
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    Cell_00554D50* GetCell(const CellStruct_00554D50& cell);
    // FUNCTION: GAMEMD 0x4F42F0 (decl; reloc)
    void Redraw(int flag);
};

struct Clock_00554D50
{
    // FUNCTION: GAMEMD 0x5B1E40 (decl; reloc)
    double Seconds();
};

// The queue object's observed fields (vector layout: vptr, items, capacity,
// two flag bytes, count).
struct LightQueue_00554D50
{
    void*                     _vtable;       // +0x00
    LightQueueItem_00554D50** Items;         // +0x04
    int                       Capacity;      // +0x08
    bool                      IsInitialized; // +0x0C
    bool                      IsAllocated;   // +0x0D
    int                       Count;         // +0x10
};
GG_STATIC_ASSERT(offsetof(LightQueue_00554D50, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(LightQueue_00554D50, Count) == 0x10);

// GLOBAL: GAMEMD 0x884D88
extern Clock_00554D50 DAT_00884D88;
// GLOBAL: GAMEMD 0x87F7E8
extern Map_00554D50 DAT_0087F7E8;
// GLOBAL: GAMEMD 0xABCA40
extern LightQueue_00554D50 DAT_00ABCA40;
// GLOBAL: GAMEMD 0xABCA74
extern unsigned int DAT_00ABCA74;
// GLOBAL: GAMEMD 0xABCA78
extern unsigned int DAT_00ABCA78;
// GLOBAL: GAMEMD 0xABCA7C
extern int DAT_00ABCA7C;
// GLOBAL: GAMEMD 0xABCA80
extern int DAT_00ABCA80;
// GLOBAL: GAMEMD 0xABCA84
extern bool DAT_00ABCA84;
// GLOBAL: GAMEMD 0x829AE8
extern unsigned int DAT_00829AE8;

// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc) -- operator delete.
void __cdecl operator delete(void* p);

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7ECF68
extern const double DAT_007ECF68;
// GLOBAL: GAMEMD 0xABC9E8
extern double DAT_00ABC9E8;

// FUNCTION: GAMEMD 0x544FF0 (decl; reloc)
bool FUN_00544FF0(int value, bool flag);

// SYNTHETIC: GAMEMD 0x554460
// GLOBAL: GAMEMD 0xABCA68
double DAT_00ABCA68 = DAT_00ABC9E8 / DAT_007ECF68;

// SYNTHETIC: GAMEMD 0x554480
// GLOBAL: GAMEMD 0xABCA38
double DAT_00ABCA38 = DAT_007E1718 / DAT_00ABCA68;

// SYNTHETIC: GAMEMD 0x00554680 -- exit-time destructor stub of DAT_00ABCA10
DynamicVectorClass<LightSourceClass*> DAT_00ABCA10;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x554D50
// Work through the light queue backwards within a time budget, sampling each
// queued cell's light values; once every cell is sampled (and, unless forced,
// enough budget is left) write them all back, free the queue and redraw.
// Finally, with time to spare, nudge the adjustment interval.
void FUN_00554D50(int budget, bool force)
{
    double start = DAT_00884D88.Seconds();
    DAT_00ABCA74++;

    if (DAT_00ABCA40.Count != 0 && !DAT_00ABCA84) {
        if (DAT_00ABCA7C <= 0) {
            DAT_00ABCA80 = DAT_00ABCA40.Count;
            DAT_00ABCA7C = DAT_00ABCA40.Count - 1;
        }
        while (DAT_00ABCA7C >= 0) {
            if (!force && (DAT_00ABCA7C & 0xF) == 0xF) {
                if (DAT_00884D88.Seconds() - start >= budget) {
                    break;
                }
            }
            if (DAT_00ABCA40.Items[DAT_00ABCA7C]->Value0 != 0) {
                DAT_00ABCA80--;
            } else {
                int v0;
                int v1;
                int v2;
                int v3;
                int v4;
                int v5;
                DAT_0087F7E8.GetCell(DAT_00ABCA40.Items[DAT_00ABCA7C]->Cell)->GetLight(&v0, &v1, &v2, &v3, &v4, &v5);
                DAT_00ABCA40.Items[DAT_00ABCA7C]->Value0 = v0;
                DAT_00ABCA40.Items[DAT_00ABCA7C]->Value1 = v1;
                DAT_00ABCA40.Items[DAT_00ABCA7C]->Value2 = v2;
                DAT_00ABCA40.Items[DAT_00ABCA7C]->Value3 = v3;
                DAT_00ABCA40.Items[DAT_00ABCA7C]->Value4 = v4;
                DAT_00ABCA40.Items[DAT_00ABCA7C]->Value5 = v5;
                DAT_00ABCA80--;
            }
            DAT_00ABCA7C--;
        }
        if (DAT_00ABCA80 <= 0) {
            DAT_00ABCA84 = true;
        }
    }

    double left = budget - (DAT_00884D88.Seconds() - start);
    if (DAT_00ABCA84) {
        if (force || left >= budget - 1) {
            for (int i = 0; i < DAT_00ABCA40.Count; i++) {
                LightQueueItem_00554D50* item = DAT_00ABCA40.Items[i];
                DAT_0087F7E8.GetCell(item->Cell)->SetLight(item->Value0, item->Value1,
                    item->Value2, item->Value3, item->Value4, item->Value5);
                delete item;
            }
            DAT_00ABCA40.Count = 0;
            if (DAT_00ABCA40.Items != 0 && DAT_00ABCA40.IsAllocated) {
                delete DAT_00ABCA40.Items;
                DAT_00ABCA40.Items = 0;
            }
            DAT_00ABCA40.IsAllocated = false;
            DAT_00ABCA40.Capacity = 0;
            DAT_00ABCA84 = false;
            DAT_0087F7E8.Redraw(1);
        }
    }

    double spare = budget - (DAT_00884D88.Seconds() - start);
    if (spare > 0.0 && DAT_00ABCA74 > DAT_00ABCA78 + DAT_00829AE8) {
        double half = spare * 0.5;
        if (!(half < 1.0)) {
            half = 1.0;
        }
        bool result = FUN_00544FF0((int)half, false);
        DAT_00ABCA78 = DAT_00ABCA74;
        DAT_00829AE8 = result ? 1 : 50;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x555130
// Returns a constant. Vtable slot 12 of LightSourceClass (RTTI).
int Obj_00555130::FUN_00555130() const
{
    return 0x4C;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x555140
// Returns a constant. Vtable slot 11 of LightSourceClass (RTTI).
int Obj_00555140::FUN_00555140() const
{
    return 0x36;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x555200
// DynamicVectorClass<LightSourceClass*>::Clear
// FUNCTION: GAMEMD 0x555230
// DynamicVectorClass<LightSourceClass*>::Slot5
// FUNCTION: GAMEMD 0x555250
// VectorClass<LightSourceClass*>::Slot6
// FUNCTION: GAMEMD 0x5552C0
// VectorClass<LightSourceClass*>::operator==
// FUNCTION: GAMEMD 0x555300
// VectorClass<LightSourceClass*>::SetCapacity
// FUNCTION: GAMEMD 0x5553B0
// VectorClass<LightSourceClass*>::Clear
// FUNCTION: GAMEMD 0x5553E0
// VectorClass<LightSourceClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x555420
// VectorClass<LightSourceClass*>::Slot5
// FUNCTION: GAMEMD 0x555440
// DynamicVectorClass<LightSourceClass*>::SetCapacity
// FUNCTION: GAMEMD 0x5554F0
// DynamicVectorClass<LightSourceClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x555780
// VectorClass<LightSourceClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x5557D0
// DynamicVectorClass<LightSourceClass*>::scalar deleting destructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x555290
// DynamicVectorClass<LightSourceClass::PendingCellClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x5552B0
// VectorClass<LightSourceClass::PendingCellClass*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x555520
// VectorClass<LightSourceClass::PendingCellClass*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x555560
// VectorClass<LightSourceClass::PendingCellClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x555640
// VectorClass<LightSourceClass::PendingCellClass*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x555680
// VectorClass<LightSourceClass::PendingCellClass*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x5556A0
// DynamicVectorClass<LightSourceClass::PendingCellClass*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x555750
// DynamicVectorClass<LightSourceClass::PendingCellClass*>::FindItemIndex (slot 4)
template class VectorClass<LightSourceClass::PendingCellClass*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x555AC0  ScenarioClass::ScenarioLighting (__fastcall, ret 0x4)
//
// Normalise a lighting triple in place: each channel is clamped to 1000 and
// floored at zero, then rounded down to the channel granularity the current
// colour depth can show (steps of 128, 64 or 32 for selector 0, 1, 2; other
// selectors leave the values as they are).
void ScenarioClass::ScenarioLighting(int* red, int* green, int* blue)
{
    *red = GG_MIN(*red, 1000);
    *green = GG_MIN(*green, 1000);
    *blue = GG_MIN(*blue, 1000);

    *red = GG_MAX(*red, 0);
    *green = GG_MAX(*green, 0);
    *blue = GG_MAX(*blue, 0);

    switch (DAT_00A8EB78) {
    case 0:
        *red &= ~0x7F;
        *green &= ~0x7F;
        *blue &= ~0x7F;
        break;
    case 1:
        *red &= ~0x3F;
        *green &= ~0x3F;
        *blue &= ~0x3F;
        break;
    case 2:
        *red &= ~0x1F;
        *green &= ~0x1F;
        *blue &= ~0x1F;
        break;
    }
}
