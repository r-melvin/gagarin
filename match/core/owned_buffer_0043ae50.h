// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Helper 0x43AE50 tests ownership at +8, frees pointer+0 and clears +0/+4/+8.
// BSurface deleting body 0x411650 calls it on its member at +0x14.
// Original source class/member names remain unconfirmed.
#ifndef GG_MATCH_CORE_OWNED_BUFFER_0043AE50_H
#define GG_MATCH_CORE_OWNED_BUFFER_0043AE50_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct Owned_0043AE50
{
    void* Buffer;
    int Length;
    unsigned char IsAllocated;
    // FUNCTION: GAMEMD 0x43AE50 (decl; reloc)
    void FUN_0043AE50();
};
GG_STATIC_ASSERT(offsetof(Owned_0043AE50, Buffer) == 0x00);
GG_STATIC_ASSERT(offsetof(Owned_0043AE50, Length) == 0x04);
GG_STATIC_ASSERT(offsetof(Owned_0043AE50, IsAllocated) == 0x08);
#endif
