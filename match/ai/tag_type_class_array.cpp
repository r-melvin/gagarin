// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Pinned retail accesses use the 24-byte prefix at 0xB0E780.
// Loader-zero storage does not establish later runtime initialization.
#include "../_layout/tag_type_class.h"
GG_STATIC_ASSERT(sizeof(DynamicVectorClassLayout) == 0x18);
// GLOBAL: GAMEMD 0xB0E780
DynamicVectorClassLayout TagTypeClass::Array;
