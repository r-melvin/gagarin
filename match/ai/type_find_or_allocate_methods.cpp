// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// /GX changes both bodies by adding the exception-cleanup path; no-GX
// reproduces the complete 131-byte retail spans. Evidence: focused entry-origin
// REA records ev_548001... and ev_11ba54... plus raw_match against pinned PE.
#include "../_layout/tag_type_class.h"
#include "../_layout/trigger_type_class.h"
#include <stddef.h>
// LIBRARY: GAMEMD 0x7C8D20 — CRT _strcmpi.
extern "C" int __cdecl _strcmpi(const char*, const char*);
// LIBRARY: GAMEMD 0x7C8E17 — global operator new(size_t).
// STRING: GAMEMD 0x817474 "<none>".
// STRING: GAMEMD 0x817694 "none".
// FUNCTION: GAMEMD 0x006E6310 (entry through RET at 0x6E6392, 0x83 bytes)
// GLOBAL: GAMEMD 0xB0E780 TagTypes (Items +4, Count +0x10).
// Calls constructor 0x6E5B60; sizeof(TagTypeClass) 0xA4.
TagTypeClass* TagTypeClass::FindOrAllocate(const char* id)
{
    if (_strcmpi("<none>", id) != 0 && _strcmpi("none", id) != 0)
    {
        for (int i = 0; i < TagTypes.Count; ++i)
        {
            if (_strcmpi(TagTypes.Items[i]->ID, id) == 0)
                return TagTypes.Items[i];
        }
        return new TagTypeClass(id);
    }
    return 0;
}
