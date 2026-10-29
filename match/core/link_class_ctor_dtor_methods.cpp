// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x556550 (links the new node after an
//   existing one) and 0x5565A0 (unlinks the node), both with the LinkClass vtable at 0x7E9344.
//   The virtual calls go through the freshly stored vtable constant, so retail inlined the
//   list operations (Add, Remove) from a pointer rather than calling them on `this`.
//
// Address index: 0x556550 0x5565A0
#include "link_class_methods.h"

// Splices `self` in after `object` and returns to the head of the list (the body of Add).
static inline void LinkAfter(LinkClass* self, LinkClass& object)
{
    self->Remove();
    LinkClass* old = object.Next;
    object.Next = self;
    self->Previous = &object;
    self->Next = old;
    if (old) {
        old->Previous = self;
    }
    self->HeadOfList();
}

// Unlinks `self` from its list (the body of Remove).
static inline void Unlink(LinkClass* self)
{
    LinkClass* head = self->HeadOfList();
    LinkClass* tail = self->TailOfList();
    if (self->Previous != 0) {
        self->Previous->Next = self->Next;
    }
    if (self->Next != 0) {
        self->Next->Previous = self->Previous;
    }
    self->Previous = 0;
    self->Next = 0;
    if (head == self) {
        if (tail != self) {
            tail->HeadOfList();
        }
    }
}

// FUNCTION: GAMEMD 0x556550
// Constructs the node, then links it after `object`.
LinkClass::LinkClass(LinkClass& object) : Next(0), Previous(0)
{
    LinkAfter(this, object);
}

// FUNCTION: GAMEMD 0x5565A0
// Unlinks the node from its list.
LinkClass::~LinkClass()
{
    Unlink(this);
}
