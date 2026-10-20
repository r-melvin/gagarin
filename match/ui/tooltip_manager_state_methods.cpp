// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x7241A0).
//   Names cross-checked against YRpp ToolTipManager.h (consult-only, no
//   LICENSE; each offset reconfirmed against the user's binary in the header).
//
// Translation unit: ToolTipManager::SetState — the activate/deactivate latch.
//
// reccmp annotation:
//   FUNCTION: GAMEMD 0x7241A0   ToolTipManager::SetState (__thiscall)

#include "tooltip_manager_state_methods.h"

// USER32 KillTimer, reached through the IAT slot at 0x7e148c (reloc-normalised).
extern "C" __declspec(dllimport) int __stdcall KillTimer(void* hWnd,
                                                         unsigned int uIDEvent);

// Stripped debug logger at 0x4068E0 (cdecl, variadic; retail body is a bare RET).
extern "C" void __cdecl ToolTipManager_DebugPrint(const char* format, ...);

// FUNCTION: GAMEMD 0x7241A0  (__thiscall)
void ToolTipManager::SetState(bool bState)
{
    if (this->IsActive == bState)
        return;

    this->IsActive = bState;
    if (!bState)
    {
        KillTimer(this->hWnd, 0x54544950);  // 'PITT'
        if (this->CurrentToolTip)
            this->MarkToRedraw(this->CurrentToolTipData);
    }

    ToolTipManager_DebugPrint("Tooltips are %s.\n",
                              this->IsActive == 1 ? "on" : "off");
}
