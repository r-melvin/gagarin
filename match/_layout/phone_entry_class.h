// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Native69873D allocatesB0 bytes without a constructor call. Native6980C0
// parses scalar fields0..1C and string regions20/70/9A;6990A0 serializes them.
// RTTI of DynamicVectorClass<PhoneEntryClass*> identifies the class name.
// String arrays describe storage extents; logical capacities are unconfirmed.
#ifndef GG_MATCH_LAYOUT_PHONE_ENTRY_CLASS_H
#define GG_MATCH_LAYOUT_PHONE_ENTRY_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
class PhoneEntryClass
{
public:
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0C;
    int unknown_10;
    int unknown_14;
    int unknown_18;
    int unknown_1C;
    char unknown_20[0x50];
    wchar_t unknown_70[0x2A / 2];
    char unknown_9A[0xB0 - 0x9A];
};
GG_STATIC_ASSERT(offsetof(PhoneEntryClass, unknown_00) == 0x0);
GG_STATIC_ASSERT(sizeof(((PhoneEntryClass*)0)->unknown_00) == 0x4);
GG_STATIC_ASSERT(offsetof(PhoneEntryClass, unknown_04) == 0x4);
GG_STATIC_ASSERT(sizeof(((PhoneEntryClass*)0)->unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(PhoneEntryClass, unknown_08) == 0x8);
GG_STATIC_ASSERT(sizeof(((PhoneEntryClass*)0)->unknown_08) == 0x4);
GG_STATIC_ASSERT(offsetof(PhoneEntryClass, unknown_0C) == 0xC);
GG_STATIC_ASSERT(sizeof(((PhoneEntryClass*)0)->unknown_0C) == 0x4);
GG_STATIC_ASSERT(offsetof(PhoneEntryClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(sizeof(((PhoneEntryClass*)0)->unknown_10) == 0x4);
GG_STATIC_ASSERT(offsetof(PhoneEntryClass, unknown_14) == 0x14);
GG_STATIC_ASSERT(sizeof(((PhoneEntryClass*)0)->unknown_14) == 0x4);
GG_STATIC_ASSERT(offsetof(PhoneEntryClass, unknown_18) == 0x18);
GG_STATIC_ASSERT(sizeof(((PhoneEntryClass*)0)->unknown_18) == 0x4);
GG_STATIC_ASSERT(offsetof(PhoneEntryClass, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(sizeof(((PhoneEntryClass*)0)->unknown_1C) == 0x4);
GG_STATIC_ASSERT(offsetof(PhoneEntryClass, unknown_20) == 0x20);
GG_STATIC_ASSERT(sizeof(((PhoneEntryClass*)0)->unknown_20) == 0x50);
GG_STATIC_ASSERT(offsetof(PhoneEntryClass, unknown_70) == 0x70);
GG_STATIC_ASSERT(sizeof(((PhoneEntryClass*)0)->unknown_70) == 0x2A);
GG_STATIC_ASSERT(offsetof(PhoneEntryClass, unknown_9A) == 0x9A);
GG_STATIC_ASSERT(sizeof(((PhoneEntryClass*)0)->unknown_9A) == 0x16);
GG_STATIC_ASSERT(sizeof(PhoneEntryClass) == 0xB0);
#endif
