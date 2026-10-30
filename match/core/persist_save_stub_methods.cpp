// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// IPersistStream::Save overrides that only chain to a base class. Each body
// pushes its three stack arguments again and calls the base Save; the
// 29-byte form then folds every success code to S_OK (`TEST EAX,EAX; JL;
// XOR EAX,EAX`), the 23-byte form returns the base result as is.
//
// The owning class of each body is the class whose vtable slot 6 holds it in
// the retail RTTI tables; the base is the class that owns the called body
// (AbstractClass::Save 0x410320, ObjectTypeClass::Save 0x5F9950 (below),
// TechnoTypeClass::Save 0x716DC0, FootClass::Save 0x4DB690). The classes are
// declared here only as views carrying Save: intermediate bases that do not
// override it are elided, and no member is touched, so there is no layout.
// The classes with a canonical header (AbstractClass, ObjectTypeClass,
// TechnoTypeClass, FootClass and the family C classes) come from it.

#include <objidl.h>
#include "../_layout/anim_type_class.h"
#include "../_layout/airstrike_class.h"
#include "../_layout/neuron_class.h"
#include "../_layout/disk_laser_class.h"
#include "../_layout/super_class.h"
#include "../_layout/super_weapon_type_class.h"
#include "../_layout/light_source_class.h"
#include "../_layout/rad_site_class.h"
#include "../_layout/tag_class.h"
#include "../_layout/trigger_type_class.h"
#include "../_layout/tube_class.h"
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
#include "../_layout/object_type_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/foot_class.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/aircraft_type_class.h"
#include "../_layout/empulse_class.h"
#include "../_layout/infantry_class.h"
#include "../_layout/light_source_class.h"
#include "../_layout/rad_site_class.h"
#include "../_layout/tactical.h"
#include "../_layout/tag_class.h"
#include "../_layout/trigger_type_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/voxel_anim_class.h"
#include "../map/terrain_objects/isometric_tile_class.h"





class IsometricTileTypeView_00549D70 : public ObjectTypeClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};

class ParasiteClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
};



// FUNCTION: GAMEMD 0x41B5C0
HRESULT __stdcall AircraftClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return FootClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x41CE90
HRESULT __stdcall AircraftTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = TechnoTypeClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x41D780
HRESULT __stdcall AirstrikeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x428970
HRESULT __stdcall AnimTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = ObjectTypeClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x43A5B0
HRESULT __stdcall NeuronClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x46AFB0
HRESULT __stdcall BulletClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x4A7C10
HRESULT __stdcall DiskLaserClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x4C5A80
HRESULT __stdcall EMPulseClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x521B00
HRESULT __stdcall InfantryClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return FootClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x5439F0
HRESULT __stdcall IsometricTileClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = MapObjClassView::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x549D70
HRESULT __stdcall IsometricTileTypeView_00549D70::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = ObjectTypeClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x555110
HRESULT __stdcall LightSourceClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6296B0
HRESULT __stdcall ParasiteClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x65B450
HRESULT __stdcall RadSiteClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x691690
HRESULT __stdcall ScriptClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x691DE0
HRESULT __stdcall ScriptTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6CDFD0
HRESULT __stdcall SuperClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6CE8D0
HRESULT __stdcall SuperWeaponTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6DBE00
HRESULT __stdcall Tactical::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6E3E30
HRESULT __stdcall TActionClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6E57A0
HRESULT __stdcall TagClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6E6470
HRESULT __stdcall TagTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6E8680
HRESULT __stdcall TaskForceClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6EC540
HRESULT __stdcall TeamClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x6F1B90
HRESULT __stdcall TeamTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x71F930
HRESULT __stdcall TEventClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x7268D0
HRESULT __stdcall TriggerClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x727C80
HRESULT __stdcall TriggerTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x7281E0
HRESULT __stdcall TubeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x7480B0
HRESULT __stdcall UnitTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = TechnoTypeClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x74AA10
HRESULT __stdcall VoxelAnimClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x74B8D0
HRESULT __stdcall VoxelAnimTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = ObjectTypeClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}
