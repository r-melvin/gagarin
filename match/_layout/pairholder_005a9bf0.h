// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_PAIRHOLDER_005A9BF0_H_H
#define GG_MATCH__LAYOUT_PAIRHOLDER_005A9BF0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class PairHolder_005A9BF0
{
public:
    // FUNCTION: GAMEMD 0x5A9BF0
    PairHolder_005A9BF0();

    void* unknown_00;   // +0x00
    void* unknown_04;   // +0x04
};
GG_STATIC_ASSERT(offsetof(PairHolder_005A9BF0, unknown_04) == 0x04);
#endif
