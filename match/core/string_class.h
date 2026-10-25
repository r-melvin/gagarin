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
// list (see match/_layout/map_stage_list.h).
#ifndef GG_MATCH_CORE_STRING_CLASS_H
#define GG_MATCH_CORE_STRING_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Retail TD 0x83F5D8 names the element of table 0x7F12B4 as class Wstring.
// Move the existing Session owner here; its four-byte layout and real
// construction/destruction declarations use this single narrow owner.
class Wstring
{
public:
    char* unknown_00;
    // Declaration: GAMEMD 0x7B4620
    Wstring();
    // Declaration: GAMEMD 0x7B4630
    Wstring(const char* text);
    // Declaration: GAMEMD 0x7B5400 -- returns fallback 0x889F64 when null.
    const char* FUN_007B5400() const;
    // Declaration: GAMEMD 0x7B5440 -- fallback pointer 0x889F64 when null.
    const char* FUN_007B5440() const;
    // Declaration: GAMEMD 0x7B54B0
    int Length() const;
    // Declaration: GAMEMD 0x7B5F10
    int FUN_007B5F10(int cursor, const char* delimiters, Wstring* token);
    // Declaration: GAMEMD 0x7B51D0
    void FUN_007B51D0(const Wstring* trim);
    // Declaration: GAMEMD 0x7B5230
    void FUN_007B5230(const Wstring* trim);
    // Declaration: GAMEMD 0x7B4690
    Wstring(const Wstring& other);
    // Declaration: GAMEMD 0x7B46F0
    ~Wstring();
    // Declaration: GAMEMD 0x7B4710 -- null pointers compare equal.
    bool FUN_007B4710(const char* text) const;
    // Declaration: GAMEMD 0x7B4780
    bool operator==(const Wstring& other) const;
    // Declaration: GAMEMD 0x7B47F0 -- inequality against a C string.
    bool FUN_007B47F0(const char* text) const;
    // Declaration: GAMEMD 0x7B4860
    bool operator!=(const Wstring& other) const;
    // Declaration: GAMEMD 0x7B4940
    Wstring& operator=(const Wstring& other);
    // Declaration: GAMEMD 0x7B48D0 -- returns this in EAX; original method name unknown.
    Wstring& operator=(const char* text);
    // Declaration: GAMEMD 0x7B5340 -- release held storage and return to null.
    void FUN_007B5340();
    // Declaration: GAMEMD 0x7B5020 -- two stack ints, RET 8; AL reports success.
    bool FUN_007B5020(int start, int count);
    // Declaration: GAMEMD 0x7B50F0
    bool FUN_007B50F0(char ch);
    // Declaration: GAMEMD 0x7B51B0
    void FUN_007B51B0();
    // Declaration: GAMEMD 0x7B53B0
    void Copy_Padded(char* dest, unsigned int size) const;
    // Declaration: GAMEMD 0x7B5AB0
    bool FUN_007B5AB0(char ch, unsigned int index);
    // Declaration: GAMEMD 0x7B5B30 -- lower-case ASCII uppercase characters.
    void FUN_007B5B30();
};
GG_STATIC_ASSERT(sizeof(Wstring) == 4);
GG_STATIC_ASSERT(offsetof(Wstring, unknown_00) == 0);

#endif // GG_MATCH_CORE_STRING_CLASS_H
