// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
// RTTI: vtable 0x7ED37C names .?AVLZOPipe@@ (COL before the table). Table
// words [0x55C6D0, 0x55C5E0, 0x477740, 0x631CC0, 0x55C350]: slot +0x10 is
// the Put override at 0x55C350. Member offsets from 0x55C350: `[ESI+0xC]`
// compared with 1 (mode), `[ESI+0x10]` staged count, `[ESI+0x14]`/`[ESI+0x18]`
// staging and output buffers, `[ESI+0x1C]` block size, words +0x24/+0x26
// of the block header (compressed count, reset to 0xFFFF; uncompressed count).
#ifndef GG_MATCH_CORE_LZ_PIPE_H
#define GG_MATCH_CORE_LZ_PIPE_H

#include "../_layout/pipe.h"

// The vendored wrapper exports both public entry points as __fastcall.
#define __LZO_ENTRY __fastcall
#include "../../third_party/lzo/lzo-1.00/include/lzoconf.h"
#include "../../third_party/lzo/lzo-1.00/include/lzo1x.h"
#undef __LZO_ENTRY

#include "../platform/compression_straws.h"

#endif
