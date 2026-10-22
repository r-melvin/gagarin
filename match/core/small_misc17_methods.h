// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC17_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC17_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7E16B0
extern char VT_007E16B0[];

struct Obj_00473A80;
void FUN_0047AA30(Obj_00473A80* self);   // GAMEMD 0x47AA30

// __thiscall with both arguments pushed.
struct Sub_0043AD00 { void FUN_0043AD00(int a, int b); };   // GAMEMD 0x43AD00

struct Obj_00473A80
{
    char           _pad00[0x58];
    Sub_0043AD00   Sub;          // +0x0058
    char           _pad5C[0x64 - 0x5C];
    int            unknown_64;   // +0x0064
    int            unknown_68;   // +0x0068

    // FUNCTION: GAMEMD 0x473A80
    Obj_00473A80* FUN_00473A80();
};
GG_STATIC_ASSERT(offsetof(Obj_00473A80, Sub) == 0x58);
GG_STATIC_ASSERT(offsetof(Obj_00473A80, unknown_68) == 0x68);

// A zero-argument virtual at +0x30 returning a pointer.
struct Provider_004103E0;
typedef char* (* Slot30)(Provider_004103E0*);
#define SLOT_30(p) ((*(Slot30*)(*(char**)(p) + 0x30))(p))

// FUNCTION: GAMEMD 0x4103E0 — publish the provider's buffer, skipping its
// four-byte header, and clear the companion word.
long __stdcall FUN_004103E0(Provider_004103E0* provider, void** out);

#endif  // GG_MATCH_CORE_SMALL_MISC17_METHODS_H
