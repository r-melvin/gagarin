// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// RTTI at COL0x7FAD18 / TD0x817508 identifies the table 0x7E1B04 as
// GenericList; its slot-zero target is 0x40E3E0, complete span 179 bytes.
// GenericNode COL0x7FACD0 / TD0x8174E8 identifies table0x7E1B0C;
// slot zero is the 69-byte 0x40E390 entry. The 0x40E320 initializer and
// 0x40E340 link body confirm the shared fields. Original native virtual
// declarations remain unrecovered; explicit vptr view.
#include "../_layout/generic_list.h"
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete.
extern "C" void __cdecl FUN_007C8B3D(void* block);

// FUNCTION: GAMEMD 0x40E340
//
// The same guarded unlink as the destructor below - all three of node, its NextNode
// and its PrevNode must be present - followed by the splice. The successor is
// re-read after the two stores rather than reused, which is retail's second
// `MOV EDX,[ECX+4]`.
void GenericNode::LinkNode(GenericNode* node)
{
    if (node != 0) {
        GenericNode* nextNode = node->NextNode;

        if (nextNode != 0) {
            GenericNode* prevNode = node->PrevNode;

            if (prevNode != 0) {
                prevNode->NextNode = nextNode;
                node->NextNode->PrevNode = node->PrevNode;

                node->PrevNode = 0;
                node->NextNode = 0;
            }
        }
    }

    // Read once into a local before the two stores - retail's `MOV EDX,[ECX+4]`
    // comes ahead of `MOV [EAX+8],ECX` - and then read again afterwards, which
    // is the second `MOV EDX,[ECX+4]`. Two locals rather than one, so the
    // reload is not folded away.
    GenericNode* successor = NextNode;

    node->PrevNode = this;
    node->NextNode = successor;

    GenericNode* reloadedSuccessor = NextNode;

    if (reloadedSuccessor) {
        reloadedSuccessor->PrevNode = node;
    }

    NextNode = node;
}

// FUNCTION: GAMEMD 0x40E390
void* GenericNode::DeletingDestructor(char flags)
{
    Vtable = &GG_VTABLE_GENERIC_NODE_SLOTS;

    if (this != 0) {
        GenericNode* nextNode = NextNode;

        if (nextNode != 0) {
            GenericNode* prevNode = PrevNode;

            if (prevNode != 0) {
                prevNode->NextNode = nextNode;
                NextNode->PrevNode = PrevNode;

                PrevNode = 0;
                NextNode = 0;
            }
        }
    }

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x40E3E0
void* GenericList::DeletingDestructor(unsigned int flags)
{
    DestroyList();
    if (flags & 1) {
        FUN_007C8B3D(this);
    }
    return this;
}

// VTABLE: GAMEMD 0x7E1B04 -- GenericList.
GenericListDeletingSlot GG_VTABLE_GENERIC_LIST_SLOTS =
    &GenericList::DeletingDestructor;
GG_STATIC_ASSERT(sizeof(GenericListDeletingSlot) == 4);

// VTABLE: GAMEMD 0x7E1B0C -- GenericNode, direct deleting-entry target.
GenericNodeDeletingSlot GG_VTABLE_GENERIC_NODE_SLOTS =
    &GenericNode::DeletingDestructor;
GG_STATIC_ASSERT(sizeof(GenericNodeDeletingSlot) == 4);
