// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x5117D0 (see the RE dossier at
//   docs/decomp_spec/re_findings/next_targets_2026-08-07.md §7). The array
//   globals are Items 0x00A83C9C and Count 0x00A83CA8 — +0x04 and +0x10 of one
//   DynamicVectorClass, so the vector object is at 0x00A83C98. The two member
//   reads confirm the committed AbstractTypeClass spine: `LEA ECX,[ESI+0x64]`
//   is Name and `LEA EDX,[ESI+0x24]` is ID.
#ifndef GG_MATCH_ECONOMY_HOUSE_TYPE_CLASS_FIND_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_TYPE_CLASS_FIND_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"
#include "../_layout/abstract_type_class.h"

// CRT case-insensitive compare at 0x007C8D20 (__cdecl, `ADD ESP,8` after each
// call). Statically-linked CRT is outside the match target, so it is declared
// and called, never reimplemented.
extern "C" int __cdecl _stricmp(const char* a, const char* b);

struct HouseTypeClass : AbstractTypeClass
{
    char _pad98[0xB8 - 0x98];   // +0x0098
    int  ArrayIndex;            // +0x00B8  returned on a hit

    // GAMEMD 0x5117D0 — ECX carries the name, so this is __fastcall.
    static int __fastcall FindIndexOfName(const char* name);
};
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ArrayIndex) == 0xB8);

// GLOBAL: GAMEMD 0x00A83C98 — HouseTypeClass::Array.
extern DynamicVectorClassLayout HouseTypeArray;

#endif  // GG_MATCH_ECONOMY_HOUSE_TYPE_CLASS_FIND_METHODS_H
