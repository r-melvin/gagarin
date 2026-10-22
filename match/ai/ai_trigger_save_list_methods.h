// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every address below is read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x41F490: the two section-name
//   pointers are loaded from `[0x7E2A18]` / `[0x7E2A1C]` before every call,
//   the vector's Items and Count are `[0xA8B204]` / `[0xA8B210]` (base
//   0xA8B200, +0x04 / +0x10), the per-item compare is `CMP [ECX+0x9C],EBP`
//   (a dword against the EDX register argument), the per-item virtual is
//   `CALL [EDX+0x68]` with one pushed argument, and the enable pass pushes
//   `[EAX+0xA4]` (a byte) and `EAX+0x24` (the item's name buffer). Method
//   and member names are the YRpp ones; every
//   offset re-derived here. Same shape as match/ai/tag_type_class_save_methods.h.
#ifndef GG_MATCH_AI_AI_TRIGGER_SAVE_LIST_METHODS_H
#define GG_MATCH_AI_AI_TRIGGER_SAVE_LIST_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// The INI reader/writer. No member of it is touched here; every call is a
// __thiscall with the arguments pushed.
struct CCINI_0041F490
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
    // FUNCTION: GAMEMD 0x529560 (decl; reloc) — WriteBool(section, key, value).
    bool WriteBool(const char* section, const char* key, bool value);
};

// GLOBAL: GAMEMD 0x7E2A18 — pointer to the list section name ("AITriggerTypes").
extern const char* DAT_007E2A18;
// GLOBAL: GAMEMD 0x7E2A1C — pointer to the enable section name ("AITriggerTypesEnable").
extern const char* DAT_007E2A1C;
// STRING: GAMEMD 0x889F64 — the shared empty default string.
extern const char STR_00889F64[];

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_0041F490;

// AITriggerTypeClass (partial): the name buffer, the global flag and the
// enabled flag.
struct AITriggerType_0041F490
{
    Vtbl_0041F490* Vtbl;      // +0x0000
    char _pad004[0x20];       // +0x0004
    char ID[0x78];            // +0x0024  the key written to the enable section
    int  IsGlobal;            // +0x009C
    char _pad0A0[4];          // +0x00A0
    bool IsEnabled;           // +0x00A4

    // FUNCTION: GAMEMD 0x41F490 — AITriggerTypeClass::SaveToINIList, a static
    // member: the INI arrives in ECX and the global flag on the stack, which
    // is what `static __fastcall` spells. Declared here rather than as a free
    // function so the class the list belongs to is named in the source.
    static void __fastcall SaveToINIList(CCINI_0041F490* ini, int isGlobal);
};
GG_STATIC_ASSERT(offsetof(AITriggerType_0041F490, ID) == 0x24);
GG_STATIC_ASSERT(offsetof(AITriggerType_0041F490, IsGlobal) == 0x9C);
GG_STATIC_ASSERT(offsetof(AITriggerType_0041F490, IsEnabled) == 0xA4);

typedef void (AITriggerType_0041F490::*Fn68_0041F490)(CCINI_0041F490* ini);

struct Vtbl_0041F490
{
    char _pad000[0x68];      // +0x0000
    Fn68_0041F490 At_68;     // +0x0068  SaveToINI(ini)
};
GG_STATIC_ASSERT(offsetof(Vtbl_0041F490, At_68) == 0x68);

// DynamicVectorClass<AITriggerTypeClass*> — only the two members read here are
// named; the rest of the header is padding.
struct AITriggerTypeVector_0041F490
{
    void*                     Vtable;       // +0x0000
    AITriggerType_0041F490**  Items;        // +0x0004
    char                      _pad008[0x8]; // +0x0008
    int                       Count;        // +0x0010

    AITriggerType_0041F490*& operator[](int i) { return Items[i]; }
};
GG_STATIC_ASSERT(offsetof(AITriggerTypeVector_0041F490, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(AITriggerTypeVector_0041F490, Count) == 0x10);

// GLOBAL: GAMEMD 0xA8B200 — AITriggerTypeClass::Array.
extern AITriggerTypeVector_0041F490 DAT_00A8B200;

#endif  // GG_MATCH_AI_AI_TRIGGER_SAVE_LIST_METHODS_H
