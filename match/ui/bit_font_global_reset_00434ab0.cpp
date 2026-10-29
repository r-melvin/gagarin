// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra
//   The entry-bounded retail disassembly at 0x434AB0..0x434AC6 is exactly XOR
//   EAX,EAX; four absolute dword stores to 0x89C4C0..0x89C4CC; RET. Address
//   references to each global were confirmed independently in Ghidra.
#include "bit_font_global_reset_00434ab0.h"
#include "../core/mathtbl_init_shapes.h"

// SYNTHETIC: GAMEMD 0x00434AB0
// GLOBAL: GAMEMD 0x0089C4C0
MathTblZero4 DAT_0089C4C0;
