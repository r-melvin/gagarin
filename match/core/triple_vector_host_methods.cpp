// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Bytes matched against retail gamemd.exe v1.001 at 0x42F1E0.

#include "triple_vector_host_methods.h"

// FUNCTION: GAMEMD 0x42E6F0
//
// The larger host: the same three vectors, then its own scalar block.
//
// The wide vector's trailing dword is zeroed between the first and second
// vectors, not with the rest of the scalars — retail's `MOV [ESI+0x1C],EDI` at
// 0x42E71A sits inside the second vector's call setup. Written with the other
// scalars it moves to the end.
//
// Every zero comes from one register (EDI), so it is a named variable here.
Host_0042F1E0* Host_0042F1E0::CtorFull()
{
    int zero = 0;

    WideVector_0042F1E0* wide = &this->Wide;
    wide->BaseCtor(zero, (const void*)zero);
    wide->Vptr = VTBL_007E38B0;
    wide->GrowthStep = 10;
    wide->ActiveCount = zero;

    NarrowVector_0042F1E0* first = &this->First;
    this->Wide._pad018 = zero;
    first->BaseCtor(zero, (const void*)zero);
    first->Vptr = VTBL_007E3890;
    first->GrowthStep = 10;
    first->ActiveCount = zero;

    NarrowVector_0042F1E0* second = &this->Second;
    second->BaseCtor(zero, (const void*)zero);
    second->Vptr = VTBL_007E3890;
    second->GrowthStep = 10;
    second->ActiveCount = zero;

    this->At_50 = (unsigned short)zero;
    this->At_52 = (unsigned short)zero;
    this->At_54 = zero;
    this->At_58 = zero;
    this->At_5C = zero;
    this->At_60 = zero;
    this->At_64 = zero;
    this->At_68 = zero;
    this->At_6C = zero;
    this->At_70 = zero;
    this->At_74 = zero;

    this->Vptr = VTBL_007E3880;
    return this;
}

// FUNCTION: GAMEMD 0x42F1E0
//
// Construct a host holding three growable vectors — one over a 0x10-byte element
// and two over a 4-byte one — each empty and each with the default growth step of
// ten.
//
// Each member's address is taken into a local: retail computes
// `LEA EDI,[ESI+disp]` once per member and reaches all four of its stores through
// it, which is the hoisted-local half of the section 4.6 address rule. Writing the
// stores as `this->Wide.Vptr = ...` gives base-plus-displacement off `this` and no
// LEA at all.
Host_0042F1E0* Host_0042F1E0::Ctor(int)
{
    WideVector_0042F1E0* wide = &this->Wide;
    wide->BaseCtor(0, 0);
    wide->Vptr = VTBL_007E38B0;
    wide->GrowthStep = 10;
    wide->ActiveCount = 0;

    NarrowVector_0042F1E0* first = &this->First;
    first->BaseCtor(0, 0);
    first->Vptr = VTBL_007E3890;
    first->GrowthStep = 10;
    first->ActiveCount = 0;

    NarrowVector_0042F1E0* second = &this->Second;
    second->BaseCtor(0, 0);
    second->Vptr = VTBL_007E3890;
    second->GrowthStep = 10;
    second->ActiveCount = 0;

    this->Vptr = VTBL_007E3880;
    return this;
}
