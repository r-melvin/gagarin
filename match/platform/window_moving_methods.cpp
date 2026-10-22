// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x776D80 (name from the
//   YRpp method map).

#include "window_moving_methods.h"

// FUNCTION: GAMEMD 0x776D80
//
// WM_MOVING handler: clamp the proposed window rectangle to the primary
// screen, preserving its size. A negative left/top is shifted to zero; a
// right/bottom beyond the screen slides the rectangle back so its far edge
// sits on the screen edge. Returns whether anything was adjusted. Each
// GetSystemMetrics result is re-queried rather than cached, as retail does.
// The last clause returns true directly (retail's `MOV AL,1` sits before the
// register pops on that path, after them on the shared path).
//
// PARTIAL (95.1%, 58/61). The whole body and both epilogues' instruction
// multisets match; the residual is the placement of the final `MOV AL,1`.
// Retail: `MOV [ESI+0xC],EAX; MOV AL,1; POP EDI; POP ESI; POP EBX; RET 4`.
// Ours:   `MOV [ESI+0xC],EAX; POP EDI; POP ESI; MOV AL,1; POP EBX; RET 4`.
// The shared `POP EDI; MOV AL,BL; POP ESI; POP EBX` tail interleaves the same
// way in both builds, so this is the pop-interleave scheduling class already
// recorded for MixFileClass::Bootstrap @0x5301A0 and BounceClass::GetCoords
// @0x4399A0. Variants tried, all 95.1% unless noted: `return true` in the
// last clause (kept), flag-then-fallthrough `moved = true; return moved`,
// `if/else` with the false path returning early, inverted last guard with an
// early `return moved` (72.1%, flips JLE to JG), `char` flag / `char` return
// with `return 1`, `return moved = true`, a `goto done` merge, hoisted
// metric temporaries, an `if (moved) return true; return false` tail
// (77.9%), and the flag sets `/Ox`, `/O2 /Ob1`, `/Og /Oi /Ot /Oy /Ob1` (all
// 95.1%) and `/O1` (18.0%). An inline-`_asm` epilogue forces an EBP frame
// (7.4%), so it is not an option here.
// This pass re-tested it against the flattened-function-boundary lever that
// resolved BuildingClass::CheckFog @0x457A10, and none of it moves: the whole
// body lifted into an inline helper with the wrapper forwarding it
// (`return ClampAll(rect);`, 95.1%); the same helper with the wrapper spelled
// `if (ClampAll(rect)) { return true; } return false;` (77.9%, the helper's
// last clause inverted into an early return); the last clause returning
// through a trivial `AlwaysTrue()` inline helper to give the block a second
// predecessor (95.1%); the last clause setting the flag and returning it
// (95.1%); and the last clause setting the flag *and* returning the literal
// (95.1%). The `MOV AL,1` stays between the pops.
bool __stdcall OnWindowMoving(Rect_00776D80* rect)
{
    bool moved = false;

    if (rect->left < 0) {
        rect->right -= rect->left;
        rect->left = 0;
        moved = true;
    }
    if (rect->top < 0) {
        rect->bottom -= rect->top;
        rect->top = 0;
        moved = true;
    }
    if (rect->right > GetSystemMetrics(0x10)) {
        rect->left += GetSystemMetrics(0x10) - rect->right;
        rect->right = GetSystemMetrics(0x10);
        moved = true;
    }
    if (rect->bottom > GetSystemMetrics(0x11)) {
        rect->top += GetSystemMetrics(0x11) - rect->bottom;
        rect->bottom = GetSystemMetrics(0x11);
        return true;
    }
    return moved;
}
