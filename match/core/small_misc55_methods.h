// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, element stride and call targets read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x4022C0 and
//   0x42F180.
#ifndef GG_MATCH_CORE_SMALL_MISC55_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC55_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// 0x4022C0 — refresh the cached triple.
//
// An installed override at +0xB0 takes precedence: it is called with no
// arguments and a non-zero answer means "handled", which clears the triple and
// is itself the return value. With no override the node at +0x16C is advanced
// and its two fields cached; anything missing along the way clears only +0x174
// and answers zero.
//
// +0x174 is written on every path, which is why its store sits in the shared
// block the two failures fall into.
// ---------------------------------------------------------------------------
struct Node_004022C0
{
    char _pad000[0xC];
    int  First;    // +0x000C
    int  Second;   // +0x0010
};
GG_STATIC_ASSERT(offsetof(Node_004022C0, Second) == 0x10);

// FUNCTION: GAMEMD 0x407470 — advance the node, __fastcall.
Node_004022C0* FUN_00407470(Node_004022C0* node);

typedef int (__cdecl* Override_004022C0)();

struct Obj_004022C0
{
    char              _pad000[0xB0];
    Override_004022C0 Override;   // +0x00B0
    char              _pad0B4[0x16C - 0xB4];
    Node_004022C0*    Node;       // +0x016C
    int               CachedA;    // +0x0170
    int               CachedB;    // +0x0174
    int               CachedC;    // +0x0178
};
GG_STATIC_ASSERT(offsetof(Obj_004022C0, Override) == 0xB0);
GG_STATIC_ASSERT(offsetof(Obj_004022C0, Node) == 0x16C);
GG_STATIC_ASSERT(offsetof(Obj_004022C0, CachedC) == 0x178);

// FUNCTION: GAMEMD 0x4022C0
int FUN_004022C0(Obj_004022C0* self);

// ---------------------------------------------------------------------------
// 0x42F180 — stream a counted table of 16-byte records.
//
// The count goes out first, then each record contributes one dword and two
// words. `ADD EDI,0x10` pins the stride and the `MOV CX,word ptr [EAX+EDI+4]` /
// `[EDX+EDI+6]` pair pins the two 16-bit fields; the base pointer is re-read
// from +0x08 before each of the three, and the count re-read from +0x14 as the
// loop bound.
// ---------------------------------------------------------------------------
struct Record_0042F180
{
    int   Value;   // +0x0000
    short Low;     // +0x0004
    short High;    // +0x0006
    char  _pad008[0x10 - 0x08];
};
GG_STATIC_ASSERT(sizeof(Record_0042F180) == 0x10);

struct Sink_0042F180
{
    // FUNCTION: GAMEMD 0x4A1D50 — write a dword.
    void FUN_004A1D50(int value);
    // FUNCTION: GAMEMD 0x4A1D30 — write a word.
    void FUN_004A1D30(short value);
};

struct Table_0042F180
{
    char             _pad000[0x8];
    Record_0042F180* Records;   // +0x0008
    char             _pad00C[0x14 - 0x0C];
    int              Count;     // +0x0014

    // FUNCTION: GAMEMD 0x42F180
    void FUN_0042F180(Sink_0042F180* sink);
};
GG_STATIC_ASSERT(offsetof(Table_0042F180, Records) == 0x8);
GG_STATIC_ASSERT(offsetof(Table_0042F180, Count) == 0x14);

#endif  // GG_MATCH_CORE_SMALL_MISC55_METHODS_H
