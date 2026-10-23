// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Removal of a node from a singly linked list of heap objects (next link at
// +0x28, deleting destructor in virtual slot 8): unlink, then delete the node.
// The list head sits at +0xB0 of the first owner and +0xAC of the second.
// Owners and nodes are placeholders `Obj_<ADDR>` / `Node_<ADDR>`; the node
// classes declare only the slots up to the destructor.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Node_007279E0 {
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual void vf_7();
    virtual ~Node_007279E0();            // slot 8
    unsigned char unknown_04[0x24];
    Node_007279E0* next;                 // +0x28
};
GG_STATIC_ASSERT(offsetof(Node_007279E0, next) == 0x28);

struct Obj_007279E0 {
    unsigned char unknown_00[0xB0];
    Node_007279E0* head;                 // +0xB0
    bool FUN_007279E0(Node_007279E0* target);
};
GG_STATIC_ASSERT(offsetof(Obj_007279E0, head) == 0xB0);

// FUNCTION: GAMEMD 0x007279E0
bool Obj_007279E0::FUN_007279E0(Node_007279E0* target)
{
    if (head == target) {
        head = target->next;
        delete target;
        return true;
    }
    for (Node_007279E0* node = head; node != 0; node = node->next) {
        if (node->next == target) {
            node->next = node->next->next;
            delete target;
            return true;
        }
    }
    return false;
}

struct Node_00727A40 {
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual void vf_7();
    virtual ~Node_00727A40();            // slot 8
    unsigned char unknown_04[0x24];
    Node_00727A40* next;                 // +0x28
};
GG_STATIC_ASSERT(offsetof(Node_00727A40, next) == 0x28);

struct Obj_00727A40 {
    unsigned char unknown_00[0xAC];
    Node_00727A40* head;                 // +0xAC
    bool FUN_00727A40(Node_00727A40* target);
};
GG_STATIC_ASSERT(offsetof(Obj_00727A40, head) == 0xAC);

// FUNCTION: GAMEMD 0x00727A40
bool Obj_00727A40::FUN_00727A40(Node_00727A40* target)
{
    if (head == target) {
        head = target->next;
        delete target;
        return true;
    }
    for (Node_00727A40* node = head; node != 0; node = node->next) {
        if (node->next == target) {
            node->next = node->next->next;
            delete target;
            return true;
        }
    }
    return false;
}
