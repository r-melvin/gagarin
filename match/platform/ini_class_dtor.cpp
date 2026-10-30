// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT
// Placement lead: ??_GINIClass (0x4F2810) belongs in the file that constructs an
// INIClass (0x4F1B80 stores the vtable; unmatched, 286 bytes), where only the
// destructor declaration is visible; until then this file avoids /Ob2, which
// would expand ~INIClass into it.
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
