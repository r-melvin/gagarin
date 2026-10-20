// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x55A7D0: `this` arrives on the stack (`MOV EBX,[ESP+0x7C]`,
//   the __stdcall COM convention) with the hidden Matrix3D return pointer
//   behind it (`[ESP+0x8C]`) and the key pointer third (`[ESP+0x90]`, RET
//   0xC); `MOV EAX,[EBX+0x8]` is the linked object, whose Location is the
//   three dwords at +0x9C/+0xA0/+0xA4 copied to a local and handed to
//   0x565730 with ECX = 0x87F7E8 (the map singleton); the returned cell's
//   slope byte is `MOV DL,[EAX+0x11C]`; 0x7559B0 is __fastcall with the hidden
//   Matrix3D pointer in ECX and the slope in EDX (it copies one 0x30-byte row
//   of the ramp table at 0xB45188); `ADD ECX,0x388` is PrimaryFacing whose
//   Current() @0x4C93D0 hands back a DirStruct through a hidden pointer. The
//   matrix is the 3x4 float layout proven in match/movement/matrix3d_methods.h
//   (RotateZ @0x5AF1A0). Names from YRpp LocomotionClass.h / CellClass.h /
//   Facing.h (consult-only); 0x7559B0 is unnamed in YRpp.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_SHADOW_MATRIX_METHODS_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_SHADOW_MATRIX_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A binary-angle direction. The user-declared constructor is what makes VC6
// return it through a hidden pointer (a POD of this size would come back in
// EAX); retail reads the whole dword off that pointer.
struct Dir_0055A7D0
{
    unsigned int Raw;   // +0x00
    Dir_0055A7D0() {}
};
GG_STATIC_ASSERT(sizeof(Dir_0055A7D0) == 4);

// FacingClass (0x18) — opaque here; only Current() is called.
struct Facing_0055A7D0
{
    char opaque[0x18];

    // FUNCTION: GAMEMD 0x4C93D0 (decl; reloc) — FacingClass::Current.
    Dir_0055A7D0 Current();
};
GG_STATIC_ASSERT(sizeof(Facing_0055A7D0) == 0x18);

// A world coordinate: three ints.
struct Coord_0055A7D0
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(Coord_0055A7D0) == 0xC);

// The linked TechnoClass — Location @0x9C and PrimaryFacing @0x388.
struct Linked_0055A7D0
{
    char            _pad000[0x9C];             // +0x0000
    Coord_0055A7D0  Location;                  // +0x009C
    char            _pad0A8[0x388 - 0xA8];     // +0x00A8
    Facing_0055A7D0 PrimaryFacing;             // +0x0388
};
GG_STATIC_ASSERT(offsetof(Linked_0055A7D0, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(Linked_0055A7D0, PrimaryFacing) == 0x388);

// CellClass — only the slope byte @0x11C is touched.
struct Cell_0055A7D0
{
    char          _pad000[0x11C];   // +0x0000
    unsigned char SlopeIndex;       // +0x011C
};
GG_STATIC_ASSERT(offsetof(Cell_0055A7D0, SlopeIndex) == 0x11C);

// MapClass singleton — opaque; only the coordinate-to-cell lookup is called.
struct Map_0055A7D0
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x565730 (decl; reloc) — MapClass::GetCellAt(coord).
    Cell_0055A7D0* GetCellAt(const Coord_0055A7D0& coord);
};

// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance.
extern Map_0055A7D0 MapInstance;

// Matrix3D — 3 rows x 4 floats, flat at offset 0 (sizeof 0x30).
struct Matrix3D_0055A7D0
{
    float Row[3][4];   // +0x00

    // User-declared so the type is non-POD: that is what makes VC6 pass the
    // hidden return pointer like a first argument (ECX for the __fastcall
    // ramp lookup, the slot after `this` for the __stdcall method) instead of
    // pushing it, and hand it back in EAX.
    Matrix3D_0055A7D0() {}

    // FUNCTION: GAMEMD 0x5AF1A0 (decl; reloc) — Matrix3D::RotateZ(float).
    void RotateZ(float angle);
};
GG_STATIC_ASSERT(sizeof(Matrix3D_0055A7D0) == 0x30);

// FUNCTION: GAMEMD 0x7559B0 (decl; reloc) — copies VoxelRampMatrices[index]
// (0xB45188, 0x30-byte stride) out through the hidden pointer.
Matrix3D_0055A7D0 __fastcall FUN_007559B0(int index);

// LocomotionClass head: the two COM vtables then LinkedTo @0x8.
struct Loco_0055A7D0
{
    void*            _vtable_ILocomotion;      // +0x00
    void*            _vtable_IPersistStream;   // +0x04
    Linked_0055A7D0* LinkedTo;                 // +0x08

    // FUNCTION: GAMEMD 0x55A7D0
    Matrix3D_0055A7D0 __stdcall Shadow_Matrix(unsigned int* key);
};
GG_STATIC_ASSERT(offsetof(Loco_0055A7D0, LinkedTo) == 0x8);

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_SHADOW_MATRIX_METHODS_H
