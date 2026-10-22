// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 at 0x602B90 and
//   0x603240. Both take a key in ECX and a window handle in EDX with no stack
//   cleanup, so both are __fastcall. Both open with the same inlined hash-table
//   lookup and then test the looked-up value against the control's dialog ID.
//
//   Disasm-derived facts for the map (all absolute operands):
//     * 0xAC1B00 is the bucket array, 0xAC1B04 the entry count, 0xAC1B0C the
//       bucket-count shift and 0xAC1B18 a hash function pointer called with the
//       key's address in ECX and no stack cleanup — a __fastcall slot. They are
//       +0x00, +0x04, +0x0C and +0x18 of one object at 0xAC1B00, modelled as
//       such so the displacements ride inside the base relocation.
//     * The bucket index is `hash & ((1 << Shift) - 1)`, straight from
//       `MOV EDX,1; SHL EDX,CL; DEC EDX; AND EDX,EAX`.
//     * A node's key is its first dword (`CMP [EAX],ECX`) and its chain pointer
//       is at +0x204 (`MOV EAX,[EAX+0x204]`). The value object starts at +0x04
//       — the `ADD EAX,4` on the hit path — and the field read is [+0x6C] of
//       that object, i.e. +0x70 of the node.
//     * The pair of null tests around that `ADD EAX,4` is not redundant code:
//       it is what two nested guarded conversions compile to, and reproducing
//       both is what takes 0x603240 from a near-miss to byte-exact.
//     * `CALL [0x7E13B4]` is USER32!GetDlgCtrlID.
//     * Return widths differ and only the exit says so: 0x602B90 ends
//       `MOV AL,1` / `XOR AL,AL` (bool) while 0x603240 ends `MOV EAX,1` /
//       `XOR EAX,EAX` (a full dword).
//
//   Neither function touches audio, so the placeholders stay.
#ifndef GG_MATCH_UI_DIALOG_TYPE_LOOKUP_PREDICATES_H
#define GG_MATCH_UI_DIALOG_TYPE_LOOKUP_PREDICATES_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef void* GG_HWND;

// GLOBAL: GAMEMD 0x7E13B4 — __imp__GetDlgCtrlID.
extern "C" __declspec(dllimport) int __stdcall GetDlgCtrlID(GG_HWND hCtl);

// The value object a node carries, starting at node+0x04.
struct MapValue_00602B90
{
    char _pad000[0x6C];   // +0x0000
    int  Field6C;         // +0x006C  (node +0x70)
};
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, Field6C) == 0x6C);
GG_STATIC_ASSERT(sizeof(MapValue_00602B90) == 0x70);

// One hash-table node: key, value, then the chain pointer at +0x204.
struct MapNode_00602B90
{
    int                Key;                    // +0x0000
    MapValue_00602B90  Value;                  // +0x0004
    char               _pad074[0x204 - 0x74];
    MapNode_00602B90*  Next;                   // +0x0204
};
GG_STATIC_ASSERT(offsetof(MapNode_00602B90, Value) == 0x04);
GG_STATIC_ASSERT(offsetof(MapNode_00602B90, Next) == 0x204);

// The hash table itself. Only the four fields retail reads are named.
struct HashMap_00602B90
{
    MapNode_00602B90** Buckets;      // +0x0000
    int                Count;        // +0x0004
    int                unknown_08;   // +0x0008
    int                Shift;        // +0x000C
    int                unknown_10;   // +0x0010
    int                unknown_14;   // +0x0014
    unsigned (__fastcall* Hash)(const int* pKey);   // +0x0018
};
GG_STATIC_ASSERT(offsetof(HashMap_00602B90, Count) == 0x04);
GG_STATIC_ASSERT(offsetof(HashMap_00602B90, Shift) == 0x0C);
GG_STATIC_ASSERT(offsetof(HashMap_00602B90, Hash) == 0x18);

// GLOBAL: GAMEMD 0xAC1B00 — the hash table.
extern HashMap_00602B90 DAT_00AC1B00;

// FUNCTION: GAMEMD 0x602B90 (__fastcall)
bool __fastcall FUN_00602B90(int nKey, GG_HWND hCtl);
// FUNCTION: GAMEMD 0x603240 (__fastcall)
int __fastcall FUN_00603240(int nKey, GG_HWND hCtl);

#endif  // GG_MATCH_UI_DIALOG_TYPE_LOOKUP_PREDICATES_H
