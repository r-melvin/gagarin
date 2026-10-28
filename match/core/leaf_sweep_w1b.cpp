// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   The owning classes are not bound by RTTI or a binary string at these addresses,
//   so each receiver keeps a placeholder name derived from its address.
//
// Small unowned leaves between 0x430000 and 0x500000. Ordered ascending by retail address.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "com_member_release_family_methods.h"

// Two plain ints written as one pair value.
struct IntPair_00430F60
{
    int First;
    int Second;
    IntPair_00430F60() : First(0), Second(0) {}
};
GG_STATIC_ASSERT(sizeof(IntPair_00430F60) == 8);

// FUNCTION: GAMEMD 0x00430F60
// Zero both ints of the pair at the argument and return it.
IntPair_00430F60* __stdcall FUN_00430F60(IntPair_00430F60* out)
{
    *out = IntPair_00430F60();
    return out;
}

// Two owned COM interface pointers at +0x70 and +0x74.
struct ComPair_004A3370
{
    char  Pad_00[0x70];
    IUnk* Second;   // +0x70
    IUnk* First;    // +0x74
};
GG_STATIC_ASSERT(offsetof(ComPair_004A3370, Second) == 0x70);
GG_STATIC_ASSERT(offsetof(ComPair_004A3370, First) == 0x74);

// FUNCTION: GAMEMD 0x004A3370
// Release the interface at +0x74, then the one at +0x70, clearing each.
void __fastcall FUN_004A3370(ComPair_004A3370* self)
{
    if (self->First != 0) {
        GG_COM_RELEASE(self->First);
        self->First = 0;
    }
    if (self->Second != 0) {
        GG_COM_RELEASE(self->Second);
        self->Second = 0;
    }
}
