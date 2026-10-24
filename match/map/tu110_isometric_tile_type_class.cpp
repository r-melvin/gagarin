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

struct Obj_00477020 {
    void FUN_00528660(int, int, const char*);
    void FUN_00477020(int a, int b, unsigned int c);
};

struct Obj_004770B0 {
    void FUN_00528660(int, int, const char*);
    void FUN_004770B0(int a, int b, unsigned int c);
};

struct Obj_005175E0 {
    bool FUN_005175D0();
    bool FUN_005175E0();
};

struct Rec_00549B50 {
    int unknown_00;
    int unknown_04;
    int unknown_08;
};
struct Obj_00549B50 {
    Rec_00549B50 FUN_00549B50(const Rec_00549B50& in);
};

struct Obj_006EA4F0 {
    void FUN_006EA500(int, int);
    void FUN_006EA4F0(int a);
};

struct Obj_007719C0 {
    bool FUN_007529E0();
    bool FUN_007719C0();
};

#include <stddef.h>
#include <objbase.h>
#include "../_rt/gg_static_assert.h"

struct Guid_007E36C0 { unsigned int unknown[4]; };
// GLOBAL: GAMEMD 0x7E36C0
extern const Guid_007E36C0 DAT_007E36C0;

// COM error raiser (COMSUPP library, 0x7DC720).
void __stdcall FUN_007DC720(unsigned int hr);

// Slot 0 of the object's own interface table, called on the object with the
// interface id at 0x7E36C0 and the caller's out pointer.
struct Iface_00429400
{
    virtual long __stdcall Slot00(const Guid_007E36C0& iid, void* out);
};

// Write one dword through 0x4A1DE0.
struct Obj_004A1D70 {
    void FUN_004A1DE0(const void* data, int length);
    void FUN_004A1D70(int value);
};

struct Obj_004A31F0 {
    void* unknown_00;
    bool FUN_004A31F0(void* arg);
};
GG_STATIC_ASSERT(offsetof(Obj_004A31F0, unknown_00) == 0x00);

// A four-integer record built from its four arguments.
struct Quad_0054A120 {
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;
    Quad_0054A120(int a, int b, int c, int d);
};
GG_STATIC_ASSERT(sizeof(Quad_0054A120) == 0x10);

// The index of an element pointer within a vector of 36-byte records.
struct Obj_00589A30 {
    unsigned char unknown_00[4];
    unsigned char* unknown_04;
    unsigned char unknown_08[4];
    bool unknown_0C;
    unsigned int FUN_00589A30(const void* item) const;
};
GG_STATIC_ASSERT(offsetof(Obj_00589A30, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_00589A30, unknown_0C) == 0x0C);

// Read one float of an inline array by index.
struct Obj_00645D10 {
    float unknown_00[1];
    float FUN_00645D10(int index) const;
};

struct Obj_0065AD40 {
    unsigned char unknown_00[0xE4];
    int* unknown_E4;
    int FUN_0065AD40(int index);
};
GG_STATIC_ASSERT(offsetof(Obj_0065AD40, unknown_E4) == 0xE4);

// Run a handler over every entry of a global table of objects.
struct Obj_0065FE00 {
    // FUNCTION: GAMEMD 0x65FE00 (decl; reloc)
    void FUN_0065FE00();
};
// GLOBAL: GAMEMD 0xB04DAC
extern Obj_0065FE00** DAT_00B04DAC;
// GLOBAL: GAMEMD 0xB04DB8
extern int DAT_00B04DB8;

// Store the argument in the first dword.
struct Obj_00681080 {
    int unknown_00;
    void FUN_00681080(int value);
};

// The held interface pointer, raising E_POINTER when there is none.
struct Obj_00683030 {
    void* unknown_00;
    void* FUN_00683030();
};
GG_STATIC_ASSERT(offsetof(Obj_00683030, unknown_00) == 0x00);

struct Map_00578AD0 {
    // FUNCTION: GAMEMD 0x578AD0 (decl; reloc)
    int FUN_00578AD0(int cell, int* arg);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the map instance.
extern Map_00578AD0 DAT_0087F7E8;
struct Obj_006A3E30 {
    unsigned char unknown_00[0xC];
    int unknown_0C;
    int FUN_006A3E30(int arg);
};
GG_STATIC_ASSERT(offsetof(Obj_006A3E30, unknown_0C) == 0x0C);

// The multimedia timer in sixteenths of a unit.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// Clear the two dwords after the header.
struct Obj_006C9D20 {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    void FUN_006C9D20();
};
GG_STATIC_ASSERT(offsetof(Obj_006C9D20, unknown_08) == 0x08);

// A value inside the half-open range [low, high).
// GLOBAL: GAMEMD 0x7E1748
extern const float DAT_007E1748;
// GLOBAL: GAMEMD 0x7E2AC8
extern const float DAT_007E2AC8;
struct Obj_0074FFC0 {
    float unknown_00;
    bool FUN_0074FFC0() const;
};

// Three-component equality.
struct Obj_00769510 {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    bool FUN_00769510(const Obj_00769510* other) const;
};
GG_STATIC_ASSERT(offsetof(Obj_00769510, unknown_08) == 0x08);

// The character at an index of a wide string, or zero past its end.
// LIBRARY: GAMEMD 0x7CA405 (decl; reloc) -- wcslen.
unsigned int __cdecl FUN_007CA405(const unsigned short* text);
struct Obj_007B7150 {
    unsigned short* unknown_00;
    unsigned short FUN_007B7150(unsigned int index) const;
};

// Forward a by-value rectangle to the held surface's fill slot (slot 5).
struct Rect_007BCF90 {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0C;
};
struct Surface_007BCF90 {
    virtual void vf_00(); virtual void vf_01(); virtual void vf_02(); virtual void vf_03(); virtual void vf_04();
    virtual bool vf_05(Rect_007BCF90* area, int color);
};
struct Obj_007BCF90 {
    unsigned char unknown_00[0x14];
    Surface_007BCF90* unknown_14;
    bool FUN_007BCF90(unsigned short color, Rect_007BCF90 area);
};
GG_STATIC_ASSERT(offsetof(Obj_007BCF90, unknown_14) == 0x14);

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EC440
extern const double DAT_007EC440;
// GLOBAL: GAMEMD 0xAA1070
extern double DAT_00AA1070;

// SYNTHETIC: GAMEMD 0x543C90
// GLOBAL: GAMEMD 0xABC2C0
double DAT_00ABC2C0 = DAT_00AA1070 / DAT_007EC440;

// SYNTHETIC: GAMEMD 0x543CB0
// GLOBAL: GAMEMD 0xABC1F0
double DAT_00ABC1F0 = DAT_007E1718 / DAT_00ABC2C0;

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
