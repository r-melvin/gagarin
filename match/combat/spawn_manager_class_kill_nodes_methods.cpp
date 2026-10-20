// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6B7100.

#include "spawn_manager_class_kill_nodes_methods.h"

// FUNCTION: GAMEMD 0x6B7100
//
// Kill every spawned unit and put its node into the dead state with a fresh
// respawn countdown — immediate when the owner is still alive and flagged,
// otherwise the regen rate. Walking the nodes from the top: a node already
// dead is left alone; an idle or returning unit (0, 6) is simply taken off
// the map; a unit on a kamikaze run (1) is first withdrawn from the
// kamikaze manager; anything else is handed to the kamikaze manager against
// the current target instead of being removed.
void SpawnManager_006B7100::KillNodes()
{
    int duration;
    if (Owner->Health > 0 && Owner->At_90 != 0) {
        duration = 0;
    } else {
        duration = RegenRate;
    }

    for (int i = Count - 1; i >= 0; --i) {
        SpawnControl_006B7100* node = Items[i];
        int status = node->Status;
        if (status != 7) {
            if (status == 0 || status == 6) {
                node->Status = 7;
                (Items[i]->Unit->*Items[i]->Unit->Vtbl->At_F8)();
                Items[i]->Unit = 0;
                Items[i]->Timer = CDTimer_006B7100(duration);
            } else if (status == 1) {
                DAT_00ABC5F8.Remove(node->Unit);
                Items[i]->Status = 7;
                (Items[i]->Unit->*Items[i]->Unit->Vtbl->At_F8)();
                Items[i]->Unit = 0;
                Items[i]->Timer = CDTimer_006B7100(duration);
            } else {
                node->Status = 7;
                DAT_00ABC5F8.Add(Items[i]->Unit, Target);
                Items[i]->Unit = 0;
                Items[i]->Timer = CDTimer_006B7100(duration);
            }
        }
    }
}
