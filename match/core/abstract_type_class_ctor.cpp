// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#include "../_layout/abstract_type_class.h"
#include "vector_class_operations.h"
#include "bounded_text.h"
#include <stdio.h>
#include "vector_add_item_free.h"
// GLOBAL: GAMEMD 0xA8E968
extern DynamicVectorClass<AbstractTypeClass*> DAT_00A8E968;
// GLOBAL: GAMEMD 0x887734
extern const wchar_t DAT_00887734[];
// STRING: GAMEMD 0x817830
extern const char STR_00817830[];
// FUNCTION: GAMEMD 0x734E60 (decl; reloc)
wchar_t* __fastcall StringTable_LoadString(const char*, int*, const char*, int);

// FUNCTION: GAMEMD 0x410800
AbstractTypeClass::AbstractTypeClass(const char* id)
{
    if (id == 0) {
        char generated[16];
        // STRING: GAMEMD 0x817828
        sprintf(generated, "%08X", this);
        GgBoundedText<25>(generated).CopyTo(ID);
    } else {
        GgBoundedText<25>(id).CopyTo(ID);
    }
    GgBoundedText<49>(ID).CopyTo(Name);
    UIName = DAT_00887734;
    DynamicVectorAddItemFree(&DAT_00A8E968, this);
}

