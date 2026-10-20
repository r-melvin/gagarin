// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x724730.

#include "tooltip_manager_remove_methods.h"

// FUNCTION: GAMEMD 0x724730  ToolTipManager::Remove (__thiscall, ret 4)
//
// Retire the tool tip filed under a key. Nothing happens when the table is
// empty or the key is not in it. Otherwise: if the tip being retired is the
// one currently on screen, the manager is asked to take it down; the key's
// entry is cut out of the sorted table (the tail slid down, the freed slot
// zeroed and the cache dropped); the tip pointer is taken out of the
// manager's own vector; and the tip itself is released.
void ToolTipManager_00724730::Remove(unsigned int key)
{
    ToolTipTable_00724730* t = &this->Table;
    if (this->Table.Count == 0) {
        return;
    }
    if (!t->Ensure(key)) {
        return;
    }

    ToolTipData_00724730* data = t->GetTip(key);

    if (this->At_4 == data && this->At_4 != 0) {
        (this->*this->Vptr->At_8)(&this->At_18);
    }

    t->RemoveEntry(data);

    this->Vec.RemoveItem(data);

    if (data != 0) {
        gg_free(data);
    }
}
