// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Table shape and bounds read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x40DCB0 plus a raw dump of 0x00816EE0: 8-byte entries
//   of {const char* Name; int Key}, keys running 0..73, and the scan bounded by
//   `CMP EAX,0x00817134` — i.e. exactly 74 entries. The address the miss path
//   loads (0x00817130) is not a 75th entry: dumping it shows the literal bytes
//   "Unkn...", so it is the string constant stored immediately after the table.
#ifndef GG_MATCH_CORE_ABSTRACT_CLASS_RTTI_METHODS_H
#define GG_MATCH_CORE_ABSTRACT_CLASS_RTTI_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#define RTTI_NAME_COUNT 74

// GLOBAL: GAMEMD 0x00816EE0 — the AbstractType -> display-name table. The scan
// reads Key at +0x04 of each entry (retail starts its pointer at 0x00816EE4)
// and returns Name from +0x00.
struct RTTINameEntry
{
    const char* Name;   // +0x00
    int         Key;    // +0x04
};
GG_STATIC_ASSERT(offsetof(RTTINameEntry, Name) == 0x00);
GG_STATIC_ASSERT(sizeof(((RTTINameEntry*)0)->Name) == 4);
GG_STATIC_ASSERT(offsetof(RTTINameEntry, Key) == 0x04);
GG_STATIC_ASSERT(sizeof(((RTTINameEntry*)0)->Key) == 4);
GG_STATIC_ASSERT(sizeof(RTTINameEntry) == 0x08);

extern RTTINameEntry RTTINames[RTTI_NAME_COUNT];

// Static member declaration and object model come from the canonical class.
#include "../_layout/abstract_class.h"

#endif  // GG_MATCH_CORE_ABSTRACT_CLASS_RTTI_METHODS_H
