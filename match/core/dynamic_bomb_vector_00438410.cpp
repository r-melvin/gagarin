// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Entry bytes, global addresses, RTTI names, table slots and call targets were
// confirmed in the retail gamemd.exe v1.001 by entry-bounded disassembly and
// Ghidra memory reads. RTTI TypeDescriptor 0x00816918 names the object at
// 0x89C668 DynamicVectorClass<BombClass*> (vtable 0x7E17CC, base vtable 0x7E17EC).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include "vector_class_operations.h"

class BombClass;

// SYNTHETIC: GAMEMD 0x00438550 -- initialiser: constructs DAT_0089C668, registers 0x438590.
// SYNTHETIC: GAMEMD 0x00438590 -- atexit cleanup: destroys DAT_0089C668.
// GLOBAL: GAMEMD 0x0089C668
DynamicVectorClass<BombClass*> DAT_0089C668;
