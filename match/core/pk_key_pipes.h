// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Public-key and cipher pipe/straw views shared by pk_block_crypt_methods.cpp
// and pk_pipe_straw_io_methods.cpp.
// RTTI type names from the pinned image: 0x7EFDAC .?AVPKPipe@@,
// 0x7EFDE0 .?AVPKStraw@@ (vtable words listed at each VTABLE marker).
// PKPipe/PKStraw member evidence: 0x632CB0 and 0x633050 store byte 1 at
// +0x0C, the random source at +0x10, the embedded cipher pipe/straw at
// +0x14, the control at +0x34, and zero +0x38, +0x13C and +0x140.
// 0x632DC0/0x633130 read the key pointer at +0x38, stage the key exchange in
// the 0x100-byte buffer at +0x3C, and track it with +0x13C/+0x140.
// The embedded cipher objects are 0x20 bytes (+0x14..+0x34); their key
// submission entries are 0x4381D0 (pipe) and 0x438300 (straw), each
// __thiscall with a buffer and the literal length 0x38.
#ifndef GG_MATCH_CORE_PK_KEY_PIPES_H
#define GG_MATCH_CORE_PK_KEY_PIPES_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "pkey_layout.h"
#include "../platform/pk_blow_pipes.h"

#endif // GG_MATCH_CORE_PK_KEY_PIPES_H
