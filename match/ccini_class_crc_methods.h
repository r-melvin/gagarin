// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x476D80: the cached flag is `CMP [ESI+0x40],BL` /
//   `MOV byte ptr [ESI+0x40],1`, the digest is `LEA ECX,[ESI+0x41]` /
//   `ADD ESI,0x41` with length 0x14. The stack hash engine at `[ESP+0x14]` is
//   laid out from its inline constructor: `[+0x04]=0`, `[+0x08]=0`,
//   `byte [+0x0C]=0`, `[+0x24..+0x34]` = the five SHA-1 seeds, `[+0x38]=0`,
//   `[+0x3C]=0`, `[+0x00]=0x7E4D78`; the frame gives it 0x80 bytes. The CRC
//   engine at `[ESP+0x08]` is three zeroed dwords. Method name from YRpp.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_CRC_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_CRC_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/sha_pipe_layout.h"

// VTABLE: GAMEMD 0x7E4D78 — the hash engine's vtable (installed inline).
extern char VT_007E4D78;

// The SHA-1 engine as built on the stack. Constructed inline by the caller,
// torn down by the out-of-line destructor.
typedef SHAPipeLayout SHA_00476D80;

#include "_layout/crc_00476d80.h"

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_CRC_METHODS_H
