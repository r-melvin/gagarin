// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#ifndef GG_DIALOG_005D3490_H
#define GG_DIALOG_005D3490_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x82083C -- an int (reads 0x20); its address seeds the dialog.
extern int DAT_0082083C;

// The 4-byte local the dialog runs on: one pointer, set to &DAT_0082083C.
struct Dialog_005D3490
{
    int* unknown_00;   // +0x00

    Dialog_005D3490() : unknown_00(&DAT_0082083C) {}

    // FUNCTION: GAMEMD 0x5D3490 (decl; reloc) -- show a message with up to
    // three buttons; RET 0x14, returns the button index. The fifth argument
    // is not visible here (0 at this call).
    int FUN_005D3490(const wchar_t* message, const wchar_t* b1,
                     const wchar_t* b2, const wchar_t* b3, int a5);
};
GG_STATIC_ASSERT(sizeof(Dialog_005D3490) == 4);

GG_STATIC_ASSERT(offsetof(Dialog_005D3490, unknown_00) == 0);
#endif
