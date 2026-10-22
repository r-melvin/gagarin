// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Bytes, globals and argument slots read off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x674550: the section-name pointer is
//   the .data slot 0x7F0CE4 (`MOV EAX,[0x7F0CE4]`); the callees are
//   INIClass::GetSection 0x526810, GetKeyCount 0x526960, GetKeyName
//   0x526CC0 and ReadString 0x528A10 (section, key, "" at 0x817474, a
//   0x20-byte stack buffer, 0x20), the movie lookup 0x48DF30 (__fastcall,
//   ECX = name, -1 when unknown) and CRT strdup 0x7D5408 (cdecl, `ADD
//   ESP,4`). The vector at 0xABF390 is read as `[0xABF398]` capacity,
//   `[0xABF39D]` byte allocated flag, `[0xABF3A0]` count, `[0xABF3A4]`
//   increment, `[0xABF394]` items, and its slot +0x08 is reached through
//   `MOV EAX,[0xABF390]; CALL [EAX+8]` with `MOV ECX,0xABF390`. `this` is
//   never touched (RET 4 with ECX unused). Names cross-checked against YRpp
//   (RulesClass::Read_Movies, MovieInfo::Array; every slot reconfirmed above).
#ifndef GG_MATCH_CORE_RULES_CLASS_READ_MOVIES_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_READ_MOVIES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Opaque INI parser; the out-of-line members are declared only, so cl emits
// reloc-normalised __thiscall CALLs.
class CCINI_00674550
{
public:
    // FUNCTION: GAMEMD 0x526810 (decl; reloc)
    void*       GetSection(const char* pSection);
    // FUNCTION: GAMEMD 0x526B10 (decl; reloc)
    void*       GetEntry(const char* pSection, const char* pKey);
    // FUNCTION: GAMEMD 0x526960 (decl; reloc)
    int         GetKeyCount(const char* pSection);
    // FUNCTION: GAMEMD 0x526CC0 (decl; reloc)
    const char* GetKeyName(const char* pSection, int index);
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc)
    int         ReadString(const char* pSection, const char* pKey,
                           const char* pDefault, char* pBuffer, int size);

    // FUNCTION: GAMEMD 0x679F40 — CCINIClass::Exists (matched out of line in
    // match/platform/ccini_class_methods.cpp); the model of the section
    // probe that Read_Movies expands inline in flag form.
    bool Exists(const char* pSection, const char* pKey = 0)
    {
        if (pKey == 0) {
            return GetSection(pSection) != 0;
        }
        return GetEntry(pSection, pKey) != 0;
    }
};

// FUNCTION: GAMEMD 0x48DF30 (decl; reloc) — index of a movie by name in the
// global movie array, -1 when it is not there yet.
int __fastcall FUN_0048DF30(const char* name);

// LIBRARY: GAMEMD 0x7D5408 (decl; reloc) — CRT strdup.
char* __cdecl GameStrdup_00674550(const char* str);

// DynamicVectorClass<MovieInfo> — the global movie list; each entry is the
// duplicated name. Slot +0x08 is Resize(newCapacity, array): two stack
// arguments, `this` in ECX, a byte result tested with `TEST AL,AL`.
struct MovieVector_00674550
{
    virtual void vt_000();
    virtual void vt_004();
    virtual bool Resize(int newCapacity, void* array);   // +0x0008

    char** Items;              // +0x0004
    int    Capacity;           // +0x0008
    char   IsInitialized;      // +0x000C
    char   IsAllocated;        // +0x000D
    char   _pad0E[0x10 - 0x0E];
    int    Count;              // +0x0010
    int    CapacityIncrement;  // +0x0014

    // DynamicVectorClass::AddItem, expanded inline by VC6 at the call site
    // (the banked phrasing: capacity bound to a local so the vtable load
    // stays ahead of the pushes, `Count++` bound to a local for MOV/INC).
    bool AddItem(char* const& item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && Resize(cap + CapacityIncrement, 0))) {
            int index = Count++;
            Items[index] = item;
            return true;
        }
        return false;
    }
};
GG_STATIC_ASSERT(offsetof(MovieVector_00674550, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(MovieVector_00674550, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(MovieVector_00674550, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(MovieVector_00674550, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(MovieVector_00674550, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(MovieVector_00674550) == 0x18);

// GLOBAL: GAMEMD 0xABF390 — MovieInfo::Array (an object, not a pointer:
// retail loads its address as the immediate `MOV ECX,0xABF390`).
extern MovieVector_00674550 DAT_00ABF390;

// GLOBAL: GAMEMD 0x7F0CE4 — pointer to the "Movies" section name.
extern char* MoviesSection_00674550;

struct Rules_00674550
{
    // FUNCTION: GAMEMD 0x674550
    bool Read_Movies(CCINI_00674550* pINI);
};

#endif  // GG_MATCH_CORE_RULES_CLASS_READ_MOVIES_METHODS_H
