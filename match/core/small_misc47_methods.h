// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, slot displacements and CRT helper addresses read numerically off
//   the user's retail gamemd.exe v1.001 via the local Ghidra CLI at 0x412610
//   and 0x41D7E0.
#ifndef GG_MATCH_CORE_SMALL_MISC47_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC47_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// 0x412610 — parse a hexadecimal string.
//
// The two CRT helpers are identified by their use: 0x7C99B4 gates the loop on
// each character and 0x7C97D3 folds a letter's case before the 0x37 subtraction,
// i.e. `isxdigit` and `toupper`. Both take an `int`, which is why retail
// sign-extends the character with `MOVSX` at each call.
//
// The loop condition is the pointer, not the digit test: retail re-tests EDI at
// the bottom (`TEST EDI,EDI; JNZ`) even though it was just incremented, and the
// non-digit exit is a `break` inside the body.
// ---------------------------------------------------------------------------
extern "C" int __cdecl FUN_007C99B4(int c);   // isxdigit
extern "C" int __cdecl FUN_007C97D3(int c);   // toupper

// FUNCTION: GAMEMD 0x412610
int FUN_00412610(const char* text);

// ---------------------------------------------------------------------------
// 0x41D7E0 — "has this entry come due, or has its target changed?"
//
// Which of the two delays applies is decided by 0x750010 against the object at
// +0x4C offset by 0x150; retail branches for it rather than using a
// conditional move. When the suppression flag at +0x3C is clear and the deadline
// has passed the answer is an outright yes, otherwise it falls through to
// comparing the argument against +0x50.
// ---------------------------------------------------------------------------
// GLOBAL: GAMEMD 0xA8ED84 — the engine frame counter.
#include "../core/frame_counter.h"

// FUNCTION: GAMEMD 0x750010 — the mode test, __fastcall, byte result.
bool FUN_00750010(void* subject);

struct Obj_0041D7E0
{
    char  _pad000[0x3C];
    char  Suppressed;   // +0x003C
    char  _pad03D[0x40 - 0x3D];
    int   Start;        // +0x0040
    int   DelayA;       // +0x0044
    int   DelayB;       // +0x0048
    char* Subject;      // +0x004C
    int   Target;       // +0x0050

    // FUNCTION: GAMEMD 0x41D7E0
    bool FUN_0041D7E0(int candidate);
};
GG_STATIC_ASSERT(offsetof(Obj_0041D7E0, Suppressed) == 0x3C);
GG_STATIC_ASSERT(offsetof(Obj_0041D7E0, Start) == 0x40);
GG_STATIC_ASSERT(offsetof(Obj_0041D7E0, Subject) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_0041D7E0, Target) == 0x50);

#endif  // GG_MATCH_CORE_SMALL_MISC47_METHODS_H
