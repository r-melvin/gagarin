// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Every offset and address below was read numerically off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI over 0x5EA8E0..0x5EAEDA.
//   Every name is this tree's own.
//
//   This is the second half of netshare.cpp (see netshare_slot_nodes.h for the
//   first): the three per-slot choice tables that sit beside the slot array,
//   and the readers that turn a slot into a house / colour / team value.
//
//   Layout evidence, all numeric:
//   * The three tables are contiguous 8-int arrays. 0x5EAB30 walks EBX from
//     0xA8B2BC and stops at 0xA8B2DC, 0x5EAC00 from 0xA8B2DC to 0xA8B2FC and
//     0x5EACD0 from 0xA8B2FC to 0xA8B31C: three 0x20-byte spans back to back.
//   * They and the slot array are ONE object, not three globals plus a fourth.
//     0x5EAB30 reads the slot as `MOV ECX,[EBX+0x27D4]` with EBX walking the
//     first table, and 0x5EADA0 as `[ESI+0x27B4]` with ESI walking the second.
//     A literal displacement with no relocation only comes out of a
//     compile-time-known distance, so 0xA8B2BC + 0x27D4 == 0xA8DA90 is a
//     layout fact about a single enclosing object, and that is what the
//     unknown gap below pins.
//   * SlotNode::unknown_77 : `CMP dword [ECX+0x77],1` at 0x5EA905. The node is
//     the 133-byte packed NodeNameType of netshare_slot_nodes.h, modelled here
//     only as far as this run reads it.
//   * The four readers 0x696F10 / 0x696F20 / 0x696F50 / 0x696F70 are
//     __thiscall on the node with no arguments, reached as a tail JMP in the
//     0x58-byte readers and as a CALL inside the list builders.
#ifndef GG_MATCH_ECONOMY_NETSHARE_SLOT_TABLES_H
#define GG_MATCH_ECONOMY_NETSHARE_SLOT_TABLES_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" {
// FUNCTION: GAMEMD 0x7C8EF4 (decl; reloc) — CRT sprintf.
int __cdecl sprintf(char* buffer, const char* format, ...);
// FUNCTION: GAMEMD (inlined intrinsic) — CRT strcat, which /O2 expands to the
// REPNZ SCASB / REP MOVSD pair retail has at 0x5EABC2.
char* __cdecl strcat(char* dst, const char* src);
}

// The lobby slot entry, modelled only as deep as this run reads it.
#pragma pack(push, 1)
struct SlotNode
{
    unsigned char unknown_00[0x77];   // +0x00
    int unknown_77;                   // +0x77
    unsigned char unknown_7B[0x0A];   // +0x7B

    // FUNCTION: GAMEMD 0x696F10 (decl; reloc)
    int Read_00696F10();
    // FUNCTION: GAMEMD 0x696F20 (decl; reloc)
    int Read_00696F20();
    // FUNCTION: GAMEMD 0x696F50 (decl; reloc)
    int Read_00696F50();
    // FUNCTION: GAMEMD 0x696F70 (decl; reloc)
    int Read_00696F70();
};
#pragma pack(pop)

GG_STATIC_ASSERT(offsetof(SlotNode, unknown_77) == 0x77 &&
                 sizeof(SlotNode) == 0x85);

// The three per-slot choice tables and, 0x27D4 further on, the slot array.
struct SlotTables
{
    int House[8];                        // +0x0000  GLOBAL: GAMEMD 0xA8B2BC
    int Colour[8];                       // +0x0020  GLOBAL: GAMEMD 0xA8B2DC
    int Team[8];                         // +0x0040  GLOBAL: GAMEMD 0xA8B2FC
    unsigned char unknown_0060[0x2774];  // +0x0060
    SlotNode* Slots[8];                  // +0x27D4  GLOBAL: GAMEMD 0xA8DA90
};

GG_STATIC_ASSERT(offsetof(SlotTables, Colour) == 0x0020 &&
                 offsetof(SlotTables, Team) == 0x0040 &&
                 offsetof(SlotTables, Slots) == 0x27D4);

// GLOBAL: GAMEMD 0xA8B2BC — the tables, and through them the slot array.
extern SlotTables SlotChoices;
// GLOBAL: GAMEMD 0xA8B29C — the fourth table, one 0x20-byte span before the
// first. Only 0x5EA920 reads it, and only through a plain relocation, so it
// stays its own global rather than widening the struct backwards.
extern int StartTable[8];

// GLOBAL: GAMEMD 0xAC119C..0xAC11B4 — the seven singleton slot nodes.
extern SlotNode* OpenNode;        // GLOBAL: GAMEMD 0xAC119C
extern SlotNode* ClosedNode;      // GLOBAL: GAMEMD 0xAC11A0
extern SlotNode* EasyAINode;      // GLOBAL: GAMEMD 0xAC11A4
extern SlotNode* MediumAINode;    // GLOBAL: GAMEMD 0xAC11A8
extern SlotNode* HardAINode;      // GLOBAL: GAMEMD 0xAC11AC
extern SlotNode* WaitingNode;     // GLOBAL: GAMEMD 0xAC11B0
extern SlotNode* ObserverNode;    // GLOBAL: GAMEMD 0xAC11B4

// GLOBAL: GAMEMD 0xA8B238 — the session kind; 3 and 4 are the two that let
// 0x5EA920 ask the dialog object for its own answer first.
extern int SessionKind;

// GLOBAL: GAMEMD 0xA8B23C — the live lobby dialog, or null outside one.
struct LobbyDialog_005EA920
{
    // Ten unread slots, then the one 0x5EA920 calls: `MOV EAX,[ECX];
    // CALL [EAX+0x28]` at 0x5EA94A, so slot 0x28/4 == 10.
    virtual void unknown_00();
    virtual void unknown_04();
    virtual void unknown_08();
    virtual void unknown_0C();
    virtual void unknown_10();
    virtual void unknown_14();
    virtual void unknown_18();
    virtual void unknown_1C();
    virtual void unknown_20();
    virtual void unknown_24();
    // VTABLE slot +0x28.
    virtual int Read_Slot();
};
extern LobbyDialog_005EA920* LobbyDialog;

// FUNCTION: GAMEMD 0x4E4E60 (decl; reloc) — the colour list's per-index item.
int __fastcall Colour_Item_004E4E60(int index);
// FUNCTION: GAMEMD 0x4E5940 (decl; reloc) — the team list's per-index item.
int __fastcall Team_Item_004E5940(int index);
// FUNCTION: GAMEMD 0x4E5480 (decl; reloc) — seat one colour entry.
void __fastcall Set_Colour_Entry_004E5480(void* target, int item, int value);
// FUNCTION: GAMEMD 0x4E5ED0 (decl; reloc) — seat one team entry.
void __fastcall Set_Team_Entry_004E5ED0(void* target, int item, int value);

int __fastcall Slot_Is_AI_Or_Ready(int index);
int __fastcall Slot_Start_Position(int index);
int __fastcall Slot_House(int index);
int __fastcall Slot_Colour(int index);
int __fastcall Slot_Team(int index);
int __fastcall Slot_Control_Id(int index);
void __fastcall Format_House_List(char* out);
void __fastcall Format_Colour_List(char* out);
void __fastcall Format_Team_List(char* out);
void __fastcall Fill_Colour_List(void* target);
void __fastcall Fill_Team_List(void* target);

#endif  // GG_MATCH_ECONOMY_NETSHARE_SLOT_TABLES_H
