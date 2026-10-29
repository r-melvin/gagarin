// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The comparison callback the load dialog sorts its saved-game list with (retail 0x559D30, a
// neighbour of LoadOptionsClass::Slot1 in LoadDlg.cpp). It sorts newest first: the entries'
// last-write times (a FILETIME at +0x1AC) are compared and the result negated.
#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct SavedGameEntry_00559D30 {
    char unknown_00[0x1AC];
    FILETIME LastWrite;   // +0x1AC
};
GG_STATIC_ASSERT(offsetof(SavedGameEntry_00559D30, LastWrite) == 0x1AC);

// FUNCTION: GAMEMD 0x559D30
int __cdecl FUN_00559D30(SavedGameEntry_00559D30** a, SavedGameEntry_00559D30** b)
{
    const FILETIME* left = &(*a)->LastWrite;
    const FILETIME* right = &(*b)->LastWrite;
    return -CompareFileTime(left, right);
}
