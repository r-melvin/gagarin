// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Inline slot-search helpers shared by the netshare.cpp slot code. Retail has
//   each as an out-of-line function (0x5E96A0 and 0x5E9720) and as an inlined
//   copy inside the control readers (0x5E9C00, 0x5E9CE0), which is why they are
//   inline helpers here with the out-of-line copies as thin wrappers.
#ifndef GG_MATCH_ECONOMY_NETSHARE_SLOT_INLINE_H
#define GG_MATCH_ECONOMY_NETSHARE_SLOT_INLINE_H

#include "netshare_slot_nodes.h"
#include "netshare_win.h"
#include "../network/multiplayer_game_mode.h"

// GLOBAL: GAMEMD 0xA8B23C -- the live game-mode object, or null.
extern MultiplayerGameMode* DAT_00A8B23C;

// GLOBAL: GAMEMD 0xA8B2BC -- the house-choice table (eight ints).
extern int DAT_00A8B2BC[8];
// GLOBAL: GAMEMD 0xA8B2DC -- the colour-choice table (eight ints).
extern int DAT_00A8B2DC[8];

// Does any seated player, or any entry of the house-choice table, hold this
// choice? -2 never matches.
static inline bool House_Choice_In_Use(int choice)
{
    if (choice != -2) {
        for (int i = 0; i < 8; i++) {
            NodeNameType* node = Slots[i];
            if (node != 0 && node != OpenNode && node != ClosedNode && node != WaitingNode &&
                node != ObserverNode && node != EasyAINode && node != MediumAINode &&
                node != HardAINode) {
                if (node->FUN_00696F20() == choice) {
                    return true;
                }
            }
        }
        for (int j = 0; j < 8; j++) {
            if (DAT_00A8B2BC[j] == choice) {
                return true;
            }
        }
    }
    return false;
}

// The same question against the second choice table and its reader.
static inline bool Colour_Choice_In_Use(int choice)
{
    if (choice != -2) {
        for (int i = 0; i < 8; i++) {
            NodeNameType* node = Slots[i];
            if (node != 0 && node != OpenNode && node != ClosedNode && node != WaitingNode &&
                node != ObserverNode && node != EasyAINode && node != MediumAINode &&
                node != HardAINode) {
                if (node->FUN_00696F50() == choice) {
                    return true;
                }
            }
        }
        for (int j = 0; j < 8; j++) {
            if (DAT_00A8B2DC[j] == choice) {
                return true;
            }
        }
    }
    return false;
}

// The player limit of a known map (0x5E64C0 minus its -1 test, which retail
// keeps outside this body): the map's own count, capped by the live game
// mode's slot-38 limit; session kind 4 then forces an even count, or two when
// the first predicate holds and the second does not.
static inline int Map_Player_Limit(int index)
{
    int limit = FUN_005E6520(index);
    if (DAT_00A8B23C != 0) {
        int modeLimit = DAT_00A8B23C->vf_38();
        if (modeLimit != -1 && modeLimit < limit) {
            limit = modeLimit;
        }
    }
    if (SessionKind == 4) {
        if (Is_005E8AE0_B()) {
            return limit & ~1;
        }
        if (Is_005E8AE0_A()) {
            limit = 2;
        }
    }
    return limit;
}

// The control id of slot `index` (0x411 + index), -1 outside 0..7: the body of
// 0x5E98F0, inlined into the slot-enable routines.
static inline int Slot_Control_Id(int index)
{
    if (index == 0) {
        return 0x411;
    }
    if (index == 1) {
        return 0x412;
    }
    if (index == 2) {
        return 0x413;
    }
    if (index == 3) {
        return 0x414;
    }
    if (index == 4) {
        return 0x415;
    }
    if (index == 5) {
        return 0x416;
    }
    if (index == 6) {
        return 0x417;
    }
    return index == 7 ? 0x418 : -1;
}

// The slot showing a name, case-insensitively, or -1: the slot search of
// 0x5E8D00, inlined into other routines.
static inline int Slot_Showing_Name(const wchar_t* name)
{
    for (int i = 0; i < 8; i++) {
        NodeNameType* node = Slots[i];
        if (node != 0 && _wcsicmp(name, node->Name) == 0) {
            return i;
        }
    }
    return -1;
}

// The same search for the local player (the vector's first node), as 0x5E8D40.
static inline int Local_Player_Slot()
{
    if (PlayerNodes.Count == 0) {
        return -1;
    }
    return Slot_Showing_Name(PlayerNodes.Vector[0]->Name);
}

// The singleton node for a kind number 2..7, or null: the body of 0x5E9800.
static inline NodeNameType* Node_For_Kind(int kind)
{
    if (kind == 2) {
        return OpenNode;
    }
    if (kind == 3) {
        return ClosedNode;
    }
    if (kind == 4) {
        return EasyAINode;
    }
    if (kind == 5) {
        return MediumAINode;
    }
    if (kind == 6) {
        return HardAINode;
    }
    return kind == 7 ? ObserverNode : 0;
}

// How many of the eight slots are playable in this session kind (the body of
// the slot-count helper of netshare_slot_nodes.cpp, as inlined elsewhere).
static inline int Playable_Slot_Count()
{
    int playable;
    if (SessionKind == 4) {
        if (Is_005E8AE0_A() && !Is_005E8AE0_B()) {
            playable = 2;
        } else {
            playable = 6;
        }
    } else {
        playable = 8;
    }
    return playable;
}

// A singleton node's kind number, 2..7; anything else answers 2: the body of
// 0x5E97A0, inlined into other routines.
static inline int Kind_Of_Node(NodeNameType* node)
{
    if (node == OpenNode) {
        return 2;
    }
    if (node == ClosedNode) {
        return 3;
    }
    if (node == EasyAINode) {
        return 4;
    }
    if (node == MediumAINode) {
        return 5;
    }
    if (node == HardAINode) {
        return 6;
    }
    return node == ObserverNode ? 7 : 2;
}

#endif  // GG_MATCH_ECONOMY_NETSHARE_SLOT_INLINE_H
