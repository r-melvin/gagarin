// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The unit at retail 0x4C5EE0..0x4C635F (it also holds EvadeClass::Do,
// evade_class_do_methods.cpp): three of its run-time initialisers and an
// unreferenced empty function, in retail address order.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../core/header_tuning_globals.h"

// GLOBAL: GAMEMD 0x8A38D8
extern double DAT_008A38D8;
// GLOBAL: GAMEMD 0x7E8808
const double DAT_007E8808 = 60.0;

// SYNTHETIC: GAMEMD 0x4C5F10
// GLOBAL: GAMEMD 0x8A3970
double DAT_008A3970 = DAT_008A38D8 / DAT_007E8808;
// SYNTHETIC: GAMEMD 0x4C5F30
// GLOBAL: GAMEMD 0x8A3958
double DAT_008A3958 = 1.0 / DAT_008A3970;
// SYNTHETIC: GAMEMD 0x4C60B0
// GLOBAL: GAMEMD 0x8A3960
TuningCoordInit DAT_008A3960(128, 128, 0);

// A record at 0x8A38E0: a cleared 50-byte block, two cleared dwords, a flag
// dword set to 1 and a cleared word; its destructor is empty.
struct Obj_008A38E0
{
    Obj_008A38E0()
    {
        unknown_34 = 0;
        unknown_38 = 0;
        unknown_3C = 1;
        unknown_40 = 0;
        memset(unknown_00, 0, sizeof(unknown_00));
    }
    ~Obj_008A38E0() {}

    unsigned char  unknown_00[0x32];   // +0x00
    unsigned char  _pad_32[2];         // +0x32
    int            unknown_34;         // +0x34
    int            unknown_38;         // +0x38
    int            unknown_3C;         // +0x3C
    unsigned short unknown_40;         // +0x40
};
GG_STATIC_ASSERT(offsetof(Obj_008A38E0, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(Obj_008A38E0, unknown_40) == 0x40);

// SYNTHETIC: GAMEMD 0x4C60F0
// SYNTHETIC: GAMEMD 0x4C6130 -- atexit callback
// GLOBAL: GAMEMD 0x8A38E0
Obj_008A38E0 DAT_008A38E0;

// FUNCTION: GAMEMD 0x4C6170
// An unreferenced empty function.
void FUN_004C6170()
{
}
