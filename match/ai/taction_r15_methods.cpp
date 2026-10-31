// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   More TActionClass handlers (TAction.CPP, code range 0x6dcd70-0x6e4b4f) read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   Address index: 0x6E2600.

#include "taction_class_methods.h"
#include "../_layout/rules_class.h"
#include "../_layout/cell.h"

// GLOBAL: GAMEMD 0x8871E0
extern RulesClass* DAT_008871E0;

// GLOBAL: GAMEMD 0xB0E680 -- the undefined cell.
extern CellStruct DAT_00B0E680;

// FUNCTION: GAMEMD 0x53A100 (decl; reloc) -- a global byte flag, read without a receiver.
bool __cdecl FUN_0053A100();
// FUNCTION: GAMEMD 0x539EB0 (decl; reloc)
void __fastcall FUN_00539EB0(int a, int b, CellStruct cell, void* c);

// FUNCTION: GAMEMD 0x6E2600
// Unless the lightning flag is raised, run the 0x539EB0 step on the action's parameter.
bool TActionClass::FUN_006E2600(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (FUN_0053A100())
        return false;
    FUN_00539EB0(unknown_90, DAT_008871E0->LightningDeferment, DAT_00B0E680, 0);
    return true;
}
