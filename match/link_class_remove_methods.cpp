// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   LinkClass::Remove, matched byte-for-byte against the user's retail
//   gamemd.exe v1.001 (Ghidra CLI disassembly at 0x556730).
//
// Functions ordered ascending by retail address.
#include "link_class_remove_methods.h"

// FUNCTION: GAMEMD 0x556730  LinkClass::Remove (__thiscall)
//   Cache the list head (HeadOfList, slot +0x18 -> EDI) and tail (TailOfList,
//   slot +0x1c -> EAX), then unlink self from the doubly-linked chain:
//     if (Previous != 0) Previous->Next     = Next;   ; [EDX+0x4] = [ESI+0x4]
//     if (Next     != 0) Next->Previous     = Previous;; [EDX+0x8] = [ESI+0x8]
//     Previous = 0; Next = 0;                          ; [ESI+0x8]=0; [ESI+0x4]=0
//   Return value:
//     if (head != this)          return head;          ; mov eax, edi
//     else if (tail == this)     return 0;             ; xor eax, eax
//     else                       return tail->HeadOfList(); ; [vptr+0x18]
LinkClass* LinkClass::Remove()
{
    LinkClass* head = HeadOfList();
    LinkClass* tail = TailOfList();
    if (Previous != 0) {
        Previous->Next = Next;
    }
    if (Next != 0) {
        Next->Previous = Previous;
    }
    Previous = 0;
    Next = 0;
    if (head == this) {
        if (tail == this) {
            return 0;
        }
        return tail->HeadOfList();
    }
    return head;
}
