// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly + memory read of the array at
//   0x7E1B78), cross-checked against YRpp Theater.h (consult-only; every
//   offset/size reconfirmed numerically from the disassembly below).
//
// Theater — the 0x70-byte per-theater descriptor (TEMPERATE, SNOW, ...). There
// are 6 entries in the fixed global Theater::Array @0x7E1B78. Only the leading
// ID[0x10] field is touched by FindIndex (the _stricmp comparand); the
// remaining members are padded to the confirmed 0x70 stride (full layout = P2).
#ifndef GG_MATCH_CORE_THEATER_METHODS_H
#define GG_MATCH_CORE_THEATER_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// Theater  (sizeof = 0x70)
//
// Confirmed from 0x48DBE0 (Theater::FindIndex): ESI starts at 0x7E1B78
// (&Array[0]), advances by 0x70 per iteration, and the end sentinel is
// 0x7E1E18 == 0x7E1B78 + 6*0x70. The element pointer is passed straight to
// _stricmp, i.e. the comparand name lives at offset 0 of the element — the
// ID field (memory read @0x7E1B78 == "TEMPERATE\0").
// ---------------------------------------------------------------------------
struct Theater
{
    static int __fastcall FindIndex(const char* pName);  // GAMEMD 0x48DBE0

    char ID[0x10];          // +0x00  e.g. "TEMPERATE"
    char _pad[0x60];        // +0x10  remaining members (P2); pad to 0x70 stride
};

GG_STATIC_ASSERT(offsetof(Theater, ID) == 0x00);
GG_STATIC_ASSERT(sizeof(Theater) == 0x70);

#endif  // GG_MATCH_CORE_THEATER_METHODS_H
