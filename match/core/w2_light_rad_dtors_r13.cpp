// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x554910 / 0x555150 (LightSourceClass destructor and its scalar
//   deleting entry) and 0x65B2F0 (RadSiteClass destructor); each announces the expired pointer,
//   leaves its class-wide array and runs the AbstractClass destructor.
//   Address index: 0x554910 ~LightSourceClass, 0x555150 LightSourceClass scalar deleting
//   destructor, 0x65B2F0 ~RadSiteClass.
//   LightSourceClass and CellClass come from match/_layout; MapClass is a local view.

#include "../_layout/abstract_class.h"
#include "../_layout/rad_site_class.h"
#include "../_layout/light_source_class.h"
#include "vector_class_operations.h"
#include <new.h>
#include "../_layout/swizzle_manager_class.h"


// GLOBAL: GAMEMD 0xABCA00 -- the default light tint.
extern LightTint DAT_00ABCA00;

GG_STATIC_ASSERT(offsetof(LightSourceClass, Tint) == 0x38);
GG_STATIC_ASSERT(offsetof(LightSourceClass, Activated) == 0x48);

// GLOBAL: GAMEMD 0xABCA10 -- the light source registry.
extern DynamicVectorClass<LightSourceClass*> DAT_00ABCA10;

struct CellStruct;
#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"


// GLOBAL: GAMEMD 0xB04BD0 -- the radiation site registry.
extern DynamicVectorClass<RadSiteClass*> DAT_00B04BD0;

// FUNCTION: GAMEMD 0x554910
// SYNTHETIC: GAMEMD 0x555150 -- the scalar deleting destructor (??_G) emitted from this destructor
LightSourceClass::~LightSourceClass()
{
    AnnounceExpiredPointer(1);
    DAT_00ABCA10.RemoveItem(this);
    if (Activated) {
        Activated = 0;
        Calculate(0);
    }
}

// FUNCTION: GAMEMD 0x65B2F0
RadSiteClass::~RadSiteClass()
{
    CellClass* cell = DAT_0087F7E8.FUN_005657A0((const CellStruct*)&BaseCell);
    cell->FUN_00487C70(0);
    AnnounceExpiredPointer(1);
    if (LightSource) {
        delete (LightSourceClass*)LightSource;
        LightSource = 0;
    }
    DAT_00B04BD0.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x554830
// Default constructor: clears the state, takes the default tint and registers the light source.
LightSourceClass::LightSourceClass()
    : unknown_24(0), TintRed(0), TintGreen(0), TintBlue(0), Tint(DAT_00ABCA00), unknown_44(0), Activated(0)
{
    DynamicVectorClass<LightSourceClass*>& v = DAT_00ABCA10;
    if (v.Count >= v.Capacity) {
        if ((v.IsAllocated || v.Capacity == 0) && v.CapacityIncrement > 0) {
            if (!v.SetCapacity(v.CapacityIncrement + v.Capacity, 0))
                return;
        } else {
            return;
        }
    }
    int index = v.Count++;
    v.Items[index] = this;
}

// FUNCTION: GAMEMD 0x554760
// Constructor from a tint and the light parameters; registers the light source.
LightSourceClass::LightSourceClass(LightTint tint, int a4, int a5, int a6, int a7, int a8)
    : unknown_24(a5), TintRed(a6), TintGreen(a7), TintBlue(a8), unknown_34(2), Tint(tint), unknown_44(a4), Activated(0)
{
    DynamicVectorClass<LightSourceClass*>& v = DAT_00ABCA10;
    if (v.Count >= v.Capacity) {
        if ((v.IsAllocated || v.Capacity == 0) && v.CapacityIncrement > 0) {
            if (!v.SetCapacity(v.CapacityIncrement + v.Capacity, 0))
                return;
        } else {
            return;
        }
    }
    int index = v.Count++;
    v.Items[index] = this;
}

// FUNCTION: GAMEMD 0x5548E0
// No-init constructor: base no-init constructor and the four vtable pointers.
LightSourceClass::LightSourceClass(const AbstractNoInit& noInit) : AbstractClass(noInit)
{
}

// FUNCTION: GAMEMD 0x65B2A0
// No-init constructor: base no-init constructor, both timers restarted, the vtable pointers.
RadSiteClass::RadSiteClass(const AbstractNoInit& noInit) : AbstractClass(noInit), RadLevelTimer(0), RadLightTimer(0)
{
}

// FUNCTION: GAMEMD 0x65B3D0
// Loads the base state, rebuilds the object in place and queues the light source pointer for swizzling.
HRESULT __stdcall RadSiteClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr >= 0) {
        new (this) RadSiteClass(AbstractNoInit());
        DAT_00B0C110.SwizzleManagerClass::vf_4(&LightSource);
    }
    return hr;
}

// SYNTHETIC: GAMEMD 0x65BED0 -- RadSiteClass scalar deleting destructor, emitted by the compiler from the virtual destructor

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xABCA00
LightTint DAT_00ABCA00;
// END defined globals
