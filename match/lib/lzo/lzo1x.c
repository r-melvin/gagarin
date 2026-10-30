/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Provenance: vendored-third-party (LZO 1.00, GPL-2.0-or-later, third_party/lzo/) + own-binary-via-Ghidra */
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT /D__LZO_ENTRY= /U_M_IX86 /Dlzo_moff_t=lzo_ptrdiff_t /Dlzo_cmoff_t=lzo_ptrdiff_t /I../../../third_party/lzo/lzo-1.00/include
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
//   0x55C0E0 is the LZO1X decoder. The shipped decoder version is not
//   available (LZO 1.00's lzo1x_d1.c scores 5.3%, 1.03's differs in the same
//   way), so lzo1x_decompress_ww.inc is a gagarin reconstruction derived from
//   LZO 1.00's lzo1x_d.ch (see third_party/lzo/MODIFICATIONS).

// FUNCTION: GAMEMD 0x55BB90
// lzo1x_1_compress (third_party/lzo/lzo-1.00/src/lzo1x_c.ch via lzo1x_1.c)

// FUNCTION: GAMEMD 0x55BC00
// do_compress (static, same file)
#include "../../../third_party/lzo/lzo-1.00/src/lzo1x_1.c"

// FUNCTION: GAMEMD 0x55C0E0
// lzo1x_decompress (gagarin reconstruction from LZO 1.00 lzo1x_d.ch)
#include "lzo1x_decompress_ww.inc"
