// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x6386E0.

#include "techno_class_clear_tokens_methods.h"

// FUNCTION: GAMEMD 0x6386E0
//
// MATCHED (100.0%, 112/112). The gate-byte test only reaches retail's
// MOVSX EAX,byte ptr [EDI+0x1D] / TEST EAX,EAX when the char is bound to an
// int through a ternary that supplies the null-gate fallback
// (`int gateFlag = (gate != 0) ? gate->At_01D : 0;`): the ternary's int type
// forces the widening while the short-circuit shape of the branch is kept.
// Every in-place spelling of the test (plain `== 0`, an `(int)` cast, `!expr`,
// `expr + 0 == 0`, `(expr | 0) == 0`, an inline accessor returning int, an
// inline accessor binding the char to an int local) narrows to
// MOV AL,byte ptr / TEST AL,AL, which also shortens three forward jumps.
//
// TechnoClass::ClearPlanningTokens — tear down every planning node hanging off
// the unit's planning token. Nothing happens without a token; the gating record
// (when one is supplied and its +0x1D byte is set) and an empty node list both
// skip straight to clearing the token's +0x1C flag. Otherwise each node's entry
// for the token's owner is unhooked, its payload and the entry itself are freed
// back to the game heap, and a node left with nothing at +0x10 is deleted. If
// the list was not empty to begin with, the owner's sector (or the global
// override at 0xA83D4C when the sector says so) is refreshed and the token's
// owner is pushed onto the list at 0xAC4C40. Finally the token's sub-object is
// reset through its slot 0x0C, the three coordinate fields at +0x8C..+0x94 go
// to -1 and the two flag bytes at +0x98/+0x99 are cleared.
void __fastcall Techno_006386E0::ClearPlanningTokens(Record_006386E0* gate)
{
    if (this == 0) {
        return;
    }

    Token_006386E0* token = this->FUN_00705D20();
    if (token == 0) {
        return;
    }

    void* slot;

    int gateFlag = (gate != 0) ? gate->At_01D : 0;
    if (gateFlag == 0 && token->NodeCount > 0) {
        Token_006386E0* list = this->FUN_00705D20();
        if (list != 0) {
        int count = list->NodeCount;
        bool wasEmpty = (count == 0);

        for (int i = 0; i < count; i++) {
            Node_006386E0* node = list->Nodes[i];
            Owner_006386E0* owner = list->Owner;
            int index = node->FUN_00634290(owner);
            Entry_006386E0* entry;
            if (index == -1) {
                entry = 0;
            } else {
                entry = node->Entries[index];
            }
            slot = entry;
            if (entry != 0) {
                node->FUN_00635060(slot);
                GameDelete_006386E0(((Entry_006386E0*)slot)->At_004);
                node->FUN_0063DFD0(&slot);
                GameDelete_006386E0(slot);
                if (node->At_010 == 0 && node != 0) {
                    node->FUN_0063D9C0(1);
                }
            }
        }

        if (!wasEmpty) {
            slot = list->Owner;
            Sector_006386E0* sector = ((Owner_006386E0*)slot)->At_21C;
            Scene_006386E0* scene = sector->At_030;
            if (sector->FUN_0050B6F0() && DAT_00A83D4C != 0) {
                scene = DAT_00A83D4C->At_030;
            }
            scene->FUN_00639F80();
            DAT_00AC4C40.FUN_0063E900(&slot);
        }

        (list->Sub.*list->Sub.Vtbl->At_00C)();
        list->At_08C = -1;
        list->At_090 = -1;
        list->At_094 = -1;
        list->At_098 = 0;
        list->At_099 = 0;
        }
    }

    token->At_01C = 0;
}
