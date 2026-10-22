// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x41F490.

#include "ai_trigger_save_list_methods.h"

// FUNCTION: GAMEMD 0x41F490
//
// Rewrite the AI trigger list into an INI. First every key already in the
// list section is walked, its value read into a small buffer, and the section
// named by that value cleared; then the list section itself is cleared; then
// every trigger type whose global flag matches the request writes itself back
// through its +0x68 virtual. A non-global (map) save also rewrites the enable
// section, one bool per trigger type keyed by its name.
//
// The key count is hoisted into a register for the first loop, but the
// section-name pointers are globals and are re-read after every call; the
// item loops re-read both the item table and the count each time round.
void AITriggerType_0041F490::SaveToINIList(CCINI_0041F490* ini, int isGlobal)
{
    char buffer[32];
    int  i;

    int count = ini->GetKeyCount(DAT_007E2A18);
    for (i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_007E2A18, i);
        ini->ReadString(DAT_007E2A18, key, STR_00889F64, buffer, 32);
        ini->Clear(buffer, 0);
    }
    ini->Clear(DAT_007E2A18, 0);

    for (i = 0; i < DAT_00A8B200.Count; i++) {
        AITriggerType_0041F490* item = DAT_00A8B200[i];
        if (item->IsGlobal == isGlobal) {
            (item->*item->Vtbl->At_68)(ini);
        }
    }

    if (isGlobal == 0) {
        ini->Clear(DAT_007E2A1C, 0);
        for (i = 0; i < DAT_00A8B200.Count; i++) {
            AITriggerType_0041F490* item = DAT_00A8B200[i];
            ini->WriteBool(DAT_007E2A1C, item->ID, item->IsEnabled);
        }
    }
}
