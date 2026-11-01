// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at 0x404DD0.

#include "small_misc45_methods.h"

// FUNCTION: GAMEMD 0x404D80
void FUN_00404D80(Obj_00404D80* self)
{
    int i = 0;

    if (i < self->Count) {
        void** slot = self->Slots;

        do {
            FUN_00401F90(*slot);

            *slot = 0;

            i++;
            slot++;
        } while (i < self->Count);
    }

    self->Count = 0;
}

// FUNCTION: GAMEMD 0x404DD0
void FUN_00404DD0(Obj_00404DD0* self)
{
    FUN_00407450(self);

    // PARTIAL: VC6 schedules the flag load ahead of this store; retail clears
    // +0x138 before reading +0x18. Not steered.
    self->Pending = 0;

    if (*(unsigned char*)&self->Flags & 0x80) {
        FUN_007C8B3D(self);

        DAT_0087E28C--;

        return;
    }

    FUN_00407530(DAT_0087E2A8, self);

    DAT_0087E28C--;
}

// FUNCTION: GAMEMD 0x404E20
//
// Walk the ten-header rows in order and return the owning object of the first
// non-empty header (node - 0xA4), or 0 if every header is empty.
//
// Second-look result: 100% (raw bytes identical). The row cursor is a walking
// pointer advanced with the row counter (`row++, cursor++`) while the columns are
// indexed off it. Retail's table base then lands in its register ahead of the
// row-count branch. Earlier notes: a bottom-tested peel of either loop, a
// hoisted `rows > 0` guard and a table re-derived at the subscript were all far
// worse; the plain `for` shape is right.
void* FUN_00404E20(int rows)
{
    Row_00404E20* cursor = DAT_0087DE38;

    for (int row = 0; row < rows; row++, cursor++) {
        for (int column = 0; column < 10; column++) {
            ListNode* node = cursor->Headers[column].FUN_004073C0();

            if (node) {
                return (char*)node - 0xA4;
            }
        }
    }

    return 0;
}
