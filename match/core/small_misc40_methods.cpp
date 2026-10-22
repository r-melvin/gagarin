// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at the three addresses below.

#include "small_misc40_methods.h"

// FUNCTION: GAMEMD 0x403820
void __fastcall FUN_00403820(Obj_00403820* self)
{
    self->field_00 = 0;
    self->field_04 = 0;
    self->field_08 = 0;
    self->field_0C = 0;
    self->field_10 = 0;
    self->field_14 = 0;
    self->field_18 = 0;
    self->field_1C = 0;
    self->field_28 = 0;
    self->field_2C = 0;
    self->field_48 = 0;
    self->field_50 = 0;
    // PARTIAL: VC6 hoists this one non-zero store to the top of the function;
    // retail has it between +0x50 and +0x44. Not steered.
    self->field_40 = 0x1388;
    self->field_44 = 0;
    self->field_30 = 0;
    self->field_34 = 0;
    self->field_38 = 0;
    self->field_3C = 0;
    self->field_54 = 0;
    self->field_4C = 0;
}

// FUNCTION: GAMEMD 0x407100
void __fastcall FUN_00407100(Timer_00407100* self, int value)
{
    self->field_00 = 0;

    Pair64 start = FUN_004093B0();

    self->StartLo   = start.Lo;
    self->field_00 |= 1;
    self->Limit     = 0x3E8;
    self->Scaled    = value << 16;
    self->StartHi   = start.Hi;
    self->Rate      = 0x10624D;
    self->field_14  = 0;

    FUN_004071C0(self);
}

// FUNCTION: GAMEMD 0x408D30
int Obj_00408D30::FUN_00408D30()
{
    // Retail loads the second operand into ECX (`MOV ECX,[ECX+0x90]`,
    // clobbering `this`): Tail is volatile (shared with the stream thread;
    // see the header).
    int head = Head;

    return head - Tail;
}
