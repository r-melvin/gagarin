// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4251F0. The cell pair is sign-extended with MOVSX and scaled
//   by 0x100 with a half-cell 0x80 added, which is the standard cell-to-lepton
//   conversion; the third component is left at zero.
#ifndef GG_MATCH_COMBAT_SPAWN_EFFECT_METHODS_H
#define GG_MATCH_COMBAT_SPAWN_EFFECT_METHODS_H

#include <stddef.h>
#include "../_layout/session_class.h"
#include "../_rt/gg_static_assert.h"

struct Coord_004251F0
{
    int X;    // +0x0000
    int Y;    // +0x0004
    int Z;    // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_004251F0) == 0xC);

struct Rules_004251F0
{
    char _pad0000[0xF8C];     // +0x0000
    int  At_F8C;              // +0x0F8C
    char _pad0F90[0x5A0];     // +0x0F90
    int  At_1530;             // +0x1530
};
GG_STATIC_ASSERT(offsetof(Rules_004251F0, At_1530) == 0x1530);

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_004251F0* DAT_008871E0;

struct Queue_004251F0 { char opaque[4]; };
// GLOBAL: GAMEMD 0x885780
extern Queue_004251F0 DAT_00885780;

// FUNCTION: GAMEMD 0x48D080 — the callback the queue is given.
extern "C" void FUN_0048D080();

// FUNCTION: GAMEMD 0x489280
void FUN_00489280(Coord_004251F0* where, int a, int b, int c,
                  int d, int e);
// FUNCTION: GAMEMD 0x4A3C30
void FUN_004A3C30(Queue_004251F0* queue, int slot, void (*fn)());

// FUNCTION: GAMEMD 0x4251F0
//
// The first parameter is never read — retail overwrites ECX with the address of
// its own local before the call — so it keeps a placeholder name.
void FUN_004251F0(int unused, const short* cell);

#endif  // GG_MATCH_COMBAT_SPAWN_EFFECT_METHODS_H
