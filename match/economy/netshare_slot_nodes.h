// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check | EA-GPL-RA1-reference
//   Every offset, global address and calling convention below was read
//   numerically off the user's retail gamemd.exe v1.001 with the local Ghidra
//   CLI over the run 0x5E8740..0x5E957E. The private-reference seed
//   (the private worklist seed, economy/slot_*.cpp) supplied only the
//   grouping and a hint at what each entry point is for; nothing was
//   transcribed and every width it gave was re-derived (its `bool` returns are
//   `int` here wherever retail exits through `MOV EAX,1` / `XOR EAX,EAX`
//   rather than the byte form). The RA1 tree was consulted for the shape of
//   NodeNameType / IPXAddressClass / DynamicVectorClass only, never copied.
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
//   * The vector at 0xA8DA74 is RA1's DynamicVectorClass: the destroy helper
//     0x5C6120 walks `[ESI+0x10]` items out of `[ESI+4]` and then calls the
//     virtual at vtable slot +0xC, so +0x00 is the vptr, +0x04 the item array
//     and +0x10 the active count. Only those two members are read here.
//
// Reviewed against docs/matching_methodology_and_toolchain.md batch forty-one
// (the free-`__fastcall`-with-a-receiver debt) and deliberately LEFT as free
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
// FUNCTION: GAMEMD 0x7DD0F8 (decl; reloc) — CRT _wcsicmp.
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
    unsigned char unknown_6F[0x16];   // +0x6F
};
#pragma pack(pop)

GG_STATIC_ASSERT(offsetof(NodeNameType, Address) == 0x28 &&
                 offsetof(NodeNameType, unknown_34) == 0x34 &&
                 offsetof(NodeNameType, unknown_6B) == 0x6B &&
                 sizeof(NodeNameType) == 0x85);

// ---------------------------------------------------------------------------
// RA1's DynamicVectorClass, only the two members this run reads.
// ---------------------------------------------------------------------------
struct NodeNameVector
{
    void* unknown_00;                 // +0x00  vptr
    NodeNameType** Vector;            // +0x04
    unsigned char unknown_08[8];      // +0x08
    int ActiveCount;                  // +0x10
    int unknown_14;                   // +0x14

};

GG_STATIC_ASSERT(offsetof(NodeNameVector, Vector) == 0x04 &&
                 offsetof(NodeNameVector, ActiveCount) == 0x10 &&
                 sizeof(NodeNameVector) == 0x18);

// --- globals ---------------------------------------------------------------

// GLOBAL: GAMEMD 0xA8DA74 — the lobby's player node vector (Vector at
// 0xA8DA78, ActiveCount at 0xA8DA84).
extern NodeNameVector PlayerNodes;
// GLOBAL: GAMEMD 0xA8DA8C — the slot index the local player picked, -1 when none.
extern int SelectedSlotIndex;
// GLOBAL: GAMEMD 0xA8DA90 — the eight lobby slots. The loops compare the
// walking pointer against 0xA8DAB0, i.e. &Slots[8].
extern NodeNameType* Slots[8];

// GLOBAL: GAMEMD 0xAC117C..0xAC1194 — the seven slot-state captions, fetched
// from the string table as "GUI:Open", "GUI:Closed", "GUI:AIEasy",
// "GUI:AINormal", "GUI:AIHard", "GUI:Waiting", "GUI:OpenObserver".
extern wchar_t* OpenText;         // GLOBAL: GAMEMD 0xAC117C
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
    // FUNCTION: GAMEMD 0x69B540 (decl; reloc) — __thiscall, no arguments.
    void Clear();
};
extern LobbyList_005E8B60 LobbyList;

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
wchar_t* __fastcall Fetch_String_00734E60(const char* label, int flag,
                                          const char* file, int line);
// FUNCTION: GAMEMD 0x7CA489 (decl; reloc) — CRT wcscpy.
wchar_t* __cdecl wcscpy(wchar_t* dst, const wchar_t* src);

// FUNCTION: GAMEMD 0x5E87A0 — declared inside this C-linkage block on
// purpose. Under the locked /GX, the `new NodeNameType` inside it emits a full
// unwind frame (PUSH -1 / FS:[0] chain) that retail has no trace of when the
// function has C++ linkage, and none at all when it has C linkage. That is
// worth 17.5% against 100%, and `throw()` on the member constructor does not
// substitute for it.
void __fastcall Build_Slot_Nodes();

// FUNCTION: GAMEMD 0x5C6120 (decl; reloc) — delete every item of the vector,
// then its virtual at slot +0xC. Written as a free __fastcall so the trailing
// call at 0x5E8AD1 stays the tail JMP retail has.
void __fastcall Clear_Nodes_005C6120(NodeNameVector* vector);
// FUNCTION: GAMEMD 0x735120 (decl; reloc) — ANSI to wide, __fastcall.
wchar_t* __fastcall Widen_00735120(const char* text);
// FUNCTION: GAMEMD 0x7350C0 (decl; reloc) — wide to ANSI, __fastcall.
char* __fastcall Narrow_007350C0(const wchar_t* text);
// FUNCTION: GAMEMD 0x77D940 (decl; reloc) — session predicate, byte result.
bool __cdecl Is_005E8AE0_A();
// FUNCTION: GAMEMD 0x77D970 (decl; reloc) — session predicate, byte result.
bool __cdecl Is_005E8AE0_B();
}

// --- the run ---------------------------------------------------------------

int __fastcall Node_Is_Blank_At(int index);
int __fastcall Local_Handle_Is_Blank();
int __fastcall Name_Is_Local_Handle(const wchar_t* name);
void __fastcall Destroy_Slot_Nodes();
void __fastcall Reset_Slots();
void __fastcall Clear_Lobby_Flags();
void __fastcall Reset_Lobby();
NodeNameType* __fastcall Find_Node_By_Name(const wchar_t* name);
int __fastcall Find_Slot_By_Name(const wchar_t* name);
int __fastcall Find_Local_Player_Slot();
void __fastcall Set_Slot_Node(int index, NodeNameType* node);
void __fastcall Select_Slot(int index);
int __fastcall Assign_Node_To_Slot(NodeNameType* node);
void __fastcall Release_Slot_By_Address(const IPXAddressClass* address);
void __fastcall Release_Slot_By_Handle(const char* handle);
int __fastcall Is_Player_Node(NodeNameType* node);
int __fastcall Is_AI_Node(NodeNameType* node);
int __fastcall Is_Occupied_Node(NodeNameType* node);
int __fastcall AI_Difficulty_Of(NodeNameType* node);
int __fastcall Count_AI_Slots();
bool __fastcall No_Open_Slot();
bool __fastcall No_Observer_Slot();

#endif  // GG_MATCH_ECONOMY_NETSHARE_SLOT_NODES_H
