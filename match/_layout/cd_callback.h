// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// RTTI at TD 0x81B940 identifies CD; table 0x7E4C30 has the three
// observed callback methods below. 0x4790FD writes the dword at +4.
// Stack caller 0x686730 reserves eight bytes and initializes only the vptr.
#ifndef GG_MATCH_LAYOUT_CD_CALLBACK_H
#define GG_MATCH_LAYOUT_CD_CALLBACK_H
#include "../_rt/gg_static_assert.h"
#include <stddef.h>
// VTABLE: GAMEMD 0x7E4C30
class CD
{
public:
    CD() {}
    virtual bool FUN_004790E0(int value); // GAMEMD 0x4790E0
    virtual bool FUN_00479110(int value); // GAMEMD 0x479110
    virtual bool FUN_004791F0(int value); // GAMEMD 0x4791F0
    int unknown_04;
};
GG_STATIC_ASSERT(offsetof(CD, unknown_04) == 4);
GG_STATIC_ASSERT(sizeof(CD) == 8);
typedef bool (CD::*CDCallbackSlot)(int);
struct CDCallbackSlots { CDCallbackSlot unknown_00, unknown_04, unknown_08; };
GG_STATIC_ASSERT(sizeof(CDCallbackSlot) == 4);
GG_STATIC_ASSERT(offsetof(CDCallbackSlots, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(CDCallbackSlots, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(CDCallbackSlots, unknown_08) == 8);
#endif
