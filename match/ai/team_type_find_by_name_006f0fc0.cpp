// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x6F0FC0, read instruction by instruction from gamemd.exe v1.001: scans the TeamType
// array (items at 0xA8ECA4, count at 0xA8ECB0) for a case-insensitive match on the ID (+0x24)
// or the name (+0x64).
#include "../core/type_find_or_allocate_family_methods.h"

// FUNCTION: GAMEMD 0x6F0FC0
// Returns the team type whose ID or name equals the text, or null.
TypeClass_006F1920* __fastcall FUN_006F0FC0(const char* text)
{
    if (text != 0) {
        for (int i = 0; i < TypeClass_006F1920_Array.Count; i++) {
            if (gg_strcmpi(text, TypeClass_006F1920_Array.Items[i]->ID.Data) == 0
                || gg_strcmpi(text, TypeClass_006F1920_Array.Items[i]->Name.Data) == 0) {
                return TypeClass_006F1920_Array.Items[i];
            }
        }
    }
    return 0;
}
