// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit TU110 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x543c60-0x54aa2f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail RTTI type descriptors name VectorClass<IsometricTileTypeClass::TileInsertType*> and
// DynamicVectorClass<IsometricTileTypeClass::TileInsertType*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// Retail RTTI type descriptors name VectorClass<unsigned short*> and
// DynamicVectorClass<unsigned short*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// Small forwarding bodies that repeat at two or more retail addresses. Each
// address is compiled and checked on its own; the copies differ in the callee
// or the table. Owners that are not modelled elsewhere are placeholders
// `Obj_<ADDR>` declaring only the callees the body uses, which are named by
// address.
//
// Small stand-alone bodies (field readers, zero-initialisers, interface
// forwarders and the like) found at one address each, in ascending retail
// address order. Owners that no other file models are placeholders
// `Obj_<ADDR>` declaring only the members the body touches, with offset
// asserts; interface objects reached through COM slots use the objbase types.

#include "vector_class_operations.h"
#include "header_init_shapes.h"

#include "iso_tile_type_class_tile_data_methods.h"
#include "ccfile_class.h"
#include "abstract_registry.h"
#include "_layout/obj_004a1d30.h"
#include "vector_class_operations.h"
#include <objidl.h>
#include "_layout/cell_class.h"
#include "_layout/rgb_class.h"
#include "scenario_class.h"
#include "cell_flag_search_shared.h"
#include <stdarg.h>
#include <stdio.h>
#include "_layout/light_convert_class.h"

template class DynamicVectorClass<IsometricTileTypeClass::TileInsertType*>;

GG_STATIC_ASSERT(sizeof(IsometricTileTypeClass::TileInsertType*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<IsometricTileTypeClass::TileInsertType* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<IsometricTileTypeClass::TileInsertType* >) == 0x18);

#include "vector_class_operations.h"

template class DynamicVectorClass<unsigned short*>;

GG_STATIC_ASSERT(sizeof(unsigned short*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<unsigned short* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<unsigned short* >) == 0x18);

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "_rt/gg_static_assert.h"






bool __cdecl FUN_00544FF0();


#include "deleting_dtor_sweep.h"
#include "winsock_interface_class.h"
#include "_layout/pipe.h"
#include "_layout/straw.h"

const char* FUN_0048E030(unsigned int index);
const char* FUN_0048E090(unsigned int index);

#include "_layout/obj_00477020.h"

#include "_layout/obj_004770b0.h"


#include "_layout/rec_00549b50.h"
#include "_layout/obj_00549b50.h"


#include "_layout/obj_007719c0.h"

#include <stddef.h>
#include <objbase.h>
#include "_rt/gg_static_assert.h"

#include "_layout/guid_007e36c0.h"
// GLOBAL: GAMEMD 0x7E36C0
extern const Guid_007E36C0 DAT_007E36C0;

// COM error raiser (COMSUPP library, 0x7DC720).
void __stdcall FUN_007DC720(unsigned int hr);

// Slot 0 of the object's own interface table, called on the object with the
// interface id at 0x7E36C0 and the caller's out pointer.
#include "_layout/iface_00429400.h"

// Write one dword through 0x4A1DE0.
#include "_layout/obj_004a1d70.h"

#include "_layout/obj_004a31f0.h"

// A four-integer record built from its four arguments.
#include "_layout/quad_0054a120.h"

// The index of an element pointer within a vector of 36-byte records.
#include "_layout/obj_00589a30.h"

// Read one float of an inline array by index.
#include "_layout/obj_00645d10.h"


// Run a handler over every entry of a global table of objects.
#include "_layout/obj_0065fe00.h"
// GLOBAL: GAMEMD 0xB04DAC
extern Obj_0065FE00** DAT_00B04DAC;
// GLOBAL: GAMEMD 0xB04DB8
extern int DAT_00B04DB8;

// Store the argument in the first dword.
#include "_layout/obj_00681080.h"

// The held interface pointer, raising E_POINTER when there is none.
#include "_layout/obj_00683030.h"

#include "_layout/obj_006a3e30.h"

// The multimedia timer in sixteenths of a unit.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// Clear the two dwords after the header.
#include "_layout/obj_006c9d20.h"

// A value inside the half-open range [low, high).
// GLOBAL: GAMEMD 0x7E1748
extern const float DAT_007E1748;
// GLOBAL: GAMEMD 0x7E2AC8
extern const float DAT_007E2AC8;
#include "_layout/obj_0074ffc0.h"

// Three-component equality.
#include "_layout/obj_00769510.h"

// The character at an index of a wide string, or zero past its end.
// LIBRARY: GAMEMD 0x7CA405 (decl; reloc) -- wcslen.
unsigned int __cdecl FUN_007CA405(const unsigned short* text);
#include "_layout/obj_007b7150.h"

// Forward a by-value rectangle to the held surface's fill slot (slot 5).
#include "_layout/rect_007bcf90.h"
#include "_layout/surface_007bcf90.h"
#include "_layout/obj_007bcf90.h"
#include "_layout/map_0087f7e8.h"

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EC440
extern const double DAT_007EC440;
// GLOBAL: GAMEMD 0xAA1070
extern double DAT_00AA1070;

// dynamic initializer for DAT_00ABC2C0

// GLOBAL: GAMEMD 0x00ABC2C0
extern double DAT_00ABC2C0;

// dynamic initializer for DAT_00ABC1F0

// GLOBAL: GAMEMD 0x00ABC1F0
extern double DAT_00ABC1F0;

// SYNTHETIC: GAMEMD 0x543F10 -- table build: constructs the 40 four-integer records in place
// GLOBAL: GAMEMD 0xABC2D0
Quad_0054A120 Gbl_00ABC2D0[40] = {
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 30, 30),
    Quad_0054A120(0, 0, 30, 30),
    Quad_0054A120(0, 0, 30, 30),
    Quad_0054A120(1, 0, 30, 30),
    Quad_0054A120(1, 0, 30, 30),
    Quad_0054A120(2, 1, 60, 15),
    Quad_0054A120(3, 1, 60, 15),
    Quad_0054A120(4, 1, 60, 15),
    Quad_0054A120(5, 0, 90, 30),
    Quad_0054A120(6, 0, 60, 15),
    Quad_0054A120(7, 1, 30, 0),
    Quad_0054A120(8, 0, 60, 15),
    Quad_0054A120(9, 0, 60, 15),
    Quad_0054A120(10, 1, 0, -15),
    Quad_0054A120(11, 1, 0, -15),
    Quad_0054A120(12, 0, 60, 15),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0),
    Quad_0054A120(0, 0, 0, 0)
};

// GLOBAL: GAMEMD 0x87F698 -- LightConvertClass registry (defined in static_vector_dtor_stubs.cpp)
extern DynamicVectorClass<LightConvertClass*> DAT_0087F698;

// GLOBAL: GAMEMD 0xA8ED28 -- every IsometricTileTypeClass, in tile order.
extern DynamicVectorClass<IsometricTileTypeClass*> DAT_00A8ED28;

// FUNCTION: GAMEMD 0x544A70
// Destructor: announce the expiry, free the chained tile type and the cell lists, and leave both registries.
IsometricTileTypeClass::~IsometricTileTypeClass()
{
    AnnounceExpiredPointer(1);
    if (unknown_2BC != 0) {
        IsometricTileTypeClass* next = unknown_2BC;
        unknown_2BC = 0;
        delete next;
    }
    DAT_00A8ED28.RemoveItem(this);
    reinterpret_cast<DynamicVectorClass<AbstractClass*>*>(&DAT_00B0F670)->RemoveItem(this);
    for (int i = unknown_vec_2A4.Count - 1; i >= 0; --i) {
        if (unknown_vec_2A4.Items[i] != 0)
            delete unknown_vec_2A4.Items[i];
        unknown_vec_2A4.Delete(i);
    }
}

// FUNCTION: GAMEMD 0x544CB0  (__thiscall, vtable slot 39)
// The loaded tile-set header, loading it on first use. Retail reads the member
// once up front and again only inside the loading arm, so the source keeps the
// first read in a local and refreshes it after the load rather than re-reading
// the member on the way out.
void* IsometricTileTypeClass::vf_39()
{
    void* data = this->Image;

    if (data == 0 && this->TileDataLoadable) {
        this->LoadTileData();
        data = this->Image;
    }
    return data;
}


// An element of the function-local cell list below (retail registers its exit-time destructor, 0x544DF0, which is empty).
struct IsoListCell_00AA0E3C
{
    CellStruct Value;
    ~IsoListCell_00AA0E3C() {}
};

// FUNCTION: GAMEMD 0x544D30
// SYNTHETIC: GAMEMD 0x544DF0 -- exit-time destructor stub of the function-local list below (`push 0x544DF0` @0x544D45)
// The cell (column, row) of every present sub-tile of the tile set, followed by the 0x7FFF marker; the list is a
// function-local static.
CellStruct* IsometricTileTypeClass::FUN_00544D30(int)
{
    // Placeholder size: retail gives no count. 120 cells is the most that fits, the list at 0xAA0E3C runs into the
    // next object, DAT_00AA101C (written at 0x545B2F).
    static IsoListCell_00AA0E3C List[120];
    TileImageHeader* data = GetTileData();
    SubTileImage** tile = data->SubTiles;
    IsoListCell_00AA0E3C* out = List;
    for (int i = 0; i < unknown_2E4 * unknown_2E8; ++i) {
        if (*tile++ != 0) {
            CellStruct cell;
            cell.X = i % unknown_2E4;
            cell.Y = i / unknown_2E4;
            (out++)->Value = cell;
        }
    }
    CellStruct end;
    end.X = 0x7FFF;
    end.Y = 0x7FFF;
    out->Value = end;
    return &List[0].Value;
}

// GLOBAL: GAMEMD 0x885780 -- the second palette (defined in colour_table_statics.cpp)
extern RGBClass DAT_00885780[256];
// GLOBAL: GAMEMD 0xABBED0 -- the first palette (defined in header_init_543c40.cpp)
extern HeaderByte3 DAT_00ABBED0[256];
// GLOBAL: GAMEMD 0x887308 -- the display surface
extern Surface* DAT_00887308;

// FUNCTION: GAMEMD 0x544E70
// The shared light converter for a colour tint: the neutral one for an untouched tint, else a match among the
// existing ones, else a new one registered at the end of the list.
LightConvertClass* __fastcall FUN_00544E70(int red, int green, int blue)
{
    if (DAT_00887308 == 0)
        return 0;
    if (red == 1000 && green == 1000 && blue == 1000 && DAT_0087F698.Count != 0)
        return DAT_0087F698.Items[0];
    ScenarioClass::ScenarioLighting(&red, &green, &blue);
    for (int i = 1; i < DAT_0087F698.Count; ++i) {
        LightConvertClass* existing = DAT_0087F698.Items[i];
        if (existing->unknown_198 == red && existing->unknown_19C == green && existing->unknown_1A0 == blue)
            return existing;
    }
    int level = 0x35;
    if (red + green + blue < 2000)
        level = 0x1B;
    LightConvertClass* created = new LightConvertClass(DAT_00ABBED0, DAT_00885780, DAT_00887308, red, green, blue,
                                                       DAT_0087F698.GetCount() != 0, false, level);
    DAT_0087F698.AddItem(created);
    return created;
}

// FUNCTION: GAMEMD 0x545000
// Rebuilds the light converter list from scratch (just the neutral one), resets the invalid cell's light and clears
// every cell's converter.
void FUN_00545000()
{
    while (DAT_0087F698.GetCount() > 0) {
        if (DAT_0087F698.Items[0] != 0)
            delete DAT_0087F698.Items[0];
        DAT_0087F698.Delete(0);
    }
    LightConvertClass* neutral = new LightConvertClass(DAT_00ABBED0, DAT_00885780, DAT_00887308, 1000, 1000, 1000,
                                                       false, false, 0x35);
    DAT_0087F698.AddItem(neutral);
    DAT_00ABDC50.LightConvert = 0;
    DAT_00ABDC50.FUN_00483E30(0, 0x10000, 0, 1000, 1000, 1000);
    DAT_0087F7E8.FUN_00578350();
    CellClass* cell = DAT_0087F7E8.FUN_00578290();
    while (cell != 0) {
        cell->LightConvert = 0;
        cell = DAT_0087F7E8.FUN_00578290();
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x544FF0
// Returns a constant boolean.
bool __cdecl FUN_00544FF0()
{
    return false;
}

// FUNCTION: GAMEMD 0x547020
// Reads the tile set file named at +0x2F5 into a fresh block, rebasing the sub-tile pointers.
int IsometricTileTypeClass::LoadTileData()
{
    CCFileClass file(unknown_2F5);
    int size = file.GetFileSize();
    if (Image != 0)
        delete Image;
    Image = new char[size];
    file.ReadBytes(Image, size);
    ImageAllocated = true;
    TileImageHeader* data = static_cast<TileImageHeader*>(Image);
    unknown_2E4 = (unsigned char)data->Width;
    unknown_2E8 = (unsigned char)data->Height;
    for (int i = 0; i < unknown_2E4 * unknown_2E8; ++i) {
        if (data->SubTiles[i] != 0 && (unsigned int)data->SubTiles[i] < (unsigned int)Image)
            data->SubTiles[i] = (SubTileImage*)((unsigned int)data->SubTiles[i] + (unsigned int)Image);
    }
    FUN_00549E90();
    return size;
}

// FUNCTION: GAMEMD 0x5471B0  (__thiscall)
// Convention read off the binary, not assumed: the argument arrives as
// `MOV EAX,[ESP+0x8]` and the exit is `RET 4`, which is a stack-passed
// argument and a callee-cleaned frame — a plain __thiscall member. Spelled
// __fastcall (the argument in EDX) the body scores 4.3%.
// The morph/slope byte of one sub-tile. The index wraps on the sub-tile count,
// which is the header's two dimensions multiplied.
//
// The exit is `MOVSX EAX, byte ptr [ECX+0x2a]`, so the stored byte is signed
// and the return is int.
int IsometricTileTypeClass::GetMorphType(int idx)
{
    TileImageHeader* data = GetTileData();

    if (data != 0) {
        SubTileImage* tile = data->SubTiles[idx % (data->Height * data->Width)];
        if (tile != 0) {
            return tile->MorphType;
        }
    }
    return 0;
}


// FUNCTION: GAMEMD 0x5471F0  (__thiscall)
// Bit 2 of the sub-tile's flag word: the connect/ramp flag the LAT draw uses to
// pick a transition variant.
//
// The out-of-range fall-back is not `return subtile / cellCount;`: both
// failure paths in the binary jump to 0x00547221, which is `XOR AL,AL; RET 4`.
// A quotient there would be a Ghidra artefact — EAX happens to hold the IDIV quotient at that label, so the
// decompiler attributed it as the returned value. The zeroing of AL alone (not
// EAX) is also what fixes the return width here as bool, against the int of
// its sibling at 0x5471B0.
bool IsometricTileTypeClass::GetConnectFlag(int idx)
{
    TileImageHeader* data = GetTileData();

    if (data != 0) {
        SubTileImage* tile = data->SubTiles[idx % (data->Height * data->Width)];
        if (tile != 0) {
            return tile->ConnectFlag;
        }
    }
    return false;
}

// GLOBAL: GAMEMD 0xAA105C -- the empty cell, defined in match/header_init_543c40.cpp
extern const HeaderCellInit DAT_00AA105C;
// GLOBAL: GAMEMD 0xAA102C -- five tile-set ids
extern int DAT_00AA102C[5];

// A cell of the function-local table: copied from a cell value, with an (empty) destructor.
struct IsoCell_00ABAD34
{
    CellStruct Value;
    IsoCell_00ABAD34(const CellStruct& c) { Value = c; }
    ~IsoCell_00ABAD34() {}
};

// FUNCTION: GAMEMD 0x547370
// SYNTHETIC: GAMEMD 0x547CE0 -- exit-time destructor stub of the function-local table below
// Returns the row of five "no cell"-terminated cell lists (the 6th cell of each row is the 0x7FFF marker)
// selected by this tile's set index, relative to whichever of five tile-set ids it falls within; null if none
// applies or the flag at +0x2E1 is clear. The table is built on first use.
CellStruct* IsometricTileTypeClass::FUN_00547370()
{
    if (!unknown_2E1)
        return 0;
    static IsoCell_00ABAD34 Table[40][6] = {
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { HeaderCellInit(0, -1), HeaderCellInit(0, -1), HeaderCellInit(-1, -2), DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { HeaderCellInit(0, -1), HeaderCellInit(0, -1), HeaderCellInit(-1, -2), DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { HeaderCellInit(-1, -3), HeaderCellInit(0, -3), DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { HeaderCellInit(-1, -3), HeaderCellInit(0, -3), DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { HeaderCellInit(-1, -3), HeaderCellInit(0, -3), DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { HeaderCellInit(0, -3), DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { HeaderCellInit(0, -3), HeaderCellInit(1, -3), HeaderCellInit(-1, -3), HeaderCellInit(-2, -3), DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { HeaderCellInit(0, -3), HeaderCellInit(-1, -3), HeaderCellInit(-2, -3), HeaderCellInit(-3, -2), DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { HeaderCellInit(0, -3), HeaderCellInit(-1, -3), HeaderCellInit(-2, -3), DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { HeaderCellInit(0, -3), HeaderCellInit(-1, -3), HeaderCellInit(-2, -3), DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { HeaderCellInit(-2, -3), DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { HeaderCellInit(-2, -3), DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { HeaderCellInit(0, -3), DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) },
    { DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, DAT_00AA105C, HeaderCellInit(0x7FFF, 0x7FFF) }
    };
    for (int i = 0; i < 5; ++i)
    {
        int d = unknown_294 - DAT_00AA102C[i];
        if (d >= 0 && d < 40)
            return &Table[d][0].Value;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00549B50
Rec_00549B50 Obj_00549B50::FUN_00549B50(const Rec_00549B50& in)
{
    return in;
}

// FUNCTION: GAMEMD 0x549B70
// Feeds the identity fields to the checksum sink.
void IsometricTileTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(unknown_294);
    crc->FUN_004A1D50(unknown_298);
    crc->FUN_004A1D50(unknown_29C);
    crc->FUN_004A1D50(unknown_2A0);
    crc->FUN_004A1D50(unknown_vec_2A4.Count);
    if (unknown_2BC != 0)
        crc->FUN_004A1D50(static_cast<IRTTITypeInfo*>(unknown_2BC)->vf_rtti_4());
    crc->FUN_004A1D50(unknown_2C0);
    crc->FUN_004A1D50(unknown_2C4);
    crc->FUN_004A1D50(unknown_2D4);
    crc->FUN_004A1D50(unknown_2D8);
    crc->FUN_004A1D50(unknown_2DC);
    crc->FUN_004A1CA0(unknown_2E0);
    crc->FUN_004A1CA0(unknown_2E1);
    crc->FUN_004A1D50(unknown_2E4);
    crc->FUN_004A1D50(unknown_2E8);
    crc->FUN_004A1D50(unknown_2EC);
    crc->FUN_004A1D50(unknown_2F0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0054A120
Quad_0054A120::Quad_0054A120(int a, int b, int c, int d)
{
    unknown_0 = a;
    unknown_4 = b;
    unknown_8 = c;
    unknown_C = d;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x54A140
// Returns a constant. Vtable slot 11 of IsometricTileTypeClass (RTTI).
int IsometricTileTypeClass::vf_11()
{
    return 0x12;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x54A150
// Returns a constant. Vtable slot 12 of IsometricTileTypeClass (RTTI).
int IsometricTileTypeClass::vf_12()
{
    return 0x30C;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x54A160
// Member getter (dword). Vtable slot 16 of IsometricTileTypeClass (RTTI).
int IsometricTileTypeClass::vf_16()
{
    return unknown_294;
}

// SYNTHETIC: GAMEMD 0x54A170 -- compiler-generated scalar deleting destructor of ~IsometricTileTypeClass (slot 8; calls 0x544A70).

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x54A1C0
// DynamicVectorClass<unsigned short*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x54A1E0
// VectorClass<unsigned short*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x54A250
// VectorClass<unsigned short*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x54A290
// VectorClass<unsigned short*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x54A370
// VectorClass<unsigned short*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x54A3B0
// VectorClass<unsigned short*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x54A3D0
// DynamicVectorClass<unsigned short*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x54A480
// DynamicVectorClass<unsigned short*>::FindItemIndex (slot 4)
template class VectorClass<unsigned short*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x54A220
// DynamicVectorClass<IsometricTileTypeClass::TileInsertType*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x54A240
// VectorClass<IsometricTileTypeClass::TileInsertType*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x54A4B0
// VectorClass<IsometricTileTypeClass::TileInsertType*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x54A4F0
// VectorClass<IsometricTileTypeClass::TileInsertType*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x54A5D0
// VectorClass<IsometricTileTypeClass::TileInsertType*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x54A610
// VectorClass<IsometricTileTypeClass::TileInsertType*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x54A630
// DynamicVectorClass<IsometricTileTypeClass::TileInsertType*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x54A6E0
// DynamicVectorClass<IsometricTileTypeClass::TileInsertType*>::FindItemIndex (slot 4)
template class VectorClass<IsometricTileTypeClass::TileInsertType*>;

#include "message_log_005bd0d0.h"

// FUNCTION: GAMEMD 0x006BEC60 (decl; reloc)
void FUN_006BEC60();
// FUNCTION: GAMEMD 0x006BEC50 (decl; reloc)
void FUN_006BEC50(int);
// FUNCTION: GAMEMD 0x005BC450 (decl; reloc) -- the object at a slot of the table at 0xABF168.
int FUN_005BC450(int index);
// FUNCTION: GAMEMD 0x54A8C0
// Writes the formatted text to the error stream, then logs the format text through message log 4.
void __cdecl FUN_0054A8C0(const char* format, ...)
{
    FUN_006BEC60();
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    ((MessageLog_005BD0D0*)FUN_005BC450(4))->Printf(format);
    FUN_006BEC50(1);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xAA102C
int DAT_00AA102C[5];
// END defined globals
