// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// A heap-owning narrow string whose only member is the `char*` at +0x00:
// every recovered body reads or writes [ECX+0x00] alone, allocates with
// operator new 0x7C8E17 and frees with operator delete 0x7C8B3D. strlen,
// strcpy, strcmp and memset are the VC6 inline expansions (REPNE SCASB,
// REP MOVSD/MOVSB, the SBB compare tail, REP STOSD/STOSB); strchr 0x7CAF30,
// strncpy 0x7C91D0 and memmove 0x7CA090 are calls.
// Method names are descriptive or placeholders. sizeof 4: the map stage
// container holds instances at +0x00/+0x04 of MapStage and at +0x28 of its
// list (see match/map/map_stage_list_methods.h).
#ifndef GG_MATCH_CORE_STRING_CLASS_H
#define GG_MATCH_CORE_STRING_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Retail TD 0x83F5D8 names the element of table 0x7F12B4 as class Wstring.
// Move the existing Session owner here; its four-byte layout and real
// construction/destruction declarations are unchanged. The manual-lifetime
// legacy receiver below still requires caller-by-caller conversion.
class Wstring
{
public:
    char* unknown_00;
    // Declaration: GAMEMD 0x7B4620
    Wstring();
    // Declaration: GAMEMD 0x7B4630
    Wstring(const char* text);
    // Declaration: GAMEMD 0x7B4690
    Wstring(const Wstring& other);
    // Declaration: GAMEMD 0x7B46F0
    ~Wstring();
    // Declaration: GAMEMD 0x7B4780
    bool operator==(const Wstring& other) const;
    // Declaration: GAMEMD 0x7B4860
    bool operator!=(const Wstring& other) const;
    // Declaration: GAMEMD 0x7B4940
    Wstring& operator=(const Wstring& other);
};
GG_STATIC_ASSERT(sizeof(Wstring) == 4);
GG_STATIC_ASSERT(offsetof(Wstring, unknown_00) == 0);

class Obj_007B4620
{
public:
    // FUNCTION: GAMEMD 0x7B4690
    Obj_007B4620(const Obj_007B4620& other);
    // FUNCTION: GAMEMD 0x7B4780
    bool operator==(const Obj_007B4620& other) const;
    // FUNCTION: GAMEMD 0x7B4860
    bool operator!=(const Obj_007B4620& other) const;
    // FUNCTION: GAMEMD 0x7B50F0
    bool FUN_007B50F0(char ch);
    // FUNCTION: GAMEMD 0x7B51B0
    void FUN_007B51B0();
    // FUNCTION: GAMEMD 0x7B53B0
    void Copy_Padded(char* dest, unsigned int size) const;
    // FUNCTION: GAMEMD 0x7B54B0
    int Length() const;
    // FUNCTION: GAMEMD 0x7B5AB0
    bool FUN_007B5AB0(char ch, unsigned int index);

    // Further members reached from other translation units, declared under
    // their call-site names; no body for them is recovered yet.
    // FUNCTION: GAMEMD 0x7B4620 (decl; reloc) — the empty construction.
    void Init();
    // An empty-bodied default construction: it stores nothing, so callers that
    // hand the object to a constructing call (0x7B4630, or a hidden-pointer
    // return) can declare one.
    Obj_007B4620() {}
    // FUNCTION: GAMEMD 0x7B4630 (decl; reloc) — construct a copy of a C string
    // in place (a null pointer leaves the string empty); __thiscall, RET 4.
    void Construct(const char* text);
    // FUNCTION: GAMEMD 0x7B4710 (decl; reloc) — compare with a C string (two
    // empty strings are equal); __thiscall, RET 4.
    bool FUN_007B4710(const char* text) const;
    // FUNCTION: GAMEMD 0x7B46F0 (decl; reloc) — release the copy.
    void Destruct();
    // FUNCTION: GAMEMD 0x7B47F0 (decl; reloc) — indexed character.
    char At(int index);
    // FUNCTION: GAMEMD 0x7B5340 (decl; reloc) — drop whatever is held and go
    // back to empty.
    void Reset();
    // FUNCTION: GAMEMD 0x7B48D0 (decl; reloc) — assign from a C string.
    void FUN_007B48D0(const char* src);
    // FUNCTION: GAMEMD 0x7B5B30 (decl; reloc) — lower-case in place.
    void FUN_007B5B30();

    char* Str;   // +0x00
};
GG_STATIC_ASSERT(sizeof(Obj_007B4620) == 4
              && offsetof(Obj_007B4620, Str) == 0x00);

#endif // GG_MATCH_CORE_STRING_CLASS_H
