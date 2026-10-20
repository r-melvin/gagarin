// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail uses a dword frame counter at 0xA8ED84. Direct operands in matched
// timer/network functions independently confirm this shared storage; e.g.
// the function at 0x6CB4D0 and Event constructors at 0x4C6650.
// DrawLinks also reads it at 0x4721A3. The address lies in the PE .data
// virtual tail, beyond its file-backed bytes, so its initial storage is zero.
// This header does not establish the counter's original namespace.
#ifndef GG_MATCH_CORE_FRAME_COUNTER_H
#define GG_MATCH_CORE_FRAME_COUNTER_H

#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84
extern int CurrentFrame;
GG_STATIC_ASSERT(sizeof(CurrentFrame) == 4);

#endif
