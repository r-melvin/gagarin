// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x55B880.

#include "logic_class_pointer_methods.h"

// FUNCTION: GAMEMD 0x55B880  LogicClass::PointerGotInvalid (__thiscall, ret 0x8)
// Drop a dying object from the per-frame logic list. `this` is never touched.
// The removal is DynamicVectorClass::RemoveItem written out inline — bounds
// check, decrement the count, then shift the tail down — followed by `i--` so
// the slot that just moved into place is examined next. That `i--; i++` pair is
// exactly the adjacent `DEC EDX; INC EDX` in the disassembly.
//
// The scan's comparison has the incoming pointer on the left. x86 has two
// encodings for a register/memory compare and VC6 picks by operand order: this
// way gives retail's `CMP EDI,[ESI+EDX*4]`, the other way `CMP [ESI+EDX*4],EDI`.
// One byte, and it was the whole residual.
void LogicClass::PointerGotInvalid(AbstractClass* invalid, bool removed)
{
    if (invalid == 0)
        return;

    if (LOGIC_WHAT_AM_I(invalid) != ABS_LOGIC_MEMBER)
        return;

    for (int i = 0; i < LogicArray.Count; i++)
    {
        if (invalid == ((AbstractClass**)LogicArray.Items)[i])
        {
            if (i < LogicArray.Count)
            {
                LogicArray.Count--;
                for (int j = i; j < LogicArray.Count; j++)
                    ((AbstractClass**)LogicArray.Items)[j] =
                        ((AbstractClass**)LogicArray.Items)[j + 1];
            }
            i--;
        }
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8B40C8
DynamicVectorClassLayout LogicArray;
// END defined globals
