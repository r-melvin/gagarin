// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes read from retail gamemd.exe v1.001 at 0x770CE0.
//   PLACEMENT LEAD (inference): its callers 0x7712C0 and 0x7714B0 (match/tu281_wdtvoice.cpp)
//   reach it by a real CALL. At /Ob2 cl inlines any body it can see, so the retail call
//   implies the body was compiled in a different original object than those callers. This
//   file is that separate object; the original file name is not known and is not claimed.
#include <stddef.h>
#include "string_class.h"

extern const char DAT_008491F0[];   // STRING: GAMEMD 0x8491F0 "WWD_Allied"
extern const char DAT_008491FC[];   // STRING: GAMEMD 0x8491FC "WWD-Soviet"

// FUNCTION: GAMEMD 0x7B6320 (decl; reloc) -- zero-padded decimal text of `value`, `width` digits.
Wstring __fastcall FUN_007B6320(int value, int width);
// FUNCTION: GAMEMD 0x7B63C0 (decl; reloc) -- `prefix` followed by `suffix`.
Wstring __fastcall FUN_007B63C0(const char* prefix, const Wstring& suffix);

// FUNCTION: GAMEMD 0x770CE0
bool __fastcall FUN_00770CE0(int side, int line, Wstring* out)
{
    if (side == 3) {
        *out = FUN_007B63C0(DAT_008491FC, FUN_007B6320(line, 2));
    } else {
        *out = FUN_007B63C0(DAT_008491F0, FUN_007B6320(line, 2));
    }
    return true;
}
