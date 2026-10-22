// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Many retail units carry their own copies of a block of header globals,
//   each filled by a compiler-generated __xc initialiser. The coordinate
//   copies are stored at run time (0x80, 0x80, 0) as three dword moves, which
//   VC6 emits only for a constructor call, never for a brace initialiser. The
//   type below supplies that constructor (store order as in retail: Z first).
#ifndef GG_MATCH_CORE_HEADER_TUNING_GLOBALS_H
#define GG_MATCH_CORE_HEADER_TUNING_GLOBALS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct TuningCoordInit
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
    TuningCoordInit(int x, int y, int z) { X = x; Y = y; Z = z; }
};
GG_STATIC_ASSERT(offsetof(TuningCoordInit, Z) == 8);
GG_STATIC_ASSERT(sizeof(TuningCoordInit) == 0xC);

#endif  // GG_MATCH_CORE_HEADER_TUNING_GLOBALS_H
