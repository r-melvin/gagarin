// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x55A730: `this` arrives on the stack (`MOV EDI,[ESP+0x40]`,
//   the __stdcall COM convention) with the hidden Matrix3D return pointer
//   behind it and the key pointer third (RET 0xC); `MOV ECX,[EDI+0x8]` then
//   `ADD ECX,0x388` is the linked object's PrimaryFacing, whose Current()
//   @0x4C93D0 hands back a DirStruct through a hidden pointer that the caller
//   reads as one dword. The matrix is the 3x4 float layout already proven in
//   match/movement/matrix3d_methods.h (MakeIdentity @0x5AE860, RotateZ
//   @0x5AF1A0). Names from YRpp LocomotionClass.h / Facing.h (consult-only).
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_DRAW_MATRIX_METHODS_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_DRAW_MATRIX_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A binary-angle direction. The user-declared constructor is what makes VC6
// return it through a hidden pointer (a POD of this size would come back in
// EAX); retail reads the whole dword off that pointer.
struct Dir_0055A730
{
    unsigned int Raw;   // +0x00
    Dir_0055A730() {}
};
GG_STATIC_ASSERT(sizeof(Dir_0055A730) == 4);

// FacingClass (0x18) — opaque here; only Current() is called.
struct Facing_0055A730
{
    char opaque[0x18];

    // FUNCTION: GAMEMD 0x4C93D0 (decl; reloc) — FacingClass::Current.
    Dir_0055A730 Current();
};
GG_STATIC_ASSERT(sizeof(Facing_0055A730) == 0x18);

// The linked TechnoClass — only PrimaryFacing @0x388 is touched.
struct Linked_0055A730
{
    char            _pad000[0x388];    // +0x0000
    Facing_0055A730 PrimaryFacing;     // +0x0388
};
GG_STATIC_ASSERT(offsetof(Linked_0055A730, PrimaryFacing) == 0x388);

// Matrix3D — 3 rows x 4 floats, flat at offset 0 (sizeof 0x30).
struct Matrix3D_0055A730
{
    float Row[3][4];   // +0x00

    // FUNCTION: GAMEMD 0x5AE860 (decl; reloc) — Matrix3D::MakeIdentity.
    void MakeIdentity();
    // FUNCTION: GAMEMD 0x5AF1A0 (decl; reloc) — Matrix3D::RotateZ(float).
    void RotateZ(float angle);
};
GG_STATIC_ASSERT(sizeof(Matrix3D_0055A730) == 0x30);

// LocomotionClass head: the two COM vtables then LinkedTo @0x8.
struct Loco_0055A730
{
    void*            _vtable_ILocomotion;      // +0x00
    void*            _vtable_IPersistStream;   // +0x04
    Linked_0055A730* LinkedTo;                 // +0x08

    // FUNCTION: GAMEMD 0x55A730
    Matrix3D_0055A730 __stdcall Draw_Matrix(unsigned int* key);
};
GG_STATIC_ASSERT(offsetof(Loco_0055A730, LinkedTo) == 0x8);

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_CLASS_DRAW_MATRIX_METHODS_H
