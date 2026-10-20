// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The entry-bounded retail disassembly at 0x434AB0..0x434AC6 is exactly XOR
//   EAX,EAX; four absolute dword stores to 0x89C4C0..0x89C4CC; RET. Address
//   references to each global were confirmed independently in Ghidra.
#include "bit_font_global_reset_00434ab0.h"

// FUNCTION: GAMEMD 0x434AB0
void __stdcall FUN_00434AB0()
{
    DAT_0089C4C0 = 0;
    DAT_0089C4C4 = 0;
    DAT_0089C4C8 = 0;
    DAT_0089C4CC = 0;
}
