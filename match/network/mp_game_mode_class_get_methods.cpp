// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5D5F30.

#include "mp_game_mode_class_get_methods.h"

// GLOBAL: GAMEMD 0xABFDA0 — the game-mode vector, a function-local static
// behind the guard byte at 0xABFD70. Each inline expansion of the accessor
// carries its own copy of the guard, which is why retail constructs the same
// object at two sites inside the loop (and again in 0x5D6130). cl 8804 will
// not inline a function holding a static local unless forced, so the accessor
// is __forceinline; the retail compiler evidently inlined it unprompted.
static __forceinline ModeVector_005D5F30& Modes_005D5F30()
{
    static ModeVector_005D5F30 modes;
    return modes;
}

// FUNCTION: GAMEMD 0x5D5F30
//
// Find the game mode whose identifier matches, or null. The loop reads the
// static through the accessor twice per pass — once for the count in the
// condition, once for the item — so the guard is expanded twice and the loop
// is not rotated (retail's `JMP` back to the guard at the head).
//
// PARTIAL (79.3%, 46/58; mnemonic multiset differs only by push,push,call vs
// three movs). Retail's first guard copy calls the VectorClass base ctor out
// of line (`PUSH EBX; PUSH EBX; MOV ECX,0xABFDA0; CALL 0x5D89F0`) while its
// second copy has that ctor inlined with size folded to zero; cl 8804 makes
// one decision for both expansions. With the base ctor declared only, both
// sites call (77.6%, first site exact); defined inline (this form), both
// sites fold it (79.3%, second site exact). Everything else — the hoisted
// 0x7EED20 / 10 / 0 registers, the guard byte sequence, the atexit push
// order, the spilled __fastcall argument, the loop shape and the epilogue —
// is byte-identical. Tried: a plain static accessor (not inlined at all:
// cl emits a call), `inline` and in-class static member accessors (same as
// __forceinline), a static declared directly in Get (one guard, rotated
// loop), a real base class with its own destructor (blocks inlining of the
// derived ctor entirely), a flat single struct with a BaseInit member,
// `#pragma inline_depth(2|3)`, an extra inline layer at either site, and
// bloating the dead allocation path of the base ctor: none moves the
// per-site decision. Recorded as a suspected 8447-vs-8804 inliner difference.
MultiplayerGameMode_005D5F30* __fastcall MultiplayerGameMode_Get(int index)
{
    int i;

    for (i = 0; i < Modes_005D5F30().Count; i++) {
        MultiplayerGameMode_005D5F30* mode = Modes_005D5F30().Items[i];
        if (mode->At_28 == index) {
            return mode;
        }
    }
    return 0;
}
