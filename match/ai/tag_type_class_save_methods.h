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

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_006E5FE0;

struct TagType_006E5FE0
{
    Vtbl_006E5FE0* Vtbl;   // +0x0000

    // FUNCTION: GAMEMD 0x6E5FE0 — TagTypeClass::SaveToINIList, a static member
    // of this class rather than a free function: retail passes the INI in ECX
    // and cleans nothing, which is exactly `static __fastcall`, and spelling it
    // here names the class the list belongs to.
    static void __fastcall SaveToINIList(CCINI_006E5FE0* ini);
};

typedef void (TagType_006E5FE0::*Fn68_006E5FE0)(CCINI_006E5FE0* ini);

struct Vtbl_006E5FE0
{
    char _pad000[0x68];      // +0x0000
    Fn68_006E5FE0 At_68;     // +0x0068  SaveToINI(ini)
};
GG_STATIC_ASSERT(offsetof(Vtbl_006E5FE0, At_68) == 0x68);

// DynamicVectorClass<TagTypeClass*> — only the two members read here are
// named; the rest of the header is padding.
struct TagTypeVector_006E5FE0
{
    void*               Vtable;       // +0x0000
    TagType_006E5FE0**  Items;        // +0x0004
    char                _pad008[0x8]; // +0x0008
    int                 Count;        // +0x0010

    TagType_006E5FE0*& operator[](int i) { return Items[i]; }
};
GG_STATIC_ASSERT(offsetof(TagTypeVector_006E5FE0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(TagTypeVector_006E5FE0, Count) == 0x10);

// GLOBAL: GAMEMD 0xB0E780 — TagTypeClass::Array.
extern TagTypeVector_006E5FE0 DAT_00B0E780;

#endif  // GG_MATCH_AI_TAG_TYPE_CLASS_SAVE_METHODS_H
