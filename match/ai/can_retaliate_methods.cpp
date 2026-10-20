// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x44F5C0.

#include "can_retaliate_methods.h"

// FUNCTION: GAMEMD 0x44F5C0
//
// Three ways out. A positive count at +0x504 refuses outright; the slot at +0x284
// grants outright; otherwise the owner's flag at +0x16B9 opens a block of
// disqualifiers, and whatever survives falls through to the owner's own
// permission at +0x408.
//
// The four disqualifiers share one refusal, reached by `goto`. Written as four
// separate `return false;` statements VC6 gives each its own three-instruction
// epilogue — eight instructions more than retail, which branches all four to a
// single copy (43.1% against byte parity).
//
// The last disqualifier is inverted relative to the three before it: the first
// three refuse when their condition fails, the fourth *allows* when +0x2C0 is
// clear and falls through into the refusal otherwise. That is why it is written
// as a jump to the allow path rather than a fourth jump to the refusal — retail's
// `JZ 0x44F622` against the three `JZ 0x44F61E` is exactly that asymmetry.
bool BuildingClass_0044F5C0::FUN_0044F5C0()
{
    if (this->At_504 > 0) {
        return false;
    }

    if ((this->*this->Vptr->At_284)()) {
        return true;
    }

    if (this->Owner->At_16B9) {
        if (!FUN_0050B730(this->At_21C)) goto refuse;
        if (DAT_00A8B238 == 0) goto refuse;
        if (DAT_00A8B320 == 0) goto refuse;
        if (this->At_2C0 == 0) goto allow;
refuse:
        return false;
    }

allow:
    return this->Owner->At_408 != 0;
}
