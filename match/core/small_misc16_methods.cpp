// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc16_methods.h"

// FUNCTION: GAMEMD 0x402B80
// Unlink, notify through the table, clear the table's own live bit, then free
// the object and forget the global handle.
void Obj_00402B80::FUN_00402B80()
{
    ((ListNode*)this)->FUN_00407450();

    (*(Slot18*)((char*)Table + 0x18))(this);

    Table->at0C &= ~1;

    FUN_007C8B3D(this);

    DAT_0087DE28 = 0;
}

// FUNCTION: GAMEMD 0x408B10
// Splice the node in before the anchor, bump the count, add the node's weight
// to the running total, point it back at the owner and drop the owner's bit 1.
// The trailing load-and-store of +0x10 is that flag clear, not a return value -
// `AND AL,0xFD` sits between them.
void __fastcall Obj_00408B10::FUN_00408B10(Node_00408B10* node)
{
    ((ListNode*)((char*)this + 4))->FUN_00407440((ListNode*)node);

    Count++;
    Total += node->at1C;

    node->at30 = this;

    unknown_10 &= ~2;
}

// EVALUATION-ORDER DELTA (status partial, 60% - 6/10). Every instruction is
// present. Retail computes the address of the second parameter first
// (`LEA EDX,[ESP+8]`) and loads the first parameter after the initial push;
// we load the first parameter early and take the address after. Argument
// evaluation order inside a call is unspecified, and neither taking the address
// inline nor binding it to a local ahead of the call moves it. Two phrasings
// tried.
// FUNCTION: GAMEMD 0x433ED0
int __stdcall FUN_00433ED0(int a, int b)
{
    FUN_00433CF0(a, &b, 0, b);

    return b;
}
