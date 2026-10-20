// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   ReadFromINI reconstructed from raw retail entry-point bytes at 0x6E6080;
//   WriteToINI from entry-point Ghidra disassembly at 0x6E6160.
//   Method names describe recovered behavior; retail has no function symbols.

#include "tag_type_class_ini_methods.h"

// FUNCTION: GAMEMD 0x6E6080
bool TagTypeClass::ReadFromINI(TagINI_006E6080* ini)
{
    char buffer[0x80];
    ini->Reset();
    if (ini->ReadString(DAT_007F4550, ID, STR_00889F64, buffer, sizeof(buffer))) {
        strtok(buffer, STR_00817F70);
        Persistence = FUN_007C9BFD(buffer);
        char* token = strtok(0, STR_00817F70);
        TagName_006E6080 name;
        if (!token) {
            name.Text[0] = 0;
        } else {
            strncpy(name.Text, token, 0x30);
            name.Text[0x30] = 0;
        }
        // Preserve the fixed-size value assignment, including its self check.
        // The compare operand order controls retail's CMP EAX,EDI spelling.
        if (&name != (TagName_006E6080*)Name) {
            *(TagName_006E6080*)Name = name;
        }
        FirstTrigger = FUN_00727AA0(strtok(0, STR_00817F70));
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6E6160
bool TagTypeClass::WriteToINI(TagINI_006E6080* ini)
{
    char buffer[0x80];
    // Each arm submits its formatted record; VC6 shares the call itself while
    // retaining the per-arm argument setup seen in the retail body.
    if (!FirstTrigger) {
        wsprintfA(buffer, STR_00842CD8, Name);
        ini->WriteString(DAT_007F4550, ID, buffer);
    } else {
        wsprintfA(buffer, STR_00842CCC, Persistence, Name,
                  FirstTrigger->ID);
        ini->WriteString(DAT_007F4550, ID, buffer);
    }
    return true;
}
