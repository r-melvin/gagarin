// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001 over
//   0x5E8740..0x5E957E. Layout evidence and the retail source-file name are
//   documented in netshare_slot_nodes.h.
//   Three of the bodies here — 0x5E8760, 0x5E93F0 and 0x5E94A0 — are not
//   in the Ghidra function list, and were found by sweeping
//   the address run as raw bytes and reading the twelve-byte 0x90 pads that
//   separate functions. NodeNameType and IPXAddressClass are retail RTTI
//   names; their members sit where the disassembly places them.
//
//   LIBRARY: GAMEMD 0x7CA5D3 wcscmp, 0x7DD0F8 _wcsicmp, 0x7C8D20 _stricmp,
//   0x7C8B3D operator delete (all reloc).

#include "netshare_slot_nodes.h"

// FUNCTION: GAMEMD 0x5E8740
//
// Is the node sitting at `index` in the player vector still unnamed? The
// blank name at 0xA8D610 is the "not filled in yet" sentinel, and the node
// pointer is its own name because Name is the first member.
int __fastcall Node_Is_Blank_At(int index)
{
    return wcscmp(PlayerNodes.Vector[index]->Name, BlankName) == 0;
}

// FUNCTION: GAMEMD 0x5E8760
//
// The same question about the local player's own handle, which is stored
// ANSI and widened for the comparison.
int __fastcall Local_Handle_Is_Blank()
{
    wchar_t* handle = Widen_00735120(LocalHandle);
    return wcscmp(handle, BlankName) == 0;
}

// FUNCTION: GAMEMD 0x5E8780
//
// Does an arbitrary wide name belong to the local player?
int __fastcall Name_Is_Local_Handle(const wchar_t* name)
{
    return wcscmp(name, Widen_00735120(LocalHandle)) == 0;
}

// FUNCTION: GAMEMD 0x5E87A0
//
// Build the seven singleton slot nodes, once. The captions come from the
// string table under their GUI labels, each fetch carrying the source file
// and its own line number, and the first caption doubles as the "already
// built" guard. Each node is then allocated and given its caption as its
// name, so a slot's caption and a player's name are the same kind of string
// everywhere else in this file.
void __fastcall Build_Slot_Nodes()
{
    if (DAT_00AC117C == 0) {
        DAT_00AC117C = Fetch_String_00734E60(OpenLabel, 0, NetshareFileName, 4078);
        ClosedText = Fetch_String_00734E60(ClosedLabel, 0, NetshareFileName, 4079);
        EasyAIText = Fetch_String_00734E60(EasyAILabel, 0, NetshareFileName, 4080);
        MediumAIText = Fetch_String_00734E60(MediumAILabel, 0, NetshareFileName, 4081);
        HardAIText = Fetch_String_00734E60(HardAILabel, 0, NetshareFileName, 4082);
        WaitingText = Fetch_String_00734E60(WaitingLabel, 0, NetshareFileName, 4083);
        ObserverText = Fetch_String_00734E60(ObserverLabel, 0, NetshareFileName, 4084);
    }

    if (OpenNode == 0) {
        OpenNode = new NodeNameType;
        wcscpy(OpenNode->Name, DAT_00AC117C);
    }
    if (ClosedNode == 0) {
        ClosedNode = new NodeNameType;
        wcscpy(ClosedNode->Name, ClosedText);
    }
    if (EasyAINode == 0) {
        EasyAINode = new NodeNameType;
        wcscpy(EasyAINode->Name, EasyAIText);
    }
    if (MediumAINode == 0) {
        MediumAINode = new NodeNameType;
        wcscpy(MediumAINode->Name, MediumAIText);
    }
    if (HardAINode == 0) {
        HardAINode = new NodeNameType;
        wcscpy(HardAINode->Name, HardAIText);
    }
    if (WaitingNode == 0) {
        WaitingNode = new NodeNameType;
        wcscpy(WaitingNode->Name, WaitingText);
    }
    if (ObserverNode == 0) {
        ObserverNode = new NodeNameType;
        wcscpy(ObserverNode->Name, ObserverText);
    }
}

// FUNCTION: GAMEMD 0x5E8A20
//
// Tear the lobby down: release each of the seven singleton slot nodes, then
// hand the player vector to its own clear-and-delete helper.
void __fastcall Destroy_Slot_Nodes()
{
    if (OpenNode != 0) {
        delete OpenNode;
        OpenNode = 0;
    }
    if (ClosedNode != 0) {
        delete ClosedNode;
        ClosedNode = 0;
    }
    if (EasyAINode != 0) {
        delete EasyAINode;
        EasyAINode = 0;
    }
    if (MediumAINode != 0) {
        delete MediumAINode;
        MediumAINode = 0;
    }
    if (HardAINode != 0) {
        delete HardAINode;
        HardAINode = 0;
    }
    if (WaitingNode != 0) {
        delete WaitingNode;
        WaitingNode = 0;
    }
    if (ObserverNode != 0) {
        delete ObserverNode;
        ObserverNode = 0;
    }
    Clear_Nodes_005C6120(&PlayerNodes);
}

// How many of the eight slots are playable in this session kind. Session kind
// 4 is the one that shrinks: two slots for the stripped-down case, six
// otherwise, and eight for every other session kind.
static __forceinline int Playable_Slot_Count()
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

// FUNCTION: GAMEMD 0x5E8AE0
//
// Put every slot back to its starting state: the playable ones show Open and
// the rest show Closed.
void __fastcall Reset_Slots()
{
    int playable = Playable_Slot_Count();

    for (int i = 0; i < playable; i++) {
        Slots[i] = OpenNode;
    }
    for (int j = playable; j < 8; j++) {
        Slots[j] = ClosedNode;
    }
}

// FUNCTION: GAMEMD 0x5E8B40
//
// Drop the four lobby redraw flags together.
void __fastcall Clear_Lobby_Flags()
{
    DirtyFlagA = false;
    DirtyFlagB = false;
    DirtyFlagC = false;
    DirtyFlagD = false;
}

// FUNCTION: GAMEMD 0x5E8B60
//
// The full lobby reset: the slot reset above, then forget which slot the
// local player picked, empty the lobby list and zero the two counters.
void __fastcall Reset_Lobby()
{
    int playable = Playable_Slot_Count();

    for (int i = 0; i < playable; i++) {
        Slots[i] = OpenNode;
    }
    for (int j = playable; j < 8; j++) {
        Slots[j] = ClosedNode;
    }

    SelectedSlotIndex = -1;
    DAT_00A8B250.Clear();
    CounterA = 0;
    CounterB = 0;
}

// FUNCTION: GAMEMD 0x5E8BF0
//
// Resolve a wide name to a node: the seven singletons first, in the order
// they were created, then the real players. Case sensitive, unlike the slot
// lookup below.
NodeNameType* __fastcall Find_Node_By_Name(const wchar_t* name)
{
    if (wcscmp(OpenNode->Name, name) == 0) {
        return OpenNode;
    }
    if (wcscmp(ClosedNode->Name, name) == 0) {
        return ClosedNode;
    }
    if (wcscmp(EasyAINode->Name, name) == 0) {
        return EasyAINode;
    }
    if (wcscmp(MediumAINode->Name, name) == 0) {
        return MediumAINode;
    }
    if (wcscmp(HardAINode->Name, name) == 0) {
        return HardAINode;
    }
    if (wcscmp(WaitingNode->Name, name) == 0) {
        return WaitingNode;
    }
    if (wcscmp(ObserverNode->Name, name) == 0) {
        return ObserverNode;
    }

    int count = PlayerNodes.Count;
    for (int i = 0; i < count; i++) {
        NodeNameType* node = PlayerNodes.Vector[i];
        if (wcscmp(node->Name, name) == 0) {
            return node;
        }
    }
    return 0;
}

// The slot search both name lookups share. Retail has it out of line at
// 0x5E8D00 and inlined into 0x5E8D40, so it must be a forced-inline helper
// with the out-of-line copy as its own wrapper: a plain call from 0x5E8D40
// comes out as a tail JMP instead.
static __forceinline int Slot_Showing_Name(const wchar_t* name)
{
    for (int i = 0; i < 8; i++) {
        NodeNameType* node = Slots[i];
        if (node != 0 && _wcsicmp(name, node->Name) == 0) {
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x5E8D00
//
// Which slot currently shows this name? Case insensitive; empty slots are
// skipped rather than compared.
int __fastcall Find_Slot_By_Name(const wchar_t* name)
{
    return Slot_Showing_Name(name);
}

// FUNCTION: GAMEMD 0x5E8D40
//
// The same search for the local player, who is always the vector's first
// entry. With no players at all there is nothing to find.
int __fastcall Find_Local_Player_Slot()
{
    if (PlayerNodes.Count == 0) {
        return -1;
    }

    return Slot_Showing_Name(PlayerNodes.Vector[0]->Name);
}

// FUNCTION: GAMEMD 0x5E8D90
//
// Seat a node in a slot.
void __fastcall Set_Slot_Node(int index, NodeNameType* node)
{
    Slots[index] = node;
}

// FUNCTION: GAMEMD 0x5E8DA0
//
// Move the local player into a slot and remember the choice.
void __fastcall Select_Slot(int index)
{
    SelectedSlotIndex = index;
    Slots[index] = PlayerNodes.Vector[0];
}

// FUNCTION: GAMEMD 0x5E9240
//
// Find a home for a node and take it. An observer, marked by -1 in the house
// field, wants an observer slot; anyone else wants an open one. Answers the
// slot index, or -1 when the lobby is full.
int __fastcall Assign_Node_To_Slot(NodeNameType* node)
{
    for (int i = 0; i < 8; i++) {
        NodeNameType* seated = Slots[i];
        if ((seated == OpenNode && node->unknown_6B != -1) ||
            (seated == ObserverNode && node->unknown_6B == -1)) {
            Slots[i] = node;
            return i;
        }
    }
    return -1;
}

// The playable count as the two release paths want it: one extra slot opens up
// when the extra-slot flag is clear and there is room for it.
static __forceinline int Releasable_Slot_Count()
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

    if (NoExtraSlot == 0 && playable < 7) {
        playable++;
    }
    return playable;
}

// FUNCTION: GAMEMD 0x5E9290
//
// Give back the slot held by a node with this network address. An observer's
// slot goes back to Observer; everyone else's goes back to Open if it is still
// playable and Closed if it is not.
void __fastcall Release_Slot_By_Address(const IPXAddressClass* address)
{
    int playable = Releasable_Slot_Count();

    for (int i = 0; i < 8; i++) {
        NodeNameType* node = Slots[i];
        if (node->Address.FUN_0053EE70(address)) {
            NodeNameType* seated = Slots[i];
            if (seated->unknown_6B == -1) {
                Slots[i] = ObserverNode;
                return;
            }
            Slots[i] = (i < playable) ? OpenNode : ClosedNode;
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x5E9340
//
// The same release keyed on an ANSI handle rather than an address. The node's
// wide name is narrowed for the comparison, and empty slots are skipped.
void __fastcall Release_Slot_By_Handle(const char* handle)
{
    int playable = Releasable_Slot_Count();

    for (int i = 0; i < 8; i++) {
        NodeNameType* seated = Slots[i];
        if (seated != 0 && _stricmp(handle, Narrow_007350C0(seated->Name)) == 0) {
            NodeNameType* found = Slots[i];
            if (found->unknown_6B == -1) {
                Slots[i] = ObserverNode;
                return;
            }
            Slots[i] = (i < playable) ? OpenNode : ClosedNode;
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x5E93F0
//
// Is this a real human player rather than one of the seven singletons? Not in
// the Ghidra function list; found by the pad sweep.
int __fastcall Is_Player_Node(NodeNameType* node)
{
    if (node == 0 || node == OpenNode || node == ClosedNode ||
        node == WaitingNode || node == ObserverNode || node == EasyAINode ||
        node == MediumAINode || node == HardAINode) {
        return 0;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x5E9440
//
// Is this one of the three AI singletons?
int __fastcall Is_AI_Node(NodeNameType* node)
{
    if (node != 0 &&
        (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5E9470
//
// Does something actually occupy this slot? Open, Closed, Observer and
// Waiting all mean no; the AI singletons and real players mean yes.
int __fastcall Is_Occupied_Node(NodeNameType* node)
{
    if (node == 0 || node == OpenNode || node == ClosedNode ||
        node == ObserverNode || node == WaitingNode) {
        return 0;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x5E94A0
//
// The difficulty an AI singleton stands for, counting down from Easy, and -1
// for anything that is not an AI. Not in the Ghidra function list; found by the pad sweep.
int __fastcall AI_Difficulty_Of(NodeNameType* node)
{
    int difficulty = -1;
    if (node == EasyAINode) {
        difficulty = 2;
    } else if (node == MediumAINode) {
        difficulty = 1;
    } else if (node == HardAINode) {
        difficulty = 0;
    }
    return difficulty;
}

// FUNCTION: GAMEMD 0x5E94D0
//
// How many slots the AI holds.
int __fastcall Count_AI_Slots()
{
    int count = 0;
    for (int i = 0; i < 8; i++) {
        NodeNameType* node = Slots[i];
        if (node != 0 &&
            (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
            count++;
        }
    }
    return count;
}

// FUNCTION: GAMEMD 0x5E9510
//
// Is the lobby full? Only the slots inside the smaller of the map's and the
// session's player limits count, plus the one extra slot when it is available.
bool __fastcall No_Open_Slot()
{
    // Only the ternary min reaches retail's register pair here: the two
    // if-spellings both hold the limit in the other register and carry the
    // loop index with them, 63.3% against 100%.
    int limit = (MapPlayerLimit < SessionPlayerLimit) ? MapPlayerLimit
                                                     : SessionPlayerLimit;

    for (int i = 0; i < limit; i++) {
        if (Slots[i] == OpenNode) {
            return false;
        }
    }

    if (NoExtraSlot == 0 && limit < 8 && Slots[limit] == OpenNode) {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x5E9560
//
// Is there nowhere left to observe from?
bool __fastcall No_Observer_Slot()
{
    for (int i = 0; i < 8; i++) {
        if (Slots[i] == ObserverNode) {
            return false;
        }
    }
    return true;
}
