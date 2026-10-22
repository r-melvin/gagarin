// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x476EB0. Name from
//   YRpp.

#include "ccini_class_techno_type_methods.h"

// FUNCTION: GAMEMD 0x476EB0
//
// Read a key as a techno-type name and resolve it against the four type
// lists in turn -- aircraft, building, infantry, unit. The first list that
// knows the name wins; an unknown (or "<none>") name yields a null pointer.
TechnoTypeClass* CCINIClass::GetTechnoType(const char* section, const char* key)
{
    char buffer[0x80];
    int  index;
    TechnoTypeClass* result = 0;

    this->ReadString(section, key, "<none>", buffer, sizeof(buffer));

    index = FUN_00523C90(buffer);
    if (index != -1) {
        result = DAT_00A8E34C[index];
    } else {
        index = FUN_00747370(buffer);
        if (index != -1) {
            result = DAT_00A83CE4[index];
        } else {
            index = FUN_0041CAA0(buffer);
            if (index != -1) {
                result = DAT_00A8B21C[index];
            } else {
                index = FUN_0045E7B0(buffer);
                if (index != -1)
                    result = DAT_00A83C6C[index];
            }
        }
    }

    return result;
}
