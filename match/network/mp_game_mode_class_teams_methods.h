// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, the vector layout and the two callees read off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x5D6690: the vector's
//   Items/Capacity/IsAllocated/Count/CapacityIncrement at +0x04/+0x08/+0x0D/
//   +0x10/+0x14 and its slot +0x08 (Resize). YRpp
//   names the function `MPGameModeClass::CreateMPTeams` (retail: MultiplayerGameMode::CreateMPTeams) and the 12-byte MPTeam
//   whose constructor is 0x5C9470.
#ifndef GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_TEAMS_METHODS_H
#define GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_TEAMS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A 12-byte multiplayer team record; only its size and constructor matter here.
struct MPTeam_005D6690
{
    int At_00;    // +0x00
    int At_04;    // +0x04
    int At_08;    // +0x08

    // FUNCTION: GAMEMD 0x5C9470 (decl; reloc) — MPTeam constructor, called
    // explicitly on raw storage: a real `new MPTeam()` under /GX registers an
    // EH frame around the constructor that retail does not have.
    MPTeam_005D6690* Construct();
};
GG_STATIC_ASSERT(sizeof(MPTeam_005D6690) == 0x0C);

// GLOBAL: GAMEMD 0xA8B548 — number of preset teams.
extern int DAT_00A8B548;

// FUNCTION: GAMEMD 0x5C1030 (decl; reloc) — the preset team for an index.
MPTeam_005D6690* __fastcall FUN_005C1030(int index);

// DynamicVectorClass<MPTeam*>. Slot +0x08 is Resize(newCapacity, array).
struct MPTeamVector_005D6690
{
    virtual void vt_000();
    virtual void vt_004();
    virtual bool Resize(int newCapacity, void* array);   // +0x0008

    MPTeam_005D6690** Items;   // +0x0004
    int   Capacity;            // +0x0008
    char  _pad0C[0x1];         // +0x000C
    char  IsAllocated;         // +0x000D
    char  _pad0E[0x10 - 0x0E]; // +0x000E
    int   Count;               // +0x0010
    int   CapacityIncrement;   // +0x0014

    // DynamicVectorClass::AddItem, expanded inline twice by VC6 at 0x5D6690.
    // The index is `index = Count; Count = index + 1;` so the increment
    // becomes retail's LEA, and the grown size is `CapacityIncrement + cap`
    // with the capacity bound to a local.
    bool AddItem(MPTeam_005D6690* item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && Resize(CapacityIncrement + cap, 0))) {
            int index = Count;
            Count = index + 1;
            Items[index] = item;
            return true;
        }
        return false;
    }
};
GG_STATIC_ASSERT(offsetof(MPTeamVector_005D6690, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(MPTeamVector_005D6690, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(MPTeamVector_005D6690, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(MPTeamVector_005D6690, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(MPTeamVector_005D6690, CapacityIncrement) == 0x14);

struct MultiplayerGameMode_005D6690
{
    // FUNCTION: GAMEMD 0x5D6690 — MultiplayerGameMode::CreateMPTeams (virtual;
    // `this` is never read, so a plain member reproduces the body bytes).
    void CreateMPTeams(MPTeamVector_005D6690* teams);
};

#endif  // GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_TEAMS_METHODS_H
