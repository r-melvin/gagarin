// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6E5FE0.

#include "tag_type_class_save_methods.h"

// FUNCTION: GAMEMD 0x6E5FE0
//
// Rewrite the tag list into an INI. First every key already in the section is
// walked, its value read into a small buffer, and the section named by that
// value cleared; then the list section itself is cleared; then every live tag
// type is asked to write itself back through its +0x68 virtual.
//
// The key count is hoisted into a register for the first loop, but the
// section-name pointer is a global and is re-read after every call; the second
// loop re-reads both the item table and the count each time round.
void __fastcall TagTypeClass::SaveToINIList(CCINI_006E5FE0* ini)
{
    char buffer[32];
    int  i;

    int count = ini->GetKeyCount(DAT_007F4550);
    for (i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_007F4550, i);
        ini->ReadString(DAT_007F4550, key, STR_00889F64, buffer, 32);
        ini->Clear(buffer, 0);
    }
    ini->Clear(DAT_007F4550, 0);

    for (i = 0; i < TagTypeClass::Array.Count; i++) {
        TagTypeClass* item = reinterpret_cast<TagTypeClass**>(TagTypeClass::Array.Items)[i];
        TagTypeSaveCallView* view = reinterpret_cast<TagTypeSaveCallView*>(item);
        (view->*view->Vtable->Method)(ini);
    }
}
