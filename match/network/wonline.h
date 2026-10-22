// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Shared declarations of the online-services translation unit (the retail
// assertion path names it wonline.cpp; string 0x84A430). Names are
// placeholders unless a string in the binary attests them.
#ifndef GG_MATCH_NETWORK_WONLINE_H
#define GG_MATCH_NETWORK_WONLINE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A one-word heap string handle (the Obj_007B4620 layout of
// match/core/string_class.h) seen here as a constructed/destroyed object:
// file-scope instances are built by 0x7B4620 and torn down at exit by
// 0x7B46F0. Members are declared only; their bodies live elsewhere.
class String_007B4620
{
public:
    // FUNCTION: GAMEMD 0x7B4620 (decl; reloc)
    String_007B4620();
    // FUNCTION: GAMEMD 0x7B4630 (decl; reloc)
    String_007B4620(const char* text);
    // FUNCTION: GAMEMD 0x7B46F0 (decl; reloc)
    ~String_007B4620();
    // FUNCTION: GAMEMD 0x7B4780 (decl; reloc)
    bool operator==(const String_007B4620& other) const;
    // FUNCTION: GAMEMD 0x7B48D0 (decl; reloc)
    String_007B4620& operator=(const char* text);
    // FUNCTION: GAMEMD 0x7B4940 (decl; reloc)
    String_007B4620& operator=(const String_007B4620& other);
    // FUNCTION: GAMEMD 0x7B5400 (decl; reloc)
    const char* FUN_007B5400();
    // FUNCTION: GAMEMD 0x7B5440 (decl; reloc)
    const char* FUN_007B5440();
    // FUNCTION: GAMEMD 0x7B5B30 (decl; reloc)
    void FUN_007B5B30();

    char* unknown_00;   // +0x00
};
GG_STATIC_ASSERT(sizeof(String_007B4620) == 4);

// GLOBAL: GAMEMD 0xB73E40 -- the stored login holder; defined in wonline.cpp (its cleanup is 0x77DA10).
extern String_007B4620 DAT_00B73E40;
// GLOBAL: GAMEMD 0xB7778C -- the stored password holder; defined in wonline.cpp (its cleanup is 0x77DA40).
extern String_007B4620 DAT_00B7778C;

// The one-word wide string handle (the Obj_007B66D0 layout of
// match/core/wide_string_class.h, which declares no default constructor or
// destructor) seen as a constructed/destroyed object: constructors 0x7B66C0
// and 0x7B66D0, destructor 0x7B6760.
class WideString_007B66C0
{
public:
    // FUNCTION: GAMEMD 0x7B66C0 (decl; reloc)
    WideString_007B66C0();
    // FUNCTION: GAMEMD 0x7B66D0 (decl; reloc)
    WideString_007B66C0(const wchar_t* text);
    // FUNCTION: GAMEMD 0x7B6760 (decl; reloc)
    ~WideString_007B66C0();

    void* unknown_00;   // +0x00
};
GG_STATIC_ASSERT(sizeof(WideString_007B66C0) == 4);

// The 0x6C-byte record of the table at 0xB77900 (count) / 0xB77908 (items).
struct Entry_00B77908
{
    char unknown_00[0x24];   // +0x00
    char unknown_24[0x0A];   // +0x24 -- name compared with strcmp
    char unknown_2E[0x3E];   // +0x2E -- second name compared with strcmp
};
GG_STATIC_ASSERT(sizeof(Entry_00B77908) == 0x6C);
GG_STATIC_ASSERT(offsetof(Entry_00B77908, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Entry_00B77908, unknown_2E) == 0x2E);

#endif // GG_MATCH_NETWORK_WONLINE_H
