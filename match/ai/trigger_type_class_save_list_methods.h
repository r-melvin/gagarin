// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x727880: the three section-name pointers 0x7F58C8
//   ("Triggers"), 0x7F58D0 ("Events") and 0x7F58CC ("Actions"), the INI
//   helpers 0x526960 (GetKeyCount), 0x526CC0 (GetKeyName), 0x528A10
//   (ReadString into a 0x20-byte frame buffer with the default string at
//   0x889F64) and 0x5257C0 (Clear), and the TriggerTypeClass::Array at
//   0x8B417C (Items) / 0x8B4188 (Count) whose entries are saved through
//   vtable slot +0x68. The INI and vector shapes match the sibling
//   match/ai/ai_trigger_save_list_methods.h. Names cross-checked against
//   YRpp TriggerTypeClass.h / CCINIClass.h (consult-only; NO LICENSE).
#ifndef GG_MATCH_AI_TRIGGER_TYPE_CLASS_SAVE_LIST_METHODS_H
#define GG_MATCH_AI_TRIGGER_TYPE_CLASS_SAVE_LIST_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct CCINI_00727880
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

// GLOBAL: GAMEMD 0x7F58C8 — pointer to the "Triggers" section name.
extern const char* DAT_007F58C8;
// GLOBAL: GAMEMD 0x7F58CC — pointer to the "Actions" section name.
extern const char* DAT_007F58CC;
// GLOBAL: GAMEMD 0x7F58D0 — pointer to the "Events" section name.
extern const char* DAT_007F58D0;
// STRING: GAMEMD 0x889F64 — the empty default.
extern const char STR_00889F64[];

#include "../_layout/trigger_type_class.h"
// Explicit primary slot call view; complete inherited COM signatures are pending.
struct TriggerTypeSaveVtable;
struct TriggerTypeSaveCallView { TriggerTypeSaveVtable* Vtable; };
typedef void (TriggerTypeSaveCallView::*TriggerTypeSaveSlot)(CCINI_00727880*);
struct TriggerTypeSaveVtable
{
    unsigned char unknown_00[0x68];
    TriggerTypeSaveSlot Method;
};
GG_STATIC_ASSERT(sizeof(TriggerTypeSaveSlot) == 4);
GG_STATIC_ASSERT(offsetof(TriggerTypeSaveCallView, Vtable) == 0);
GG_STATIC_ASSERT(offsetof(TriggerTypeSaveVtable, Method) == 0x68);
#endif
