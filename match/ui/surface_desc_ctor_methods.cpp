// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x433880.
//
// FUNCTION: GAMEMD 0x433880   BitFont::BitFont (__thiscall)
//
// Class identity RTTI-confirmed directly against the user's binary (Tier 1):
// vtable 0x7E3A78 -> complete object locator @0x7E3A74 -> type descriptor
// 0x818B68 -> name `.?AVBitFont@@`.

#include "surface_desc_ctor_methods.h"

// FUNCTION: GAMEMD 0x433880
//
// Construct the descriptor from a key: reset it to the empty 1x1 state, look the
// key up, and adopt the width and height it reports. If the lookup fails the
// reset runs again, which puts the object back to empty after the failed
// assignment to +0x4.
//
// The success path returns early rather than skipping the second reset with an
// else; retail has two epilogues (0x4338F2 and the tail), so the early return is
// the shape.
BitFont::BitFont(Key_00433880* key)
{
    this->Vptr = VTBL_007E3A78;
    this->Reset();

    this->Info = FUN_00433990(key);
    if (this->Info != 0) {
        this->Width = this->Info->Width;
        this->Height = this->Info->Height;
        this->FUN_00434700();
        return;
    }

    this->Reset();
    return;
}
