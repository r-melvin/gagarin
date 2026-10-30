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

#include "../core/wide_string_class.h"

// The 0x6C-byte record of the table at 0xB77900 (count) / 0xB77908 (items).
struct Entry_00B77908
{
    // The flag word at +0x00 (bit 0 = channel owner) is cleared by the record-search locals.
    union {
        char unknown_00[0x18];   // +0x00
        int Flags;               // +0x00
    };
    int unknown_18;          // +0x18 -- passed to slot +0x20 of the object at 0xAC1170 by 0x7A0F40
    char unknown_1C[0x04];   // +0x1C
    Entry_00B77908* Next;    // +0x20 -- chain link of the temporary lists built by 0x77E1D0 / 0x77E300
    char unknown_24[0x0A];   // +0x24 -- name compared with strcmp
    char unknown_2E[0x3E];   // +0x2E -- second name compared with strcmp
};
GG_STATIC_ASSERT(sizeof(Entry_00B77908) == 0x6C);
GG_STATIC_ASSERT(offsetof(Entry_00B77908, Flags) == 0x00);
GG_STATIC_ASSERT(offsetof(Entry_00B77908, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Entry_00B77908, Next) == 0x20);
GG_STATIC_ASSERT(offsetof(Entry_00B77908, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Entry_00B77908, unknown_2E) == 0x2E);

#endif // GG_MATCH_NETWORK_WONLINE_H
