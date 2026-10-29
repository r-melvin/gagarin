// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001 over
//   0x5EA8E0..0x5EAEDA. Layout evidence is documented in
//   netshare_slot_tables.h.
//
//   The shared shape below — AI slots answer from the table, the four
//   non-playing singletons answer -2, and anything else is asked directly —
//   is the same one already matched out of line at 0x46F810 and 0x46F880 in
//   match/core/house_index_lookup_methods.cpp (read, not edited). Written out
//   per reader here because retail inlines it, and because each reader has its
//   own table and its own node reader.
//
//   LIBRARY: GAMEMD 0x7C8EF4 sprintf (reloc); strcat expanded inline by /O2.

#include "netshare_slot_tables.h"

// FUNCTION: GAMEMD 0x5EA8E0
//
// Is this slot settled? An AI is always settled, and a human is settled once
// its ready flag reads 1. Retail lets the null slot fall into the flag test,
// which the short-circuit reproduces exactly.
int Slot_Is_AI_Or_Ready(int index)
{
    SlotNode* node = SlotChoices.Slots[index];

    int ready = 0;
    if ((node != 0 &&
         (node == EasyAINode || node == MediumAINode || node == HardAINode)) ||
        node->unknown_77 == 1) {
        ready = 1;
    }
    return ready;
}

// FUNCTION: GAMEMD 0x5EA920
//
// The slot's start position. Inside a live lobby of the two session kinds that
// place starts by hand, the dialog answers first and the slot only overrides
// it; outside one the answer starts at -2.
int Slot_Start_Position(int index)
{
    int position = -2;
    SlotNode* node = SlotChoices.Slots[index];
    LobbyDialog_005EA920* dialog = LobbyDialog;

    if (dialog != 0 && (SessionKind == 3 || SessionKind == 4)) {
        position = dialog->Read_Slot();
    }

    if (node != 0 &&
        (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
        return StartTable[index];
    }

    if (node != OpenNode && node != ClosedNode && node != WaitingNode) {
        // An observer answers -3 here, not the -2 the other three give.
        if (node == ObserverNode) {
            return -3;
        }
        position = node->Read_00696F10();
    }
    return position;
}

// FUNCTION: GAMEMD 0x5EA9B0
//
// The house this slot plays. An AI plays whatever the house table says; the
// four non-playing singletons play nothing; a real player is asked.
int Slot_House(int index)
{
    SlotNode* node = SlotChoices.Slots[index];
    if (node != 0 &&
        (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
        return SlotChoices.House[index];
    }

    if (node == OpenNode) {
        return -2;
    }
    if (node == ClosedNode) {
        return -2;
    }
    if (node == WaitingNode) {
        return -2;
    }
    if (node == ObserverNode) {
        return -2;
    }
    return node->Read_00696F20();
}

// FUNCTION: GAMEMD 0x5EAA10
//
// The same reader against the colour table.
int Slot_Colour(int index)
{
    SlotNode* node = SlotChoices.Slots[index];
    if (node != 0 &&
        (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
        return SlotChoices.Colour[index];
    }

    if (node == OpenNode) {
        return -2;
    }
    if (node == ClosedNode) {
        return -2;
    }
    if (node == WaitingNode) {
        return -2;
    }
    if (node == ObserverNode) {
        return -2;
    }
    return node->Read_00696F50();
}

// FUNCTION: GAMEMD 0x5EAA70
//
// The same reader against the team table.
int Slot_Team(int index)
{
    SlotNode* node = SlotChoices.Slots[index];
    if (node != 0 &&
        (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
        return SlotChoices.Team[index];
    }

    if (node == OpenNode) {
        return -2;
    }
    if (node == ClosedNode) {
        return -2;
    }
    if (node == WaitingNode) {
        return -2;
    }
    if (node == ObserverNode) {
        return -2;
    }
    return node->Read_00696F70();
}

// FUNCTION: GAMEMD 0x5EAAD0
//
// The dialog control that draws a given slot: eight consecutive ids, and -1
// for anything off the end. cl folds the last two arms into the
// NEG/SBB/AND/ADD idiom retail has, so they are ordinary arms in the chain.
int Slot_Control_Id(int index)
{
    if (index == 0) {
        return 0x6D2;
    }
    if (index == 1) {
        return 0x6D3;
    }
    if (index == 2) {
        return 0x6D4;
    }
    if (index == 3) {
        return 0x6D5;
    }
    if (index == 4) {
        return 0x6D6;
    }
    if (index == 5) {
        return 0x6D7;
    }
    if (index == 6) {
        return 0x6D8;
    }
    if (index == 7) {
        return 0x6D9;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x5EAB30
//
// Every slot's house as one comma-terminated decimal list, for the lobby
// packet. The four-byte scratch buffer is retail's own: the frame carries
// exactly one dword between the return address and the saved registers.
void Format_House_List(char* out)
{
    out[0] = '\0';
    for (int i = 0; i < 8; i++) {
        SlotNode* node = SlotChoices.Slots[i];

        int value;
        if (node != 0 &&
            (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
            value = SlotChoices.House[i];
        } else if (node == OpenNode) {
            value = -2;
        } else if (node == ClosedNode) {
            value = -2;
        } else if (node == WaitingNode) {
            value = -2;
        } else if (node == ObserverNode) {
            value = -2;
        } else {
            value = node->Read_00696F20();
        }

        char text[4];
        sprintf(text, "%d,", value);
        strcat(out, text);
    }
}

// FUNCTION: GAMEMD 0x5EAC00
//
// The same list for the colour table.
void Format_Colour_List(char* out)
{
    out[0] = '\0';
    for (int i = 0; i < 8; i++) {
        SlotNode* node = SlotChoices.Slots[i];

        int value;
        if (node != 0 &&
            (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
            value = SlotChoices.Colour[i];
        } else if (node == OpenNode) {
            value = -2;
        } else if (node == ClosedNode) {
            value = -2;
        } else if (node == WaitingNode) {
            value = -2;
        } else if (node == ObserverNode) {
            value = -2;
        } else {
            value = node->Read_00696F50();
        }

        char text[4];
        sprintf(text, "%d,", value);
        strcat(out, text);
    }
}

// FUNCTION: GAMEMD 0x5EACD0
//
// The same list for the team table.
void Format_Team_List(char* out)
{
    out[0] = '\0';
    for (int i = 0; i < 8; i++) {
        SlotNode* node = SlotChoices.Slots[i];

        int value;
        if (node != 0 &&
            (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
            value = SlotChoices.Team[i];
        } else if (node == OpenNode) {
            value = -2;
        } else if (node == ClosedNode) {
            value = -2;
        } else if (node == WaitingNode) {
            value = -2;
        } else if (node == ObserverNode) {
            value = -2;
        } else {
            value = node->Read_00696F70();
        }

        char text[4];
        sprintf(text, "%d,", value);
        strcat(out, text);
    }
}

// FUNCTION: GAMEMD 0x5EADA0
//
// Push every slot's colour into the lobby's colour list control.
void Fill_Colour_List(void* target)
{
    for (int i = 0; i < 8; i++) {
        int item = Colour_Item_004E4E60(i);
        SlotNode* node = SlotChoices.Slots[i];

        int value;
        if (node != 0 &&
            (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
            value = SlotChoices.Colour[i];
        } else if (node == OpenNode) {
            value = -2;
        } else if (node == ClosedNode) {
            value = -2;
        } else if (node == WaitingNode) {
            value = -2;
        } else if (node == ObserverNode) {
            value = -2;
        } else {
            value = node->Read_00696F50();
        }

        Set_Colour_Entry_004E5480(target, item, value);
    }
}

// FUNCTION: GAMEMD 0x5EAE40
//
// The same for the team list control.
void Fill_Team_List(void* target)
{
    for (int i = 0; i < 8; i++) {
        int item = Team_Item_004E5940(i);
        SlotNode* node = SlotChoices.Slots[i];

        int value;
        if (node != 0 &&
            (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
            value = SlotChoices.Team[i];
        } else if (node == OpenNode) {
            value = -2;
        } else if (node == ClosedNode) {
            value = -2;
        } else if (node == WaitingNode) {
            value = -2;
        } else if (node == ObserverNode) {
            value = -2;
        } else {
            value = node->Read_00696F70();
        }

        Set_Team_Entry_004E5ED0(target, item, value);
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8B29C
int StartTable[8];
// GLOBAL: GAMEMD 0xA8B2BC
SlotTables SlotChoices;
// END defined globals
