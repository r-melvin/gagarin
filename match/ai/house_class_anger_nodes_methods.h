// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x504790: the anger-node vector's items at
//   `[this+0x5608]` and count at `[this+0x5614]` (8-byte nodes, `[ECX+EDX*8]`
//   house then `[ECX+4]` level); the house's ArrayIndex `[EDX+0x30]` /
//   `[EAX+0x30]`, its byte `[EDX+0x1F5]`, the ally bit mask `[EAX+0x5788]`
//   tested against `1 << index`, and the result stored at `[this+0x5600]`
//   (-1 when nothing qualifies). The inlined ally test is the same body as
//   HouseClass::IsAlliedWith(HouseClass const*) at 0x4F9A50
//   (match/economy/house_class_ally_methods.cpp). Method name from YRpp
//   HouseClass.h (consult-only; name only).
#ifndef GG_MATCH_AI_HOUSE_CLASS_ANGER_NODES_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_ANGER_NODES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct House_00504790;

// One anger node: the house being tracked and how angry we are at it.
struct AngerNode_00504790
{
    House_00504790* House;        // +0x0000
    int             AngerLevel;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(AngerNode_00504790, AngerLevel) == 0x04);
GG_STATIC_ASSERT(sizeof(AngerNode_00504790) == 0x08);

// DynamicVectorClass<AngerNode> — only Items and Count are touched here.
struct AngerVector_00504790
{
    void*               Vtbl;            // +0x0000
    AngerNode_00504790* Items;           // +0x0004
    int                 Capacity;        // +0x0008
    char                IsInitialized;   // +0x000C
    char                IsAllocated;     // +0x000D
    char                _pad00E[2];      // +0x000E
    int                 Count;           // +0x0010
};
GG_STATIC_ASSERT(offsetof(AngerVector_00504790, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(AngerVector_00504790, Count) == 0x10);

struct House_00504790
{
    char                 _pad0000[0x30];               // +0x0000
    int                  ArrayIndex;                   // +0x0030
    char                 _pad0034[0x1F5 - 0x34];       // +0x0034
    char                 Defeated;                     // +0x01F5
    char                 _pad01F6[0x5600 - 0x1F6];     // +0x01F6
    int                  EnemyHouseIndex;              // +0x5600
    AngerVector_00504790 AngerNodes;                   // +0x5604
    char                 _pad5618[0x5788 - 0x5618];    // +0x5618
    int                  Allies;                       // +0x5788

    // Same body as the retail 0x4F9A50 overload; expanded inline here.
    bool IsAlliedWith(House_00504790 const* pHouse) const
    {
        if (pHouse) {
            if (pHouse == this) return true;
            if (pHouse->ArrayIndex == this->ArrayIndex) return true;
            if (pHouse->ArrayIndex != -1) {
                bool allied = (this->Allies & (1 << pHouse->ArrayIndex)) != 0;
                return allied;
            }
        }
        return false;
    }

    // FUNCTION: GAMEMD 0x504790 — HouseClass::UpdateAngerNodes.
    void UpdateAngerNodes(int scoreAdd, House_00504790* house);
};
GG_STATIC_ASSERT(offsetof(House_00504790, ArrayIndex) == 0x30);
GG_STATIC_ASSERT(offsetof(House_00504790, Defeated) == 0x1F5);
GG_STATIC_ASSERT(offsetof(House_00504790, EnemyHouseIndex) == 0x5600);
GG_STATIC_ASSERT(offsetof(House_00504790, AngerNodes) == 0x5604);
GG_STATIC_ASSERT(offsetof(House_00504790, AngerNodes.Items) == 0x5608);
GG_STATIC_ASSERT(offsetof(House_00504790, AngerNodes.Count) == 0x5614);
GG_STATIC_ASSERT(offsetof(House_00504790, Allies) == 0x5788);

#endif  // GG_MATCH_AI_HOUSE_CLASS_ANGER_NODES_METHODS_H
