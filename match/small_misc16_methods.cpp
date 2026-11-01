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
void Obj_00408B10::FUN_00408B10(Node_00408B10* node)
{
    ((ListNode*)((char*)this + 4))->FUN_00407440((ListNode*)node);

    Count++;
    Total += node->at1C;

    node->at30 = this;

    unknown_10 &= ~2;
}

// MATCHED. Both 0x433ED0 and its callee 0x433CF0 are __thiscall members: 0x433CF0
// reads ECX as its receiver (`MOV EAX,[ECX+4]`), and 0x433ED0 leaves ECX untouched
// so the receiver passes straight through (RET 8, two stack arguments). As a
// __stdcall free function it scored 60% on argument-evaluation order.
// FUNCTION: GAMEMD 0x433ED0
int Obj_00433CF0::FUN_00433ED0(int a, int b)
{
    FUN_00433CF0(a, &b, 0, b);

    return b;
}
