// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x6E5ED0: the section-name pointer 0x7F4550 with the INI
//   helpers 0x526960, 0x526CC0 and 0x528A10 (a 0x18-byte frame buffer and
//   the default string at 0x889F64), the CRT `strcmp` 0x7C8D20 against the
//   empty string at 0x817474 and the placeholder at 0x817694, the
//   TagTypeClass array at 0xB0E784 with its count at 0xB0E790 and each
//   entry's ID at `+0x24`, the 0xA4-byte allocation through 0x7C8E17 with
//   the constructor at 0x6E5B60, the name registration 0x412610 plus
//   0x6CF2C0 on the table at 0xB0C110, and the per-entry load through
//   vtable slot +0x64. The INI and vector shapes match the sibling
//   match/ai/tag_type_class_save_methods.h. Names cross-checked against
//   YRpp TagTypeClass.h (consult-only; NO LICENSE).
#ifndef GG_MATCH_AI_TAG_TYPE_CLASS_LOAD_LIST_METHODS_H
#define GG_MATCH_AI_TAG_TYPE_CLASS_LOAD_LIST_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct CCINI_006E5ED0
{
    // FUNCTION: GAMEMD 0x526960 (decl; reloc) — GetKeyCount(section).
    int GetKeyCount(const char* section);
    // FUNCTION: GAMEMD 0x526CC0 (decl; reloc) — GetKeyName(section, index).
    const char* GetKeyName(const char* section, int index);
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) — ReadString(section, key,
    // default, buffer, size).
    int ReadString(const char* section, const char* key, const char* def,
                   char* buffer, int size);
};

// GLOBAL: GAMEMD 0x7F4550 — pointer to the "Tags" section name.
extern const char* DAT_007F4550;
// STRING: GAMEMD 0x889F64 — the empty default handed to ReadString.
extern const char STR_00889F64[];
// STRING: GAMEMD 0x817474 — the empty name.
extern const char STR_00817474[];
// STRING: GAMEMD 0x817694 — the placeholder name.
extern const char STR_00817694[];

// FUNCTION: GAMEMD 0x7C8D20 (decl; reloc) — CRT strcmp.
extern "C" int __cdecl gg_strcmp(const char* a, const char* b);
// FUNCTION: GAMEMD 0x7C8E17 (decl; reloc) — operator new.
extern "C" void* __cdecl gg_new(unsigned int size);

struct Vtbl_006E5ED0;

struct TagType_006E5ED0
{
    Vtbl_006E5ED0* Vtbl;      // +0x0000
    char           _pad004[0x20];  // +0x0004
    char           ID[0x18];  // +0x0024

    // FUNCTION: GAMEMD 0x6E5B60 (decl; reloc) — TagTypeClass::TagTypeClass.
    TagType_006E5ED0* Construct(const char* id);

    // FUNCTION: GAMEMD 0x6E5ED0 — TagTypeClass::LoadFromINIList, a static
    // member of this class rather than a free function: the INI arrives in ECX
    // and nothing is cleaned, which is exactly `static __fastcall`.
    static void __fastcall LoadFromINIList(CCINI_006E5ED0* ini);
};
GG_STATIC_ASSERT(offsetof(TagType_006E5ED0, ID) == 0x24);

typedef void (TagType_006E5ED0::*Fn64_006E5ED0)(CCINI_006E5ED0* ini);
struct Vtbl_006E5ED0
{
    char           _pad000[0x64];   // +0x0000
    Fn64_006E5ED0  At_64;           // +0x0064  LoadFromINI(ini)
};
GG_STATIC_ASSERT(offsetof(Vtbl_006E5ED0, At_64) == 0x64);

// GLOBAL: GAMEMD 0xB0E784 — TagTypeClass::Array.Items.
extern TagType_006E5ED0** DAT_00B0E784;
// GLOBAL: GAMEMD 0xB0E790 — TagTypeClass::Array.Count.
extern int DAT_00B0E790;

// FUNCTION: GAMEMD 0x412610 (decl; reloc) — the name's registry key.
int __fastcall FUN_00412610(const char* name);
// GLOBAL: GAMEMD 0xB0C110 — the name registry.
extern char DAT_00B0C110;
// FUNCTION: GAMEMD 0x6CF2C0 (decl; reloc) — register a tag type by name.
void __stdcall FUN_006CF2C0(void* registry, int key, TagType_006E5ED0* tag);

#endif  // GG_MATCH_AI_TAG_TYPE_CLASS_LOAD_LIST_METHODS_H
