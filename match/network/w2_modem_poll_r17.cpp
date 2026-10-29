// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5F33B0 (the modem poll callback installed by
//   FUN_005F3400) in the NullMgr translation unit range.
//
// Address index: 0x5F33B0

#include "../platform/input_manager_class_methods.h"

// FUNCTION: GAMEMD 0x48D080 (decl; reloc)
void __cdecl FUN_0048D080();
// FUNCTION: GAMEMD 0x5D4D50 (decl; reloc)
void __cdecl FUN_005D4D50();

// GLOBAL: GAMEMD 0xAC1344
extern bool DAT_00AC1344;

// FUNCTION: GAMEMD 0x5F33B0
// Modem poll callback: pump the UI, and answer -1000 once Escape was pressed.
int __cdecl FUN_005F33B0()
{
    FUN_0048D080();
    FUN_005D4D50();
    unsigned int key = DAT_0087F770->FUN_0054F000();
    if (key != 0) {
        DAT_0087F770->DoSomething();
        if (key == 0x1B) {
            DAT_00AC1344 = true;
            return -1000;
        }
    }
    return DAT_00AC1344 ? -1000 : 0;
}
