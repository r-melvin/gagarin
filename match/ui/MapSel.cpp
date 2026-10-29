// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit MapSel.CPP. The name is the source-file string at 0x82c11c
//   in retail gamemd.exe v1.001, passed by the assert at 0x5add9a inside this object's
//   code range (0x5adb20-0x5ae8ef). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   cross-checked against YRpp.
//

#include "../_layout/matrix3d.h"

#include "../movement/trivial_tu131_methods.h"

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EDB38
extern const double DAT_007EDB38;
// GLOBAL: GAMEMD 0xABED78
extern double DAT_00ABED78;
// GLOBAL: GAMEMD 0xABEDB0
extern double DAT_00ABEDB0;
// GLOBAL: GAMEMD 0xABEDB8
extern int DAT_00ABEDB8;
// GLOBAL: GAMEMD 0xABEDBC
extern int DAT_00ABEDBC;
// GLOBAL: GAMEMD 0xABEDC0
extern int DAT_00ABEDC0;
// GLOBAL: GAMEMD 0xABEDC8
extern double DAT_00ABEDC8;



#include "../_layout/matrix3d.h"

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE4F0
// Returns zero; pops its stack arguments.
int __stdcall FUN_005AE4F0(int a1)
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE570
// Empty function that pops its stack arguments.
void __stdcall FUN_005AE570(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE580
// Empty function that pops its stack arguments.
void __stdcall FUN_005AE580(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE860  (__thiscall)
// Reset to the identity transform. Retail is fully unrolled: 1.0f's bit
// pattern is hoisted into EDX, 0.0f into EAX, then the 12 cells are stored in
// source order, so the flat assignment list below reproduces it exactly.
void Matrix3D::MakeIdentity()
{
    Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
    Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
    Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE890  (__thiscall)
// Combined translate, fully unrolled x87. Per row the retail add order is
// (y*col1 + z*col2) + x*col0, then += col3.
void Matrix3D::Translate(float x, float y, float z)
{
    Row[0][3] += y * Row[0][1] + z * Row[0][2] + x * Row[0][0];
    Row[1][3] += y * Row[1][1] + z * Row[1][2] + x * Row[1][0];
    Row[2][3] += y * Row[2][1] + z * Row[2][2] + x * Row[2][0];
}
