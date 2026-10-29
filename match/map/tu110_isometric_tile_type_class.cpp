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

#include "../core/vector_class_operations.h"

#include "iso_tile_type_class_tile_data_methods.h"

template class DynamicVectorClass<IsometricTileTypeClass::TileInsertType*>;

GG_STATIC_ASSERT(sizeof(IsometricTileTypeClass::TileInsertType*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<IsometricTileTypeClass::TileInsertType* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<IsometricTileTypeClass::TileInsertType* >) == 0x18);

#include "../core/vector_class_operations.h"

template class DynamicVectorClass<unsigned short*>;

GG_STATIC_ASSERT(sizeof(unsigned short*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<unsigned short* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<unsigned short* >) == 0x18);

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0054A140;
struct Obj_0054A150;
struct Obj_0054A160;

struct Obj_0054A140
{
    // FUNCTION: GAMEMD 0x54A140
    int FUN_0054A140() const;
};

struct Obj_0054A150
{
    // FUNCTION: GAMEMD 0x54A150
    int FUN_0054A150() const;
};

struct Obj_0054A160
{
    char unknown_00[0x294];
    int unknown_294;   // +0x0294
    // FUNCTION: GAMEMD 0x54A160
    int FUN_0054A160() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0054A160, unknown_294) == 0x294);


void __cdecl FUN_00544DF0();
bool __cdecl FUN_00544FF0();
void __cdecl FUN_00547CE0();


#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

const char* FUN_0048E030(unsigned int index);
const char* FUN_0048E090(unsigned int index);

#include "../_layout/obj_00477020.h"

#include "../_layout/obj_004770b0.h"

#include "../_layout/obj_005175e0.h"

#include "../_layout/rec_00549b50.h"
#include "../_layout/obj_00549b50.h"

#include "../_layout/obj_006ea4f0.h"

#include "../_layout/obj_007719c0.h"

#include <stddef.h>
#include <objbase.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/guid_007e36c0.h"
// GLOBAL: GAMEMD 0x7E36C0
extern const Guid_007E36C0 DAT_007E36C0;

// COM error raiser (COMSUPP library, 0x7DC720).
void __stdcall FUN_007DC720(unsigned int hr);

// Slot 0 of the object's own interface table, called on the object with the
// interface id at 0x7E36C0 and the caller's out pointer.
#include "../_layout/iface_00429400.h"

// Write one dword through 0x4A1DE0.
#include "../_layout/obj_004a1d70.h"

#include "../_layout/obj_004a31f0.h"

// A four-integer record built from its four arguments.
#include "../_layout/quad_0054a120.h"

// The index of an element pointer within a vector of 36-byte records.
#include "../_layout/obj_00589a30.h"

// Read one float of an inline array by index.
#include "../_layout/obj_00645d10.h"


// Run a handler over every entry of a global table of objects.
#include "../_layout/obj_0065fe00.h"
// GLOBAL: GAMEMD 0xB04DAC
extern Obj_0065FE00** DAT_00B04DAC;
// GLOBAL: GAMEMD 0xB04DB8
extern int DAT_00B04DB8;

// Store the argument in the first dword.
#include "../_layout/obj_00681080.h"

// The held interface pointer, raising E_POINTER when there is none.
#include "../_layout/obj_00683030.h"

#include "../_layout/obj_006a3e30.h"

// The multimedia timer in sixteenths of a unit.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// Clear the two dwords after the header.
#include "../_layout/obj_006c9d20.h"

// A value inside the half-open range [low, high).
// GLOBAL: GAMEMD 0x7E1748
extern const float DAT_007E1748;
// GLOBAL: GAMEMD 0x7E2AC8
extern const float DAT_007E2AC8;
#include "../_layout/obj_0074ffc0.h"

// Three-component equality.
#include "../_layout/obj_00769510.h"

// The character at an index of a wide string, or zero past its end.
// LIBRARY: GAMEMD 0x7CA405 (decl; reloc) -- wcslen.
unsigned int __cdecl FUN_007CA405(const unsigned short* text);
#include "../_layout/obj_007b7150.h"

// Forward a by-value rectangle to the held surface's fill slot (slot 5).
#include "../_layout/rect_007bcf90.h"
#include "../_layout/surface_007bcf90.h"
#include "../_layout/obj_007bcf90.h"
#include "../_layout/map_0087f7e8.h"

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

// FUNCTION: GAMEMD 0x544CB0  (__thiscall)
// The loaded tile-set header, loading it on first use. Retail reads the member
// once up front and again only inside the loading arm, so the source keeps the
// first read in a local and refreshes it after the load rather than re-reading
// the member on the way out.
TileImageHeader* IsometricTileTypeClass::GetTileData()
{
    TileImageHeader* data = this->unknown_A4;

    if (data == 0 && this->TileDataLoadable) {
        this->LoadTileData();
        data = this->unknown_A4;
    }
    return data;
}


// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x544DF0
// Empty function.
void __cdecl FUN_00544DF0()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x544FF0
// Returns a constant boolean.
bool __cdecl FUN_00544FF0()
{
    return false;
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
    TileImageHeader* data = (this->*this->Vfptr->At_9C)();

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
    TileImageHeader* data = (this->*this->Vfptr->At_9C)();

    if (data != 0) {
        SubTileImage* tile = data->SubTiles[idx % (data->Height * data->Width)];
        if (tile != 0) {
            return tile->ConnectFlag;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x547CE0
// Empty function.
void __cdecl FUN_00547CE0()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00549B50
Rec_00549B50 Obj_00549B50::FUN_00549B50(const Rec_00549B50& in)
{
    return in;
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
int Obj_0054A140::FUN_0054A140() const
{
    return 0x12;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x54A150
// Returns a constant. Vtable slot 12 of IsometricTileTypeClass (RTTI).
int Obj_0054A150::FUN_0054A150() const
{
    return 0x30C;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x54A160
// Member getter (dword). Vtable slot 16 of IsometricTileTypeClass (RTTI).
int Obj_0054A160::FUN_0054A160() const
{
    return unknown_294;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x54A170
void* Obj_54A170::FUN_54A170(unsigned int flags)
{
    FUN_00544A70(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

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
