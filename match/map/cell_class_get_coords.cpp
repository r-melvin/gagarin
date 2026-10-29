// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Retail CellClass slot 18 contains 0x486840; its override keeps the native
// virtual dispatch used by CellClass::vf_22. Entry bytes establish RET 4.
// Signed word reads at this+24/+26 establish the cell coordinate fields;
// the output stores establish CoordStruct's three dwords and hidden result.
#include "../core/vector_class_operations.h"
#include "../_layout/cell_class.h"
#include "../_layout/geometry2d.h"
#include "../map/cell_flag_search_shared.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/stream_persist_methods.h"
#include <new.h>

namespace CellLoadABIAssertions {
GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(FoggedObjectClass*) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->MapCoords) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->IsoTileTypeIndex) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->FoggedObjects) == 4);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<FoggedObjectClass*>) == 0x18);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<FoggedObjectClass*>, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<FoggedObjectClass*>, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<FoggedObjectClass*>, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<FoggedObjectClass*>, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<FoggedObjectClass*>*)0)->Capacity) == 4);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<FoggedObjectClass*>*)0)->IsInitialized) == 1);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<FoggedObjectClass*>*)0)->IsAllocated) == 1);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<FoggedObjectClass*>, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<FoggedObjectClass*>, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<FoggedObjectClass*>*)0)->Items) == 4);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<FoggedObjectClass*>*)0)->Count) == 4);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClass<FoggedObjectClass*>*)0)->CapacityIncrement) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->BridgeOwnerCell) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->unknown_30) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->LightConvert) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->Passability) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->PixelFX) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->OverlayTypeIndex) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->OverlayData) == 1);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->AttachedTag) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->Jumpjet) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->FirstObject) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->AltObject) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->RadSite) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->Rubble) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->MapCoords.X) == 2);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->MapCoords.Y) == 2);
}

// FUNCTION: GAMEMD 0x47B360
CellClass::CellClass(const AbstractNoInit& noInit)
    : AbstractClass(noInit), LightConvert(0), Passability(0)
{
}

// FUNCTION: GAMEMD 0x4839F0
HRESULT __stdcall CellClass::Load(IStream* pStm)
{
    HRESULT result = FUN_00410380(
        reinterpret_cast<Subject_00410320*>(this),
        reinterpret_cast<Stream_00410320*>(pStm));
    if (result < 0) {
        return result;
    }

    new (this) CellClass(AbstractNoInit());

    if (FoggedObjects != 0) {
        FoggedObjects = new DynamicVectorClass<FoggedObjectClass*>(0, 0);

        int count;
        result = pStm->Read(&count, sizeof(count), 0);
        if (result < 0) {
            return result;
        }

        for (int i = 0; i < count; ++i) {
            FoggedObjectClass* object = 0;
            result = pStm->Read(&object, sizeof(object), 0);
            if (result < 0) {
                return 0;
            }
            FoggedObjects->AddItem(object);
        }

        for (int j = 0; j < FoggedObjects->Count; ++j)
            DAT_00B0C110.SwizzleManagerClass::vf_4(&FoggedObjects->Items[j]);
    }

    PixelFX = 0;
    int cellIndex = MapCoords.Y * 512 + MapCoords.X;
    if (DAT_0087F924[cellIndex] != 0) {
        delete DAT_0087F924[cellIndex];
        DAT_0087F924[cellIndex] = 0;
    }
    DAT_0087F924[cellIndex] = this;

    DAT_00B0C110.SwizzleManagerClass::vf_4(&BridgeOwnerCell);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_30);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&AttachedTag);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Jumpjet);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&FirstObject);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&AltObject);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&RadSite);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Rubble);

    if (OverlayTypeIndex == 0xB3 || OverlayTypeIndex == 0xF2) {
        OverlayTypeIndex = -1;
        OverlayData = 0;
    }
    return 0;
}

// CellClass::Save calls the native base-save helper at 0x00410320 (__stdcall).
extern "C" HRESULT __stdcall FUN_00410320(void* subject, void* stream,
                                          int clearDirty);
// GLOBAL: GAMEMD 0x0089E7B4
extern int DAT_0089E7B4;
// GLOBAL: GAMEMD 0x00AA0738
extern int DAT_00AA0738;

// FUNCTION: GAMEMD 0x483C10
HRESULT __stdcall CellClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT result = FUN_00410320(this, pStm, fClearDirty);
    if (result < 0) {
        return result;
    }

    if (FoggedObjects != 0) {
        int count = FoggedObjects->Count;
        result = pStm->Write(&count, 4, 0);
        if (result < 0) {
            return result;
        }

        for (int i = 0; i < count; ++i) {
            result = pStm->Write(&FoggedObjects->Items[i],
                                 sizeof(FoggedObjectClass*), 0);
            if (result < 0) {
                break;
            }
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x4867E0
bool CellClass::IsOnFloor() const
{
    if (IsoTileTypeIndex < DAT_00AA0738 ||
        IsoTileTypeIndex >= DAT_00AA0738 + 0xE) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x486840
CoordStruct CellClass::vf_18()
{
    int x = MapCoords.X * 256 + 128;
    int y = MapCoords.Y * 256 + 128;
    Point2D center(x, y);
    int z = GetFloorHeight(center);
    CoordStruct result = { x, y, z };
    return result;
}

// FUNCTION: GAMEMD 0x486890
CoordStruct CellClass::vf_22()
{
    if ((Flags & 0x100) != 0) {
        int zAdjustment = DAT_0089E7B4;
        CoordStruct result = vf_18();
        result.Z += zAdjustment;
        return result;
    }

    return vf_18();
}

// FUNCTION: GAMEMD 0x487E50
int __stdcall CellClass::vf_rtti_3()
{
    return 0x0B;
}

// FUNCTION: GAMEMD 0x487E80
// VC6 emits this scalar deleting destructor from CellClass's virtual destructor declaration.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87F924
CellClass** DAT_0087F924;
// END defined globals
