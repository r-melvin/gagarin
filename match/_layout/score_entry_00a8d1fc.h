// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   One entry of the multiplayer score table at 0xA8D1FC (stride 0x70), embedded in
//   SessionClass at +0x1FC4. See mp_score.h for the evidence.
#ifndef GG_MATCH_LAYOUT_SCORE_ENTRY_00A8D1FC_H
#define GG_MATCH_LAYOUT_SCORE_ENTRY_00A8D1FC_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct ScoreEntry_00A8D1FC
{
    wchar_t Name[0x14];       // +0x00
    int     unknown_28;       // +0x28 colour scheme
    int     unknown_2C;       // +0x2C winner count
    int     unknown_30[4];    // +0x30 losses
    int     unknown_40[4];    // +0x40 kills
    int     unknown_50[4];    // +0x50 production
    int     unknown_60[4];    // +0x60 score
};
GG_STATIC_ASSERT(offsetof(ScoreEntry_00A8D1FC, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(ScoreEntry_00A8D1FC, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(ScoreEntry_00A8D1FC, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(ScoreEntry_00A8D1FC, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(ScoreEntry_00A8D1FC, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(ScoreEntry_00A8D1FC, unknown_60) == 0x60);
GG_STATIC_ASSERT(sizeof(ScoreEntry_00A8D1FC) == 0x70);

#endif
