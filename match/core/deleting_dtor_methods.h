// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x408E00 / 0x40E4A0 / 0x41C210 / 0x426590. None is
//   bound by YRpp.
//
// One teardown. The scalar deleting destructors that used to live here are
// compiler output now (see the classes' own translation units).
#ifndef GG_MATCH_CORE_DELETING_DTOR_METHODS_H
#define GG_MATCH_CORE_DELETING_DTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

struct Obj_00408E00
{
    char  _pad00[0x10];
    void* unknown_10;   // +0x0010  owned buffer

    // FUNCTION: GAMEMD 0x408E00
    void FUN_00408E00();
};
GG_STATIC_ASSERT(offsetof(Obj_00408E00, unknown_10) == 0x10);

#endif  // GG_MATCH_CORE_DELETING_DTOR_METHODS_H
