// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x7275D0.

// GX adds exception cleanup around native construction, absent from retail.
#include "trigger_type_class_load_methods.h"

// FUNCTION: GAMEMD 0x7275D0
//
// Read the trigger list out of an INI. Every key of the list section is a
// trigger ID: the two "no trigger" spellings are rejected, an existing trigger
// type with that ID is reused, and otherwise a new one is allocated and
// constructed. Whatever came out of that (retail dispatches through a null
// item too) is then asked to load itself through its +0x64 virtual.
//
// The key count is hoisted into a frame slot for the loop, but the section-name
// pointer is a global and is re-read after every call.
void TriggerTypeClass::LoadFromINIList(CCINI_007275D0* ini)
{
    int count = ini->GetKeyCount(DAT_007F58C8);
    for (int n = 0; n < count; n++) {
        const char* key = ini->GetKeyName(DAT_007F58C8, n);
        TriggerTypeClass* item;

        if (FUN_007C8D20(STR_00817474, key) != 0
            && FUN_007C8D20(STR_00817694, key) != 0) {

            int i = 0;
            while (i < TriggerTypeClass::Array.Count) {
                if (FUN_007C8D20(reinterpret_cast<TriggerTypeClass**>(TriggerTypeClass::Array.Items)[i]->ID, key) == 0) {
                    item = reinterpret_cast<TriggerTypeClass**>(TriggerTypeClass::Array.Items)[i];
                    goto have_item;
                }
                ++i;
            }

            item = new TriggerTypeClass(key);
            goto have_item;
        }

        item = 0;
have_item:
        TriggerTypeLoadCallView* view = reinterpret_cast<TriggerTypeLoadCallView*>(item);
        (view->*view->Vtable->LoadFromINI)(ini);
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x844A3C
extern const char STR_00844A3C[] = "Triggers";
// GLOBAL: GAMEMD 0x844A3C
extern const char STR_00844A3C[];
// GLOBAL: GAMEMD 0x844A3C
extern const char STR_00844A3C[];
// END defined globals
