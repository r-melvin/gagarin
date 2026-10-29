// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at the three addresses below.

#include "small_misc40_methods.h"
#include "triple_timer_init_methods.h"
#include "../audio/audio_time_methods.h"

// FUNCTION: GAMEMD 0x403820
void FUN_00403820(Obj_00403820* self)
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
void FUN_00407100(Timer_00401000* self, int value)
{
    // The clock returns EDX:EAX; retail stores the two words separately at
    // 0x407113 and 0x407128, with other field updates between them.
    union { __int64 value; struct { unsigned int lo; int hi; } words; } start;
    self->Flags32 = 0;
    start.value = Unsorted_AudioGetTime();
    self->unknown_18_lo = start.words.lo;
    self->Flags32 |= 1;
    self->unknown_10_lo = 0x3E8;
    self->Target = value << 16;
    self->unknown_1C = start.words.hi;
    self->unknown_0C = 0x10624D;
    self->unknown_14 = 0;
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
