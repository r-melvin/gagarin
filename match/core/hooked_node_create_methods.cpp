// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at 0x402AF0.

#include <string.h>
#include "hooked_node_create_methods.h"

#pragma intrinsic(memset)

// FUNCTION: GAMEMD 0x402AF0
//
// Allocate a node for an owner and try to attach it. The owner's attach hook
// decides: zero means it took, anything else means it refused and the node is
// detached again and freed.
//
// PARTIAL (96.5%). The residual is one adjacent swap: retail stores
// `At_10 = 0` and only then loads ECX for the hook call, while cl hoists the
// ECX setup one slot earlier. A volatile store that pinned the order was
// removed as match steering; the swap is accepted.
//
// Both outcomes re-test the node pointer against null even though it was tested
// for null nowhere in between; retail has `TEST ESI,ESI` on both arms
// (0x402B26 and 0x402B48), so both are in the source and the two null branches
// share one `return 0`.
//
// The refusal path reaches the owner through the node's own back-pointer
// (`MOV EAX,[ESI+0xC]`) rather than through the owner parameter still live in
// EBX, so it is written that way.
Node_00402AF0* __fastcall FUN_00402AF0(Owner_00402AF0* owner)
{
    Node_00402AF0* node = (Node_00402AF0*)FUN_007C8E17(sizeof(Node_00402AF0));
    memset(node, 0, sizeof(Node_00402AF0));

    FUN_004072D0(node);
    node->At_10 = 0;
    node->Owner = owner;

    if ((node->*owner->Attach)() != 0) {
        if (node != 0) {
            (node->*node->Owner->Detach)();
            node->Owner->Flags0C = node->Owner->Flags0C & ~1;
            FUN_007C8B3D(node);
            return 0;
        }
        return 0;
    }

    if (node == 0) {
        return 0;
    }

    int one = 1;
    owner->Flags0C = owner->Flags0C | one;
    FUN_00407420(DAT_00815E98, node);
    if (owner->Flags08 & 2) {
        DAT_0087DE28 = one;
    }
    return node;
}
