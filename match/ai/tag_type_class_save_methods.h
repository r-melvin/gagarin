// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every address below is read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x6E5FE0: the section-name pointer is
//   loaded from `[0x7F4550]` before every call, the vector's Items and Count
//   are `[0xB0E784]` / `[0xB0E790]` (base 0xB0E780, +0x04 / +0x10), and the
//   per-item virtual is `CALL [EDX+0x68]` with one pushed argument. Method
//   names are the YRpp ones (consult-only); every offset re-derived here.
#ifndef GG_MATCH_AI_TAG_TYPE_CLASS_SAVE_METHODS_H
#define GG_MATCH_AI_TAG_TYPE_CLASS_SAVE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// The INI reader/writer. No member of it is touched here; every call is a
// __thiscall with the arguments pushed.
struct CCINI_006E5FE0
{
    // FUNCTION: GAMEMD 0x526960 (decl; reloc) — GetKeyCount(section).
    int GetKeyCount(const char* section);
    // FUNCTION: GAMEMD 0x526CC0 (decl; reloc) — GetKeyName(section, index).
    const char* GetKeyName(const char* section, int index);
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) — ReadString(section, key,
    // default, buffer, size).
    int ReadString(const char* section, const char* key, const char* def,
                   char* buffer, int size);
    // FUNCTION: GAMEMD 0x5257C0 (decl; reloc) — Clear(section, key).
    bool Clear(const char* section, const char* key);
};

// GLOBAL: GAMEMD 0x7F4550 — pointer to the section name ("Tags").
extern const char* DAT_007F4550;
// STRING: GAMEMD 0x889F64 — the shared empty default string.
extern const char STR_00889F64[];

#include "../_layout/tag_type_class.h"
// Only the observed primary-slot dispatch is modelled; complete COM API is pending.
struct TagTypeSaveCallViewVtable;
struct TagTypeSaveCallView { TagTypeSaveCallViewVtable* Vtable; };
typedef void (TagTypeSaveCallView::*TagTypeSaveCallViewSlot)(CCINI_006E5FE0*);
struct TagTypeSaveCallViewVtable
{
    unsigned char unknown_00[0x68];
    TagTypeSaveCallViewSlot Method;
};
GG_STATIC_ASSERT(sizeof(TagTypeSaveCallViewSlot) == 4);
GG_STATIC_ASSERT(offsetof(TagTypeSaveCallView, Vtable) == 0);
GG_STATIC_ASSERT(offsetof(TagTypeSaveCallViewVtable, Method) == 0x68);

#endif
