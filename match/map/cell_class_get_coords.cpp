// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Retail CellClass slot 18 contains 0x486840; its override keeps the native
// virtual dispatch used by CellClass::vf_22. Entry bytes establish RET 4.
// Signed word reads at this+24/+26 establish the cell coordinate fields;
// the output stores establish CoordStruct's three dwords and hidden result.
#include "../_layout/cell_class.h"
#include "../_layout/geometry2d.h"

GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass, IsoTileTypeIndex) == 0x38);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->IsoTileTypeIndex) == 4);
GG_STATIC_ASSERT(offsetof(CellStruct, X) == 0x00);
GG_STATIC_ASSERT(offsetof(CellStruct, Y) == 0x02);
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);
GG_STATIC_ASSERT(offsetof(CoordStruct, X) == 0x00);
GG_STATIC_ASSERT(offsetof(CoordStruct, Y) == 0x04);
GG_STATIC_ASSERT(offsetof(CoordStruct, Z) == 0x08);
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0x0C);

GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->FoggedObjects) == 4);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClassLayout*)0)->Items) == 4);
GG_STATIC_ASSERT(sizeof(((DynamicVectorClassLayout*)0)->Count) == 4);
GG_STATIC_ASSERT(sizeof(DynamicVectorClassLayout) == 0x18);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->Flags) == 4);

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
        DynamicVectorClassLayout* vector =
            static_cast<DynamicVectorClassLayout*>(FoggedObjects);
        int count = vector->Count;
        result = pStm->Write(&count, 4, 0);
        if (result < 0) {
            return result;
        }

        for (int i = 0; i < count; ++i) {
            void** items = static_cast<void**>(
                static_cast<DynamicVectorClassLayout*>(FoggedObjects)->Items);
            result = pStm->Write(&items[i], 4, 0);
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
