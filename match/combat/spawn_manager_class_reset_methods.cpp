// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x6B7BB0 and 0x6B7C60.

#include "spawn_manager_class_reset_methods.h"

// FUNCTION: GAMEMD 0x6B7BB0
//
// Drop the current target. Every node in the recallable state whose unit's
// type carries the flag is handed to the kamikaze manager against the old
// target, the manager's timer is restarted at two frames, and the unit is
// unlinked from this manager. Then the target, pending target and status are
// all cleared.
void SpawnManager_006B7BB0::ResetTarget()
{
    for (int i = 0; i < Count; ++i) {
        SpawnControl_006B7BB0* node = Items[i];
        if (node->Status == 2 && node->Unit->Type->At_D68 != 0) {
            DAT_00ABC5F8.Add(node->Unit, Target);
            DAT_00ABC5F8.UpdateTimer = CDTimer_006B7BB0(2);
            UnlinkPointer((AbstractClass*)Items[i]->Unit);
        }
    }

    Status = 0;
    NewTarget = 0;
    Target = 0;
}

// FUNCTION: GAMEMD 0x6B7C60
//
// Something is going away. If it was the target, drop it and, with no
// pending target either, fall back to ResetTarget; if it was the pending
// target, just forget it. Otherwise look for it among the spawned units,
// searching from the top: a unit that is still alive, not on a kamikaze run
// and whose node is not in the 1 state is left alone, any other is detached,
// marked dead and given a fresh respawn countdown. Finally, if it was the
// owner itself, every node is released and the target reset.
void SpawnManager_006B7BB0::UnlinkPointer(AbstractClass* remove)
{
    if (remove == Target) {
        Target = 0;
        if (NewTarget == 0)
            ResetTarget();
        return;
    }

    if (remove == NewTarget) {
        NewTarget = 0;
        return;
    }

    for (int i = Count - 1; i >= 0; --i) {
        if (remove == (AbstractClass*)Items[i]->Unit) {
            SpawnControl_006B7BB0* node = Items[i];
            SpawnUnit_006B7BB0* unit = node->Unit;
            if (unit->Health > 0 && unit->At_6CA == 0 && node->At_14 != 1)
                return;
            node->Unit = 0;
            Items[i]->Status = 7;
            Items[i]->Timer = CDTimer_006B7BB0(RegenRate);
            return;
        }
    }

    if (remove == Owner) {
        FUN_006B7100();
        ResetTarget();
    }
}
