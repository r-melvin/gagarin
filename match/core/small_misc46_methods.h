// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, table extents, element strides and call targets read numerically
//   off the user's retail gamemd.exe v1.001 via the local Ghidra CLI at
//   0x42DD60, 0x433940 and 0x473980.
#ifndef GG_MATCH_CORE_SMALL_MISC46_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC46_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void* __cdecl FUN_007C8E17(unsigned int size);   // operator new
extern "C" void  __cdecl FUN_007C8B3D(void* block);         // operator delete
extern "C" void  __cdecl FUN_007C93E8(void* block);         // the other free
extern "C" int   __cdecl FUN_007C8D20(const char* a, const char* b);

// ---------------------------------------------------------------------------
// 0x42DD60 — VectorClass<unsigned short> constructor. Class identity RTTI-confirmed: vtable 0x7E3824
// -> type descriptor 0x818868 `.?AV?$VectorClass@G@@` (`G` = unsigned short). The constructor and the
// scalar deleting destructors 0x42DBB0 / 0x42DC00 are compiler output of the real template
// instantiations in small_misc46_methods.cpp.
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// 0x473980 — index of the first table entry either of whose two names matches.
//
// The table at 0x81B7C8 runs to 0x81B820, so 0x58 bytes at eight per entry:
// eleven entries of two `const char*`. A null argument, or no match, answers -1
// (`OR EAX,0xFFFFFFFF`).
// ---------------------------------------------------------------------------
struct NamePair_00473980
{
    const char* First;    // +0x0000
    const char* Second;   // +0x0004
};

// GLOBAL: GAMEMD 0x81B7C8 — eleven entries, ending at 0x81B820.
extern NamePair_00473980 DAT_0081B7C8[11];

// FUNCTION: GAMEMD 0x473980
int FUN_00473980(const char* name);

#endif  // GG_MATCH_CORE_SMALL_MISC46_METHODS_H
