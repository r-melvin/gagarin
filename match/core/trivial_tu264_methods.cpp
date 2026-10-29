// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu264_methods.h"
#include "mathtbl_init_shapes.h"
#include "../_layout/vector3d.h"

// SYNTHETIC: GAMEMD 0x7539B0
// GLOBAL: GAMEMD 0xB2D810
MathTblZero4 DAT_00B2D810;

// FUNCTION: GAMEMD 0x752AB0
// Branching.
void FUN_00752AB0(int a1)
{
    DAT_00846614 = a1;
    if (a1 >= 0xFF)
    {
        DAT_00846614 = 0xFF;
    }
}

// FUNCTION: GAMEMD 0x7533A0
// Returns a constant boolean.
bool __cdecl FUN_007533A0()
{
    return true;
}

// FUNCTION: GAMEMD 0x753570
// Stores to a global.
int __cdecl FUN_00753570()
{
    DAT_00B1D3D8++;
    return DAT_00B1D3D8;
}

// FUNCTION: GAMEMD 0x753A30
// Calls other functions.
void FUN_00753A30(int a1, int a2)
{
    FUN_0043AE50(DAT_00B2D93C, a2);
    DAT_00B2D928 = 0x7E2198;
}

// FUNCTION: GAMEMD 0x753AB0
// Calls other functions.
void FUN_00753AB0(int a1, int a2)
{
    FUN_0043AE50(DAT_00B2D804, a2);
    DAT_00B2D7F0 = 0x7E2198;
}

// Two globals whose constructors are empty: retail's initialisers at 0x753AD0
// and 0x753AE0 are a bare RET. Neither writes anything, so their addresses and
// real types are not recovered; the placeholder types below only carry the
// empty constructor.
struct Empty_00753AD0
{
    Empty_00753AD0() {}
};
struct Empty_00753AE0
{
    Empty_00753AE0() {}
};

// SYNTHETIC: GAMEMD 0x753AD0
Empty_00753AD0 Obj_00753AD0;

// SYNTHETIC: GAMEMD 0x753AE0
Empty_00753AE0 Obj_00753AE0;

// A rectangle of the 256-square buffer: origin (0, 0), extent 255 x 255.
struct Rect_00753AF0
{
    int X;
    int Y;
    int Width;
    int Height;
    Rect_00753AF0() : X(0), Y(0), Width(0xFF), Height(0xFF) {}
};

// SYNTHETIC: GAMEMD 0x753AF0
// GLOBAL: GAMEMD 0xB2FB60
Rect_00753AF0 DAT_00B2FB60;

// FUNCTION: GAMEMD 0x753C60
// Returns the address of a global.
void* __cdecl FUN_00753C60()
{
    return DAT_00B2FF78;
}

// Eight corner points followed by 0x28 bytes whose constructor does nothing.
// 64 records at 0xB2D980; retail builds the array with the vector constructor
// iterator over the corners (constructor 0x754900) once per record.
struct Record_00753B10
{
    Vector3D Corners[8];    // +0x00
    char unknown_60[0x28];  // +0x60
};
GG_STATIC_ASSERT(sizeof(Record_00753B10) == 0x88);

// SYNTHETIC: GAMEMD 0x753B10
// GLOBAL: GAMEMD 0xB2D980
Record_00753B10 DAT_00B2D980[64];
