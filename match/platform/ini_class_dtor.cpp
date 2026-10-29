// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Complete entry-origin span 0x5256F0..0x5257B7, 200 bytes.
// Retail frees the index, drains the list, then destroys its two sentinels.
#include "../_layout/ini_class.h"
// SYNTHETIC: GAMEMD 0x4F2810
// Compiler-generated scalar deleting destructor, 30 bytes.

// FUNCTION: GAMEMD 0x5256F0
INIClass::~INIClass()
{
    Clear(0, 0);
    SectionIndex.Clear();
}
