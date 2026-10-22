// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x727880.

#include "trigger_type_class_save_list_methods.h"

// FUNCTION: GAMEMD 0x727880
//
// Clear the three trigger sections and rewrite them. Each key in a section
// names a subsection, which is cleared with it; the section itself follows.
// The key names for all three are looked up in the Triggers section, which
// is where the per-trigger records live. Every registered trigger type then
// writes itself back.
//
// Each key name is bound to a local before the read: retail calls
// GetKeyName and only then pushes the read's own arguments, where the
// nested call form pushes the constants first.
void TriggerTypeClass::SaveToINIList(CCINI_00727880* ini)
{
    char buffer[0x20];
    int  i;

    int count = ini->GetKeyCount(DAT_007F58C8);
    for (i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_007F58C8, i);
        ini->ReadString(DAT_007F58C8, key, STR_00889F64, buffer, 0x20);
        ini->Clear(buffer, 0);
    }
    ini->Clear(DAT_007F58C8, 0);

    count = ini->GetKeyCount(DAT_007F58D0);
    for (i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_007F58D0, i);
        ini->ReadString(DAT_007F58C8, key, STR_00889F64, buffer, 0x20);
        ini->Clear(buffer, 0);
    }
    ini->Clear(DAT_007F58D0, 0);

    count = ini->GetKeyCount(DAT_007F58CC);
    for (i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_007F58CC, i);
        ini->ReadString(DAT_007F58C8, key, STR_00889F64, buffer, 0x20);
        ini->Clear(buffer, 0);
    }
    ini->Clear(DAT_007F58CC, 0);

    for (i = 0; i < TriggerTypeClass::Array.Count; i++) {
        TriggerTypeClass* item = reinterpret_cast<TriggerTypeClass**>(TriggerTypeClass::Array.Items)[i];
        TriggerTypeSaveCallView* view = reinterpret_cast<TriggerTypeSaveCallView*>(item);
        (view->*view->Vtable->Method)(ini);
    }
}
