// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
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
// GLOBAL: GAMEMD 0xB0E780 TagTypeClass::Array (Items +4, Count +0x10).
// Calls constructor 0x6E5B60; sizeof(TagTypeClass) 0xA4.
TagTypeClass* __fastcall TagTypeClass::FindOrAllocate(const char* id)
{
    if (_strcmpi("<none>", id) != 0 && _strcmpi("none", id) != 0)
    {
        for (int i = 0; i < TagTypeClass::Array.Count; ++i)
        {
            if (_strcmpi(TagTypeClass::Array.Items[i]->ID, id) == 0)
                return TagTypeClass::Array.Items[i];
        }
        return new TagTypeClass(id);
    }
    return 0;
}
// FUNCTION: GAMEMD 0x00727AA0 (entry through RET at 0x727B22, 0x83 bytes)
// GLOBAL: GAMEMD 0x8B4178 TriggerTypeClass::Array (Items +4, Count +0x10).
// Calls constructor 0x726C80; sizeof(TriggerTypeClass) 0xB4.
TriggerTypeClass* __fastcall TriggerTypeClass::FindOrAllocate(const char* id)
{
    if (_strcmpi("<none>", id) != 0 && _strcmpi("none", id) != 0)
    {
        for (int i = 0; i < TriggerTypeClass::Array.Count; ++i)
        {
            if (_strcmpi(reinterpret_cast<TriggerTypeClass**>(TriggerTypeClass::Array.Items)[i]->ID, id) == 0)
                return reinterpret_cast<TriggerTypeClass**>(TriggerTypeClass::Array.Items)[i];
        }
        return new TriggerTypeClass(id);
    }
    return 0;
}
