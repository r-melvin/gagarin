// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   LinkClass doubly-linked-list primitives, matched byte-for-byte against the
//   user's retail gamemd.exe v1.001 (Ghidra CLI disassembly).
//
// Functions ordered ascending by retail address.
#include "link_class_methods.h"

// FUNCTION: GAMEMD 0x5565F0  LinkClass::Zap (__thiscall)
//   xor eax,eax / mov [ecx+4],eax / mov [ecx+8],eax / ret
void LinkClass::Zap()
{
    Next = 0;
    Previous = 0;
}

// FUNCTION: GAMEMD 0x556620
LinkClass* LinkClass::GetNext()
{
    return Next;
}

// FUNCTION: GAMEMD 0x556630
LinkClass* LinkClass::GetPrev()
{
    return Previous;
}

// FUNCTION: GAMEMD 0x556640  LinkClass::HeadOfList (__thiscall)
//   Walk the Previous chain to the head; stop if we loop back to `this`.
LinkClass* LinkClass::HeadOfList()
{
    LinkClass* link = this;
    while (link->Previous) {
        link = link->Previous;
        if (link == this) {
            break;
        }
    }
    return link;
}

// FUNCTION: GAMEMD 0x556670  LinkClass::TailOfList (__thiscall)
//   Walk the Next chain to the tail; stop if we loop back to `this`.
LinkClass* LinkClass::TailOfList()
{
    LinkClass* link = this;
    while (link->Next) {
        link = link->Next;
        if (link == this) {
            break;
        }
    }
    return link;
}

// FUNCTION: GAMEMD 0x5566A0  LinkClass::Add (__thiscall)
//   Unlink self (Remove, slot 0x24), splice in after `object`, then return the
//   head of the list (HeadOfList, slot 0x18).
LinkClass* LinkClass::Add(LinkClass& object)
{
    Remove();
    LinkClass* old = object.Next;
    object.Next = this;
    Previous = &object;
    Next = old;
    if (old) {
        old->Previous = this;
    }
    return HeadOfList();
}
