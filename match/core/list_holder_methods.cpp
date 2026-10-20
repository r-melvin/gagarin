// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "list_holder_methods.h"

// FUNCTION: GAMEMD 0x402C00
// Seed the holder from the global list head, filtered.
ListNode* Holder_00402C00::FUN_00402C00()
{
    Node = (DAT_00815E98)->FUN_004073C0();
    return Node;
}

// FUNCTION: GAMEMD 0x402C20
// Refresh the cached node. The trailing read is a genuine reload - retail emits
// `MOV EAX,[ESI]` after the store rather than reusing the call's result, so the
// return is a separate read of the member and not the value just written.
ListNode* Holder_00402C00::FUN_00402C20()
{
    if (Node) {
        Node = (Node)->FUN_004073E0();
    }
    return Node;
}

// FUNCTION: GAMEMD 0x4031F0
ListNode* Holder_004031F0::FUN_004031F0()
{
    if (Node) {
        Node = (Node)->FUN_004073E0();
    }
    return Node;
}

// FUNCTION: GAMEMD 0x4035B0
void __fastcall FUN_004035B0(void* owner, ListNode** out)
{
    *out = ((ListNode*)((char*)owner + 0xF8))->FUN_004073C0();
}

// FUNCTION: GAMEMD 0x4035D0
ListNode* Holder_004035D0::FUN_004035D0()
{
    if (Node) {
        Node = (Node)->FUN_004073E0();
    }
    return Node;
}
