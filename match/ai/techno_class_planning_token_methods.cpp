// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6385C0.

#include "techno_class_planning_token_methods.h"

// FUNCTION: GAMEMD 0x6385C0
//
// Advance this unit along its planning token. The token must exist, hold at
// least one node, have a usable +0x8C (-1 or positive) and not already be
// stepping (+0x1C). The unit is queued mission 0x1C, the token builds the next
// 0x6F-byte record, a heap copy of it (kind 4 forced to sub-kind 2) is
// appended to the global record list, and the token is marked as stepping.
bool Techno_006385C0::TryNextPlanningTokenNode()
{
    Token_006385C0* token = this->FUN_00705D20();
    if (token
        && token->NodeCount > 0
        && (token->At_08C == -1 || token->At_08C > 0)
        && !token->At_01C) {
        (this->*this->Vtbl->QueueMission)(0x1C, 1);

        Node_006385C0 rec = token->FUN_00636590();
        Node_006385C0* copy = new Node_006385C0;
        *copy = rec;
        if (copy->At_000 == 4) {
            copy->At_01D = 2;
        }
        DAT_00AC4B48.AddItem(copy);

        token->At_01C = 1;
        return true;
    }
    return false;
}
