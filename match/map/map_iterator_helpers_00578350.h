// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; gamemd.exe v1.001, REA evidence IDs
// ev_e05e00a27d16a257c5724358f1903184922c1cc7710d6be15822a900b0314c8f,
// ev_7b1be62e932396f417ee84510d2c282c54462f4999676572539a389af7a039c9,
// ev_00790bd64714f953cce6be91948d4f24ee987a6d1f38b618221a9cd12f4c1f84,
// and ev_16274bbb748eff1dd0e623342c0ffc63d1f7ec695a8089d2446a71b19c1474ee.
#ifndef GG_MAP_ITERATOR_HELPERS_00578350_H
#define GG_MAP_ITERATOR_HELPERS_00578350_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Prefix views only; full object allocation sizes are not inferred here.
struct MapIterator_00578350 {
    char unknown_000[0xF4];
    int cellCount; // +0xF4
    char unknown_0F8[0xFC - 0xF8];
    int stepBase; // +0xFC
    int stepOffset; // +0x100
    char unknown_104[0x10C - 0x104];
    int iterState; // +0x10C
    int iterCount; // +0x110
    int iterLast; // +0x114
    int iterCursor; // +0x118
    int iterNext; // +0x11C
    int iterLimit; // +0x120
    char unknown_124[0x13C - 0x124];
    int cellBase; // +0x13C
    void FUN_00578350();
    void FUN_00578850();
};
GG_STATIC_ASSERT(offsetof(MapIterator_00578350, cellCount) == 0xF4);
GG_STATIC_ASSERT(offsetof(MapIterator_00578350, stepBase) == 0xFC);
GG_STATIC_ASSERT(offsetof(MapIterator_00578350, stepOffset) == 0x100);
GG_STATIC_ASSERT(offsetof(MapIterator_00578350, iterState) == 0x10C);
GG_STATIC_ASSERT(offsetof(MapIterator_00578350, iterCount) == 0x110);
GG_STATIC_ASSERT(offsetof(MapIterator_00578350, iterLast) == 0x114);
GG_STATIC_ASSERT(offsetof(MapIterator_00578350, iterCursor) == 0x118);
GG_STATIC_ASSERT(offsetof(MapIterator_00578350, iterNext) == 0x11C);
GG_STATIC_ASSERT(offsetof(MapIterator_00578350, iterLimit) == 0x120);
GG_STATIC_ASSERT(offsetof(MapIterator_00578350, cellBase) == 0x13C);

GG_STATIC_ASSERT(sizeof(MapIterator_00578350) == 0x140);

#include "screenredraw_00578ac0.h"

// FUNCTION: GAMEMD 0x578D60
unsigned char FUN_00578D60(int value);
// GLOBAL: GAMEMD 0xABAD28
extern int DAT_00ABAD28;
#endif
