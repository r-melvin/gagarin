// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The pinned PE maps all 24 bytes at 0xB0E720 into .data's loader-zero tail.
// This raw storage definition does not install a vtable or invent startup
// constructors. Runtime initialization remains a separate recovery task.
#include "../_layout/tag_class.h"
GG_STATIC_ASSERT(sizeof(DynamicVectorClassLayout) == 0x18);
// GLOBAL: GAMEMD 0xB0E720
DynamicVectorClassLayout TagClass::Array;

// GLOBAL: GAMEMD 0xB0E700
// Four loader-zero bytes read by the TagClass constructor.
CellStruct DAT_00B0E700;
