// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x408930. Not bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC32_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC32_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Eight-byte entries starting at +0x20 of the source, indexed by the cursor's
// own channel number - `[EAX + ESI*8 + 0x20]` gives both the stride and the base.
struct Entry8b { int First; int Second; };
struct Source_00408930 { char _pad[0x20]; Entry8b Entries[1]; };

struct Cursor_00408930
{
    char              _pad00[0x4];
    int               unknown_04;   // +0x0004
    int               unknown_08;   // +0x0008
    Source_00408930*  unknown_0C;   // +0x000C
    int               Flags;        // +0x0010
    int               Channel;      // +0x0014
    char              _pad18[0x28 - 0x18];
    Source_00408930*  Source;       // +0x0028
    int               unknown_2C;   // +0x002C

    // FUNCTION: GAMEMD 0x408930
    void FUN_00408930();
};
GG_STATIC_ASSERT(offsetof(Cursor_00408930, Channel) == 0x14);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, Source) == 0x28);
GG_STATIC_ASSERT(offsetof(Cursor_00408930, unknown_2C) == 0x2C);

#endif  // GG_MATCH_CORE_SMALL_MISC32_METHODS_H
