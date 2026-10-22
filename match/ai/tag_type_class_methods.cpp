// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp (reconfirmed).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6E5E70  TagTypeClass::FindByNameOrID  (__fastcall)
//   GLOBAL:   GAMEMD 0xB0E780  TagTypes  (DynamicVectorClass<TagTypeClass*>)
//   LIBRARY:  GAMEMD 0x7C8D20  _strcmpi  (CRT; excluded from match target)

#include "tag_type_class_methods.h"

// --- referenced retail callee (declared, no body => reloc-normalised CALL) ---
extern "C" int __cdecl _strcmpi(const char*, const char*);


// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6E5E70  (__fastcall — name in ECX)
//
// Linear case-insensitive lookup of `name` in TagTypes, matching
// either the entry's ID (+0x24) or its Name (+0x64). Returns the entry pointer,
// or null. Count/Items are reloaded from the global each iteration.
// ---------------------------------------------------------------------------
TagTypeClass* TagTypeClass::FindByNameOrID(const char* name)
{
    if (name)
    {
        for (int i = 0; i < TagTypes.Count; ++i)
        {
            TagTypeClass* item = TagTypes.Items[i];
            if (_strcmpi(item->ID, name) == 0 ||
                _strcmpi(item->Name, name) == 0)
                return item;
        }
    }
    return 0;
}
