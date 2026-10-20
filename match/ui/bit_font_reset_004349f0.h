// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The 0x4349F0 entry reads ECX as the object pointer and writes offsets
//   +0x04 through +0x41. The same field initialization is independently
//   visible in BitFont constructor 0x433880, which stores the RTTI-confirmed
//   BitFont vtable 0x7E3A78. Its SetRect call uses IAT slot 0x7E14B4 and passes
//   the address of +0x30 plus four zero coordinates. The 0x44-byte object
//   allocation and constructor call are visible at 0x434AD3..0x434AEE.
#ifndef GG_MATCH_UI_BIT_FONT_RESET_004349F0_H
#define GG_MATCH_UI_BIT_FONT_RESET_004349F0_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Rect_004349F0
{
    int left;
    int top;
    int right;
    int bottom;
};
GG_STATIC_ASSERT(offsetof(Rect_004349F0, left) == 0);
GG_STATIC_ASSERT(offsetof(Rect_004349F0, top) == 4);
GG_STATIC_ASSERT(offsetof(Rect_004349F0, right) == 8);
GG_STATIC_ASSERT(offsetof(Rect_004349F0, bottom) == 12);
GG_STATIC_ASSERT(sizeof(Rect_004349F0) == 0x10);

// Address-specific object view; each member offset below is written by
// 0x4349F0, and offsets corroborate the BitFont constructor at 0x433880.
struct BitFontResetView_004349F0
{
    unsigned int unknown_00;
    unsigned int unknown_04;
    unsigned int unknown_08;
    unsigned int unknown_0C;
    unsigned int unknown_10;
    unsigned int unknown_14;
    unsigned int unknown_18;
    unsigned int unknown_1C;
    unsigned int unknown_20;
    unsigned short unknown_24;
    unsigned short unknown_26;
    unsigned int unknown_28;
    unsigned int unknown_2C;
    Rect_004349F0 unknown_30;
    unsigned char unknown_40;
    unsigned char unknown_41;
    unsigned short unknown_42;
};
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_26) == 0x26);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(BitFontResetView_004349F0, unknown_41) == 0x41);
GG_STATIC_ASSERT(sizeof(BitFontResetView_004349F0) == 0x44);

// LIBRARY: GAMEMD 0x7E14B4 — USER32 SetRect import; retail calls through this IAT slot.
extern "C" __declspec(dllimport) int __stdcall SetRect(
    Rect_004349F0* rect, int left, int top, int right, int bottom);

#endif  // GG_MATCH_UI_BIT_FONT_RESET_004349F0_H
