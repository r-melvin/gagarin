// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, strides and call targets read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x4074D0 and 0x4589C0.
#ifndef GG_MATCH_CORE_SMALL_MISC39_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC39_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void* __cdecl FUN_007C8E17(unsigned int size);   // operator new

// ---------------------------------------------------------------------------
// 0x4074D0 — allocate a block and thread every element onto a free list.
//
// The stride is the element size plus eight, and the block is one stride's
// header (`+8`) plus `count` strides. Each cell's first word points at the next
// one and the last holds null, so the returned block doubles as the list head.
// Both arguments arrive in registers (`MOV ESI,ECX` for the count and
// `LEA EDI,[EDX+8]` for the element size), so this is __fastcall.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x4074D0
void* FUN_004074D0(int count, int elementSize);

// ---------------------------------------------------------------------------
// 0x4589C0 — scale the stored total against a divisor.
//
// The storage sub-object at +0x33C is the already-matched StorageClass, whose
// GetTotalAmount @0x6C9650 returns a float; each use is followed by the CRT
// `_ftol` at 0x7C5F00, which is the `(int)` cast. Retail calls it twice - the
// zero test and the arithmetic each get their own call.
//
// The empty case returns the converted total itself rather than a fresh zero:
// retail's early exit has no `XOR EAX,EAX`, it just falls into the epilogue
// with _ftol's result still in EAX.
// ---------------------------------------------------------------------------
struct StorageStub_004589C0
{
    char _pad000[0x10];

    // FUNCTION: GAMEMD 0x6C9650  StorageClass::GetTotalAmount
    float GetTotalAmount() const;
};

struct Settings_004589C0
{
    char _pad000[0x800];
    int  Divisor;   // +0x0800
};
GG_STATIC_ASSERT(offsetof(Settings_004589C0, Divisor) == 0x800);

struct Obj_004589C0
{
    char                _pad000[0x33C];
    StorageStub_004589C0 Storage;    // +0x033C
    char                _pad34C[0x520 - 0x34C];
    Settings_004589C0*   Settings;   // +0x0520

    // FUNCTION: GAMEMD 0x4589C0
    int FUN_004589C0();
};
GG_STATIC_ASSERT(offsetof(Obj_004589C0, Storage) == 0x33C);
GG_STATIC_ASSERT(offsetof(Obj_004589C0, Settings) == 0x520);

// ---------------------------------------------------------------------------
// 0x4349B0 — a two-level table lookup returning one byte.
//
// The argument is masked to sixteen bits before indexing (`AND EDX,0xFFFF`), so
// it is an `unsigned short` parameter widened at the call. The word it selects
// is a one-based slot number; zero means "absent". The record address is then
// `Base + Stride * (slot - 1)`, and retail tests that sum for zero straight off
// the `ADD`'s own flags before dereferencing it.
//
// Both loads are zero-extending into a wider variable: `XOR EAX,EAX; MOV AX,..`
// for the word and `XOR ECX,ECX; MOV CL,..` for the byte.
// ---------------------------------------------------------------------------
struct Sub_004349B0
{
    char            _pad000[0x14];
    int             Stride;   // +0x0014
    unsigned short* Table;    // +0x0018
    unsigned char*  Base;     // +0x001C
};
GG_STATIC_ASSERT(offsetof(Sub_004349B0, Stride) == 0x14);
GG_STATIC_ASSERT(offsetof(Sub_004349B0, Table) == 0x18);
GG_STATIC_ASSERT(offsetof(Sub_004349B0, Base) == 0x1C);

struct Obj_004349B0
{
    char          _pad000[0x4];
    Sub_004349B0* Sub;   // +0x0004

    // FUNCTION: GAMEMD 0x4349B0
    int FUN_004349B0(unsigned short index);
};
GG_STATIC_ASSERT(offsetof(Obj_004349B0, Sub) == 0x4);

#endif  // GG_MATCH_CORE_SMALL_MISC39_METHODS_H
