// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x6E5ED0: the section-name pointer 0x7F4550 with the INI
//   helpers 0x526960, 0x526CC0 and 0x528A10 (a 0x18-byte frame buffer and
//   the default string at 0x889F64), the CRT comparison 0x7C8D20 against the
//   sentinel at 0x817474 and the placeholder at 0x817694, the
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
// STRING: GAMEMD 0x817474 — "<none>" sentinel.
extern const char STR_00817474[];
// STRING: GAMEMD 0x817694 — the placeholder name.
extern const char STR_00817694[];

// LIBRARY: GAMEMD 0x7C8D20 — CRT string comparison.
extern "C" int __cdecl gg_strcmp(const char* a, const char* b);

#include "../_layout/tag_type_class.h"
// Only the observed primary-slot dispatch is modelled; complete COM API is pending.
struct TagTypeLoadCallViewVtable;
struct TagTypeLoadCallView { TagTypeLoadCallViewVtable* Vtable; };
typedef void (TagTypeLoadCallView::*TagTypeLoadCallViewSlot)(CCINI_006E5ED0*);
struct TagTypeLoadCallViewVtable
{
    unsigned char unknown_00[0x64];
    TagTypeLoadCallViewSlot Method;
};
GG_STATIC_ASSERT(sizeof(TagTypeLoadCallViewSlot) == 4);
GG_STATIC_ASSERT(offsetof(TagTypeLoadCallView, Vtable) == 0);
GG_STATIC_ASSERT(offsetof(TagTypeLoadCallViewVtable, Method) == 0x64);

// FUNCTION: GAMEMD 0x412610 (decl; reloc) — the name's registry key.
int __fastcall FUN_00412610(const char* name);
// GLOBAL: GAMEMD 0xB0C110 — the name registry.
extern char DAT_00B0C110;
// FUNCTION: GAMEMD 0x6CF2C0 (decl; reloc) — register a tag type by name.
void __stdcall FUN_006CF2C0(void* registry, int key, TagTypeClass* tag);

#endif  // GG_MATCH_AI_TAG_TYPE_CLASS_LOAD_LIST_METHODS_H
