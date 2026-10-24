// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Existing Tactical pair owner, shared with interpolation helper0x75F5C0.
// Native helper reads two signed DWORDs at0/4 and writes8bytes to its result.
// Original type name is unproved; preserve the existing address-based name.
#ifndef GG_MATCH_LAYOUT_PAIR_006D9F80_H
#define GG_MATCH_LAYOUT_PAIR_006D9F80_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct Pair_006D9F80
{
    Pair_006D9F80() {}
    Pair_006D9F80(int x, int y) : unknown_00(x), unknown_04(y) {}
    bool operator==(const Pair_006D9F80& other) const
    { return unknown_00 == other.unknown_00 && unknown_04 == other.unknown_04; }
    Pair_006D9F80* FUN_006D1EB0(int x, int y); // 0x6D1EB0; ECX=result, RET 8
    int unknown_00;
    int unknown_04;
};
GG_STATIC_ASSERT(offsetof(Pair_006D9F80, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(Pair_006D9F80, unknown_04) == 4);
GG_STATIC_ASSERT(sizeof(Pair_006D9F80) == 8);
// Declaration: GAMEMD 0x75F5C0 -- ECX result, EDX first, second/weight stacked.
Pair_006D9F80* __fastcall FUN_0075F5C0(Pair_006D9F80* output,
    const Pair_006D9F80* first, const Pair_006D9F80* second, float weight);
#endif
