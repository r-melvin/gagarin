// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x477640.

#include "ccini_class_abilities_methods.h"

// FUNCTION: GAMEMD 0x477640
//
// Read a comma-separated ability list. When the key is present each token is
// looked up by name and the matching flag set in a zeroed result; an absent
// key hands back the caller's default unchanged.
AbilitiesStruct CCINIClass::ReadAbilities(const char* section, const char* key,
                                          const AbilitiesStruct& def)
{
    char buffer[0x80];

    if (this->ReadString(section, key, DAT_00889F64, buffer, 0x80) != 0) {
        AbilitiesStruct result;
        memset(&result, 0, sizeof(result));

        char* token;
        for (token = strtok(buffer, DAT_00817F70); token != 0 && *token != 0;
             token = strtok(0, DAT_00817F70)) {
            int index = FUN_0074FEF0(token);
            if (index != -1) {
                result.Flags[index] = true;
            }
        }
        return result;
    }

    return def;
}
