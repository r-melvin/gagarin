// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Fourth translation unit of the FlyLocomotionClass cluster: the two
//   ILocomotion slots that hand back a 3x4 draw matrix. The class was
//   identified from its own runtime type information - see
//   fly_locomotion_com_methods.h for that derivation.
//
//   The locomotor interface vtable at 0x7E89F4 was read out whole
//   (`ghidra memory read 0x7E89F4 200`, decimal count). The two slots here,
//   by byte offset into that table: +0x24 = 0x4CF610 (Draw_Matrix) and
//   +0x28 = 0x4CFB00 (Shadow_Matrix). Both override the plain locomotor's
//   own bodies at 0x55A730 / 0x55A7D0, already matched in
//   locomotion_class_draw_matrix_methods.cpp and
//   locomotion_class_shadow_matrix_methods.cpp, and this header is that
//   header's model widened by the members the flyer's overrides read.
//
// Offsets confirmed numerically against the user's retail gamemd.exe v1.001.
// The displacements are interface-relative (four lower than the object's),
// because a COM slot receives the locomotor interface pointer:
//   +0x08 LinkedTo   `MOV ESI,[ESP+0x3C]` then `MOV ECX,[ESI+0x8]` in
//                    0x4CF610; `MOV EAX,[EBX+0x8]` in 0x4CFB00
//   +0x44 Height     `FLD QWORD PTR [ESI+0x44]` in 0x4CF610, twice
// Both bodies are `RET 0xC`: the receiver at the first stack slot, the hidden
// 48-byte return buffer at the second, the voxel key pointer at the third -
// which is the __stdcall MEMBER layout, not the free-function one.
//
// The linked object's own members, read off the member accesses:
//   +0x009C Location        `MOV EDX,[EAX+0x9C]` in 0x4CFB00
//   +0x0328 unknown_328       `MOV EAX,[ECX+0x328]` in 0x4CF610 (float)
//   +0x032C unknown_32C        `FLD DWORD PTR [ECX+0x32C]` in 0x4CF610 (float)
//   +0x03A0 SecondaryFacing `ADD ECX,0x3A0` before 0x4C93D0/0x4C94B0/0x4C94F0
//   +0x0425 IsTilting       `MOV AL,[ECX+0x425]` in 0x4CF610
// and its vtable slots +0x84 (the type object) and +0x1C8 (remaining travel).
// The type object's own doubles: +0x3A0, +0x3A8, +0x3B0, and the gate byte at
// +0xC95 that zeroes the ramp slope.
#ifndef GG_MATCH_MOVEMENT_FLY_LOCOMOTION_MATRIX_METHODS_H
#define GG_MATCH_MOVEMENT_FLY_LOCOMOTION_MATRIX_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// A binary-angle direction. The user-declared constructor is what makes VC6
// return it through a hidden pointer (a POD of this size would come back in
// EAX); retail reads the whole dword off that pointer.
struct Dir_004CF610
{
    unsigned int Raw;   // +0x00
    Dir_004CF610() {}
};
GG_STATIC_ASSERT(sizeof(Dir_004CF610) == 4);

// FacingClass (0x18) — opaque here; three of its readers are called.
struct Facing_004CF610
{
    char opaque[0x18];

    // FUNCTION: GAMEMD 0x4C93D0 (decl; reloc) — FacingClass::Current.
    Dir_004CF610 Current();
    // FUNCTION: GAMEMD 0x4C94B0 (decl; reloc) — turning one way.
    char IsTurningA();
    // FUNCTION: GAMEMD 0x4C94F0 (decl; reloc) — turning the other way.
    char IsTurningB();
};
GG_STATIC_ASSERT(sizeof(Facing_004CF610) == 0x18);

// A world coordinate: three ints.
struct Coord_004CF610
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(Coord_004CF610) == 0xC);

// CellClass — only the slope byte @0x11C is touched.
struct Cell_004CF610
{
    char          _pad000[0x11C];   // +0x0000
    unsigned char SlopeIndex;       // +0x011C
};
GG_STATIC_ASSERT(offsetof(Cell_004CF610, SlopeIndex) == 0x11C);

// MapClass singleton — opaque; only the coordinate-to-cell lookup is called.
struct Map_004CF610
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x565730 (decl; reloc) — MapClass::GetCellAt(coord).
    Cell_004CF610* GetCellAt(const Coord_004CF610& coord);
};

// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance.
extern Map_004CF610 MapInstance_004CF610;

// The linked object's type object. Three doubles and the ramp gate byte.
struct AircraftType_004CF610
{
    char   _pad000[0x3A0];            // +0x0000
    double RollAngle;                 // +0x03A0
    double PitchHeight;               // +0x03A8
    double PitchAngle;                // +0x03B0
    char   _pad3B8[0xC95 - 0x3B8];    // +0x03B8
    char   IsFlatOnGround;            // +0x0C95
};
GG_STATIC_ASSERT(offsetof(AircraftType_004CF610, RollAngle) == 0x3A0 &&
                 offsetof(AircraftType_004CF610, PitchHeight) == 0x3A8 &&
                 offsetof(AircraftType_004CF610, PitchAngle) == 0x3B0 &&
                 offsetof(AircraftType_004CF610, IsFlatOnGround) == 0xC95);

// The locomotor's client object. Declaration order matters - see gg_vslot.h.
struct FootVtbl_004CF610;

struct Foot_004CF610
{
    FootVtbl_004CF610* Vtbl;              // +0x0000
    char            _pad004[0x9C - 0x4];  // +0x0004
    Coord_004CF610  Location;             // +0x009C
    char            _pad0A8[0x328 - 0xA8];
    float           unknown_328;            // +0x0328
    float           unknown_32C;             // +0x032C
    char            _pad330[0x3A0 - 0x330];
    Facing_004CF610 SecondaryFacing;      // +0x03A0
    char            _pad3B8[0x425 - 0x3B8];
    char            IsTilting;            // +0x0425
};
GG_STATIC_ASSERT(offsetof(Foot_004CF610, Location) == 0x9C &&
                 offsetof(Foot_004CF610, unknown_328) == 0x328 &&
                 offsetof(Foot_004CF610, unknown_32C) == 0x32C &&
                 offsetof(Foot_004CF610, SecondaryFacing) == 0x3A0 &&
                 offsetof(Foot_004CF610, IsTilting) == 0x425);

typedef AircraftType_004CF610* (Foot_004CF610::*FnType_004CF610)();
typedef int (Foot_004CF610::*FnInt_004CF610)();

struct FootVtbl_004CF610
{
    char            _pad000[0x84];          // +0x0000
    FnType_004CF610 At_84;                  // +0x0084
    char            _pad088[0x1C8 - 0x88];  // +0x0088
    FnInt_004CF610  At_1C8;                 // +0x01C8
};
GG_STATIC_ASSERT(offsetof(FootVtbl_004CF610, At_84) == 0x84 &&
                 offsetof(FootVtbl_004CF610, At_1C8) == 0x1C8);

// Matrix3D — 3 rows x 4 floats, flat at offset 0 (sizeof 0x30).
struct Matrix3D_004CF610
{
    float Row[3][4];   // +0x00

    // User-declared so the type is non-POD: that is what makes VC6 pass the
    // hidden return pointer like a first argument (ECX for the __fastcall
    // ramp lookup, the slot after `this` for the __stdcall method) instead of
    // pushing it, and hand it back in EAX.
    Matrix3D_004CF610() {}

    // FUNCTION: GAMEMD 0x5AE860 (decl; reloc) — Matrix3D::MakeIdentity.
    void MakeIdentity();
    // FUNCTION: GAMEMD 0x5AEF60 (decl; reloc) — Matrix3D::RotateX(float).
    void RotateX(float angle);
    // FUNCTION: GAMEMD 0x5AF080 (decl; reloc) — Matrix3D::RotateY(float).
    void RotateY(float angle);
    // FUNCTION: GAMEMD 0x5AF1A0 (decl; reloc) — Matrix3D::RotateZ(float).
    void RotateZ(float angle);
};
GG_STATIC_ASSERT(sizeof(Matrix3D_004CF610) == 0x30);

// FUNCTION: GAMEMD 0x7559B0 (decl; reloc) — copies VoxelRampMatrices[index]
// (0xB45188, 0x30-byte stride) out through the hidden pointer.
Matrix3D_004CF610 __fastcall FUN_007559B0_M(int index);

// FlyLocomotionClass seen through its locomotor interface at object +0x04.
// Packed to four, because the interface pointer sits four into the object, so
// the double at object +0x48 lands on an odd four-byte boundary here.
#pragma pack(push, 4)
struct FlyLocoMatrix
{
    void*          _vtable_locomotor;      // +0x0000  (object +0x04)
    void*          _vtable_persist;        // +0x0004  (object +0x08)
    Foot_004CF610* LinkedTo;               // +0x0008  (object +0x0C)
    char           _pad00C[0x44 - 0xC];    // +0x000C
    double         Height;                 // +0x0044  (object +0x48)

    // FUNCTION: GAMEMD 0x4CF610
    Matrix3D_004CF610 __stdcall Draw_Matrix(int* key);
    // FUNCTION: GAMEMD 0x4CFB00
    Matrix3D_004CF610 __stdcall Shadow_Matrix(unsigned int* key);
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(FlyLocoMatrix, LinkedTo) == 0x08 &&
                 offsetof(FlyLocoMatrix, Height) == 0x44);

#endif  // GG_MATCH_MOVEMENT_FLY_LOCOMOTION_MATRIX_METHODS_H
