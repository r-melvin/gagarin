// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 0x410A60 selects the ID section, reads Name/UIName through a 1024-byte
// scratch buffer, then copies bounded temporaries into the fields. It resolves
// a nonempty UI label through 0x734E60 or uses the empty wide string.
#include "../_layout/abstract_type_class.h"
#include "../platform/ccini_class_methods.h"
#include <string.h>

// STRING: GAMEMD 0x817830 -- native source-file tag for the text lookup.
extern const char STR_00817830[];
// GLOBAL: GAMEMD 0x887734 -- shared empty wide string.
extern const wchar_t DAT_00887734[];
// FUNCTION: GAMEMD 0x734E60 (decl; reloc), ECX=label, EDX=output-or-null.
wchar_t* __fastcall StringTable_LoadString(const char* label, int* output,
                                               const char* file, int line);

#include "bounded_text.h"
GG_STATIC_ASSERT(sizeof(GgBoundedText<49>) == 49);
GG_STATIC_ASSERT(sizeof(GgBoundedText<32>) == 32);
GG_STATIC_ASSERT(offsetof(AbstractTypeClass, ID) == 0x24);
GG_STATIC_ASSERT(sizeof(((AbstractTypeClass*)0)->ID) == 25);
GG_STATIC_ASSERT(offsetof(AbstractTypeClass, UINameLabel) == 0x3D);
GG_STATIC_ASSERT(sizeof(((AbstractTypeClass*)0)->UINameLabel) == 32);
GG_STATIC_ASSERT(offsetof(AbstractTypeClass, UIName) == 0x60);
GG_STATIC_ASSERT(sizeof(((AbstractTypeClass*)0)->UIName) == 4);
GG_STATIC_ASSERT(offsetof(AbstractTypeClass, Name) == 0x64);
GG_STATIC_ASSERT(sizeof(((AbstractTypeClass*)0)->Name) == 49);

// FUNCTION: GAMEMD 0x410A60
bool AbstractTypeClass::vf_25(CCINIClass* ini)
{
    ini->Reset();
    if (ini->GetSection(ID) != 0)
    {
        char buffer[1024];
        // STRING: GAMEMD 0x817854
        ini->FUN_00528A10(ID, "Name", Name, buffer, 49);
        GgBoundedText<49>(buffer).CopyTo(Name);
        // STRING: GAMEMD 0x81784C
        ini->FUN_00528A10(ID, "UIName", UINameLabel, buffer, 32);
        GgBoundedText<32>(buffer).CopyTo(UINameLabel);
        if (UINameLabel[0])
            UIName = StringTable_LoadString(UINameLabel, 0, STR_00817830, 0xD7);
        else
            UIName = DAT_00887734;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x410B90
bool AbstractTypeClass::vf_26(CCINIClass* ini)
{
    ini->Clear(ID, 0);
    // STRING: GAMEMD 0x817854
    ini->WriteString(ID, "Name", Name);
    if (UINameLabel[0])
    {
        // STRING: GAMEMD 0x81784C
        ini->WriteString(ID, "UIName", UINameLabel);
    }
    return true;
}
