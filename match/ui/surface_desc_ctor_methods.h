// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x433880. The rectangle at +0x30 is identified by the
//   SetRect import call (`CALL DWORD PTR [0x7E14B4]` with the address of +0x30
//   and four zeroes), which fixes it at 0x10 bytes and puts the two flag bytes
//   immediately after it at +0x40/+0x41.
#ifndef GG_MATCH_UI_SURFACE_DESC_CTOR_METHODS_H
#define GG_MATCH_UI_SURFACE_DESC_CTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7E3A78
extern void* const VTBL_007E3A78[];

struct Rect_00433880 { int Left, Top, Right, Bottom; };
GG_STATIC_ASSERT(sizeof(Rect_00433880) == 0x10);

// USER32, dllimport so the call goes indirect through the IAT thunk at 0x7E14B4.
extern "C" __declspec(dllimport) int __stdcall SetRect(Rect_00433880* rect,
                                                       int left, int top,
                                                       int right, int bottom);

// What 0x433990 resolves the argument to. Only the two fields the constructor
// copies out are modelled.
struct Info_00433880
{
    char _pad000[0x4];       // +0x0000
    int  Width;              // +0x0004
    char _pad008[0x4];       // +0x0008
    int  Height;             // +0x000C
};
GG_STATIC_ASSERT(offsetof(Info_00433880, Height) == 0xC);

struct Key_00433880;

// FUNCTION: GAMEMD 0x433990 — resolve the key to an info block, or null.
Info_00433880* __fastcall FUN_00433990(Key_00433880* key);

// RTTI-confirmed (Tier 1, re-verified independently against the user's own
// binary): vtable 0x7E3A78's complete object locator (at 0x7E3A74) resolves to
// type descriptor 0x818B68, name string `.?AVBitFont@@`. This TU's minimal
// view of BitFont carries only the fields this constructor touches, matching
// the sibling minimal views in bit_text_ctor_methods.h / bit_text_print_methods.h.
struct BitFont
{
    const void* Vptr;        // +0x0000
    Info_00433880* Info;     // +0x0004
    int  At_08;              // +0x0008
    int  At_0C;              // +0x000C
    char _pad010[0x8];       // +0x0010
    int  Width;              // +0x0018
    int  Height;             // +0x001C
    int  At_20;              // +0x0020
    short At_24;             // +0x0024
    short At_26;             // +0x0026
    int  At_28;              // +0x0028
    int  At_2C;              // +0x002C
    Rect_00433880 Rect;      // +0x0030
    char At_40;              // +0x0040
    char At_41;              // +0x0041

    // Defined inline and called from both arms: retail emits the same thirteen
    // stores twice, once before the lookup and once when it fails, and the
    // second copy does not repeat the vptr store — so the vptr is the
    // constructor's own and the rest is a shared reset.
    void Reset()
    {
        int zero = 0;
        int one = 1;

        this->Info = (Info_00433880*)zero;
        this->At_24 = 0x7FFF;
        this->At_26 = 0x3555;
        this->At_28 = 0x40;
        this->At_40 = (char)one;
        this->At_41 = (char)one;
        this->Width = one;
        this->Height = one;
        this->At_20 = zero;
        this->At_0C = zero;
        this->At_08 = zero;
        SetRect(&this->Rect, zero, zero, zero, zero);
        this->At_2C = one;
    }

    // FUNCTION: GAMEMD 0x434700
    void FUN_00434700();

    // FUNCTION: GAMEMD 0x433880
    BitFont(Key_00433880* key);
};
GG_STATIC_ASSERT(offsetof(BitFont, Width) == 0x18);
GG_STATIC_ASSERT(offsetof(BitFont, At_24) == 0x24);
GG_STATIC_ASSERT(offsetof(BitFont, Rect) == 0x30);
GG_STATIC_ASSERT(offsetof(BitFont, At_40) == 0x40);

#endif  // GG_MATCH_UI_SURFACE_DESC_CTOR_METHODS_H
