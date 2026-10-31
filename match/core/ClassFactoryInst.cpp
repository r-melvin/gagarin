// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Template instantiation unit for the persistence class factories, placed at the retail
//   address of their COMDAT blocks (0x6bed80-0x6c6450, directly after the Startup.CPP code of
//   0x6bb070-0x6bed50). Functions are in ascending retail address order.
//
//   Why a separate file: retail's WinMain registration routine (0x6BB9A0) calls every
//   TClassFactory<T> constructor out of line (77 sites); a two-store constructor that the
//   compiler can see is inlined at every site whatever the inline budget, so the constructor
//   body must not be visible in the file that holds WinMain. class_factory.h declares the
//   constructor; this file defines it and holds the explicit instantiations.
//
// TClassFactory<T>::CreateInstance (IClassFactory slot 3) for the persistable
// classes registered through TClassFactory (RTTI: `.?AV?$TClassFactory@V<T>@@@@`
// instantiations; vtable slot 3 of each). The body is the same for every T:
// a null result pointer gives E_INVALIDARG, aggregation gives
// CLASS_E_NOAGGREGATION, then `new T` (size pushed from the class size, T's
// default constructor), QueryInterface through the new object's slot 0 and, on
// failure, its deleting destructor (slot 8) with flag 1. Only the allocation
// size and constructor differ per T; both are read from each body.
//
// Each T is declared here only as far as `new T` and the two virtual calls
// need: the real base (AbstractClass or LocomotionClass), the overrides that
// keep it concrete, an `unknown_` block that carries the allocation size, and
// the constructor declaration bound to its retail address. No further layout
// is claimed; the classes are replaced by the canonical ones when they exist.
//
// Retail RTTI type descriptors name VectorClass<unsigned long> and
// DynamicVectorClass<unsigned long>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// Factory slot identities follow the native tables recorded below.

#include "class_factory.h"
#include "mathtbl_init_shapes.h"
#include "../_layout/abstract_class.h"
#include "../_layout/bomb_class.h"
#include "../movement/loco_base.h"
#include "../_layout/side_class.h"
#include "../_layout/wave_class.h"
#include "../_layout/unit_class.h"
#include "../_layout/i_link_stream.h"
#include "../combat/bullet_type_class.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/parasite_class.h"
#include "../_layout/aircraft_type_class.h"
#include "../_layout/anim_class.h"
#include "../_layout/infantry_class.h"
#include "../_layout/infantry_type_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/voxel_anim_class.h"
#include "../_layout/building_class.h"
#include "../combat/weapon_type_class.h"
#include "../_layout/jumpjet_locomotion_class.h"
#include "../_layout/ship_locomotion_class.h"
#include "../_layout/teleport_locomotion_class.h"
#include "../_layout/tunnel_locomotion_class.h"
#include "../movement/walk_locomotion_class.h"
#include "../movement/drive_locomotion.h"

template<class T> HRESULT TClassFactory<T>::CreateInstance(IUnknown* outer, REFIID riid, void** ppv)
{
    if (ppv == NULL)
        return E_INVALIDARG;
    *ppv = NULL;
    if (outer != NULL)
        return CLASS_E_NOAGGREGATION;
    T* object = new T;
    if (object == NULL)
        return E_OUTOFMEMORY;
    HRESULT hr = object->QueryInterface(riid, ppv);
    if (FAILED(hr))
        delete object;
    return hr;
}

// CALLEE: GAMEMD 0x7C8E17 -- library operator new(size_t), ??2@YAPAXI@Z.

// TClassFactory<T>::TClassFactory: out-of-class on purpose, see above.
template<class T> TClassFactory<T>::TClassFactory() : RefCount(0) {}


#include "../_layout/cstream_class.h"

#include "../map/terrain_objects/terrain_class.h"

#include "../_layout/super_weapon_type_class.h"

#include "../_layout/super_class.h"

#include "../_layout/tactical.h"

#include "../_layout/cell_class.h"

#include "../_layout/empulse_class.h"

#include "../_layout/light_source_class.h"






#include "../_layout/building_light_class.h"


#include "../_layout/temporal_class.h"
#include "../ai/tevent_class_methods.h"
#include "../_layout/voxel_anim_type_class.h"
#include "../ai/taction_class_methods.h"
#include "../_layout/trigger_class.h"
#include "../_layout/script_class.h"
#include "../_layout/script_type_class.h"
#include "../_layout/tag_type_class.h"
#include "../_layout/team_class.h"
#include "../_layout/team_type_class.h"
#include "../_layout/task_force_class.h"
#include "../_layout/anim_type_class.h"
#include "../_layout/bullet_class.h"
#include "../_layout/warhead_type_class.h"

// CALLEE: GAMEMD 0x0045DD90 (decl; reloc) -- BuildingTypeClass default constructor.
// Declaring these overrides on the canonical class changes the code generated for
// ObjectTypeClass::FUN_005F9070 in object_type_class_shape_load.cpp, so the factory
// instantiates a derived view that carries them instead.
class BuildingTypeFactoryView_0045DD90 : public BuildingTypeClass
{
public:
    BuildingTypeFactoryView_0045DD90(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    virtual bool vf_32(const CellStruct* cell, HouseClass* house);
    virtual ObjectClass* vf_35(HouseClass* owner);
};






// CALLEE: GAMEMD 0x004385D0 (decl; reloc) -- BombClass default constructor.
#include "../_layout/rad_site_class.h"













#include "../_layout/iso_tile_type_class.h"


// CALLEE: GAMEMD 0x006B5260 (decl; reloc) -- SmudgeTypeClass default constructor.
class SmudgeTypeClass : public AbstractClass
{
public:
    SmudgeTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x2A4 - sizeof(AbstractClass)];
};


#include "../_layout/house_type_class.h"

#include "../_layout/house_class.h"

#include "../_layout/fly_locomotion_class.h"


// CALLEE: GAMEMD 0x00513C20 (decl; reloc) -- HoverLocomotionClass default constructor.
class HoverLocomotionClass : public LocomotionClass
{
public:
    HoverLocomotionClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual int Size();
    virtual int __stdcall InWhichLayer();
    unsigned char unknown_[0x78 - sizeof(LocomotionClass)];
};


// CALLEE: GAMEMD 0x004B5AB0 (decl; reloc) -- DropPodLocomotionClass default constructor.
class DropPodLocomotionClass : public LocomotionClass
{
public:
    DropPodLocomotionClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual int Size();
    virtual int __stdcall InWhichLayer();
    unsigned char unknown_[0x30 - sizeof(LocomotionClass)];
};




// CALLEE: GAMEMD 0x0062BB20 (decl; reloc) -- ParticleClass default constructor.
class ParticleClass : public AbstractClass
{
public:
    ParticleClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x138 - sizeof(AbstractClass)];
};

// CALLEE: GAMEMD 0x00644BE0 (decl; reloc) -- ParticleTypeClass default constructor.
class ParticleTypeClass : public AbstractClass
{
public:
    ParticleTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x318 - sizeof(AbstractClass)];
};

// CALLEE: GAMEMD 0x0062DF20 (decl; reloc) -- ParticleSystemClass default constructor.
class ParticleSystemClass : public AbstractClass
{
public:
    ParticleSystemClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x100 - sizeof(AbstractClass)];
};

// CALLEE: GAMEMD 0x006440A0 (decl; reloc) -- ParticleSystemTypeClass default constructor.
class ParticleSystemTypeClass : public AbstractClass
{
public:
    ParticleSystemTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x310 - sizeof(AbstractClass)];
};



// CALLEE: GAMEMD 0x004D08B0 (decl; reloc) -- FoggedObjectClass default constructor.
#include "../_layout/fogged_object_class.h"

#include "../_layout/alpha_shape_class.h"


#include <windows.h>
#include <objbase.h>

#include "vector_class_operations.h"

template class DynamicVectorClass<unsigned long>;

GG_STATIC_ASSERT(sizeof(unsigned long) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<unsigned long >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<unsigned long >) == 0x18);


// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x6BED80
// DynamicVectorClass<unsigned long>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6BEDA0
// VectorClass<unsigned long>::Slot6 (slot 6)
// GLOBAL: GAMEMD 0x817BC0 - IID_IUnknown; also the held interface's IID here.
extern const IID DAT_00817BC0;

// A holder of one IUnknown pointer (same shape as the one at 0x41C250).
struct ComPtr_006BEDB0
{
    IUnknown* Interface;   // +0x0000

    HRESULT CreateInstance(const CLSID& rclsid, IUnknown* outer, DWORD context);
};
GG_STATIC_ASSERT(offsetof(ComPtr_006BEDB0, Interface) == 0);

// FUNCTION: GAMEMD 0x6BEDB0
// Releases the held interface, then creates a new object. Out-of-process
// contexts (0x14) create as IUnknown, OleRun it, then query the held IID.
HRESULT ComPtr_006BEDB0::CreateInstance(const CLSID& rclsid, IUnknown* outer, DWORD context)
{
    HRESULT hr;
    if (Interface != 0) {
        Interface->Release();
    }
    if (context & 0x14) {
        IUnknown* unknown;
        hr = CoCreateInstance(rclsid, outer, context, DAT_00817BC0, (void**)&unknown);
        if (hr < 0) {
            return hr;
        }
        hr = OleRun(unknown);
        if (hr >= 0) {
            hr = unknown->QueryInterface(DAT_00817BC0, (void**)&Interface);
        }
        unknown->Release();
    } else {
        hr = CoCreateInstance(rclsid, outer, context, DAT_00817BC0, (void**)&Interface);
    }
    return hr;
}

template class VectorClass<unsigned long>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3768
#include "../_layout/tiberium_class.h"
#include "campaign_class.h"
#include "../movement/waypoint_path_class_methods.h"
#include "../_layout/airstrike_class.h"
#include "../_layout/spawn_manager_class.h"
#include "../_layout/slave_manager_class.h"
#include "../_layout/disk_laser_class.h"
#include "../_layout/trigger_type_class.h"
#include "../_layout/tag_class.h"
#include "../_layout/overlay_type_class.h"
#include "../movement/rocket_locomotion.h"
#include "../movement/mech_locomotion_class.h"
#include "../_layout/factory_class.h"
#include "../_layout/ai_trigger_type_class.h"
#include "../_layout/tube_class.h"
#include "../_layout/capture_manager_class.h"
#include "../_layout/neuron_class.h"

// class TClassFactory<CStreamClass>
// TEMPLATE: GAMEMD 0x6BEE40
// TClassFactory<CStreamClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BEE50
// TClassFactory<CStreamClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BEEC0
// TClassFactory<CStreamClass>::AddRef
// TEMPLATE: GAMEMD 0x6BEEE0
// TClassFactory<CStreamClass>::Release
// TEMPLATE: GAMEMD 0x006BEF10
// TClassFactory<CStreamClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6BEF90
// TClassFactory<CStreamClass>::LockServer
template class TClassFactory<CStreamClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3780
// class TClassFactory<WaveClass>
// TEMPLATE: GAMEMD 0x6BEFC0
// TClassFactory<WaveClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BEFD0
// TClassFactory<WaveClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF040
// TClassFactory<WaveClass>::AddRef
// TEMPLATE: GAMEMD 0x6BF060
// TClassFactory<WaveClass>::Release
// TEMPLATE: GAMEMD 0x006BF090
// TClassFactory<WaveClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6BF110
// TClassFactory<WaveClass>::LockServer
template class TClassFactory<WaveClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3798
// class TClassFactory<TerrainTypeClass>
// TEMPLATE: GAMEMD 0x6BF140
// TClassFactory<TerrainTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BF150
// TClassFactory<TerrainTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF1C0
// TClassFactory<TerrainTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6BF1E0
// TClassFactory<TerrainTypeClass>::Release
// TEMPLATE: GAMEMD 0x006BF210
// TClassFactory<TerrainTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6BF290
// TClassFactory<TerrainTypeClass>::LockServer
template class TClassFactory<TerrainTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F37B0
// class TClassFactory<TerrainClass>
// TEMPLATE: GAMEMD 0x6BF2C0
// TClassFactory<TerrainClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BF2D0
// TClassFactory<TerrainClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF340
// TClassFactory<TerrainClass>::AddRef
// TEMPLATE: GAMEMD 0x6BF360
// TClassFactory<TerrainClass>::Release
// TEMPLATE: GAMEMD 0x006BF390
// TClassFactory<TerrainClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6BF410
// TClassFactory<TerrainClass>::LockServer
template class TClassFactory<TerrainClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F37C8
// class TClassFactory<SuperWeaponTypeClass>
// TEMPLATE: GAMEMD 0x6BF440
// TClassFactory<SuperWeaponTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BF450
// TClassFactory<SuperWeaponTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF4C0
// TClassFactory<SuperWeaponTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6BF4E0
// TClassFactory<SuperWeaponTypeClass>::Release
// TEMPLATE: GAMEMD 0x006BF510
// TClassFactory<SuperWeaponTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6BF590
// TClassFactory<SuperWeaponTypeClass>::LockServer
template class TClassFactory<SuperWeaponTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F37E0
// class TClassFactory<SuperClass>
// TEMPLATE: GAMEMD 0x6BF5C0
// TClassFactory<SuperClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BF5D0
// TClassFactory<SuperClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF640
// TClassFactory<SuperClass>::AddRef
// TEMPLATE: GAMEMD 0x6BF660
// TClassFactory<SuperClass>::Release
// TEMPLATE: GAMEMD 0x006BF690
// TClassFactory<SuperClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6BF710
// TClassFactory<SuperClass>::LockServer
template class TClassFactory<SuperClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F37F8
// class TClassFactory<Tactical>
// TEMPLATE: GAMEMD 0x6BF740
// TClassFactory<Tactical>::TClassFactory
// TEMPLATE: GAMEMD 0x6BF750
// TClassFactory<Tactical>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF7C0
// TClassFactory<Tactical>::AddRef
// TEMPLATE: GAMEMD 0x6BF7E0
// TClassFactory<Tactical>::Release
// TEMPLATE: GAMEMD 0x006BF810
// TClassFactory<Tactical>::CreateInstance
// TEMPLATE: GAMEMD 0x6BF890
// TClassFactory<Tactical>::LockServer
template class TClassFactory<Tactical>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3810
// class TClassFactory<CellClass>
// TEMPLATE: GAMEMD 0x6BF8C0
// TClassFactory<CellClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BF8D0
// TClassFactory<CellClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BF940
// TClassFactory<CellClass>::AddRef
// TEMPLATE: GAMEMD 0x6BF960
// TClassFactory<CellClass>::Release
// TEMPLATE: GAMEMD 0x006BF990
// TClassFactory<CellClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6BFA10
// TClassFactory<CellClass>::LockServer
template class TClassFactory<CellClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3828
// class TClassFactory<EMPulseClass>
// TEMPLATE: GAMEMD 0x6BFA40
// TClassFactory<EMPulseClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BFA50
// TClassFactory<EMPulseClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BFAC0
// TClassFactory<EMPulseClass>::AddRef
// TEMPLATE: GAMEMD 0x6BFAE0
// TClassFactory<EMPulseClass>::Release
// TEMPLATE: GAMEMD 0x006BFB10
// TClassFactory<EMPulseClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6BFB90
// TClassFactory<EMPulseClass>::LockServer
template class TClassFactory<EMPulseClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3840
// class TClassFactory<LightSourceClass>
// TEMPLATE: GAMEMD 0x6BFBC0
// TClassFactory<LightSourceClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BFBD0
// TClassFactory<LightSourceClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BFC40
// TClassFactory<LightSourceClass>::AddRef
// TEMPLATE: GAMEMD 0x6BFC60
// TClassFactory<LightSourceClass>::Release
// TEMPLATE: GAMEMD 0x006BFC90
// TClassFactory<LightSourceClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6BFD10
// TClassFactory<LightSourceClass>::LockServer
template class TClassFactory<LightSourceClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3858
// class TClassFactory<SideClass>
// TEMPLATE: GAMEMD 0x6BFD40
// TClassFactory<SideClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BFD50
// TClassFactory<SideClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BFDC0
// TClassFactory<SideClass>::AddRef
// TEMPLATE: GAMEMD 0x6BFDE0
// TClassFactory<SideClass>::Release
// TEMPLATE: GAMEMD 0x006BFE10
// TClassFactory<SideClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6BFE90
// TClassFactory<SideClass>::LockServer
template class TClassFactory<SideClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3870
// class TClassFactory<TiberiumClass>
// TEMPLATE: GAMEMD 0x6BFEC0
// TClassFactory<TiberiumClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6BFED0
// TClassFactory<TiberiumClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6BFF40
// TClassFactory<TiberiumClass>::AddRef
// TEMPLATE: GAMEMD 0x6BFF60
// TClassFactory<TiberiumClass>::Release
// TEMPLATE: GAMEMD 0x006BFF90
// TClassFactory<TiberiumClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C0010
// TClassFactory<TiberiumClass>::LockServer
template class TClassFactory<TiberiumClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3888
// class TClassFactory<TubeClass>
// TEMPLATE: GAMEMD 0x6C0040
// TClassFactory<TubeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0050
// TClassFactory<TubeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C00C0
// TClassFactory<TubeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C00E0
// TClassFactory<TubeClass>::Release
// TEMPLATE: GAMEMD 0x006C0110
// TClassFactory<TubeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C0190
// TClassFactory<TubeClass>::LockServer
template class TClassFactory<TubeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F38A0
// class TClassFactory<CampaignClass>
// TEMPLATE: GAMEMD 0x6C01C0
// TClassFactory<CampaignClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C01D0
// TClassFactory<CampaignClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0240
// TClassFactory<CampaignClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0260
// TClassFactory<CampaignClass>::Release
// TEMPLATE: GAMEMD 0x006C0290
// TClassFactory<CampaignClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C0310
// TClassFactory<CampaignClass>::LockServer
template class TClassFactory<CampaignClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F38B8
// class TClassFactory<BuildingLightClass>
// TEMPLATE: GAMEMD 0x6C0340
// TClassFactory<BuildingLightClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0350
// TClassFactory<BuildingLightClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C03C0
// TClassFactory<BuildingLightClass>::AddRef
// TEMPLATE: GAMEMD 0x6C03E0
// TClassFactory<BuildingLightClass>::Release
// TEMPLATE: GAMEMD 0x006C0410
// TClassFactory<BuildingLightClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C0490
// TClassFactory<BuildingLightClass>::LockServer
template class TClassFactory<BuildingLightClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F38D0
// class TClassFactory<WaypointPathClass>
// TEMPLATE: GAMEMD 0x6C04C0
// TClassFactory<WaypointPathClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C04D0
// TClassFactory<WaypointPathClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0540
// TClassFactory<WaypointPathClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0560
// TClassFactory<WaypointPathClass>::Release
// TEMPLATE: GAMEMD 0x006C0590
// TClassFactory<WaypointPathClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C0610
// TClassFactory<WaypointPathClass>::LockServer
template class TClassFactory<WaypointPathClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F38E8
// class TClassFactory<TemporalClass>
// TEMPLATE: GAMEMD 0x6C0640
// TClassFactory<TemporalClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0650
// TClassFactory<TemporalClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C06C0
// TClassFactory<TemporalClass>::AddRef
// TEMPLATE: GAMEMD 0x6C06E0
// TClassFactory<TemporalClass>::Release
// TEMPLATE: GAMEMD 0x006C0710
// TClassFactory<TemporalClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C0790
// TClassFactory<TemporalClass>::LockServer
template class TClassFactory<TemporalClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3900
// class TClassFactory<AirstrikeClass>
// TEMPLATE: GAMEMD 0x6C07C0
// TClassFactory<AirstrikeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C07D0
// TClassFactory<AirstrikeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0840
// TClassFactory<AirstrikeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0860
// TClassFactory<AirstrikeClass>::Release
// TEMPLATE: GAMEMD 0x006C0890
// TClassFactory<AirstrikeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C0910
// TClassFactory<AirstrikeClass>::LockServer
template class TClassFactory<AirstrikeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3918
// class TClassFactory<SpawnManagerClass>
// TEMPLATE: GAMEMD 0x6C0940
// TClassFactory<SpawnManagerClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0950
// TClassFactory<SpawnManagerClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C09C0
// TClassFactory<SpawnManagerClass>::AddRef
// TEMPLATE: GAMEMD 0x6C09E0
// TClassFactory<SpawnManagerClass>::Release
// TEMPLATE: GAMEMD 0x006C0A10
// TClassFactory<SpawnManagerClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C0A90
// TClassFactory<SpawnManagerClass>::LockServer
template class TClassFactory<SpawnManagerClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3930
// class TClassFactory<SlaveManagerClass>
// TEMPLATE: GAMEMD 0x6C0AC0
// TClassFactory<SlaveManagerClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0AD0
// TClassFactory<SlaveManagerClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0B40
// TClassFactory<SlaveManagerClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0B60
// TClassFactory<SlaveManagerClass>::Release
// TEMPLATE: GAMEMD 0x006C0B90
// TClassFactory<SlaveManagerClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C0C10
// TClassFactory<SlaveManagerClass>::LockServer
template class TClassFactory<SlaveManagerClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3948
// class TClassFactory<CaptureManagerClass>
// TEMPLATE: GAMEMD 0x6C0C40
// TClassFactory<CaptureManagerClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0C50
// TClassFactory<CaptureManagerClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0CC0
// TClassFactory<CaptureManagerClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0CE0
// TClassFactory<CaptureManagerClass>::Release
// TEMPLATE: GAMEMD 0x006C0D10
// TClassFactory<CaptureManagerClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C0D90
// TClassFactory<CaptureManagerClass>::LockServer
template class TClassFactory<CaptureManagerClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3960
// class TClassFactory<DiskLaserClass>
// TEMPLATE: GAMEMD 0x6C0DC0
// TClassFactory<DiskLaserClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0DD0
// TClassFactory<DiskLaserClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0E40
// TClassFactory<DiskLaserClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0E60
// TClassFactory<DiskLaserClass>::Release
// TEMPLATE: GAMEMD 0x006C0E90
// TClassFactory<DiskLaserClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C0F10
// TClassFactory<DiskLaserClass>::LockServer
template class TClassFactory<DiskLaserClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3978
// class TClassFactory<ParasiteClass>
// TEMPLATE: GAMEMD 0x6C0F40
// TClassFactory<ParasiteClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C0F50
// TClassFactory<ParasiteClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C0FC0
// TClassFactory<ParasiteClass>::AddRef
// TEMPLATE: GAMEMD 0x6C0FE0
// TClassFactory<ParasiteClass>::Release
// TEMPLATE: GAMEMD 0x006C1010
// TClassFactory<ParasiteClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C1090
// TClassFactory<ParasiteClass>::LockServer
template class TClassFactory<ParasiteClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3990
// class TClassFactory<BombClass>
// TEMPLATE: GAMEMD 0x6C10C0
// TClassFactory<BombClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C10D0
// TClassFactory<BombClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1140
// TClassFactory<BombClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1160
// TClassFactory<BombClass>::Release
// TEMPLATE: GAMEMD 0x006C1190
// TClassFactory<BombClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C1210
// TClassFactory<BombClass>::LockServer
template class TClassFactory<BombClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F39A8
// class TClassFactory<RadSiteClass>
// TEMPLATE: GAMEMD 0x6C1240
// TClassFactory<RadSiteClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1250
// TClassFactory<RadSiteClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C12C0
// TClassFactory<RadSiteClass>::AddRef
// TEMPLATE: GAMEMD 0x6C12E0
// TClassFactory<RadSiteClass>::Release
// TEMPLATE: GAMEMD 0x006C1310
// TClassFactory<RadSiteClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C1390
// TClassFactory<RadSiteClass>::LockServer
template class TClassFactory<RadSiteClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F39C0
// class TClassFactory<TEventClass>
// TEMPLATE: GAMEMD 0x6C13C0
// TClassFactory<TEventClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C13D0
// TClassFactory<TEventClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1440
// TClassFactory<TEventClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1460
// TClassFactory<TEventClass>::Release
// TEMPLATE: GAMEMD 0x006C1490
// TClassFactory<TEventClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C1510
// TClassFactory<TEventClass>::LockServer
template class TClassFactory<TEventClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F39D8
// class TClassFactory<VoxelAnimTypeClass>
// TEMPLATE: GAMEMD 0x6C1540
// TClassFactory<VoxelAnimTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1550
// TClassFactory<VoxelAnimTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C15C0
// TClassFactory<VoxelAnimTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C15E0
// TClassFactory<VoxelAnimTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C1610
// TClassFactory<VoxelAnimTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C1690
// TClassFactory<VoxelAnimTypeClass>::LockServer
template class TClassFactory<VoxelAnimTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F39F0
// class TClassFactory<VoxelAnimClass>
// TEMPLATE: GAMEMD 0x6C16C0
// TClassFactory<VoxelAnimClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C16D0
// TClassFactory<VoxelAnimClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1740
// TClassFactory<VoxelAnimClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1760
// TClassFactory<VoxelAnimClass>::Release
// TEMPLATE: GAMEMD 0x006C1790
// TClassFactory<VoxelAnimClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C1810
// TClassFactory<VoxelAnimClass>::LockServer
template class TClassFactory<VoxelAnimClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3A08
// class TClassFactory<TActionClass>
// TEMPLATE: GAMEMD 0x6C1840
// TClassFactory<TActionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1850
// TClassFactory<TActionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C18C0
// TClassFactory<TActionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C18E0
// TClassFactory<TActionClass>::Release
// TEMPLATE: GAMEMD 0x006C1910
// TClassFactory<TActionClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C1990
// TClassFactory<TActionClass>::LockServer
template class TClassFactory<TActionClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3A20
// class TClassFactory<TriggerClass>
// TEMPLATE: GAMEMD 0x6C19C0
// TClassFactory<TriggerClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C19D0
// TClassFactory<TriggerClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1A40
// TClassFactory<TriggerClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1A60
// TClassFactory<TriggerClass>::Release
// TEMPLATE: GAMEMD 0x006C1A90
// TClassFactory<TriggerClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C1B10
// TClassFactory<TriggerClass>::LockServer
template class TClassFactory<TriggerClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3A38
// class TClassFactory<TriggerTypeClass>
// TEMPLATE: GAMEMD 0x6C1B40
// TClassFactory<TriggerTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1B50
// TClassFactory<TriggerTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1BC0
// TClassFactory<TriggerTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1BE0
// TClassFactory<TriggerTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C1C10
// TClassFactory<TriggerTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C1C90
// TClassFactory<TriggerTypeClass>::LockServer
template class TClassFactory<TriggerTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3A50
// class TClassFactory<ScriptClass>
// TEMPLATE: GAMEMD 0x6C1CC0
// TClassFactory<ScriptClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1CD0
// TClassFactory<ScriptClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1D40
// TClassFactory<ScriptClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1D60
// TClassFactory<ScriptClass>::Release
// TEMPLATE: GAMEMD 0x006C1D90
// TClassFactory<ScriptClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C1E10
// TClassFactory<ScriptClass>::LockServer
template class TClassFactory<ScriptClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3A68
// class TClassFactory<ScriptTypeClass>
// TEMPLATE: GAMEMD 0x6C1E40
// TClassFactory<ScriptTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1E50
// TClassFactory<ScriptTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C1EC0
// TClassFactory<ScriptTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C1EE0
// TClassFactory<ScriptTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C1F10
// TClassFactory<ScriptTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C1F90
// TClassFactory<ScriptTypeClass>::LockServer
template class TClassFactory<ScriptTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3A80
// class TClassFactory<TagClass>
// TEMPLATE: GAMEMD 0x6C1FC0
// TClassFactory<TagClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C1FD0
// TClassFactory<TagClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2040
// TClassFactory<TagClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2060
// TClassFactory<TagClass>::Release
// TEMPLATE: GAMEMD 0x006C2090
// TClassFactory<TagClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C2110
// TClassFactory<TagClass>::LockServer
template class TClassFactory<TagClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3A98
// class TClassFactory<TagTypeClass>
// TEMPLATE: GAMEMD 0x6C2140
// TClassFactory<TagTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2150
// TClassFactory<TagTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C21C0
// TClassFactory<TagTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C21E0
// TClassFactory<TagTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C2210
// TClassFactory<TagTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C2290
// TClassFactory<TagTypeClass>::LockServer
template class TClassFactory<TagTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3AB0
// class TClassFactory<TeamClass>
// TEMPLATE: GAMEMD 0x6C22C0
// TClassFactory<TeamClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C22D0
// TClassFactory<TeamClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2340
// TClassFactory<TeamClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2360
// TClassFactory<TeamClass>::Release
// TEMPLATE: GAMEMD 0x006C2390
// TClassFactory<TeamClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C2410
// TClassFactory<TeamClass>::LockServer
template class TClassFactory<TeamClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3AC8
// class TClassFactory<TeamTypeClass>
// TEMPLATE: GAMEMD 0x6C2440
// TClassFactory<TeamTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2450
// TClassFactory<TeamTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C24C0
// TClassFactory<TeamTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C24E0
// TClassFactory<TeamTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C2510
// TClassFactory<TeamTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C2590
// TClassFactory<TeamTypeClass>::LockServer
template class TClassFactory<TeamTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3AE0
// class TClassFactory<TaskForceClass>
// TEMPLATE: GAMEMD 0x6C25C0
// TClassFactory<TaskForceClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C25D0
// TClassFactory<TaskForceClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2640
// TClassFactory<TaskForceClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2660
// TClassFactory<TaskForceClass>::Release
// TEMPLATE: GAMEMD 0x006C2690
// TClassFactory<TaskForceClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C2710
// TClassFactory<TaskForceClass>::LockServer
template class TClassFactory<TaskForceClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3AF8
// class TClassFactory<UnitTypeClass>
// TEMPLATE: GAMEMD 0x6C2740
// TClassFactory<UnitTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2750
// TClassFactory<UnitTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C27C0
// TClassFactory<UnitTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C27E0
// TClassFactory<UnitTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C2810
// TClassFactory<UnitTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C2890
// TClassFactory<UnitTypeClass>::LockServer
template class TClassFactory<UnitTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3B10
// class TClassFactory<BuildingTypeClass>
// TEMPLATE: GAMEMD 0x6C28C0
// TClassFactory<BuildingTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C28D0
// TClassFactory<BuildingTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2940
// TClassFactory<BuildingTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2960
// TClassFactory<BuildingTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C2990
// TClassFactory<BuildingTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C2A10
// TClassFactory<BuildingTypeClass>::LockServer
template class TClassFactory<BuildingTypeFactoryView_0045DD90>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3B28
// class TClassFactory<AircraftTypeClass>
// TEMPLATE: GAMEMD 0x6C2A40
// TClassFactory<AircraftTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2A50
// TClassFactory<AircraftTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2AC0
// TClassFactory<AircraftTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2AE0
// TClassFactory<AircraftTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C2B10
// TClassFactory<AircraftTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C2B90
// TClassFactory<AircraftTypeClass>::LockServer
template class TClassFactory<AircraftTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3B40
// class TClassFactory<InfantryTypeClass>
// TEMPLATE: GAMEMD 0x6C2BC0
// TClassFactory<InfantryTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2BD0
// TClassFactory<InfantryTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2C40
// TClassFactory<InfantryTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2C60
// TClassFactory<InfantryTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C2C90
// TClassFactory<InfantryTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C2D10
// TClassFactory<InfantryTypeClass>::LockServer
template class TClassFactory<InfantryTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3B58
// class TClassFactory<BulletTypeClass>
// TEMPLATE: GAMEMD 0x6C2D40
// TClassFactory<BulletTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2D50
// TClassFactory<BulletTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2DC0
// TClassFactory<BulletTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2DE0
// TClassFactory<BulletTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C2E10
// TClassFactory<BulletTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C2E90
// TClassFactory<BulletTypeClass>::LockServer
template class TClassFactory<BulletTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3B70
// class TClassFactory<IsometricTileTypeClass>
// TEMPLATE: GAMEMD 0x6C2EC0
// TClassFactory<IsometricTileTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C2ED0
// TClassFactory<IsometricTileTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C2F40
// TClassFactory<IsometricTileTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C2F60
// TClassFactory<IsometricTileTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C2F90
// TClassFactory<IsometricTileTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C3010
// TClassFactory<IsometricTileTypeClass>::LockServer
template class TClassFactory<IsometricTileTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3B88
// class TClassFactory<OverlayTypeClass>
// TEMPLATE: GAMEMD 0x6C3040
// TClassFactory<OverlayTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3050
// TClassFactory<OverlayTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C30C0
// TClassFactory<OverlayTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C30E0
// TClassFactory<OverlayTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C3110
// TClassFactory<OverlayTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C3190
// TClassFactory<OverlayTypeClass>::LockServer
template class TClassFactory<OverlayTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3BA0
// class TClassFactory<SmudgeTypeClass>
// TEMPLATE: GAMEMD 0x6C31C0
// TClassFactory<SmudgeTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C31D0
// TClassFactory<SmudgeTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3240
// TClassFactory<SmudgeTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3260
// TClassFactory<SmudgeTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C3290
// TClassFactory<SmudgeTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C3310
// TClassFactory<SmudgeTypeClass>::LockServer
template class TClassFactory<SmudgeTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3BB8
// class TClassFactory<UnitClass>
// TEMPLATE: GAMEMD 0x6C3340
// TClassFactory<UnitClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3350
// TClassFactory<UnitClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C33C0
// TClassFactory<UnitClass>::AddRef
// TEMPLATE: GAMEMD 0x6C33E0
// TClassFactory<UnitClass>::Release
// TEMPLATE: GAMEMD 0x006C3410
// TClassFactory<UnitClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C3490
// TClassFactory<UnitClass>::LockServer
template class TClassFactory<UnitClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3BD0
// class TClassFactory<BuildingClass>
// TEMPLATE: GAMEMD 0x6C34C0
// TClassFactory<BuildingClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C34D0
// TClassFactory<BuildingClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3540
// TClassFactory<BuildingClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3560
// TClassFactory<BuildingClass>::Release
// TEMPLATE: GAMEMD 0x006C3590
// TClassFactory<BuildingClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C3610
// TClassFactory<BuildingClass>::LockServer
template class TClassFactory<BuildingClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3BE8
// class TClassFactory<AircraftClass>
// TEMPLATE: GAMEMD 0x6C3640
// TClassFactory<AircraftClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3650
// TClassFactory<AircraftClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C36C0
// TClassFactory<AircraftClass>::AddRef
// TEMPLATE: GAMEMD 0x6C36E0
// TClassFactory<AircraftClass>::Release
// TEMPLATE: GAMEMD 0x006C3710
// TClassFactory<AircraftClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C3790
// TClassFactory<AircraftClass>::LockServer
template class TClassFactory<AircraftClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3C00
// class TClassFactory<InfantryClass>
// TEMPLATE: GAMEMD 0x6C37C0
// TClassFactory<InfantryClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C37D0
// TClassFactory<InfantryClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3840
// TClassFactory<InfantryClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3860
// TClassFactory<InfantryClass>::Release
// TEMPLATE: GAMEMD 0x006C3890
// TClassFactory<InfantryClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C3910
// TClassFactory<InfantryClass>::LockServer
template class TClassFactory<InfantryClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3C18
// class TClassFactory<AnimClass>
// TEMPLATE: GAMEMD 0x6C3940
// TClassFactory<AnimClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3950
// TClassFactory<AnimClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C39C0
// TClassFactory<AnimClass>::AddRef
// TEMPLATE: GAMEMD 0x6C39E0
// TClassFactory<AnimClass>::Release
// TEMPLATE: GAMEMD 0x006C3A10
// TClassFactory<AnimClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C3A90
// TClassFactory<AnimClass>::LockServer
template class TClassFactory<AnimClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3C30
// class TClassFactory<AnimTypeClass>
// TEMPLATE: GAMEMD 0x6C3AC0
// TClassFactory<AnimTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3AD0
// TClassFactory<AnimTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3B40
// TClassFactory<AnimTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3B60
// TClassFactory<AnimTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C3B90
// TClassFactory<AnimTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C3C10
// TClassFactory<AnimTypeClass>::LockServer
template class TClassFactory<AnimTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3C48
// class TClassFactory<HouseTypeClass>
// TEMPLATE: GAMEMD 0x6C3C40
// TClassFactory<HouseTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3C50
// TClassFactory<HouseTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3CC0
// TClassFactory<HouseTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3CE0
// TClassFactory<HouseTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C3D10
// TClassFactory<HouseTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C3D90
// TClassFactory<HouseTypeClass>::LockServer
template class TClassFactory<HouseTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3C60
// class TClassFactory<HouseClass>
// TEMPLATE: GAMEMD 0x6C3DC0
// TClassFactory<HouseClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3DD0
// TClassFactory<HouseClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3E40
// TClassFactory<HouseClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3E60
// TClassFactory<HouseClass>::Release
// TEMPLATE: GAMEMD 0x006C3E90
// TClassFactory<HouseClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C3F10
// TClassFactory<HouseClass>::LockServer
template class TClassFactory<HouseClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3C78
// class TClassFactory<DriveLocomotionClass>
// TEMPLATE: GAMEMD 0x6C3F40
// TClassFactory<DriveLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C3F50
// TClassFactory<DriveLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C3FC0
// TClassFactory<DriveLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C3FE0
// TClassFactory<DriveLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x006C4010
// TClassFactory<DriveLocomotionClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C4090
// TClassFactory<DriveLocomotionClass>::LockServer
template class TClassFactory<DriveLocomotionClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3C90
// class TClassFactory<JumpjetLocomotionClass>
// TEMPLATE: GAMEMD 0x6C40C0
// TClassFactory<JumpjetLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C40D0
// TClassFactory<JumpjetLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4140
// TClassFactory<JumpjetLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4160
// TClassFactory<JumpjetLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x006C4190
// TClassFactory<JumpjetLocomotionClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C4210
// TClassFactory<JumpjetLocomotionClass>::LockServer
template class TClassFactory<JumpjetLocomotionClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3CA8
// class TClassFactory<HoverLocomotionClass>
// TEMPLATE: GAMEMD 0x6C4240
// TClassFactory<HoverLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4250
// TClassFactory<HoverLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C42C0
// TClassFactory<HoverLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C42E0
// TClassFactory<HoverLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x006C4310
// TClassFactory<HoverLocomotionClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C4390
// TClassFactory<HoverLocomotionClass>::LockServer
template class TClassFactory<HoverLocomotionClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3CC0
// class TClassFactory<RocketLocomotionClass>
// TEMPLATE: GAMEMD 0x6C43C0
// TClassFactory<RocketLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C43D0
// TClassFactory<RocketLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4440
// TClassFactory<RocketLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4460
// TClassFactory<RocketLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x006C4490
// TClassFactory<RocketLocomotionClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C4510
// TClassFactory<RocketLocomotionClass>::LockServer
template class TClassFactory<RocketLocomotionClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3CD8
// class TClassFactory<TunnelLocomotionClass>
// TEMPLATE: GAMEMD 0x6C4540
// TClassFactory<TunnelLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4550
// TClassFactory<TunnelLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C45C0
// TClassFactory<TunnelLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C45E0
// TClassFactory<TunnelLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x006C4610
// TClassFactory<TunnelLocomotionClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C4690
// TClassFactory<TunnelLocomotionClass>::LockServer
template class TClassFactory<TunnelLocomotionClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3CF0
// class TClassFactory<WalkLocomotionClass>
// TEMPLATE: GAMEMD 0x6C46C0
// TClassFactory<WalkLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C46D0
// TClassFactory<WalkLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4740
// TClassFactory<WalkLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4760
// TClassFactory<WalkLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x006C4790
// TClassFactory<WalkLocomotionClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C4810
// TClassFactory<WalkLocomotionClass>::LockServer
template class TClassFactory<WalkLocomotionClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3D08
// class TClassFactory<DropPodLocomotionClass>
// TEMPLATE: GAMEMD 0x6C4840
// TClassFactory<DropPodLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4850
// TClassFactory<DropPodLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C48C0
// TClassFactory<DropPodLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C48E0
// TClassFactory<DropPodLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x006C4910
// TClassFactory<DropPodLocomotionClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C4990
// TClassFactory<DropPodLocomotionClass>::LockServer
template class TClassFactory<DropPodLocomotionClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3D20
// class TClassFactory<FlyLocomotionClass>
// TEMPLATE: GAMEMD 0x6C49C0
// TClassFactory<FlyLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C49D0
// TClassFactory<FlyLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4A40
// TClassFactory<FlyLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4A60
// TClassFactory<FlyLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x006C4A90
// TClassFactory<FlyLocomotionClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C4B10
// TClassFactory<FlyLocomotionClass>::LockServer
template class TClassFactory<FlyLocomotionClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3D38
// class TClassFactory<TeleportLocomotionClass>
// TEMPLATE: GAMEMD 0x6C4B40
// TClassFactory<TeleportLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4B50
// TClassFactory<TeleportLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4BC0
// TClassFactory<TeleportLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4BE0
// TClassFactory<TeleportLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x006C4C10
// TClassFactory<TeleportLocomotionClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C4C90
// TClassFactory<TeleportLocomotionClass>::LockServer
template class TClassFactory<TeleportLocomotionClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3D50
// class TClassFactory<MechLocomotionClass>
// TEMPLATE: GAMEMD 0x6C4CC0
// TClassFactory<MechLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4CD0
// TClassFactory<MechLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4D40
// TClassFactory<MechLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4D60
// TClassFactory<MechLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x006C4D90
// TClassFactory<MechLocomotionClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C4E10
// TClassFactory<MechLocomotionClass>::LockServer
template class TClassFactory<MechLocomotionClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3D68
// class TClassFactory<ShipLocomotionClass>
// TEMPLATE: GAMEMD 0x6C4E40
// TClassFactory<ShipLocomotionClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4E50
// TClassFactory<ShipLocomotionClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C4EC0
// TClassFactory<ShipLocomotionClass>::AddRef
// TEMPLATE: GAMEMD 0x6C4EE0
// TClassFactory<ShipLocomotionClass>::Release
// TEMPLATE: GAMEMD 0x006C4F10
// TClassFactory<ShipLocomotionClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C4F90
// TClassFactory<ShipLocomotionClass>::LockServer
template class TClassFactory<ShipLocomotionClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3D80
// class TClassFactory<BulletClass>
// TEMPLATE: GAMEMD 0x6C4FC0
// TClassFactory<BulletClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C4FD0
// TClassFactory<BulletClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5040
// TClassFactory<BulletClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5060
// TClassFactory<BulletClass>::Release
// TEMPLATE: GAMEMD 0x006C5090
// TClassFactory<BulletClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C5110
// TClassFactory<BulletClass>::LockServer
template class TClassFactory<BulletClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3D98
// class TClassFactory<FactoryClass>
// TEMPLATE: GAMEMD 0x6C5140
// TClassFactory<FactoryClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5150
// TClassFactory<FactoryClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C51C0
// TClassFactory<FactoryClass>::AddRef
// TEMPLATE: GAMEMD 0x6C51E0
// TClassFactory<FactoryClass>::Release
// TEMPLATE: GAMEMD 0x006C5210
// TClassFactory<FactoryClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C5290
// TClassFactory<FactoryClass>::LockServer
template class TClassFactory<FactoryClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3DB0
// class TClassFactory<WarheadTypeClass>
// TEMPLATE: GAMEMD 0x6C52C0
// TClassFactory<WarheadTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C52D0
// TClassFactory<WarheadTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5340
// TClassFactory<WarheadTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5360
// TClassFactory<WarheadTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C5390
// TClassFactory<WarheadTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C5410
// TClassFactory<WarheadTypeClass>::LockServer
template class TClassFactory<WarheadTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3DC8
// class TClassFactory<WeaponTypeClass>
// TEMPLATE: GAMEMD 0x6C5440
// TClassFactory<WeaponTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5450
// TClassFactory<WeaponTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C54C0
// TClassFactory<WeaponTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C54E0
// TClassFactory<WeaponTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C5510
// TClassFactory<WeaponTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C5590
// TClassFactory<WeaponTypeClass>::LockServer
template class TClassFactory<WeaponTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3DE0
// class TClassFactory<ParticleClass>
// TEMPLATE: GAMEMD 0x6C55C0
// TClassFactory<ParticleClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C55D0
// TClassFactory<ParticleClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5640
// TClassFactory<ParticleClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5660
// TClassFactory<ParticleClass>::Release
// TEMPLATE: GAMEMD 0x006C5690
// TClassFactory<ParticleClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C5710
// TClassFactory<ParticleClass>::LockServer
template class TClassFactory<ParticleClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3DF8
// class TClassFactory<ParticleTypeClass>
// TEMPLATE: GAMEMD 0x6C5740
// TClassFactory<ParticleTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5750
// TClassFactory<ParticleTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C57C0
// TClassFactory<ParticleTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C57E0
// TClassFactory<ParticleTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C5810
// TClassFactory<ParticleTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C5890
// TClassFactory<ParticleTypeClass>::LockServer
template class TClassFactory<ParticleTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3E10
// class TClassFactory<ParticleSystemClass>
// TEMPLATE: GAMEMD 0x6C58C0
// TClassFactory<ParticleSystemClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C58D0
// TClassFactory<ParticleSystemClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5940
// TClassFactory<ParticleSystemClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5960
// TClassFactory<ParticleSystemClass>::Release
// TEMPLATE: GAMEMD 0x006C5990
// TClassFactory<ParticleSystemClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C5A10
// TClassFactory<ParticleSystemClass>::LockServer
template class TClassFactory<ParticleSystemClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3E28
// class TClassFactory<ParticleSystemTypeClass>
// TEMPLATE: GAMEMD 0x6C5A40
// TClassFactory<ParticleSystemTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5A50
// TClassFactory<ParticleSystemTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5AC0
// TClassFactory<ParticleSystemTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5AE0
// TClassFactory<ParticleSystemTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C5B10
// TClassFactory<ParticleSystemTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C5B90
// TClassFactory<ParticleSystemTypeClass>::LockServer
template class TClassFactory<ParticleSystemTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3E40
// class TClassFactory<AITriggerTypeClass>
// TEMPLATE: GAMEMD 0x6C5BC0
// TClassFactory<AITriggerTypeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5BD0
// TClassFactory<AITriggerTypeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5C40
// TClassFactory<AITriggerTypeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5C60
// TClassFactory<AITriggerTypeClass>::Release
// TEMPLATE: GAMEMD 0x006C5C90
// TClassFactory<AITriggerTypeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C5D10
// TClassFactory<AITriggerTypeClass>::LockServer
template class TClassFactory<AITriggerTypeClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3E58
// class TClassFactory<NeuronClass>
// TEMPLATE: GAMEMD 0x6C5D40
// TClassFactory<NeuronClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5D50
// TClassFactory<NeuronClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5DC0
// TClassFactory<NeuronClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5DE0
// TClassFactory<NeuronClass>::Release
// TEMPLATE: GAMEMD 0x006C5E10
// TClassFactory<NeuronClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C5E90
// TClassFactory<NeuronClass>::LockServer
template class TClassFactory<NeuronClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3E70
// class TClassFactory<FoggedObjectClass>
// TEMPLATE: GAMEMD 0x6C5EC0
// TClassFactory<FoggedObjectClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C5ED0
// TClassFactory<FoggedObjectClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C5F40
// TClassFactory<FoggedObjectClass>::AddRef
// TEMPLATE: GAMEMD 0x6C5F60
// TClassFactory<FoggedObjectClass>::Release
// TEMPLATE: GAMEMD 0x006C5F90
// TClassFactory<FoggedObjectClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C6010
// TClassFactory<FoggedObjectClass>::LockServer
template class TClassFactory<FoggedObjectClass>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// VTABLE: GAMEMD 0x7F3E88
// class TClassFactory<AlphaShapeClass>
// TEMPLATE: GAMEMD 0x6C6040
// TClassFactory<AlphaShapeClass>::TClassFactory
// TEMPLATE: GAMEMD 0x6C6050
// TClassFactory<AlphaShapeClass>::QueryInterface
// TEMPLATE: GAMEMD 0x6C60C0
// TClassFactory<AlphaShapeClass>::AddRef
// TEMPLATE: GAMEMD 0x6C60E0
// TClassFactory<AlphaShapeClass>::Release
// TEMPLATE: GAMEMD 0x006C6110
// TClassFactory<AlphaShapeClass>::CreateInstance
// TEMPLATE: GAMEMD 0x6C6190
// TClassFactory<AlphaShapeClass>::LockServer
template class TClassFactory<AlphaShapeClass>;

// TEMPLATE: GAMEMD 0x6C61D0
// VectorClass<unsigned long>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x6C6210
// VectorClass<unsigned long>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x6C62F0
// VectorClass<unsigned long>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x6C6330
// VectorClass<unsigned long>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x6C6350
// DynamicVectorClass<unsigned long>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x6C6450
// DynamicVectorClass<unsigned long>::FindItemIndex (slot 4)

// Factory layout shared by the native factory instantiations above.
typedef TClassFactory<CStreamClass> GgClassFactoryRep;
GG_STATIC_ASSERT(offsetof(GgClassFactoryRep, RefCount) == 0x4);
GG_STATIC_ASSERT(sizeof(GgClassFactoryRep) == 0x8);

