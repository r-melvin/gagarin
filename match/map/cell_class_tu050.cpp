// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//   CellClass members between 0x47B3A0 and 0x488280 (the inferred cell translation unit).
//
//   Ordered ascending by retail address.

#include "../core/vector_class_operations.h"
#include "../_layout/cell_class.h"
#include "../_layout/light_convert_class.h"
#include "../_layout/pixel_fx_class.h"
#include "../_layout/tag_class.h"
#include "../_layout/fogged_object_class.h"

// GLOBAL: GAMEMD 0x886FA4
extern int DAT_00886FA4;
// FUNCTION: GAMEMD 0x5FDCC0 (decl; reloc) -- overlay type draw offset, written through `out`.
Point2D* __fastcall FUN_005FDCC0(Point2D* out, int typeIndex);

// GLOBAL: GAMEMD 0xAA1020
extern int DAT_00AA1020;
// GLOBAL: GAMEMD 0xAA073C
extern int DAT_00AA073C;
// GLOBAL: GAMEMD 0xABB110
extern int DAT_00ABB110;
// GLOBAL: GAMEMD 0xAA1050
extern int DAT_00AA1050;
// GLOBAL: GAMEMD 0xAA10A0
extern int DAT_00AA10A0;
// GLOBAL: GAMEMD 0xABBEBC
extern int DAT_00ABBEBC;
// GLOBAL: GAMEMD 0xABAD24
extern int DAT_00ABAD24;
// GLOBAL: GAMEMD 0xAA0E28
extern int DAT_00AA0E28;
// GLOBAL: GAMEMD 0xABAD1C
extern int DAT_00ABAD1C;
// GLOBAL: GAMEMD 0xABC2C8
extern int DAT_00ABC2C8;
// GLOBAL: GAMEMD 0xAA101C
extern int DAT_00AA101C;
// GLOBAL: GAMEMD 0x880944
extern DynamicVectorClass<CellStruct> DAT_00880944;
// GLOBAL: GAMEMD 0xA8E9A0
extern unsigned char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0x89E748
extern CellStruct DAT_0089E748;

// FUNCTION: GAMEMD 0x47BB60
CellClass::~CellClass()
{
    if (FoggedObjects != 0) {
        delete FoggedObjects;
        FoggedObjects = 0;
    }
    if (PixelFX != 0) {
        delete PixelFX;
        PixelFX = 0;
    }
    FirstObject = 0;
    if (MapCoords != DAT_0089E748 && LightConvert != 0) {
        if (DAT_00A8E9A0 != 0)
            LightConvert->unknown_194--;
        LightConvert = 0;
    }
}

// FUNCTION: GAMEMD 0x480110
void CellClass::FUN_00480110(Point2D* out)
{
    Point2D offset;
    Point2D pt = *FUN_005FDCC0(&offset, OverlayTypeIndex);
    if (Flags & 0x80) {
        pt.Y -= 0x10;
        if (OverlayData >= 9 && OverlayData <= 0x11)
            pt.Y -= 0xF;
    } else if (OverlayTypeIndex == 0xEF) {
        pt.Y -= 0xF;
    }
    pt.X += 0x1E;
    pt.Y += DAT_00886FA4 - Level * 15;
    pt.Y += 0xF;
    *out = pt;
}

// FUNCTION: GAMEMD 0x485130
void CellClass::FUN_00485130(void* target)
{
    if (AttachedTag == target) {
        if (AttachedTag != 0)
            AttachedTag->InstanceCount--;
        AttachedTag = 0;
        DAT_00880944.RemoveItem(MapCoords);
    }
    if (BridgeOwnerCell == target)
        BridgeOwnerCell = 0;
    if (unknown_30 == target)
        unknown_30 = 0;
    if (FoggedObjects != 0) {
        if (((AbstractClass*)target)->vf_11() == 0x3D) {
            FoggedObjectClass* fogged = (FoggedObjectClass*)target;
            FoggedObjects->RemoveItem(fogged);
        }
    }
}

// FUNCTION: GAMEMD 0x4863D0
bool CellClass::FUN_004863D0()
{
    if (DAT_00AA1020 != -1 && IsoTileTypeIndex >= DAT_00AA1020 && IsoTileTypeIndex < DAT_00AA1020 + 0x28)
        return true;
    if (DAT_00AA073C != -1 && IsoTileTypeIndex >= DAT_00AA073C && IsoTileTypeIndex < DAT_00AA073C + 4) {
        if (IsoTileTypeIndex == DAT_00AA073C || IsoTileTypeIndex == DAT_00AA073C + 3) {
            if (Height == 0 || Height == 4)
                return false;
        }
        return true;
    }
    if (DAT_00ABB110 != -1 && IsoTileTypeIndex >= DAT_00ABB110 && IsoTileTypeIndex < DAT_00ABB110 + 4) {
        if (IsoTileTypeIndex == DAT_00ABB110 || IsoTileTypeIndex == DAT_00ABB110 + 3) {
            if (Height == 1 || Height == 3)
                return false;
        }
        return true;
    }
    if (DAT_00AA1050 != -1 && IsoTileTypeIndex >= DAT_00AA1050 && IsoTileTypeIndex < DAT_00AA1050 + 4) {
        if (IsoTileTypeIndex == DAT_00AA1050 || IsoTileTypeIndex == DAT_00AA1050 + 3) {
            if (Height == 0 || Height == 1)
                return false;
        }
        return true;
    }
    if (DAT_00AA10A0 != -1 && IsoTileTypeIndex >= DAT_00AA10A0 && IsoTileTypeIndex < DAT_00AA10A0 + 4) {
        if (IsoTileTypeIndex == DAT_00AA10A0 || IsoTileTypeIndex == DAT_00AA10A0 + 3) {
            if (Height == 2 || Height == 3)
                return false;
        }
        return true;
    }
    if (DAT_00ABBEBC != -1 && IsoTileTypeIndex >= DAT_00ABBEBC && IsoTileTypeIndex < DAT_00ABBEBC + 0x14)
        return true;
    if (DAT_00ABAD24 != -1 && IsoTileTypeIndex >= DAT_00ABAD24 && IsoTileTypeIndex < DAT_00ABAD24 + 4)
        return true;
    if (DAT_00AA0E28 != -1 && IsoTileTypeIndex >= DAT_00AA0E28 && IsoTileTypeIndex < DAT_00AA0E28 + 0x10)
        return true;
    if (DAT_00ABAD1C != -1 && IsoTileTypeIndex >= DAT_00ABAD1C && IsoTileTypeIndex < DAT_00ABAD1C + 0x10)
        return true;
    if (DAT_00ABC2C8 != -1 && IsoTileTypeIndex >= DAT_00ABC2C8 && IsoTileTypeIndex < DAT_00ABC2C8 + 2)
        return true;
    if (DAT_00AA101C != -1 && IsoTileTypeIndex >= DAT_00AA101C && IsoTileTypeIndex < DAT_00AA101C + 0x1C)
        return true;
    return false;
}
