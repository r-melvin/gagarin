// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x401FC0.

#include "drain_and_unlink_methods.h"

// FUNCTION: GAMEMD 0x401FC0
//
// Take the object apart: unlink it if it is still in a list, drain every node off
// +0x24 back to the context's free list, tear down +0x1C, and finally return the
// object itself to the context's other free list.
//
// The self-comparison is written with the member on the left. x86 picks the
// compare encoding from operand order, and retail has `CMP [EDI+4],EDI` — the
// memory form — so `this->Link != this` is the way round that reproduces it.
//
// The last call is a tail `JMP`, so 0x407530 is a free __fastcall rather than a
// member.
void Obj_00401FC0::FUN_00401FC0()
{
    if (this->Link != this) {
        FUN_00407450(this);
    }

    Node_00401FC0* node;
    while ((node = FUN_00407470(this->At_24)) != 0) {
        FUN_00407450(node);
        FUN_00408600(node);
        FUN_00407530(this->Ctx->NodeList, node);
    }

    FUN_00408530(this->At_1C);
    FUN_00407530(this->Ctx->ObjList, this);
}
