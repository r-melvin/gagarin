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

// FUNCTION: GAMEMD 0x7C8D20 (decl; reloc) — CRT strcmp.
extern "C" int   __cdecl FUN_007C8D20(const char* a, const char* b);
// FUNCTION: GAMEMD 0x7C8E17 (decl; reloc) — operator new.
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);

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

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_007275D0;

// TriggerTypeClass — only the vtable and the ID string are touched; the
// allocation size 0xB4 is the object's full size.
struct TriggerType_007275D0
{
    Vtbl_007275D0* Vtbl;       // +0x0000
    char  _pad004[0x20];       // +0x0004
    char  ID[0x18];            // +0x0024
    char  _pad03C[0xB4 - 0x3C];// +0x003C

    // FUNCTION: GAMEMD 0x726C80 (decl; reloc) — TriggerTypeClass constructor
    // (ID), called explicitly on raw storage: a real `new T(name)` under /GX
    // registers an EH frame around the constructor that retail does not have.
    TriggerType_007275D0* Construct(const char* id);

    // FUNCTION: GAMEMD 0x7275D0 — TriggerTypeClass::LoadFromINIList, a static
    // member: the INI arrives in ECX and nothing is cleaned, which is what
    // `static __fastcall` spells.
    static void __fastcall LoadFromINIList(CCINI_007275D0* ini);
};
GG_STATIC_ASSERT(offsetof(TriggerType_007275D0, ID) == 0x24);
GG_STATIC_ASSERT(sizeof(TriggerType_007275D0) == 0xB4);

typedef void (TriggerType_007275D0::*Fn64_007275D0)(CCINI_007275D0* ini);

struct Vtbl_007275D0
{
    char _pad000[0x64];      // +0x0000
    Fn64_007275D0 At_64;     // +0x0064  LoadFromINI(ini)
};
GG_STATIC_ASSERT(offsetof(Vtbl_007275D0, At_64) == 0x64);

// DynamicVectorClass<TriggerTypeClass*> — only the two members read here are
// named; the rest of the header is padding.
struct TriggerTypeVector_007275D0
{
    void*                   Vtable;       // +0x0000
    TriggerType_007275D0**  Items;        // +0x0004
    char                    _pad008[0x8]; // +0x0008
    int                     Count;        // +0x0010
};
GG_STATIC_ASSERT(offsetof(TriggerTypeVector_007275D0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(TriggerTypeVector_007275D0, Count) == 0x10);

// GLOBAL: GAMEMD 0x8B4178 — TriggerTypeClass::Array.
extern TriggerTypeVector_007275D0 DAT_008B4178;

#endif  // GG_MATCH_AI_TRIGGER_TYPE_CLASS_LOAD_METHODS_H
