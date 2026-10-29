// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit WDTTerr.cpp. The name is the source-file string at 0x84917c
//   in retail gamemd.exe v1.001, passed by the assert at 0x76fa3a inside this object's
//   code range (0x76f720-0x77007f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The deleting destructors (??_G) of the World Domination Tour data classes are
// compiler output: the out-of-line destructors below make cl emit the tables and
// the wrappers, and /Ob2 expands the destructor bodies into them as retail has it.

#include "../core/trivial_tu280_methods.h"

#include "world_domination_tour.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F7320
extern const double DAT_007F7320;
// GLOBAL: GAMEMD 0xB72B30
extern double DAT_00B72B30;
// GLOBAL: GAMEMD 0xB72B68
extern double DAT_00B72B68;
// GLOBAL: GAMEMD 0xB72B70
extern int DAT_00B72B70;
// GLOBAL: GAMEMD 0xB72B74
extern int DAT_00B72B74;
// GLOBAL: GAMEMD 0xB72B78
extern int DAT_00B72B78;
// GLOBAL: GAMEMD 0xB72B80
extern double DAT_00B72B80;

// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0076F750()
{
    DAT_00B72B80 = DAT_00B72B30 / DAT_007F7320;
}

// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0076F770()
{
    DAT_00B72B68 = DAT_007E1718 / DAT_00B72B80;
}

// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_0076F8F0()
{
    DAT_00B72B78 = 0;
    DAT_00B72B70 = 0x80;
    DAT_00B72B74 = 0x80;
}

// FUNCTION: GAMEMD 0x76F910
// The Territory factory: a new Territory over the five values, returned in a handle (hidden result
// pointer in ECX, the first value in EDX).
rc_ptr<WorldDominationTour::Territory> FUN_0076F910(int a, void* b, char* c, unsigned int* d, unsigned int* e)
{
    return rc_ptr<WorldDominationTour::Territory>(new WorldDominationTour::Territory(a, b, c, d, e));
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76FD10
// Seats the Territory table, then the members in reverse order and the
// ReferenceCounted destructor.
WorldDominationTour::Territory::~Territory()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76FF20
// Stores its argument in a member; pops its stack arguments.
void Obj_0076FF20::FUN_0076FF20(int a1)
{
    unknown_2C = a1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76FF30
// Stores its argument in a member.
int Obj_0076FF30::FUN_0076FF30()
{
    int t1 = unknown_2C;
    unknown_2C = 0;
    return t1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x770020
// Territory scalar deleting destructor.
