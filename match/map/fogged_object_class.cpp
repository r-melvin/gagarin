// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   FoggedObjectClass members read off the user's retail gamemd.exe v1.001
//   (vtable 0x7E8B38): default constructor 0x4D08B0, stream writer 0x4D24A0
//   (slot 6), slots 11 and 12, checksum 0x4D2810 (slot 13).

#include "../_layout/fogged_object_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../core/vector_class_operations.h"
#include "../core/vector_add_item_free.h"

// GLOBAL: GAMEMD 0x8B3D10 -- every live fogged object (defined with its exit
// stub in core/static_vector_member_dtor_stubs_a.cpp).
extern DynamicVectorClass<FoggedObjectClass*> DAT_008B3D10;

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
