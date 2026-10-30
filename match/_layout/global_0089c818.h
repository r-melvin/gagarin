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
#include "cell.h"   // CellStruct

struct Global_0089C818_Words
{
    unsigned short word_00;
    unsigned short word_02;
};
union Global_0089C818_View
{
    unsigned int raw_dword;
    Global_0089C818_Words words;
    CellStruct cell;
    Global_0089C818_View() { words.word_00 = 0; words.word_02 = 0; }
    // The "no cell" reading of the dword: the same four bytes as a CellStruct.
    operator CellStruct() const { return cell; }
};
GG_STATIC_ASSERT(sizeof(unsigned short) == 2);
GG_STATIC_ASSERT(sizeof(unsigned int) == 4);
GG_STATIC_ASSERT(offsetof(Global_0089C818_Words, word_00) == 0);
GG_STATIC_ASSERT(offsetof(Global_0089C818_Words, word_02) == 2);
GG_STATIC_ASSERT(sizeof(Global_0089C818_Words) == 4);
GG_STATIC_ASSERT(offsetof(Global_0089C818_View, raw_dword) == 0);
GG_STATIC_ASSERT(offsetof(Global_0089C818_View, words) == 0);
GG_STATIC_ASSERT(offsetof(Global_0089C818_View, cell) == 0);
GG_STATIC_ASSERT(sizeof(Global_0089C818_View) == 4);

// GLOBAL: GAMEMD 0x0089C818
// Not volatile: the only writer is the static initialiser 0x43B0E0 (__xc
// entry 0x8127A4), this view's constructor, and no thread procedure touches it.
extern Global_0089C818_View DAT_0089C818;
#endif
