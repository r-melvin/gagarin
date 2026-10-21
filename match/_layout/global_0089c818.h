// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x43B0E0 writes two words at 0x89C818 and 0x89C81A; other
// instructions compare each word and read the combined dword. 0x4587D0
// forwards a dword read into a call argument. These widths do not establish
// the original type, semantic owner, signedness or a pointer interpretation.
#ifndef GG_GLOBAL_0089C818_H
#define GG_GLOBAL_0089C818_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Global_0089C818_Words
{
    unsigned short word_00;
    unsigned short word_02;
};
union Global_0089C818_View
{
    unsigned int raw_dword;
    Global_0089C818_Words words;
};
GG_STATIC_ASSERT(sizeof(unsigned short) == 2);
GG_STATIC_ASSERT(sizeof(unsigned int) == 4);
GG_STATIC_ASSERT(offsetof(Global_0089C818_Words, word_00) == 0);
GG_STATIC_ASSERT(offsetof(Global_0089C818_Words, word_02) == 2);
GG_STATIC_ASSERT(sizeof(Global_0089C818_Words) == 4);
GG_STATIC_ASSERT(offsetof(Global_0089C818_View, raw_dword) == 0);
GG_STATIC_ASSERT(offsetof(Global_0089C818_View, words) == 0);
GG_STATIC_ASSERT(sizeof(Global_0089C818_View) == 4);

// GLOBAL: GAMEMD 0x0089C818
// Volatile preserves the separate observed accesses; it is a source choice.
extern volatile Global_0089C818_View DAT_0089C818;
#endif
