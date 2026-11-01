// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x408D80.

#include "aligned_alloc_methods.h"

// FUNCTION: GAMEMD 0x408D80
//
// MATCHED (100%, 51/51, was 98.0%). The residual was one SIB byte: retail's
// `LEA EDX,[EDI+EAX*1-0x1]` makes the alignment the base and the pointer the
// index, and reusing the named `align` local here emitted `[EAX+EDI*1-0x1]`
// with the roles swapped. The lever is *re-deriving* the alignment at the use
// site - writing `(1 << shift)` again in the round-up instead of naming it -
// which makes the shift result the LEA's base exactly as retail has it. The
// named local is still what the allocation size uses, so cl computes the shift
// once and the source reads as two uses of one expression rather than one use
// of a local.
//
// This is the inverse of the name-the-load lever, and it is not reachable by
// reordering the addition: seven other spellings all sat at 98.0% - the
// alignment cast to a pointer so it is the pointer operand, the pointer plus
// the alignment, the sum named before the mask, the bias `align - 1` named,
// the mask named first, and the bias parenthesised onto the pointer.
//
// The same lever then took 0x4074D0 from 96.3% to 100%.
Aligned_00408D80* FUN_00408D80(int size, int shift)
{
    Aligned_00408D80* node = (Aligned_00408D80*)FUN_007C8E17(0x3C);

    memset(node, 0, 0x3C);

    FUN_004072D0(node);

    int align = 1 << shift;

    void* raw = FUN_007C8E17(align + size);

    node->Raw = raw;

    if (raw == 0) {
        if (node) {
            FUN_007C8B3D(node);
        }

        return 0;
    }

    node->Shift   = shift;
    node->Size    = size;
    node->Aligned = ((1 << shift) + (int)raw - 1) & (-1 << shift);

    return node;
}
