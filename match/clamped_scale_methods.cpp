// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4061D0.

#include "clamped_scale_methods.h"

// Clamp to 0..0x4000. Retail duplicates this per branch, which is what an
// inline helper called from each branch gives; written out inline in each
// branch (or hoisted before the mode test) VC6 loads the mode into ESI and
// hoists the `PUSH ESI` to the prologue.
static inline unsigned Clamp_004061D0(unsigned level)
{
    unsigned clamped = level;
    if (level > 0x4000) {
        clamped = 0x4000;
    } else if ((int)level < 0) {
        clamped = 0;
    }
    return clamped;
}

// FUNCTION: GAMEMD 0x4061D0
//
// Scale a clamped level by the rate and hand it to the mode-3 setter (a
// tail-jump to 0x407170) or to the set-then-notify pair (0x407150 by `CALL`,
// 0x4071C0 by tail-jump).
//
// Three things decide the bytes here: the clamp is an inline helper called
// once per branch (a shared `clamped` local hoists the ESI save to the
// prologue), the second branch is an inlined `Sink::Set` so its `PUSH ESI`
// sits inside the branch, and 0x4071C0 is declared __fastcall — as a
// __thiscall member VC6 emits `CALL; POP ESI; RET` instead of retail's
// `POP ESI; JMP`.
int AudioEvent::FUN_004061D0(unsigned level)
{
    if (State == 3) {
        return FUN_00407170(&Sink.Timer,
                            (EventType->Volume.Value >> 16) * Clamp_004061D0(level) >> 14);
    }

    return Sink.Set((EventType->Volume.Value >> 16) * Clamp_004061D0(level) >> 14);
}
