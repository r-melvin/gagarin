// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail 0x523C90: the name is tested against "<none>" (0x817474) and "none" (0x817694) with
//   _strcmpi (0x7C8D20), then compared with the ID (+0x24) of each entry of the infantry type
//   array at 0xA8E348 (Items +4, Count +0x10).

#include "../_layout/infantry_type_class.h"
#include "../core/vector_class.h"

// LIBRARY: GAMEMD 0x7C8D20 -- CRT _strcmpi.
extern "C" int __cdecl _strcmpi(const char*, const char*);

// GLOBAL: GAMEMD 0xA8E348 -- every InfantryTypeClass.
extern DynamicVectorClass<InfantryTypeClass*> DAT_00A8E348;

// FUNCTION: GAMEMD 0x523C90
int InfantryTypeClass::FUN_00523C90(const char* name)
{
    if (_strcmpi(name, "<none>") != 0 && _strcmpi(name, "none") != 0) {
        for (int i = 0; i < DAT_00A8E348.Count; i++) {
            if (_strcmpi(DAT_00A8E348.Items[i]->ID, name) == 0) {
                return i;
            }
        }
    }
    return -1;
}
