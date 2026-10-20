// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Instruction order, constants, and member offsets follow the complete
//   0x4349F0..0x434A39 retail entry. Its only call is the SetRect IAT at
//   0x7E14B4; the destination +0x30 and four zero arguments are confirmed by
//   the entry disassembly. The same initialization sequence appears in the
//   RTTI-confirmed BitFont constructor at 0x433880.
#include "bit_font_reset_004349f0.h"

// FUNCTION: GAMEMD 0x4349F0
void __fastcall FUN_004349F0(BitFontResetView_004349F0* self)
{
    int zero = 0;
    int one = 1;

    self->unknown_04 = zero;
    self->unknown_20 = zero;
    self->unknown_0C = zero;
    self->unknown_08 = zero;
    self->unknown_24 = 0x7FFF;
    self->unknown_26 = 0x3555;
    self->unknown_28 = 0x40;
    self->unknown_40 = (unsigned char)one;
    self->unknown_41 = (unsigned char)one;
    self->unknown_18 = one;
    self->unknown_1C = one;
    SetRect(&self->unknown_30, zero, zero, zero, zero);
    self->unknown_2C = one;
}
