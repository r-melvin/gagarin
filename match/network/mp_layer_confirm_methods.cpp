// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x5C60D0, in the retail
//   block of MPLayer.CPP (its __FILE__ string 0x82E134 is the one passed to
//   the string-table loads below).

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x82083C -- an int (reads 0x20); its address seeds the dialog.
extern int DAT_0082083C;

// STRING: GAMEMD 0x825FB0 -- "TXT_OK".
extern const char STR_00825FB0[];
// STRING: GAMEMD 0x825FD0 -- "TXT_CANCEL".
extern const char STR_00825FD0[];
// STRING: GAMEMD 0x82E134 -- this module's __FILE__ ("D:\\ra2mdpost\\MPLayer.CPP").
extern const char STR_0082E134[];

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- StringTable::LoadString.
wchar_t* StringTable_LoadString(const char* label, int* out,
                                const char* file, int line);

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

// FUNCTION: GAMEMD 0x5C60D0
// Ask an OK / Cancel question; true when the first button (OK) was chosen.
bool FUN_005C60D0(const wchar_t* message)
{
    Dialog_005D3490 dialog;
    return dialog.FUN_005D3490(message,
                               StringTable_LoadString(STR_00825FB0, 0, STR_0082E134, 0x6C),
                               StringTable_LoadString(STR_00825FD0, 0, STR_0082E134, 0x6C),
                               0, 0) == 0;
}
