// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small leaf functions read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI
//   at the address in each annotation. Receivers are placeholder views named after their address.
//   Address index: 0x6DA360.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x6DA360
// Copies the dword at src to dst and returns dst; the third argument is ignored.
int* __stdcall FUN_006DA360(int* dst, int* src, int unused)
{
    *dst = *src;
    return dst;
}
