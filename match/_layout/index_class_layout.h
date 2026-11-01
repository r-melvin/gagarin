// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// The index members of INIClass (+0x28) and INISection (+0x2C). Their layout, Clear and destructor are the
// canonical IndexClass<T, U> (index.h); the value type is the four-byte placeholder because the code reached
// from these owners only frees and zeroes the index. Retail constructs it through an out-of-line call (0x49EA10,
// from the INIClass constructor expanded at 0x5D5C07), which an inline template constructor cannot reproduce
// (VC6 ignores an explicit-specialisation declaration and expands the primary), so this thin class carries the
// constructor declaration only.
#ifndef GG_MATCH_LAYOUT_INDEX_CLASS_LAYOUT_H
#define GG_MATCH_LAYOUT_INDEX_CLASS_LAYOUT_H
#include "index.h"
struct IndexClassRaw : public IndexClass<int, void*>
{
    // FUNCTION: GAMEMD 0x49EA10 (decl; reloc) -- zero all five fields.
    IndexClassRaw();
};
GG_STATIC_ASSERT(sizeof(IndexClassRaw) == 0x14);
#endif
