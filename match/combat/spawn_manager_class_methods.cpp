// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp SpawnManagerClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6B7B90  SpawnManagerClass::SetTarget         (__thiscall)
//   FUNCTION: GAMEMD 0x6B7D30  SpawnManagerClass::CountAliveSpawns  (__thiscall)
//   FUNCTION: GAMEMD 0x6B7D50  SpawnManagerClass::CountDockedSpawns (__thiscall)

#include "spawn_manager_class_methods.h"

// FUNCTION: GAMEMD 0x6B7B90  (__thiscall)
// Record a pending target. If it already equals the live Target, do nothing;
// otherwise stash it in NewTarget for the next UpdateTarget pass.
void SpawnManagerClass::SetTarget(AbstractClass* pTarget)
{
    if (pTarget != Target)
        NewTarget = pTarget;
}

// FUNCTION: GAMEMD 0x6B7D30  (__thiscall)
// Count spawn nodes that are not Dead (Status != 7).
int SpawnManagerClass::CountAliveSpawns() const
{
    int count = 0;
    int n = SpawnedNodes_Count;
    if (n > 0) {
        SpawnControl** node = SpawnedNodes_Items;
        do {
            if ((*node)->Status != 7)
                ++count;
            ++node;
            --n;
        } while (n != 0);
    }
    return count;
}

// FUNCTION: GAMEMD 0x6B7D50  (__thiscall)
// Count docked spawn nodes: Reloading (Status == 6) or Idle (Status == 0).
int SpawnManagerClass::CountDockedSpawns() const
{
    int count = 0;
    int n = SpawnedNodes_Count;
    if (n > 0) {
        SpawnControl** node = SpawnedNodes_Items;
        do {
            int status = (*node)->Status;
            if (status == 6 || status == 0)
                ++count;
            ++node;
            --n;
        } while (n != 0);
    }
    return count;
}
