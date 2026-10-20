// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x42DF40.

#include "pending_flush_methods.h"

// FUNCTION: GAMEMD 0x42DF40
//
// Flush whatever is pending through one of two codecs and report the total
// queued afterwards. With nothing pending both the encode and the hand-off are
// skipped and only the queued total is returned.
//
// The two branches mirror each other: each passes one of +0x14 / +0x18 as the
// codec's receiver and the other as the output buffer, and the buffer is the one
// handed on afterwards. Retail keeps it in EDI across the join, so it is a local
// assigned in both arms rather than being recomputed after the branch.
int Obj_0042DF40::FUN_0042DF40()
{
    int encoded = 0;

    if (this->Pending != 0) {
        void* buffer;
        int written;

        if (this->Mode == 0) {
            buffer = this->At_14;
            written = FUN_0042FD30(this->At_18, this->Pending, buffer, 4);
        } else {
            buffer = this->At_18;
            written = FUN_0042FE50(this->At_14, this->Pending, buffer, 3);
        }

        encoded = this->FUN_00631D10(buffer, written);
        this->Pending = 0;
    }

    return this->FUN_00631D30() + encoded;
}
