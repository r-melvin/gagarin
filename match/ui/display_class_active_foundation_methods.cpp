// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4A8BF0.

#include "display_class_active_foundation_methods.h"

// FUNCTION: GAMEMD 0x4A8BF0
//
// Put a building footprint under the cursor. Any footprint already shown is
// erased at its current place, the offset is reset, and a new foundation is
// copied into the display's own static buffer, its size queried and halved
// to centre it, and the new footprint drawn.
//
// PARTIAL (49.4%, 43/87). The erase call with its by-value cell temporary,
// the offset reset from the global, the trailing null arm, the
// function-local static with its guard byte, atexit registration and
// `REP MOVSD` copy, the size query and the final draw all match. The
// residual is the halving: retail keeps the size pair in a frame slot,
// decrements both halves in place (`DEC word ptr [ESP+0x10]` twice) and
// then reloads the whole pair as a dword and negates it before sign
// extending the low half, where cl 8804 keeps the pair in registers and
// negates after sign extension; that also costs the second four-byte frame
// slot (`PUSH ECX` instead of `SUB ESP,8`), which shifts every later
// displacement. Tried: the halved cell as a by-value temporary and as a
// named local written member-wise, the null arm as an early return and as a
// trailing else, and the size query's result read through the returned
// pointer versus the out buffer.
void Display_004A8BF0::SetActiveFoundation(Foundation_004A8BF0* foundation)
{
    if (Active != 0) {
        RedrawFoundation(MakeCell_004A8BF0(Offset.X + unknown_1174.X,
                                           Offset.Y + unknown_1174.Y), 0);
    }

    Offset = DAT_008A03F8;
    if (foundation != 0) {
        static Foundation_004A8BF0 copy;
        copy = *foundation;
        Active = &copy;

        Cell_004A8BF0 size;
        Cell_004A8BF0 span = *GetFoundationSize(&size, &copy);
        span.X--;
        span.Y--;

        Cell_004A8BF0 half;
        half.X = (short)(-span.X / 2);
        half.Y = (short)(-span.Y / 2);
        Offset = half;

        RedrawFoundation(MakeCell_004A8BF0(unknown_1174.X + Offset.X,
                                           unknown_1174.Y + Offset.Y), 1);
    } else {
        Active = 0;
    }
}
