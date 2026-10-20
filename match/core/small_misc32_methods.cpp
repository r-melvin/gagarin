// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x408930.

#include "small_misc32_methods.h"

// REGISTER-RELEASE DELTA (status partial, 90.9% - 20/22, was 86.4%). Every
// instruction is present and in retail's order except `POP ESI`, which retail
// issues as soon as the indexed load is done and we issue after the two
// stores. Binding the loaded value to a local to end ESI's live range earlier
// does not move it.
//
// The volatile qualifiers came off the two cursor stores and that was worth
// 4.5 points: with them, cl held the pair in declared order and displaced
// three instructions; plain stores let it reorder them into retail's own
// +0x08-then-+0x04 sequence, leaving only the POP. Seven spellings were
// measured in one compile (the loaded value named, the channel named, the
// entry bound to a named pointer, the two stores swapped in source, a shared
// tail fed by a `first` local, and a volatile read of the entry); the swapped
// pair is 9.1% and the shared tail 13.6%, everything else 86.4%. Only the
// Flags clear still needs volatile, to keep its declared width.
//
// FUNCTION: GAMEMD 0x408930
// Rewind the cursor onto its source. The flag clear at the end is written once
// but appears in both arms of the disassembly - retail duplicates the tail
// rather than merging the paths.
void Cursor_00408930::FUN_00408930()
{
    // PERMUTER FINDING (score 0 at candidate 2028, base 80). Minimised to one
    // construct: the +0x04 store is made through a *pointer-to-pointer* alias
    // of the receiver. That is what releases ESI where retail releases it -
    // `POP ESI` immediately after the indexed load rather than after the two
    // stores - and it also flips the two stores into retail's +0x04-then-+0x08
    // order. A plain single-level alias (`Cursor* a = this; a->unknown_04 =`)
    // is worth nothing (80, i.e. the base), and moving the double indirection
    // onto the `Channel` read instead is also worth nothing (80). It is
    // specifically the store's receiver that has to be re-read through memory.
    Cursor_00408930* alias = this;
    Cursor_00408930** pp = &alias;

    Source_00408930* source = Source;

    unknown_2C = 0;
    unknown_0C = source;

    if (source != 0) {
        (*pp)->unknown_04 = source->Entries[Channel].First;
        unknown_08 = 0;
    } else {
        unknown_04 = 0;
        unknown_08 = 0;
    }

    // Volatile so the clear keeps its declared width: a plain `&= ~1` narrows
    // to `AND AL,0xFE` where retail uses the full dword.
    *(volatile int*)&Flags &= ~1;
}
