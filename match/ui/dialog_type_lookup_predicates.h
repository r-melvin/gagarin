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

// The value object a node carries, starting at node+0x04. It spans the whole
// 0x200 bytes between the key and the chain pointer; only the fields retail
// touches are named, at the displacements of the instructions that use them.
struct MapValue_00602B90
{
    char _pad000[0x10];   // +0x0000
    struct Hook_006223C0* Field10;   // +0x0010
    int  Field14;         // +0x0014  (node +0x18)
    char _pad018[0x68 - 0x18];
    int  Field68;         // +0x0068
    int  Field6C;         // +0x006C  (node +0x70)
    int  Field70;         // +0x0070
    int  Field74;         // +0x0074
    char _pad078[0xB0 - 0x78];
    int  FieldB0;         // +0x00B0
    char _pad0B4[0xBC - 0xB4];
    bool FieldBC;         // +0x00BC
    bool FieldBD;         // +0x00BD
    bool FieldBE;         // +0x00BE
    char _pad0BF[0xC0 - 0xBF];
    int  FieldC0;         // +0x00C0
    char _pad0C4[0xD4 - 0xC4];
    bool FieldD4;         // +0x00D4
    bool FieldD5;         // +0x00D5
    bool FieldD6;         // +0x00D6
    bool FieldD7;         // +0x00D7
    bool FieldD8;         // +0x00D8
    char _pad0D9[0xDC - 0xD9];
    int  FieldDC;         // +0x00DC
    int  FieldE0;         // +0x00E0
    int  FieldE4;         // +0x00E4
    char _pad0E8[0x200 - 0xE8];
};
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, Field10) == 0x10);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, Field14) == 0x14);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, Field68) == 0x68);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, Field6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, Field70) == 0x70);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, Field74) == 0x74);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, FieldB0) == 0xB0);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, FieldBC) == 0xBC);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, FieldBD) == 0xBD);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, FieldBE) == 0xBE);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, FieldC0) == 0xC0);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, FieldD4) == 0xD4);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, FieldD5) == 0xD5);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, FieldD6) == 0xD6);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, FieldD7) == 0xD7);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, FieldD8) == 0xD8);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, FieldDC) == 0xDC);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, FieldE0) == 0xE0);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, FieldE4) == 0xE4);
GG_STATIC_ASSERT(sizeof(MapValue_00602B90) == 0x200);

// One hash-table node: key, value, then the chain pointer at +0x204.
struct MapNode_00602B90
{
    int                Key;                    // +0x0000
    MapValue_00602B90  Value;                  // +0x0004
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
    unsigned (* Hash)(const int* pKey);   // +0x0018
};
GG_STATIC_ASSERT(offsetof(HashMap_00602B90, Count) == 0x04);
GG_STATIC_ASSERT(offsetof(HashMap_00602B90, Shift) == 0x0C);
GG_STATIC_ASSERT(offsetof(HashMap_00602B90, Hash) == 0x18);

// GLOBAL: GAMEMD 0xAC1B00 — the hash table.
extern HashMap_00602B90 DAT_00AC1B00;

// FUNCTION: GAMEMD 0x602B90 (__fastcall)
bool FUN_00602B90(int nKey, GG_HWND hCtl);
// FUNCTION: GAMEMD 0x603240 (__fastcall)
int FUN_00603240(int nKey, GG_HWND hCtl);

#endif  // GG_MATCH_UI_DIALOG_TYPE_LOOKUP_PREDICATES_H
