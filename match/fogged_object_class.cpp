// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   FoggedObjectClass members read off the user's retail gamemd.exe v1.001
//   (vtable 0x7E8B38): default constructor 0x4D08B0, stream writer 0x4D24A0
//   (slot 6), slots 11 and 12, checksum 0x4D2810 (slot 13).

#include "FUNCTION.H"
#include "vector_add_item_free.h"
#include "_layout/index.h"
#include "_layout/cell_class.h"
#include "_layout/map_0087f7e8.h"
#include "_layout/building_class.h"
#include "_layout/anim_class.h"
#include "_layout/tactical.h"
#include "_layout/swizzle_manager_class.h"
#include "sorted_pair_search_family_methods.h"

// GLOBAL: GAMEMD 0x8B3D10 -- every live fogged object (defined with its exit
// stub in core/static_vector_member_dtor_stubs_a.cpp).
extern DynamicVectorClass<FoggedObjectClass*> DAT_008B3D10;

// GLOBAL: GAMEMD 0x8B3CC0 -- the index of fogged objects, keyed by a value built from the cell and unknown_30
// (defined with its exit stub in static_index_member_dtor_stubs.cpp).
extern IndexClass<int, void*> DAT_008B3CC0;
// GLOBAL: GAMEMD 0x887324 -- the tactical object.
extern Tactical* DAT_00887324;
// GLOBAL: GAMEMD 0xB0C110 -- the pointer-swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;

// The coordinate to cell conversion expanded in the destructor: signed divide by 256 per axis, returned by value.
static inline CellStructInit CoordToCell_004D1650(const CoordStruct& c)
{
    CellStructInit r;
    r.X = (short)(c.X / 256);
    r.Y = (short)(c.Y / 256);
    return r;
}

// FUNCTION: GAMEMD 0x4D2ED0 (decl; reloc) -- the node comparator handed to qsort (defined in global_leaf_helper_methods.cpp).
int __cdecl FUN_004D2ED0(const void* a, const void* b);

// The sorted search of this index leaves the binary search out of line (0x4D2F00).
template<>
inline IndexClass<int, void*>::NodeElement* IndexClass<int, void*>::SearchForNode(const int& id)
{
    if (IndexCount == 0) {
        return 0;
    }
    if (!IsSorted) {
        qsort(IndexTable, IndexCount, sizeof(NodeElement), FUN_004D2ED0);
        Archive = 0;
        IsSorted = true;
    }
    NodeElement node;
    node.ID = id;
    // 0x4D2F00 walks eight-byte {key, value} nodes and reads the key at +0: the same layout as NodeElement.
    return (NodeElement*)FUN_004D2F00((SortedEntry_004D2F00*)IndexTable, IndexCount, &node.ID);
}

// The removal shifts whole nodes down.
template<>
inline bool IndexClass<int, void*>::RemoveIndex(const int& id)
{
    NodeElement* node = SearchForNode(id);
    if (node != 0) {
        int found = node - IndexTable;
        if (found != -1) {
            for (int i = found + 1; i < IndexCount; i++) {
                IndexTable[i - 1] = IndexTable[i];
            }
            IndexCount--;
            NodeElement zero;
            zero.ID = 0;
            zero.Data = 0;
            IndexTable[IndexCount] = zero;
            Archive = 0;
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x4D08B0
//
// An empty fogged object: no draw records, no coordinate, and registered in the
// global list of fogged objects.
FoggedObjectClass::FoggedObjectClass()
    : unknown_24(-1), unknown_28(0), unknown_2C(0), unknown_30(0), unknown_50(0), unknown_54(-1), unknown_58(0),
      DrawRecords(0, 0), unknown_74(true)
{
    DynamicVectorAddItemFree(&DAT_008B3D10, this);
}

// FUNCTION: GAMEMD 0x4D1650
//
// Leave the list of fogged objects and the index, clear the fog flags on the building standing on the cell
// (when unknown_30 is 6) and ask the tactical view to repaint the object's rectangle.
FoggedObjectClass::~FoggedObjectClass()
{
    DAT_008B3D10.RemoveItem(this);
    CellStruct cell = CoordToCell_004D1650(Coords);
    int y = cell.Y;
    int x = cell.X;
    int key = (y - x - ((x + y) << 9)) * 74 - unknown_30 + 0x7FFFFFFF;
    DAT_008B3CC0.RemoveIndex(key);
    if (unknown_30 == 6) {
        BuildingClass* building = DAT_0087F7E8.FUN_005657A0(&cell)->GetBuilding();
        if (building != 0) {
            building->IsFogged = 0;
            for (int i = 0; i < 0x15; i++) {
                if (building->Anims[i] != 0) {
                    building->Anims[i]->IsFogged = 0;
                }
            }
        }
    }
    if (DAT_00887324 != 0) {
        RectangleStruct rect = Bounds;
        Pair_006D9F80 off = DAT_00887324->unknown_B0;
        rect.X -= off.unknown_00;
        rect.Y -= off.unknown_04;
        DAT_00887324->FUN_006D2790(rect, false);
    }
}

// FUNCTION: GAMEMD 0x4D24A0
//
// Write the base object, the number of draw records and then each 0x10-byte
// record. A failed record write stops the loop but still reports success, as
// retail does.
HRESULT __stdcall FoggedObjectClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    int count;
    int i;
    if (hr < 0) {
        return hr;
    }
    count = DrawRecords.Count;
    hr = pStm->Write(&count, 4, 0);
    if (hr < 0) {
        return hr;
    }
    for (i = 0; i < count; i++) {
        if (pStm->Write(&DrawRecords.Items[i], sizeof(DrawRecord), 0) < 0) {
            return 0;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4D2510
//
// Load the base object, rebuild it around the loaded bytes, read the draw records (each one swizzled) and
// register the object in the index.
HRESULT __stdcall FoggedObjectClass::Load(IStream* pStm)
{
    HRESULT loaded = AbstractClass::Load(pStm);
    if (loaded < 0) {
        return loaded;
    }
    new (this) FoggedObjectClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_28);
    int count = 0;
    HRESULT hr = pStm->Read(&count, 4, 0);
    if (hr < 0) {
        return hr;
    }
    for (int i = 0; i < count; i++) {
        DrawRecord record;
        hr = pStm->Read(&record, sizeof(DrawRecord), 0);
        if (hr < 0) {
            return hr;
        }
        DrawRecords.AddItem(record);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&DrawRecords.Items[DrawRecords.Count - 1]);
    }
    FoggedShortPair cell = FUN_004D28D0();
    int y = cell.Y;
    int x = cell.X;
    int key = (y - x - ((x + y) << 9)) * 74 - unknown_30 + 0x7FFFFFFF;
    DAT_008B3CC0.AddIndex(key, this);
    return hr;
}

// FUNCTION: GAMEMD 0x4D27B0
// The object's RTTI type code (vtable slot 11).
int FoggedObjectClass::vf_11()
{
    return 0x3D;
}

// FUNCTION: GAMEMD 0x4D27C0
// The object's size in bytes (vtable slot 12).
int FoggedObjectClass::vf_12()
{
    return 0x78;
}

// FUNCTION: GAMEMD 0x4D2810
//
// Feed the base object and every state field to the checksum sink.
void FoggedObjectClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1D50(unknown_24);
    crc->FUN_004A1D50(unknown_2C);
    crc->FUN_004A1D50(unknown_30);
    crc->FUN_004A1D50(Coords.X);
    crc->FUN_004A1D50(Coords.Y);
    crc->FUN_004A1D50(Coords.Z);
    crc->FUN_004A1D50(Bounds.X);
    crc->FUN_004A1D50(Bounds.Y);
    crc->FUN_004A1D50(Bounds.Width);
    crc->FUN_004A1D50(Bounds.Height);
    crc->FUN_004A1D50(unknown_50);
    crc->FUN_004A1D50(unknown_54);
    crc->FUN_004A1D50(unknown_58);
    crc->FUN_004A1D50(DrawRecords.Count);
}

// SYNTHETIC: GAMEMD 0x4D2910 -- FoggedObjectClass scalar deleting destructor, emitted by the compiler from the virtual destructor
