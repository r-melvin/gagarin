// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_RULES_008871E0_H_H
#define GG_MATCH__LAYOUT_RULES_008871E0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Rules_008871E0
{
    char _pad000[0x8AC];            // +0x0000
    char unknown_8AC[0x18];         // +0x08AC
    char _pad8C4[0xFA8 - 0x8C4];
    void* At_FA8;                   // +0x0FA8
    char _padFAC[0x1700 - 0xFAC];
    double unknown_1700;            // health-ratio threshold (compared with GetHealthPercentage)
    char unknown_1708[0x16C];
    unsigned char unknown_1874[16][3];   // colour table, three bytes per entry
    int unknown_18A4;               // table index, airstrike tint
    char unknown_18A8[8];
    int unknown_18B0;               // table index, force-shield tint
};
GG_STATIC_ASSERT(offsetof(Rules_008871E0, unknown_8AC) == 0x8AC);
GG_STATIC_ASSERT(offsetof(Rules_008871E0, At_FA8) == 0xFA8);
GG_STATIC_ASSERT(offsetof(Rules_008871E0, unknown_1700) == 0x1700);
GG_STATIC_ASSERT(offsetof(Rules_008871E0, unknown_1874) == 0x1874);
GG_STATIC_ASSERT(offsetof(Rules_008871E0, unknown_18A4) == 0x18A4);
GG_STATIC_ASSERT(offsetof(Rules_008871E0, unknown_18B0) == 0x18B0);

#endif
