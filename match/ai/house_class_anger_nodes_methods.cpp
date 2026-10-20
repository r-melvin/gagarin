// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x504790. Name from
//   YRpp HouseClass.h (consult-only).

#include "house_class_anger_nodes_methods.h"

// FUNCTION: GAMEMD 0x504790
//
// Add `scoreAdd` to the anger level of every node tracking `house`, then
// re-pick the enemy: the angriest node whose house is not defeated and not an
// ally (the ally test is the 0x4F9A50 overload inlined). The winner's array
// index lands in EnemyHouseIndex, or -1 when no node qualifies.
void House_00504790::UpdateAngerNodes(int scoreAdd, House_00504790* house)
{
    int i;

    for (i = 0; i < this->AngerNodes.Count; i++) {
        if (this->AngerNodes.Items[i].House == house)
            this->AngerNodes.Items[i].AngerLevel += scoreAdd;
    }

    House_00504790* best = 0;
    int bestLevel = 0;

    for (i = 0; i < this->AngerNodes.Count; i++) {
        int level = this->AngerNodes.Items[i].AngerLevel;
        House_00504790* h = this->AngerNodes.Items[i].House;
        if (level > bestLevel && !h->Defeated && !this->IsAlliedWith(h)) {
            bestLevel = level;
            best = h;
        }
    }

    if (best != 0)
        this->EnemyHouseIndex = best->ArrayIndex;
    else
        this->EnemyHouseIndex = -1;
}
