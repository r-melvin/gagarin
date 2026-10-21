// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Entry 0x47ADA0 reads the dword at 0x89E414, stores ECX there, then stores
// the prior dword at 0x89E418. Entry 0x47AAC0 later reads the low byte of
// 0x89E414 and adds 'A', supporting a scalar index view. Original ownership
// and method name are unknown.
#include "../_rt/gg_static_assert.h"

GG_STATIC_ASSERT(sizeof(unsigned int) == 4);

// GLOBAL: GAMEMD 0x0089E414
extern unsigned int DAT_0089E414;
// GLOBAL: GAMEMD 0x0089E418
extern unsigned int DAT_0089E418;
GG_STATIC_ASSERT(sizeof(DAT_0089E414) == 4);
GG_STATIC_ASSERT(sizeof(DAT_0089E418) == 4);

// FUNCTION: GAMEMD 0x0047ADA0 (17 bytes, entry-origin, RET)
void __fastcall FUN_0047ADA0(unsigned int value)
{
    unsigned int previous = DAT_0089E414;
    DAT_0089E414 = value;
    DAT_0089E418 = previous;
}
