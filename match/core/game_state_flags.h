// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Native Tactical update0x6D2540 tests bit1 of A8D5F8 and tests A8ED5C
// as a byte. Preserve the existing shared-consumer unsigned-byte/bool types.
// Original flag names and remaining alias names are not asserted.
#ifndef GG_MATCH_CORE_GAME_STATE_FLAGS_H
#define GG_MATCH_CORE_GAME_STATE_FLAGS_H
#include "../_rt/gg_static_assert.h"
extern unsigned char DAT_00A8D5F8; // GLOBAL: GAMEMD 0xA8D5F8 (decl; reloc)
extern bool DAT_00A8ED5C; // GLOBAL: GAMEMD 0xA8ED5C (decl; reloc)
GG_STATIC_ASSERT(sizeof(DAT_00A8D5F8) == 1);
GG_STATIC_ASSERT(sizeof(DAT_00A8ED5C) == 1);
#endif
