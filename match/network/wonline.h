// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Shared declarations of the online-services translation unit (the retail
// assertion path names it wonline.cpp; string 0x84A430). Names are
// placeholders unless a string in the binary attests them.
#ifndef GG_MATCH_NETWORK_WONLINE_H
#define GG_MATCH_NETWORK_WONLINE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../core/string_class.h"

// GLOBAL: GAMEMD 0xB73E40 -- the stored login holder; defined in wonline.cpp (its cleanup is 0x77DA10).
extern Wstring DAT_00B73E40;
// GLOBAL: GAMEMD 0xB7778C -- the stored password holder; defined in wonline.cpp (its cleanup is 0x77DA40).
extern Wstring DAT_00B7778C;

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
    // FUNCTION: GAMEMD 0x7B7600 (decl; reloc)
    void FUN_007B7600(const wchar_t* text);
    // FUNCTION: GAMEMD 0x7B7100 (decl; reloc)
    const wchar_t* FUN_007B7100();
    // FUNCTION: GAMEMD 0x7B7D90 (decl; reloc)
    bool FUN_007B7D90();

    void* unknown_00;   // +0x00
};
GG_STATIC_ASSERT(sizeof(WideString_007B66C0) == 4);

// The 0x6C-byte record of the table at 0xB77900 (count) / 0xB77908 (items).
struct Entry_00B77908
{
    char unknown_00[0x18];   // +0x00
    int unknown_18;          // +0x18 -- passed to slot +0x20 of the object at 0xAC1170 by 0x7A0F40
    char unknown_1C[0x08];   // +0x1C
    char unknown_24[0x0A];   // +0x24 -- name compared with strcmp
    char unknown_2E[0x3E];   // +0x2E -- second name compared with strcmp
};
GG_STATIC_ASSERT(sizeof(Entry_00B77908) == 0x6C);
GG_STATIC_ASSERT(offsetof(Entry_00B77908, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Entry_00B77908, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Entry_00B77908, unknown_2E) == 0x2E);

#endif // GG_MATCH_NETWORK_WONLINE_H
