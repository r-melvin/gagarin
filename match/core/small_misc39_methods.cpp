// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4074D0 and 0x4589C0.

#include "small_misc39_methods.h"

// FUNCTION: GAMEMD 0x4074D0
//
// MATCHED (100%, 27/27, was 96.3%). The residual was one SIB byte: retail's
// `LEA EDX,[EDI+ECX*1]` makes the stride the base and the cell the index, and
// reusing the named `stride` local emitted `LEA EDX,[ECX+EDI*1]` with the
// roles reversed. Reordering the addition does nothing (`stride + cell`,
// `cell + stride`, and both orders with the address held as an `unsigned`, all
// 96.3%). The lever is *re-deriving* the stride at the use site: writing
// `(elementSize + 8) + cell` inside the loop makes the addend the LEA base.
// Dropping the named local entirely and re-deriving it at both use sites also
// reaches 100%, and so does the re-derived form with the cell written first;
// only the spellings that name the stride at the addition stay at 96.3%. Same
// lever, found the same day, as 0x408D80.
void* FUN_004074D0(int count, int elementSize)
{
    int stride = elementSize + 8;

    void* block = FUN_007C8E17(stride * count + 8);

    // A failed allocation shares the epilogue with the success path rather than
    // returning early: retail's `JZ` at 0x4074EA jumps to the same
    // `POP EDI; POP ESI; RET` the loop falls into, with the null still in EAX.
    if (block != 0) {
        // The remaining-count guard is `TEST EDX,EDX; JBE`, an *unsigned* test, so
    // the counter is unsigned - a signed `> 0` would emit `JLE`.
        unsigned remaining = (unsigned)(count - 1);
        char*    cell      = (char*)block + 8;

        *(char**)block = cell;

        while (remaining > 0) {
            char* next = (elementSize + 8) + cell;

            remaining--;

            *(char**)cell = next;
            cell = next;
        }

        *(char**)cell = 0;
    }

    return block;
}


// FUNCTION: GAMEMD 0x4349B0
int Obj_004349B0::FUN_004349B0(unsigned short index)
{
    // All three refusals share the one `XOR EAX,EAX; RET 4` at 0x4349E7, so
    // they nest down to a single trailing `return 0` rather than exiting early
    // three times - written as three early returns VC6 emits three copies of
    // that tail and scores 7.7%.
    Sub_004349B0* sub = Sub;

    if (sub != 0) {
        unsigned int slot = sub->Table[index];

        if (slot != 0) {
            unsigned char* record = sub->Base + sub->Stride * (slot - 1);

            if (record != 0) {
                return *record;
            }
        }
    }

    return 0;
}
