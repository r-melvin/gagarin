// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5D5F30.

// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// No /GX: retail inlines the DynamicVectorClass constructor around the
// static guard with no EH frame; under /GX cl calls the whole constructor.
#include "mp_game_mode_class_get_methods.h"

// GLOBAL: GAMEMD 0xABFDA0 — the game-mode vector, a function-local static
// behind the guard byte at 0xABFD70. Each inline expansion of the accessor
// carries its own copy of the guard, which is why retail constructs the same
// object at two sites inside the loop (and again in 0x5D6130).
static inline ModeVector_005D5F30& Modes_005D5F30()
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
// PARTIAL (79.3%, 46/58). Retail's first guard copy calls the VectorClass
// base ctor out of line (`PUSH EBX; PUSH EBX; MOV ECX,0xABFDA0; CALL
// 0x5D89F0`) while its second copy has it inlined with size folded to zero;
// cl 8804 makes one decision for both expansions (both inline here). The
// canonical DynamicVectorClass template gives the same 79.3% as the earlier
// hand-written vector; see the history of this file for the variants tried.
// Also 79.3%, so no lever on that decision: the count through GetCount() (kept
// here), the count through a second inline accessor wrapping Modes, and the
// item through an inline operator[] together with GetCount().
MultiplayerGameMode* __fastcall MultiplayerGameMode_Get(int index)
{
    int i;

    for (i = 0; i < Modes_005D5F30().GetCount(); i++) {
        MultiplayerGameMode* mode = Modes_005D5F30().Items[i];
        if (mode->unknown_28 == index) {
            return mode;
        }
    }
    return 0;
}
