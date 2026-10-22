// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6E5ED0.

// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Native construction under GX adds exception cleanup absent from retail.
#include "tag_type_class_load_list_methods.h"

// FUNCTION: GAMEMD 0x6E5ED0
//
// Read every tag out of the Tags section. A key that names nothing keeps a
// null tag; otherwise the existing tag type of that name is reused, or a
// new one built. Either way the name is registered and the tag loads its
// own record.
void __fastcall TagTypeClass::LoadFromINIList(CCINI_006E5ED0* ini)
{
    int count = ini->GetKeyCount(DAT_007F4550);
    for (int i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_007F4550, i);
        char buffer[0x18];
        if (ini->ReadString(DAT_007F4550, key, STR_00889F64, buffer, 0x18) > 0) {
            TagTypeClass* tag;
            if (gg_strcmp(STR_00817474, key) == 0
                || gg_strcmp(STR_00817694, key) == 0) {
                tag = 0;
            } else {
                for (int j = 0; j < TagTypes.Count; j++) {
                    if (gg_strcmp(TagTypes.Items[j]->ID, key) == 0) {
                        tag = TagTypes.Items[j];
                        goto have;
                    }
                }
                tag = new TagTypeClass(key);
            }
        have:
            FUN_006CF2C0(&DAT_00B0C110, FUN_00412610(key), tag);
            TagTypeLoadCallView* view = reinterpret_cast<TagTypeLoadCallView*>(tag);
            (view->*view->Vtable->Method)(ini);
        }
    }
}
