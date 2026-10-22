// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC11_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC11_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A dispatch table of zero-argument __thiscall slots hung off +0xD4, and a flag
// word at +0xA4. 0x4026C0 and 0x4026F0 differ only in whether they set or clear
// bit 4, so they are the on/off pair for one property.
struct Obj_004026C0;
typedef void (__fastcall* DispSlot)(Obj_004026C0*);

struct Obj_004026C0
{
    char  _pad000[0xA4];
    int   Flags;      // +0x00A4
    char  _padA8[0xD4 - 0xA8];
    char* Dispatch;   // +0x00D4

    // FUNCTION: GAMEMD 0x4026C0
    void FUN_004026C0();
    // FUNCTION: GAMEMD 0x4026F0
    void FUN_004026F0();
};
GG_STATIC_ASSERT(offsetof(Obj_004026C0, Flags) == 0xA4);
GG_STATIC_ASSERT(offsetof(Obj_004026C0, Dispatch) == 0xD4);

#define DISP(o, off) ((*(DispSlot*)((o)->Dispatch + (off)))(o))


struct Obj_004085B0
{
    char _pad00[0x4];
    int  Mode;         // +0x0004
    int  unknown_08;   // +0x0008
    int  unknown_0C;   // +0x000C
    int  unknown_10;   // +0x0010
    int  unknown_14;   // +0x0014

    // FUNCTION: GAMEMD 0x4085B0
    void FUN_004085B0();
};
GG_STATIC_ASSERT(offsetof(Obj_004085B0, unknown_14) == 0x14);

#endif  // GG_MATCH_CORE_SMALL_MISC11_METHODS_H
