// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check | YRpp-cross-check
//   Every offset, global address and calling convention below was read
//   numerically off the user's retail gamemd.exe v1.001 with the local Ghidra
//   CLI over the run 0x5E8740..0x5E957E. Every width is derived from the
//   disassembly (returns are
//   `int` here wherever retail exits through `MOV EAX,1` / `XOR EAX,EAX`
//   rather than the byte form).
//
//   The retail source file is named by the string table call sites in
//   0x5E87A0: `PUSH <line>; PUSH 0x8317D8` where 0x8317D8 is
//   "D:\ra2mdpost\netshare.cpp" and the pushed line numbers run 0xFEE..0xFF4
//   consecutively. So this run is netshare.cpp, the multiplayer lobby's
//   player-slot table.
//
//   Layout evidence, all numeric:
//   * NodeNameType is allocated with `PUSH 0x85; CALL 0x7C8E17` in 0x5E87A0,
//     so sizeof == 133. It is byte-packed: 0x85 is odd and 0x5E9302 reads a
//     dword at `[EAX+0x6B]`, an offset no naturally aligned layout can put an
//     int at.
//   * Name at +0 : the node pointer is handed straight to wcscmp at 0x5E8BFD
//     and to wcscpy as the destination at 0x5E88A0, so the first member is the
//     wide name buffer.
//   * Address at +0x28 : `LEA ECX,[ESI+0x28]` before constructor 0x53ECB0,
//     and `LEA ECX,[EAX+0x28]` before comparison 0x53EE70 at 0x5E92E1. The
//     constructor stores 0xFF through +0x9. The shared IPXAddressClass has a
//     12-byte extent: 0x53FA90 allocates its array at 0xC strides and 0x53F430
//     embeds/copies one through +0xB. The lobby's last two address bytes are
//     not independently observed here.
//   * unknown_6B at +0x6B : `CMP dword [EAX+0x6B],-1` at 0x5E9302 / 0x5E93BC
//     and `CMP [ECX+0x6B],EBX` (EBX = -1) at 0x5E9260 / 0x5E9269. -1 marks an
//     observer, so this is the node's chosen house/side index.
//   * The vector at 0xA8DA74 has the DynamicVectorClass layout: the destroy helper
//     0x5C6120 walks `[ESI+0x10]` items out of `[ESI+4]` and then calls the
//     virtual at vtable slot +0xC, so +0x00 is the vptr, +0x04 the item array
//     and +0x10 the active count. Only those two members are read here.
//
// Reviewed for the free-`__fastcall`-with-a-receiver pattern and deliberately LEFT as free
// functions. `NodeNameType` and `IPXAddressClass` ARE recovered types, but the
// six routines that take one are not methods on them: the retail source file
// is named in the image itself — "D:\ra2mdpost\netshare.cpp", pushed with its
// line numbers by the string-table fetches in 0x5E87A0 — and these are that
// file's lobby-scope helpers over the slot table and the node vector, one of
// which (0x5E87A0) needs C linkage to match at all. A node handed to a
// predicate is an argument, not a receiver; making them `NodeNameType`
// members would assert a class identity retail's own file layout contradicts.
#ifndef GG_MATCH_ECONOMY_NETSHARE_SLOT_NODES_H
#define GG_MATCH_ECONOMY_NETSHARE_SLOT_NODES_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/ipx_address_class.h"

extern "C" {
// FUNCTION: GAMEMD 0x7CA5D3 (decl; reloc) — CRT wcscmp.
int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);
// LIBRARY: GAMEMD 0x7DD0F8 (decl; reloc) — CRT _wcsicmp.
int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);
// FUNCTION: GAMEMD 0x7C8D20 (decl; reloc) — CRT _stricmp.
int __cdecl _stricmp(const char* a, const char* b);
}

#pragma pack(push, 1)
// ---------------------------------------------------------------------------
// One lobby player slot entry. 133 bytes, byte-packed.
// ---------------------------------------------------------------------------
struct NodeNameType
{
    wchar_t Name[20];                 // +0x00
    IPXAddressClass Address;          // +0x28
    unsigned char unknown_34[0x37];   // +0x34
    int unknown_6B;                   // +0x6B  (-1 == observer)
    unsigned char unknown_6F[0x08];   // +0x6F
    int unknown_77;                   // +0x77  tested against 1 at 0x5EA905 and 0x5EA3A5, cleared at 0x5E98DD
    unsigned char unknown_7B[0x04];   // +0x7B
    int unknown_7F;                   // +0x7F  stored by 0x5E3A36 (0 = no map, 2 = map transfer)
    unsigned char unknown_83[0x02];   // +0x83

    // FUNCTION: GAMEMD 0x696F20 (decl; reloc) -- __thiscall, no arguments: a
    // choice reader (the fallback of 0x46F810).
    int FUN_00696F20();
    // FUNCTION: GAMEMD 0x696F50 (decl; reloc) -- __thiscall, no arguments: a
    // choice reader (the fallback of 0x46F880).
    int FUN_00696F50();
    // FUNCTION: GAMEMD 0x696F90 (decl; reloc) -- __thiscall, one argument: store
    // a choice pair at +0x4B/+0x4F (-2 stores 0 and -2, anything else stores the
    // value and -1); called with the start-position control's value.
    void FUN_00696F90(int value);
    // FUNCTION: GAMEMD 0x696FC0 (decl; reloc) -- __thiscall, one argument: the
    // same pair store at +0x53/+0x57 (-2 stores -1 and -2).
    void FUN_00696FC0(int value);
    // FUNCTION: GAMEMD 0x696FF0 (decl; reloc) -- __thiscall, one argument: the
    // same pair store at +0x5B/+0x5F.
    void FUN_00696FF0(int value);
    // FUNCTION: GAMEMD 0x697020 (decl; reloc) -- __thiscall, one argument: the
    // same pair store at +0x63/+0x67.
    void FUN_00697020(int value);
};
#pragma pack(pop)

GG_STATIC_ASSERT(offsetof(NodeNameType, Address) == 0x28 &&
                 offsetof(NodeNameType, unknown_34) == 0x34 &&
                 offsetof(NodeNameType, unknown_6B) == 0x6B &&
                 offsetof(NodeNameType, unknown_77) == 0x77 &&
                 offsetof(NodeNameType, unknown_7F) == 0x7F &&
                 sizeof(NodeNameType) == 0x85);

// ---------------------------------------------------------------------------
// The node vector (DynamicVectorClass layout), only the two members this run reads.
// ---------------------------------------------------------------------------
struct NodeNameVector
{
    void* unknown_00;                 // +0x00  vptr
    NodeNameType** Vector;            // +0x04
    unsigned char unknown_08[8];      // +0x08
    int Count;                  // +0x10
    int unknown_14;                   // +0x14

};

GG_STATIC_ASSERT(offsetof(NodeNameVector, Vector) == 0x04 &&
                 offsetof(NodeNameVector, Count) == 0x10 &&
                 sizeof(NodeNameVector) == 0x18);

// --- globals ---------------------------------------------------------------

// GLOBAL: GAMEMD 0xA8DA74 — the lobby's player node vector (Vector at
// 0xA8DA78, Count at 0xA8DA84).
extern NodeNameVector PlayerNodes;
// GLOBAL: GAMEMD 0xA8DA8C — the slot index the local player picked, -1 when none.
extern int SelectedSlotIndex;
// GLOBAL: GAMEMD 0xA8DA90 — the eight lobby slots. The loops compare the
// walking pointer against 0xA8DAB0, i.e. &Slots[8].
extern NodeNameType* Slots[8];

// GLOBAL: GAMEMD 0xAC117C..0xAC1194 — the seven slot-state captions, fetched
// from the string table as "GUI:Open", "GUI:Closed", "GUI:AIEasy",
// "GUI:AINormal", "GUI:AIHard", "GUI:Waiting", "GUI:OpenObserver".
extern wchar_t* DAT_00AC117C;         // GLOBAL: GAMEMD 0xAC117C
extern wchar_t* ClosedText;       // GLOBAL: GAMEMD 0xAC1180
extern wchar_t* EasyAIText;       // GLOBAL: GAMEMD 0xAC1184
extern wchar_t* MediumAIText;     // GLOBAL: GAMEMD 0xAC1188
extern wchar_t* HardAIText;       // GLOBAL: GAMEMD 0xAC118C
extern wchar_t* WaitingText;      // GLOBAL: GAMEMD 0xAC1190
extern wchar_t* ObserverText;     // GLOBAL: GAMEMD 0xAC1194

// GLOBAL: GAMEMD 0xAC119C..0xAC11B4 — the seven singleton nodes a slot holds
// when no real player owns it. Order fixed by 0x5E87A0, which builds each one
// from the caption of the same index.
extern NodeNameType* OpenNode;        // GLOBAL: GAMEMD 0xAC119C
extern NodeNameType* ClosedNode;      // GLOBAL: GAMEMD 0xAC11A0
extern NodeNameType* EasyAINode;      // GLOBAL: GAMEMD 0xAC11A4
extern NodeNameType* MediumAINode;    // GLOBAL: GAMEMD 0xAC11A8
extern NodeNameType* HardAINode;      // GLOBAL: GAMEMD 0xAC11AC
extern NodeNameType* WaitingNode;     // GLOBAL: GAMEMD 0xAC11B0
extern NodeNameType* ObserverNode;    // GLOBAL: GAMEMD 0xAC11B4

// GLOBAL: GAMEMD 0xA8D610 — the empty/blank wide name the two name predicates
// test a node against.
extern wchar_t BlankName[];
// GLOBAL: GAMEMD 0xA8B380 — the local player's handle, ANSI.
extern char LocalHandle[];
// GLOBAL: GAMEMD 0xA8B238 — the session kind; 4 selects the reduced slot count.
extern int SessionKind;
// GLOBAL: GAMEMD 0x8316A4 — set when the extra slot is unavailable.
extern int NoExtraSlot;
// GLOBAL: GAMEMD 0xA8B548 — the map's player limit.
extern int MapPlayerLimit;
// GLOBAL: GAMEMD 0xA8BB0C — the session's player limit.
extern int SessionPlayerLimit;
// GLOBAL: GAMEMD 0xAC0AC8 / 0xAC0AEC / 0xAC0EA4 / 0xAC0B10 — the four lobby
// dirty flags cleared together.
extern bool DirtyFlagA;
extern bool DirtyFlagB;
extern bool DirtyFlagC;
extern bool DirtyFlagD;
// GLOBAL: GAMEMD 0xAC0D44 / 0xAC0B94 — two 16-bit lobby counters zeroed with
// the full reset.
extern short CounterA;
extern short CounterB;

// GLOBAL: GAMEMD 0xA8B250 — a lobby list the full reset empties.
struct LobbyList_005E8B60
{
    // FUNCTION: GAMEMD 0x69B540 (decl; reloc) — __thiscall, no arguments; clears +0x24
    // and the two eight-entry tables at +0x4C and +0x6C.
    void Clear();

    int unknown_00;   // +0x00 the identifier of the selected game mode (netshare 0x5E2F80 and others)
};
GG_STATIC_ASSERT(offsetof(LobbyList_005E8B60, unknown_00) == 0x0);
extern LobbyList_005E8B60 DAT_00A8B250;

extern "C" {
// GLOBAL: GAMEMD 0x8317D8 — "D:\\ra2mdpost\\netshare.cpp", the retail source
// file name the string-table fetches carry along with their line numbers.
extern char NetshareFileName[];
// The seven string-table labels, ASCII, at 0x831C80, 0x831C74, 0x831C68,
// 0x831C58, 0x831C4C, 0x831C40 and 0x831C2C.
extern char OpenLabel[];
extern char ClosedLabel[];
extern char EasyAILabel[];
extern char MediumAILabel[];
extern char HardAILabel[];
extern char WaitingLabel[];
extern char ObserverLabel[];

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) — the string-table fetch. __fastcall
// with the label in ECX and a zero in EDX, then the source file and line as
// callee-cleaned stack arguments (no `ADD ESP,8` follows any of the seven
// calls in 0x5E87A0).
wchar_t* Fetch_String_00734E60(const char* label, int flag,
                               const char* file, int line);
// FUNCTION: GAMEMD 0x7CA489 (decl; reloc) — CRT wcscpy.
wchar_t* __cdecl wcscpy(wchar_t* dst, const wchar_t* src);

// FUNCTION: GAMEMD 0x5E87A0 — declared inside this C-linkage block on
// purpose. Under /GX (the tree's flag set when this was measured), the
// `new NodeNameType` inside it emits a full
// unwind frame (PUSH -1 / FS:[0] chain) that retail has no trace of when the
// function has C++ linkage, and none at all when it has C linkage. That is
// worth 17.5% against 100%, and `throw()` on the member constructor does not
// substitute for it.
void Build_Slot_Nodes();

// FUNCTION: GAMEMD 0x5C6120 (decl; reloc) — delete every item of the vector,
// then its virtual at slot +0xC. Written as a free __fastcall so the trailing
// call at 0x5E8AD1 stays the tail JMP retail has.
void Clear_Nodes_005C6120(NodeNameVector* vector);
// FUNCTION: GAMEMD 0x735120 (decl; reloc) — ANSI to wide, __fastcall.
wchar_t* Widen_00735120(const char* text);
// FUNCTION: GAMEMD 0x7350C0 (decl; reloc) — wide to ANSI, __fastcall.
char* Narrow_007350C0(const wchar_t* text);
// FUNCTION: GAMEMD 0x77D940 (decl; reloc) — session predicate, byte result.
bool __cdecl Is_005E8AE0_A();
// FUNCTION: GAMEMD 0x77D970 (decl; reloc) — session predicate, byte result.
bool __cdecl Is_005E8AE0_B();
}

// --- the run ---------------------------------------------------------------

int Node_Is_Blank_At(int index);
int Local_Handle_Is_Blank();
int Name_Is_Local_Handle(const wchar_t* name);
void Destroy_Slot_Nodes();
void Reset_Slots();
void Clear_Lobby_Flags();
void Reset_Lobby();
NodeNameType* Find_Node_By_Name(const wchar_t* name);
int Find_Slot_By_Name(const wchar_t* name);
int Find_Local_Player_Slot();
void Set_Slot_Node(int index, NodeNameType* node);
void Select_Slot(int index);
int Assign_Node_To_Slot(NodeNameType* node);
void Release_Slot_By_Address(const IPXAddressClass* address);
void Release_Slot_By_Handle(const char* handle);
int Is_Player_Node(NodeNameType* node);
int Is_AI_Node(NodeNameType* node);
int Is_Occupied_Node(NodeNameType* node);
int AI_Difficulty_Of(NodeNameType* node);
int Count_AI_Slots();
bool No_Open_Slot();
bool No_Observer_Slot();

#endif  // GG_MATCH_ECONOMY_NETSHARE_SLOT_NODES_H
