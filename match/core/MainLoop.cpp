// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit MainLoop.CPP. The name is the source-file string at 0x82a170
//   in retail gamemd.exe v1.001, passed by the assert at 0x55e4f5 inside this object's
//   code range (0x55ca00-0x55f77f). Functions are in ascending retail address order.
//
// The four remaining identity tests, ordered ascending by retail address.
//
// The two conditions have to sit in one `&&` with the `true` inline: split
// into two early-return `if`s the failure block is duplicated and the score
// drops to 18.2%.

#include "same_object_test_sweep.h"

#include "trivial_tu125_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7ED3A0
extern const double DAT_007ED3A0;
// GLOBAL: GAMEMD 0xABCD80
extern double DAT_00ABCD80;
// GLOBAL: GAMEMD 0xABCDD0
extern double DAT_00ABCDD0;
// GLOBAL: GAMEMD 0xABCDE0
extern int DAT_00ABCDE0;
// GLOBAL: GAMEMD 0xABCDE4
extern int DAT_00ABCDE4;
// GLOBAL: GAMEMD 0xABCDE8
extern int DAT_00ABCDE8;
// GLOBAL: GAMEMD 0xABCDF0
extern double DAT_00ABCDF0;

// FUNCTION: GAMEMD 0x55CA30
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0055CA30()
{
    DAT_00ABCDF0 = DAT_00ABCD80 / DAT_007ED3A0;
}

// FUNCTION: GAMEMD 0x55CA50
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0055CA50()
{
    DAT_00ABCDD0 = DAT_007E1718 / DAT_00ABCDF0;
}

// FUNCTION: GAMEMD 0x55CBD0
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_0055CBD0()
{
    DAT_00ABCDE8 = 0;
    DAT_00ABCDE0 = 0x80;
    DAT_00ABCDE4 = 0x80;
}

// FUNCTION: GAMEMD 0x55CC00
// Stores to a global.
void __cdecl FUN_0055CC00()
{
    DAT_00ABCD58 = 1;
}

// FUNCTION: GAMEMD 0x55CC10
// Stores to a global.
void __cdecl FUN_0055CC10()
{
    DAT_00ABCD58 = 0;
}

// FUNCTION: GAMEMD 0x55E410
// Empty function.
void __cdecl FUN_0055E410()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55F6C0
bool HandleHolder::FUN_0055F6C0(void** other)
{
    if (this->Held != 0 && *this->Held == *other) {
        return true;
    }

    return false;
}
