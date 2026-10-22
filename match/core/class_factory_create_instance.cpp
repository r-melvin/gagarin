// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
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
#include "class_factory.h"
#include "../_layout/abstract_class.h"
#include "../movement/loco_base.h"
#include "../_layout/side_class.h"
#include "../_layout/wave_class.h"

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

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x004A2820 (decl; reloc) -- CStreamClass default constructor.
class CStreamClass : public IPersistStream
{
public:
    CStreamClass();
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);
    virtual ULONG __stdcall AddRef();
    virtual ULONG __stdcall Release();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall IsDirty();
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);
    virtual void vf_8();
    virtual void vf_9();
    virtual void vf_10();
    virtual void vf_11();
    virtual void vf_12();
    virtual void vf_13();
    virtual ~CStreamClass();
    unsigned char unknown_[0x2C - sizeof(IPersistStream)];
};
// FUNCTION: GAMEMD 0x0071DA80 (decl; reloc) -- TerrainTypeClass default constructor.
class TerrainTypeClass : public AbstractClass
{
public:
    TerrainTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x2BC - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0071BDF0 (decl; reloc) -- TerrainClass default constructor.
class TerrainClass : public AbstractClass
{
public:
    TerrainClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0xE0 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006CE5B0 (decl; reloc) -- SuperWeaponTypeClass default constructor.
class SuperWeaponTypeClass : public AbstractClass
{
public:
    SuperWeaponTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x100 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006CAEC0 (decl; reloc) -- SuperClass default constructor.
class SuperClass : public AbstractClass
{
public:
    SuperClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x80 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006D1C20 (decl; reloc) -- Tactical default constructor.
class Tactical : public AbstractClass
{
public:
    Tactical();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0xE18 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0047BBF0 (decl; reloc) -- CellClass default constructor.
class CellClass : public AbstractClass
{
public:
    CellClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x148 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x004C5370 (decl; reloc) -- EMPulseClass default constructor.
class EMPulseClass : public AbstractClass
{
public:
    EMPulseClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x34 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x00554830 (decl; reloc) -- LightSourceClass default constructor.
class LightSourceClass : public AbstractClass
{
public:
    LightSourceClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x4C - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x007216C0 (decl; reloc) -- TiberiumClass default constructor.
class TiberiumClass : public AbstractClass
{
public:
    TiberiumClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x128 - sizeof(AbstractClass)];
};
extern int DAT_00B0BC68;
// FUNCTION: GAMEMD 0x00727FD0 (decl; reloc) -- TubeClass default constructor.
class TubeClass : public AbstractClass
{
public:
    TubeClass(int* unknown_arg0 = &DAT_00B0BC68, int unknown_arg1 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x1C4 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0046CB60 (decl; reloc) -- CampaignClass default constructor.
class CampaignClass : public AbstractClass
{
public:
    CampaignClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x3A0 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x00435820 (decl; reloc) -- BuildingLightClass default constructor.
class BuildingLightClass : public AbstractClass
{
public:
    BuildingLightClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0xE8 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x00763730 (decl; reloc) -- WaypointPathClass default constructor.
class WaypointPathClass : public AbstractClass
{
public:
    WaypointPathClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x40 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0071A450 (decl; reloc) -- TemporalClass default constructor.
class TemporalClass : public AbstractClass
{
public:
    TemporalClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x50 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0041D300 (decl; reloc) -- AirstrikeClass default constructor.
class AirstrikeClass : public AbstractClass
{
public:
    AirstrikeClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x60 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006B6EA0 (decl; reloc) -- SpawnManagerClass default constructor.
class SpawnManagerClass : public AbstractClass
{
public:
    SpawnManagerClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x74 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006AF360 (decl; reloc) -- SlaveManagerClass default constructor.
class SlaveManagerClass : public AbstractClass
{
public:
    SlaveManagerClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x64 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x00471890 (decl; reloc) -- CaptureManagerClass default constructor.
class CaptureManagerClass : public AbstractClass
{
public:
    CaptureManagerClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x50 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x004A7A30 (decl; reloc) -- DiskLaserClass default constructor.
class DiskLaserClass : public AbstractClass
{
public:
    DiskLaserClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x40 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x00629210 (decl; reloc) -- ParasiteClass default constructor.
class ParasiteClass : public AbstractClass
{
public:
    ParasiteClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x58 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x004385D0 (decl; reloc) -- BombClass default constructor.
class BombClass : public AbstractClass
{
public:
    BombClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x5C - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0065B1E0 (decl; reloc) -- RadSiteClass default constructor.
class RadSiteClass : public AbstractClass
{
public:
    RadSiteClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x74 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0071E6A0 (decl; reloc) -- TEventClass default constructor.
class TEventClass : public AbstractClass
{
public:
    TEventClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x58 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0074AD80 (decl; reloc) -- VoxelAnimTypeClass default constructor.
class VoxelAnimTypeClass : public AbstractClass
{
public:
    VoxelAnimTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x308 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x007498D0 (decl; reloc) -- VoxelAnimClass default constructor.
class VoxelAnimClass : public AbstractClass
{
public:
    VoxelAnimClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x148 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006DD000 (decl; reloc) -- TActionClass default constructor.
class TActionClass : public AbstractClass
{
public:
    TActionClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x94 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x00725FA0 (decl; reloc) -- TriggerClass default constructor.
class TriggerClass : public AbstractClass
{
public:
    TriggerClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x48 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x00726C80 (decl; reloc) -- TriggerTypeClass default constructor.
class TriggerTypeClass : public AbstractClass
{
public:
    TriggerTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0xB4 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006913C0 (decl; reloc) -- ScriptClass default constructor.
class ScriptClass : public AbstractClass
{
public:
    ScriptClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x30 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006916B0 (decl; reloc) -- ScriptTypeClass default constructor.
class ScriptTypeClass : public AbstractClass
{
public:
    ScriptTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x234 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006E4DE0 (decl; reloc) -- TagClass default constructor.
class TagClass : public AbstractClass
{
public:
    TagClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x38 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006E5B60 (decl; reloc) -- TagTypeClass default constructor.
class TagTypeClass : public AbstractClass
{
public:
    TagTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0xA4 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006E8A90 (decl; reloc) -- TeamClass default constructor.
class TeamClass : public AbstractClass
{
public:
    TeamClass(int unknown_arg0 = 0, int unknown_arg1 = 0, int unknown_arg2 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0xA0 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006F06E0 (decl; reloc) -- TeamTypeClass default constructor.
class TeamTypeClass : public AbstractClass
{
public:
    TeamTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0xF8 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006E7E80 (decl; reloc) -- TaskForceClass default constructor.
class TaskForceClass : public AbstractClass
{
public:
    TaskForceClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0xD4 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x007470D0 (decl; reloc) -- UnitTypeClass default constructor.
class UnitTypeClass : public AbstractClass
{
public:
    UnitTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0xE78 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0045DD90 (decl; reloc) -- BuildingTypeClass default constructor.
class BuildingTypeClass : public AbstractClass
{
public:
    BuildingTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x1798 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0041C8B0 (decl; reloc) -- AircraftTypeClass default constructor.
class AircraftTypeClass : public AbstractClass
{
public:
    AircraftTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0xE10 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x005236A0 (decl; reloc) -- InfantryTypeClass default constructor.
class InfantryTypeClass : public AbstractClass
{
public:
    InfantryTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0xED0 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0046BBC0 (decl; reloc) -- BulletTypeClass default constructor.
class BulletTypeClass : public AbstractClass
{
public:
    BulletTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x2F8 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x005447C0 (decl; reloc) -- IsometricTileTypeClass default constructor.
class IsometricTileTypeClass : public AbstractClass
{
public:
    IsometricTileTypeClass(int unknown_arg0 = 0, int unknown_arg1 = 0, int unknown_arg2 = 0, int unknown_arg3 = 0, int unknown_arg4 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x30C - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x005FE250 (decl; reloc) -- OverlayTypeClass default constructor.
class OverlayTypeClass : public AbstractClass
{
public:
    OverlayTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x2BC - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x006B5260 (decl; reloc) -- SmudgeTypeClass default constructor.
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
// FUNCTION: GAMEMD 0x007353C0 (decl; reloc) -- UnitClass default constructor.
class UnitClass : public AbstractClass
{
public:
    UnitClass(int unknown_arg0 = 0, int unknown_arg1 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x8E8 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0043B740 (decl; reloc) -- BuildingClass default constructor.
class BuildingClass : public AbstractClass
{
public:
    BuildingClass(int unknown_arg0 = 0, int unknown_arg1 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x720 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x00413D20 (decl; reloc) -- AircraftClass default constructor.
class AircraftClass : public AbstractClass
{
public:
    AircraftClass(int unknown_arg0 = 0, int unknown_arg1 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x6D8 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x00517A50 (decl; reloc) -- InfantryClass default constructor.
class InfantryClass : public AbstractClass
{
public:
    InfantryClass(int unknown_arg0 = 0, int unknown_arg1 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x6F0 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x00422720 (decl; reloc) -- AnimClass default constructor.
class AnimClass : public AbstractClass
{
public:
    AnimClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x1C8 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x00427530 (decl; reloc) -- AnimTypeClass default constructor.
class AnimTypeClass : public AbstractClass
{
public:
    AnimTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x378 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x005113F0 (decl; reloc) -- HouseTypeClass default constructor.
class HouseTypeClass : public AbstractClass
{
public:
    HouseTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x1B0 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x004F54A0 (decl; reloc) -- HouseClass default constructor.
class HouseClass : public AbstractClass
{
public:
    HouseClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x160B8 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x004AF540 (decl; reloc) -- DriveLocomotionClass default constructor.
class DriveLocomotionClass : public LocomotionClass
{
public:
    DriveLocomotionClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual int Size();
    virtual int __stdcall InWhichLayer();
    unsigned char unknown_[0x70 - sizeof(LocomotionClass)];
};
// FUNCTION: GAMEMD 0x0054AC40 (decl; reloc) -- JumpjetLocomotionClass default constructor.
class JumpjetLocomotionClass : public LocomotionClass
{
public:
    JumpjetLocomotionClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual int Size();
    virtual int __stdcall InWhichLayer();
    unsigned char unknown_[0x98 - sizeof(LocomotionClass)];
};
// FUNCTION: GAMEMD 0x00513C20 (decl; reloc) -- HoverLocomotionClass default constructor.
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
// FUNCTION: GAMEMD 0x00661EC0 (decl; reloc) -- RocketLocomotionClass default constructor.
class RocketLocomotionClass : public LocomotionClass
{
public:
    RocketLocomotionClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual int Size();
    virtual int __stdcall InWhichLayer();
    unsigned char unknown_[0x60 - sizeof(LocomotionClass)];
};
// FUNCTION: GAMEMD 0x00728A00 (decl; reloc) -- TunnelLocomotionClass default constructor.
class TunnelLocomotionClass : public LocomotionClass
{
public:
    TunnelLocomotionClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual int Size();
    virtual int __stdcall InWhichLayer();
    unsigned char unknown_[0x3C - sizeof(LocomotionClass)];
};
// FUNCTION: GAMEMD 0x0075AA90 (decl; reloc) -- WalkLocomotionClass default constructor.
class WalkLocomotionClass : public LocomotionClass
{
public:
    WalkLocomotionClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual int Size();
    virtual int __stdcall InWhichLayer();
    unsigned char unknown_[0x3C - sizeof(LocomotionClass)];
};
// FUNCTION: GAMEMD 0x004B5AB0 (decl; reloc) -- DropPodLocomotionClass default constructor.
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
// FUNCTION: GAMEMD 0x004CC9A0 (decl; reloc) -- FlyLocomotionClass default constructor.
class FlyLocomotionClass : public LocomotionClass
{
public:
    FlyLocomotionClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual int Size();
    virtual int __stdcall InWhichLayer();
    unsigned char unknown_[0x60 - sizeof(LocomotionClass)];
};
// FUNCTION: GAMEMD 0x00718000 (decl; reloc) -- TeleportLocomotionClass default constructor.
class TeleportLocomotionClass : public LocomotionClass
{
public:
    TeleportLocomotionClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual int Size();
    virtual int __stdcall InWhichLayer();
    unsigned char unknown_[0x4C - sizeof(LocomotionClass)];
};
// FUNCTION: GAMEMD 0x005AFEF0 (decl; reloc) -- MechLocomotionClass default constructor.
class MechLocomotionClass : public LocomotionClass
{
public:
    MechLocomotionClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual int Size();
    virtual int __stdcall InWhichLayer();
    unsigned char unknown_[0x34 - sizeof(LocomotionClass)];
};
// FUNCTION: GAMEMD 0x0069EC50 (decl; reloc) -- ShipLocomotionClass default constructor.
class ShipLocomotionClass : public LocomotionClass
{
public:
    ShipLocomotionClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual int Size();
    virtual int __stdcall InWhichLayer();
    unsigned char unknown_[0x70 - sizeof(LocomotionClass)];
};
// FUNCTION: GAMEMD 0x00466380 (decl; reloc) -- BulletClass default constructor.
class BulletClass : public AbstractClass
{
public:
    BulletClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x160 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x004C98B0 (decl; reloc) -- FactoryClass default constructor.
class FactoryClass : public AbstractClass
{
public:
    FactoryClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x74 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0075CEC0 (decl; reloc) -- WarheadTypeClass default constructor.
class WarheadTypeClass : public AbstractClass
{
public:
    WarheadTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x1D0 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x00771C70 (decl; reloc) -- WeaponTypeClass default constructor.
class WeaponTypeClass : public AbstractClass
{
public:
    WeaponTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x160 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0062BB20 (decl; reloc) -- ParticleClass default constructor.
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
// FUNCTION: GAMEMD 0x00644BE0 (decl; reloc) -- ParticleTypeClass default constructor.
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
// FUNCTION: GAMEMD 0x0062DF20 (decl; reloc) -- ParticleSystemClass default constructor.
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
// FUNCTION: GAMEMD 0x006440A0 (decl; reloc) -- ParticleSystemTypeClass default constructor.
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
// FUNCTION: GAMEMD 0x0041E350 (decl; reloc) -- AITriggerTypeClass default constructor.
class AITriggerTypeClass : public AbstractClass
{
public:
    AITriggerTypeClass(int unknown_arg0 = 0);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x110 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x0043A350 (decl; reloc) -- NeuronClass default constructor.
class NeuronClass : public AbstractClass
{
public:
    NeuronClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x38 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x004D08B0 (decl; reloc) -- FoggedObjectClass default constructor.
class FoggedObjectClass : public AbstractClass
{
public:
    FoggedObjectClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x78 - sizeof(AbstractClass)];
};
// FUNCTION: GAMEMD 0x00420AF0 (decl; reloc) -- AlphaShapeClass default constructor.
class AlphaShapeClass : public AbstractClass
{
public:
    AlphaShapeClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    unsigned char unknown_[0x40 - sizeof(AbstractClass)];
};

// FUNCTION: GAMEMD 0x006BEF10
// TClassFactory<CStreamClass>::CreateInstance
template class TClassFactory<CStreamClass>;

// FUNCTION: GAMEMD 0x006BF090
// TClassFactory<WaveClass>::CreateInstance
template class TClassFactory<WaveClass>;

// FUNCTION: GAMEMD 0x006BF210
// TClassFactory<TerrainTypeClass>::CreateInstance
template class TClassFactory<TerrainTypeClass>;

// FUNCTION: GAMEMD 0x006BF390
// TClassFactory<TerrainClass>::CreateInstance
template class TClassFactory<TerrainClass>;

// FUNCTION: GAMEMD 0x006BF510
// TClassFactory<SuperWeaponTypeClass>::CreateInstance
template class TClassFactory<SuperWeaponTypeClass>;

// FUNCTION: GAMEMD 0x006BF690
// TClassFactory<SuperClass>::CreateInstance
template class TClassFactory<SuperClass>;

// FUNCTION: GAMEMD 0x006BF810
// TClassFactory<Tactical>::CreateInstance
template class TClassFactory<Tactical>;

// FUNCTION: GAMEMD 0x006BF990
// TClassFactory<CellClass>::CreateInstance
template class TClassFactory<CellClass>;

// FUNCTION: GAMEMD 0x006BFB10
// TClassFactory<EMPulseClass>::CreateInstance
template class TClassFactory<EMPulseClass>;

// FUNCTION: GAMEMD 0x006BFC90
// TClassFactory<LightSourceClass>::CreateInstance
template class TClassFactory<LightSourceClass>;

// FUNCTION: GAMEMD 0x006BFE10
// TClassFactory<SideClass>::CreateInstance
template class TClassFactory<SideClass>;

// FUNCTION: GAMEMD 0x006BFF90
// TClassFactory<TiberiumClass>::CreateInstance
template class TClassFactory<TiberiumClass>;

// FUNCTION: GAMEMD 0x006C0110
// TClassFactory<TubeClass>::CreateInstance
template class TClassFactory<TubeClass>;

// FUNCTION: GAMEMD 0x006C0290
// TClassFactory<CampaignClass>::CreateInstance
template class TClassFactory<CampaignClass>;

// FUNCTION: GAMEMD 0x006C0410
// TClassFactory<BuildingLightClass>::CreateInstance
template class TClassFactory<BuildingLightClass>;

// FUNCTION: GAMEMD 0x006C0590
// TClassFactory<WaypointPathClass>::CreateInstance
template class TClassFactory<WaypointPathClass>;

// FUNCTION: GAMEMD 0x006C0710
// TClassFactory<TemporalClass>::CreateInstance
template class TClassFactory<TemporalClass>;

// FUNCTION: GAMEMD 0x006C0890
// TClassFactory<AirstrikeClass>::CreateInstance
template class TClassFactory<AirstrikeClass>;

// FUNCTION: GAMEMD 0x006C0A10
// TClassFactory<SpawnManagerClass>::CreateInstance
template class TClassFactory<SpawnManagerClass>;

// FUNCTION: GAMEMD 0x006C0B90
// TClassFactory<SlaveManagerClass>::CreateInstance
template class TClassFactory<SlaveManagerClass>;

// FUNCTION: GAMEMD 0x006C0D10
// TClassFactory<CaptureManagerClass>::CreateInstance
template class TClassFactory<CaptureManagerClass>;

// FUNCTION: GAMEMD 0x006C0E90
// TClassFactory<DiskLaserClass>::CreateInstance
template class TClassFactory<DiskLaserClass>;

// FUNCTION: GAMEMD 0x006C1010
// TClassFactory<ParasiteClass>::CreateInstance
template class TClassFactory<ParasiteClass>;

// FUNCTION: GAMEMD 0x006C1190
// TClassFactory<BombClass>::CreateInstance
template class TClassFactory<BombClass>;

// FUNCTION: GAMEMD 0x006C1310
// TClassFactory<RadSiteClass>::CreateInstance
template class TClassFactory<RadSiteClass>;

// FUNCTION: GAMEMD 0x006C1490
// TClassFactory<TEventClass>::CreateInstance
template class TClassFactory<TEventClass>;

// FUNCTION: GAMEMD 0x006C1610
// TClassFactory<VoxelAnimTypeClass>::CreateInstance
template class TClassFactory<VoxelAnimTypeClass>;

// FUNCTION: GAMEMD 0x006C1790
// TClassFactory<VoxelAnimClass>::CreateInstance
template class TClassFactory<VoxelAnimClass>;

// FUNCTION: GAMEMD 0x006C1910
// TClassFactory<TActionClass>::CreateInstance
template class TClassFactory<TActionClass>;

// FUNCTION: GAMEMD 0x006C1A90
// TClassFactory<TriggerClass>::CreateInstance
template class TClassFactory<TriggerClass>;

// FUNCTION: GAMEMD 0x006C1C10
// TClassFactory<TriggerTypeClass>::CreateInstance
template class TClassFactory<TriggerTypeClass>;

// FUNCTION: GAMEMD 0x006C1D90
// TClassFactory<ScriptClass>::CreateInstance
template class TClassFactory<ScriptClass>;

// FUNCTION: GAMEMD 0x006C1F10
// TClassFactory<ScriptTypeClass>::CreateInstance
template class TClassFactory<ScriptTypeClass>;

// FUNCTION: GAMEMD 0x006C2090
// TClassFactory<TagClass>::CreateInstance
template class TClassFactory<TagClass>;

// FUNCTION: GAMEMD 0x006C2210
// TClassFactory<TagTypeClass>::CreateInstance
template class TClassFactory<TagTypeClass>;

// FUNCTION: GAMEMD 0x006C2390
// TClassFactory<TeamClass>::CreateInstance
template class TClassFactory<TeamClass>;

// FUNCTION: GAMEMD 0x006C2510
// TClassFactory<TeamTypeClass>::CreateInstance
template class TClassFactory<TeamTypeClass>;

// FUNCTION: GAMEMD 0x006C2690
// TClassFactory<TaskForceClass>::CreateInstance
template class TClassFactory<TaskForceClass>;

// FUNCTION: GAMEMD 0x006C2810
// TClassFactory<UnitTypeClass>::CreateInstance
template class TClassFactory<UnitTypeClass>;

// FUNCTION: GAMEMD 0x006C2990
// TClassFactory<BuildingTypeClass>::CreateInstance
template class TClassFactory<BuildingTypeClass>;

// FUNCTION: GAMEMD 0x006C2B10
// TClassFactory<AircraftTypeClass>::CreateInstance
template class TClassFactory<AircraftTypeClass>;

// FUNCTION: GAMEMD 0x006C2C90
// TClassFactory<InfantryTypeClass>::CreateInstance
template class TClassFactory<InfantryTypeClass>;

// FUNCTION: GAMEMD 0x006C2E10
// TClassFactory<BulletTypeClass>::CreateInstance
template class TClassFactory<BulletTypeClass>;

// FUNCTION: GAMEMD 0x006C2F90
// TClassFactory<IsometricTileTypeClass>::CreateInstance
template class TClassFactory<IsometricTileTypeClass>;

// FUNCTION: GAMEMD 0x006C3110
// TClassFactory<OverlayTypeClass>::CreateInstance
template class TClassFactory<OverlayTypeClass>;

// FUNCTION: GAMEMD 0x006C3290
// TClassFactory<SmudgeTypeClass>::CreateInstance
template class TClassFactory<SmudgeTypeClass>;

// FUNCTION: GAMEMD 0x006C3410
// TClassFactory<UnitClass>::CreateInstance
template class TClassFactory<UnitClass>;

// FUNCTION: GAMEMD 0x006C3590
// TClassFactory<BuildingClass>::CreateInstance
template class TClassFactory<BuildingClass>;

// FUNCTION: GAMEMD 0x006C3710
// TClassFactory<AircraftClass>::CreateInstance
template class TClassFactory<AircraftClass>;

// FUNCTION: GAMEMD 0x006C3890
// TClassFactory<InfantryClass>::CreateInstance
template class TClassFactory<InfantryClass>;

// FUNCTION: GAMEMD 0x006C3A10
// TClassFactory<AnimClass>::CreateInstance
template class TClassFactory<AnimClass>;

// FUNCTION: GAMEMD 0x006C3B90
// TClassFactory<AnimTypeClass>::CreateInstance
template class TClassFactory<AnimTypeClass>;

// FUNCTION: GAMEMD 0x006C3D10
// TClassFactory<HouseTypeClass>::CreateInstance
template class TClassFactory<HouseTypeClass>;

// FUNCTION: GAMEMD 0x006C3E90
// TClassFactory<HouseClass>::CreateInstance
template class TClassFactory<HouseClass>;

// FUNCTION: GAMEMD 0x006C4010
// TClassFactory<DriveLocomotionClass>::CreateInstance
template class TClassFactory<DriveLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4190
// TClassFactory<JumpjetLocomotionClass>::CreateInstance
template class TClassFactory<JumpjetLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4310
// TClassFactory<HoverLocomotionClass>::CreateInstance
template class TClassFactory<HoverLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4490
// TClassFactory<RocketLocomotionClass>::CreateInstance
template class TClassFactory<RocketLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4610
// TClassFactory<TunnelLocomotionClass>::CreateInstance
template class TClassFactory<TunnelLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4790
// TClassFactory<WalkLocomotionClass>::CreateInstance
template class TClassFactory<WalkLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4910
// TClassFactory<DropPodLocomotionClass>::CreateInstance
template class TClassFactory<DropPodLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4A90
// TClassFactory<FlyLocomotionClass>::CreateInstance
template class TClassFactory<FlyLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4C10
// TClassFactory<TeleportLocomotionClass>::CreateInstance
template class TClassFactory<TeleportLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4D90
// TClassFactory<MechLocomotionClass>::CreateInstance
template class TClassFactory<MechLocomotionClass>;

// FUNCTION: GAMEMD 0x006C4F10
// TClassFactory<ShipLocomotionClass>::CreateInstance
template class TClassFactory<ShipLocomotionClass>;

// FUNCTION: GAMEMD 0x006C5090
// TClassFactory<BulletClass>::CreateInstance
template class TClassFactory<BulletClass>;

// FUNCTION: GAMEMD 0x006C5210
// TClassFactory<FactoryClass>::CreateInstance
template class TClassFactory<FactoryClass>;

// FUNCTION: GAMEMD 0x006C5390
// TClassFactory<WarheadTypeClass>::CreateInstance
template class TClassFactory<WarheadTypeClass>;

// FUNCTION: GAMEMD 0x006C5510
// TClassFactory<WeaponTypeClass>::CreateInstance
template class TClassFactory<WeaponTypeClass>;

// FUNCTION: GAMEMD 0x006C5690
// TClassFactory<ParticleClass>::CreateInstance
template class TClassFactory<ParticleClass>;

// FUNCTION: GAMEMD 0x006C5810
// TClassFactory<ParticleTypeClass>::CreateInstance
template class TClassFactory<ParticleTypeClass>;

// FUNCTION: GAMEMD 0x006C5990
// TClassFactory<ParticleSystemClass>::CreateInstance
template class TClassFactory<ParticleSystemClass>;

// FUNCTION: GAMEMD 0x006C5B10
// TClassFactory<ParticleSystemTypeClass>::CreateInstance
template class TClassFactory<ParticleSystemTypeClass>;

// FUNCTION: GAMEMD 0x006C5C90
// TClassFactory<AITriggerTypeClass>::CreateInstance
template class TClassFactory<AITriggerTypeClass>;

// FUNCTION: GAMEMD 0x006C5E10
// TClassFactory<NeuronClass>::CreateInstance
template class TClassFactory<NeuronClass>;

// FUNCTION: GAMEMD 0x006C5F90
// TClassFactory<FoggedObjectClass>::CreateInstance
template class TClassFactory<FoggedObjectClass>;

// FUNCTION: GAMEMD 0x006C6110
// TClassFactory<AlphaShapeClass>::CreateInstance
template class TClassFactory<AlphaShapeClass>;

