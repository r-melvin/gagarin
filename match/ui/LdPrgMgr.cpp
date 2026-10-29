// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit LdPrgMgr.cpp. The name is the source-file string at 0x829ac8
//   in retail gamemd.exe v1.001, passed by the assert at 0x552ebc inside this object's
//   code range (0x552850-0x55442f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.

#include "../core/trivial_tu117_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7ECF50
extern const double DAT_007ECF50;
// GLOBAL: GAMEMD 0xABC960
extern double DAT_00ABC960;
// GLOBAL: GAMEMD 0xABC9A0
extern int DAT_00ABC9A0;
// GLOBAL: GAMEMD 0xABC9A4
extern int DAT_00ABC9A4;
// GLOBAL: GAMEMD 0xABC9A8
extern int DAT_00ABC9A8;

// dynamic initializer for DAT_00ABC9B0
// GLOBAL: GAMEMD 0x00ABC9B0
extern double DAT_00ABC9B0;

// dynamic initializer for DAT_00ABC998
// GLOBAL: GAMEMD 0x00ABC998
extern double DAT_00ABC998;

GG_STATIC_ASSERT(sizeof(DAT_00ABC9B0) == 8);
GG_STATIC_ASSERT(sizeof(DAT_00ABC998) == 8);


// GLOBAL: GAMEMD 0xABC9BC
extern int DAT_00ABC9BC;

// FUNCTION: GAMEMD 0x554370 (decl; reloc)
void FUN_00554370(int, int);
// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc)
void __cdecl FUN_007C8B3D(int);


// FUNCTION: GAMEMD 0x552AA0
void FUN_00552AA0(int a1, int a2);

// FUNCTION: GAMEMD 0x552AA0
// Branching.
void FUN_00552AA0(int a1, int a2)
{
    if (DAT_00ABC9BC != 0)
    {
        FUN_00554370(DAT_00ABC9BC, a2);
        FUN_007C8B3D(DAT_00ABC9BC);
        DAT_00ABC9BC = 0;
    }
    DAT_00ABC9BC = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x554350
// Branching.
void Obj_00554350::FUN_00554350(Arg1_00554350* a1)
{
    if (unknown_60 != 0)
    {
        a1->vf_1(unknown_60, 0, 1);
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xABC9BC
int DAT_00ABC9BC;
// END defined globals
