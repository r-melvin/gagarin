// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x404DD0.

#include "small_misc45_methods.h"

// FUNCTION: GAMEMD 0x404D80
void __fastcall FUN_00404D80(Obj_00404D80* self)
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
void __fastcall FUN_00404DD0(Obj_00404DD0* self)
{
    FUN_00407450(self);

    // Volatile: the flag load has no dependency on this store, so plainly
    // written VC6 schedules it first; retail clears +0x138 before reading
    // +0x18.
    *(volatile int*)&self->Pending = 0;

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
// SCHEDULING DELTA (status partial, 94.9% - 37/39). One instruction is in the
// wrong place: retail materialises the table base (`MOV EBX,0x87DE38`) between
// the row-count test and its `JLE`, and we emit it after the `JLE`. Everything
// else, both loop rotations and the 0xA4 bias included, is exact. Holding the
// base in a named local, indexing the global directly, flattening to a single
// header array, and driving both loops on walking pointers all give the same
// 94.9%, so the placement is register-allocator state rather than source order.
//
// The loop-rotation lever was measured here and this is the case its
// precondition excludes. Retail's outer back edge is already a conditional
// `CMP EBP,EAX; JL`, i.e. a bottom-tested loop cl reaches from a plain `for`.
// Writing the peel out literally - `if (row < rows) { do { ... } while (row <
// rows); }` - inverts the layout and costs 42 points (52.5%), and so does the
// same peel on both loops, on a walked row pointer (55.0%), or with the table
// re-derived at the subscript. Hoisting the guard to `if (rows > 0)` around the
// whole body is 9.8%. The plain `for` is the best measured form.
void* __fastcall FUN_00404E20(int rows)
{
    Row_00404E20* table = DAT_0087DE38;

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < 10; column++) {
            ListNode* node = (&table[row].Headers[column])->FUN_004073C0();

            if (node) {
                return (char*)node - 0xA4;
            }
        }
    }

    return 0;
}
