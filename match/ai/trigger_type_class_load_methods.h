// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every address below is read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x7275D0: the section-name pointer is
//   loaded from `[0x7F58C8]` before the key-count call and again before every
//   key-name call; the two rejected spellings are the strcmp arguments
//   `0x817474` / `0x817694`; the array's Items and Count are `[0x8B417C]` /
//   `[0x8B4188]` (base 0x8B4178, +0x04 / +0x10) with the item's ID compared
//   at `[item+0x24]`; the allocation is `PUSH 0xB4; CALL 0x7C8E17` followed
//   by the __thiscall constructor 0x726C80 with the name pushed; and the
//   per-item virtual is `CALL [EDX+0x64]` with the INI pushed. Method names
//   are the YRpp ones (consult-only); every offset re-derived here.
#ifndef GG_MATCH_AI_TRIGGER_TYPE_CLASS_LOAD_METHODS_H
#define GG_MATCH_AI_TRIGGER_TYPE_CLASS_LOAD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// LIBRARY: GAMEMD 0x7C8D20 — CRT string comparison (callee declaration).
extern "C" int   __cdecl FUN_007C8D20(const char* a, const char* b);

// The INI reader. No member of it is touched here; both calls are __thiscall
// with the arguments pushed.
struct CCINI_007275D0
{
    // FUNCTION: GAMEMD 0x526960 (decl; reloc) — GetKeyCount(section).
    int GetKeyCount(const char* section);
    // FUNCTION: GAMEMD 0x526CC0 (decl; reloc) — GetKeyName(section, index).
    const char* GetKeyName(const char* section, int index);
};

// GLOBAL: GAMEMD 0x7F58C8 — pointer to the section name ("Triggers" @0x844A3C).
extern const char* DAT_007F58C8;
// STRING: GAMEMD 0x817474  "<none>"
extern const char STR_00817474[];
// STRING: GAMEMD 0x817694  "none"
extern const char STR_00817694[];

// Explicit call view for the observed primary virtual slot at +0x64.
// Complete COM signatures and inherited virtual declarations remain unknown.
// This view describes the dispatch only; TriggerTypeClass owns the layout.
#include "../_layout/trigger_type_class.h"
struct TriggerTypeLoadVtable;
struct TriggerTypeLoadCallView
{
    TriggerTypeLoadVtable* Vtable;
};
typedef void (TriggerTypeLoadCallView::*TriggerTypeLoadSlot)(CCINI_007275D0*);
struct TriggerTypeLoadVtable
{
    unsigned char unknown_00[0x64];
    TriggerTypeLoadSlot LoadFromINI;
};
GG_STATIC_ASSERT(sizeof(TriggerTypeLoadSlot) == 4);
GG_STATIC_ASSERT(offsetof(TriggerTypeLoadVtable, LoadFromINI) == 0x64);
GG_STATIC_ASSERT(offsetof(TriggerTypeLoadCallView, Vtable) == 0);
#endif
