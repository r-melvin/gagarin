// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
// /Ob2 inlines the real destructor into the retail scalar wrapper at 0x434A40.
// The normal destructor remains a separately emitted function.
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
BitFont::BitFont(const char* key) throw()
{
    this->Reset();

    this->InternalPTR = FUN_00433990(key);
    if (this->InternalPTR != 0) {
        this->Width = this->InternalPTR->Width;
        this->unknown_1C = this->InternalPTR->Height;
        this->FUN_00434700();
        return;
    }

    this->Reset();
    return;
}

// LIBRARY: GAMEMD 0x7C93E8 — CRT free.
// LIBRARY: GAMEMD 0x7C8B3D — operator delete used by the destructor.
extern "C" void __cdecl FUN_007C93E8(void* block);

// FUNCTION: GAMEMD 0x433940
// SYNTHETIC: GAMEMD 0x434A40
BitFont::~BitFont()
{
    void* block = Pointer_8;
    if (block) FUN_007C93E8(block);
    BitFontInternalData* data = InternalPTR;
    if (data) {
        if (data->SymbolTable) ::operator delete(data->SymbolTable);
        if (data->Bitmaps) ::operator delete(data->Bitmaps);
        ::operator delete(data);
    }
}
