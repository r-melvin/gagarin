// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at each address below.
//
// Leaf accessors, ordered ascending by retail address.

#include "leaf_accessor_methods.h"

// FUNCTION: GAMEMD 0x401F80
int Obj_00401F00::FUN_00401F80()
{
    return ++unknown_0C;
}

// MATCHED 100% (7/7). The historic 28.6% residual here was the dropped
// `TEST EAX,EAX` before the store: our compiler reused the flags `DEC` had
// already set and branched `JNS` where retail branches `JGE`. The
// write-the-decrement-twice device below (§4.6, "SOLVED: the redundant
// test-self after DEC") reintroduces retail's TEST; this note is kept only so
// the earlier reading is not re-derived.
// FUNCTION: GAMEMD 0x401F90
// Decrement, floored at zero. The counter is stored before the sign test and
// overwritten with a literal zero on the underflow path, rather than the value
// being clamped first and stored once - retail writes the field twice.
void Obj_00401F00::FUN_00401F90()
{
    // The decrement is written twice so VC6 keeps the `TEST` retail has: CSE
    // folds the arithmetic to one `DEC`, but the comparison being its own
    // expression rather than a reference to the stored value stops the flags
    // being reused. See section 4.6.
    int value = unknown_0C;

    unknown_0C = value - 1;

    if (value - 1 < 0) {
        unknown_0C = 0;
    }
}

// FUNCTION: GAMEMD 0x402030
void* Obj_00402000::FUN_00402030()
{
    return &unknown_1C;
}

// FUNCTION: GAMEMD 0x4052E0
void Obj_00405200::FUN_004052E0()
{
    unknown_18 |= 8;
}

// FUNCTION: GAMEMD 0x4072B0
unsigned int Obj_004072B0::FUN_004072B0() const
{
    return (unsigned int)unknown_08 >> 16;
}

// FUNCTION: GAMEMD 0x408070
int Obj_00408000::FUN_00408070() const
{
    return unknown_0C & 1;
}

// FUNCTION: GAMEMD 0x408600
void Obj_00408600::FUN_00408600()
{
    unknown_14 = 0;
}

// Retail loads the subtrahend into ECX, clobbering the object pointer on its
// last use; the plain difference (`return unknown_4C - unknown_50;`) puts it in
// EDX and leaves ECX alone - identical instructions, one register apart, 50%.
// PARTIAL (50%): a volatile subtrahend reached 100% only by steering the
// register choice and was removed; the one-register difference is accepted.
// FUNCTION: GAMEMD 0x408D40
int Obj_00408D00::FUN_00408D40()
{
    int value = unknown_4C;
    return value - unknown_50;
}

// FUNCTION: GAMEMD 0x408D50
int Obj_00408D00::FUN_00408D50() const
{
    return unknown_14;
}

// FUNCTION: GAMEMD 0x409320
// Same shape as 0x408D40 above and the same accepted register difference:
// retail loads the subtrahend into ECX (`MOV ECX,[ECX+0x38]`). PARTIAL (50%).
int Obj_00409300::FUN_00409320()
{
    int value = unknown_34;
    return value - unknown_38;
}

// FUNCTION: GAMEMD 0x424C90
void Obj_00424C00::FUN_00424C90(int value)
{
    unknown_17C = value;
}

// FUNCTION: GAMEMD 0x424CA0
void Obj_00424C00::FUN_00424CA0(int value)
{
    unknown_180 = value;
}

// FUNCTION: GAMEMD 0x425260
void Obj_00425200::FUN_00425260()
{
    unknown_19E = 1;
}

// FUNCTION: GAMEMD 0x425270
void Obj_00425200::FUN_00425270()
{
    unknown_19E = 0;
}

// FUNCTION: GAMEMD 0x465D70
int Obj_00465D00::FUN_00465D70() const
{
    return unknown_EDC;
}

// FUNCTION: GAMEMD 0x46B260
void Obj_0046B200::FUN_0046B260(int value)
{
    unknown_130 = value;
}

// FUNCTION: GAMEMD 0x46B270
int Obj_0046B200::FUN_0046B270() const
{
    return unknown_130;
}

// FUNCTION: GAMEMD 0x473450
int Obj_00473400::FUN_00473450() const
{
    return unknown_04;
}

// FUNCTION: GAMEMD 0x407010
void* __cdecl FUN_00407010()
{
    return DAT_0087E728;
}

// FUNCTION: GAMEMD 0x40A7A0
void* __cdecl FUN_0040A7A0()
{
    return DAT_0087E89C;
}

// FUNCTION: GAMEMD 0x417FD0
int __cdecl FUN_00417FD0()
{
    return GameRules->unknown_44;
}
