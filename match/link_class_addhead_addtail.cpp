// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   LinkClass::AddHead / LinkClass::AddTail, matched byte-for-byte against the
//   user's retail gamemd.exe v1.001 (Ghidra CLI disassembly).
//
// Functions ordered ascending by retail address.
#include "link_class_addhead_addtail.h"

// FUNCTION: GAMEMD 0x5566D0  LinkClass::AddHead (__thiscall)
//   Unlink self (Remove, slot +0x24), find the head of `object`'s list
//   (HeadOfList, slot +0x18), and splice self in front of that head.
//     mov [head+0x8], this   ; head->Previous = this
//     mov [this+0x4], head   ; this->Next     = head
//     mov [this+0x8], 0      ; this->Previous = 0
//   Returns `this`.
LinkClass* LinkClass::AddHead(LinkClass& object)
{
    Remove();
    LinkClass* head = object.HeadOfList();
    head->Previous = this;
    Next = head;
    Previous = 0;
    return this;
}

// FUNCTION: GAMEMD 0x556700  LinkClass::AddTail (__thiscall)
//   Unlink self (Remove, slot +0x24), find the tail of `object`'s list
//   (TailOfList, slot +0x1c), and splice self after that tail.
//     mov [tail+0x4], this   ; tail->Next     = this
//     mov [this+0x8], tail   ; this->Previous = tail
//     mov [this+0x4], 0      ; this->Next     = 0
//   Returns HeadOfList() (slot +0x18).
LinkClass* LinkClass::AddTail(LinkClass& object)
{
    Remove();
    LinkClass* tail = object.TailOfList();
    tail->Next = this;
    Previous = tail;
    Next = 0;
    return HeadOfList();
}
