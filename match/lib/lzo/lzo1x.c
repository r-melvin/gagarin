/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Provenance: vendored-third-party (LZO 1.00, GPL-2.0-or-later, third_party/lzo/) + own-binary-via-Ghidra */
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /D__LZO_ENTRY= /U_M_IX86 /Dlzo_moff_t=lzo_ptrdiff_t /Dlzo_cmoff_t=lzo_ptrdiff_t /I../../../third_party/lzo/lzo-1.00/include
//   Build wrapper for the vendored LZO 1.00 LZO1X-1 sources. The sources are
//   included unmodified; every configuration difference from upstream is a
//   flag on the line above (see third_party/lzo/MODIFICATIONS):
//   - /Gr with an empty __LZO_ENTRY: the public entry points are __fastcall
//     (retail passes in/in_len in ECX/EDX and returns with RET 0xC);
//   - /U_M_IX86: no unaligned-access fast paths (retail copies byte by byte);
//   - lzo_moff_t/lzo_cmoff_t = lzo_ptrdiff_t: signed match offsets (the jle/jg
//     compares in 0x55BC00).
//   One C object: the retail Rich header lists exactly one Utc12_C 8447
//   object, so both upstream files are compiled as one translation unit.
//
//   0x55C0E0 is the LZO1X decoder but LZO 1.00's lzo1x_d1.c does not
//   reproduce it (5.3% positional; same algorithm and constants, different
//   literal-run code and block layout). It stays partial until the source
//   version that produced it (1.01/1.02 or a local edit) is found.

// FUNCTION: GAMEMD 0x55BB90
// lzo1x_1_compress (third_party/lzo/lzo-1.00/src/lzo1x_c.ch via lzo1x_1.c)

// FUNCTION: GAMEMD 0x55BC00
// do_compress (static, same file)
#include "../../../third_party/lzo/lzo-1.00/src/lzo1x_1.c"

// FUNCTION: GAMEMD 0x55C0E0
// lzo1x_decompress (third_party/lzo/lzo-1.00/src/lzo1x_d.ch via lzo1x_d1.c)
#include "../../../third_party/lzo/lzo-1.00/src/lzo1x_d1.c"
