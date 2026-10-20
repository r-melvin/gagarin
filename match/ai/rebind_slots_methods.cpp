// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x472330.

#include "rebind_slots_methods.h"

// FUNCTION: GAMEMD 0x472330
//
// Find the item whose type carries the current selection value, then point every
// slot holding the given key at it. Reports whether anything was rebound.
//
// Three things decide the bytes. The list count is read *before* the selection
// call (retail's `MOV ESI,[0xA80238]` precedes `CALL 0x6A46D0`), which is what
// puts the count in ESI and the walk cursor in EDX. The search is a plain
// indexed loop over the global — `DAT_00A8022C[i]` in both the compare and the
// found re-index — so VC6 loads the list base into EBX inside the preheader,
// after the `count <= 0` test, and strength-reduces the compare into the
// `ADD EDX,4` cursor; a cursor local initialised before the loop hoists that
// load above the test (90.6%). And the found path is `item = ...; break;`
// with one `if (item == 0) return false;` after the loop: the not-found exit
// and the null-item exit then come out as retail's two separate false tails
// (0x472369 and 0x472379), where a `return false` inside the found body is
// cross-jumped into the loop's exit (45.3%).
//
// The slot walk runs backwards and re-reads both the key parameter and the slot
// array on every iteration — retail reloads `[ESP+0x14]` and `[EDI+0x28]` inside
// the loop rather than holding either.
bool Obj_00472330::FUN_00472330(int key)
{
    int count = DAT_00A80238;
    int wanted = DAT_00818164.FUN_006A46D0();
    Item_00472330* item = 0;
    for (int i = 0; i < count; i++) {
        if (DAT_00A8022C[i]->Type->At_BC == wanted) {
            item = DAT_00A8022C[i];
            break;
        }
    }
    if (item == 0) {
        return false;
    }
    for (int j = this->SlotCount - 1; j >= 0; j--) {
        Slot_00472330* slot = this->Slots[j];
        if (slot->Key == key) {
            slot->Value = item;
        }
    }
    return true;
}
