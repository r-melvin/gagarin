// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   All instruction order and field accesses follow the full retail entry at
//   0x434A40..0x434AA1. The call at +0x11 targets 0x7C93E8; the four calls at
//   +0x29/+0x39/+0x42/+0x54 target 0x7C8B3D, confirmed from rel32 bytes and
//   each target's entry disassembly. The member ABI is confirmed by the
//   vtable slot and one stack flags parameter; both helpers use caller cleanup.
#include "bit_font_scalar_dtor_00434a40.h"

// LIBRARY: GAMEMD 0x7C93E8 (decl; reloc) -- CRT free (the project-wide free symbol is
// bound to operator delete 0x7C8B3D by its other callers).
extern "C" void __cdecl FUN_007C93E8(void* block);
