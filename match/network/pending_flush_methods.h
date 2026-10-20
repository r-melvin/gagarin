// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x42DF40. Both codec calls take the pending count in EDX
//   with two pushed arguments, and the two branches swap which of +0x14 and +0x18
//   is the receiver and which is the buffer.
#ifndef GG_MATCH_NETWORK_PENDING_FLUSH_METHODS_H
#define GG_MATCH_NETWORK_PENDING_FLUSH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x42FD30 — the four-bit codec.
int __fastcall FUN_0042FD30(void* state, int pending, void* buffer, int width);
// FUNCTION: GAMEMD 0x42FE50 — the three-bit codec.
int __fastcall FUN_0042FE50(void* state, int pending, void* buffer, int width);

struct Obj_0042DF40
{
    char _pad000[0xC];      // +0x0000
    int  Mode;              // +0x000C  chooses which codec runs
    int  Pending;           // +0x0010  cleared once flushed
    char At_14[4];          // +0x0014
    char At_18[4];          // +0x0018

    // FUNCTION: GAMEMD 0x631D10 — hand the encoded bytes on.
    int FUN_00631D10(void* buffer, int written);
    // FUNCTION: GAMEMD 0x631D30 — whatever is already queued.
    int FUN_00631D30();

    // FUNCTION: GAMEMD 0x42DF40
    int FUN_0042DF40();
};
GG_STATIC_ASSERT(offsetof(Obj_0042DF40, Mode) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_0042DF40, Pending) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_0042DF40, At_18) == 0x18);

#endif  // GG_MATCH_NETWORK_PENDING_FLUSH_METHODS_H
