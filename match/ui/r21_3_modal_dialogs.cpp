// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Modal dialog runners of retail gamemd.exe v1.001: each opens a dialog, pumps the UI until
//   its procedure (or the host) stores a result, and closes it again.
//
// Address index: 0x6586D0
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../platform/input_manager_class_methods.h"
#include "ui_updated_methods.h"
#include "../_layout/map_0087f7e8.h"


// GLOBAL: GAMEMD 0xA8B230
#include "../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;
// GLOBAL: GAMEMD 0xA8ED9C
extern char DAT_00A8ED9C;

// FUNCTION: GAMEMD 0x622650 (decl; reloc) -- UI::BeginDialog.
HWND __fastcall UI_BeginDialog(unsigned short id, int (__stdcall* proc)(HWND, unsigned int, unsigned int, long),
                               int param);
// FUNCTION: GAMEMD 0x622800 (decl; reloc) -- UI::FocusOnWindow.
void __fastcall UI_FocusOnWindow(HWND window);
// FUNCTION: GAMEMD 0x622720 (decl; reloc)
void __fastcall FUN_00622720(HWND window);
// FUNCTION: GAMEMD 0x657DA0 (decl; reloc) -- the dialog procedure.
int __stdcall FUN_00657DA0(HWND window, unsigned int message, unsigned int wParam, long lParam);

// FUNCTION: GAMEMD 0x6586D0
// Run dialog 0x73 with the input manager poked before and after, until the UI reports
// a pending update (stored as result 0x423) or the procedure stores a result; then
// restore the flag from the session and redraw the map.
void FUN_006586D0()
{
    HWND window = UI_BeginDialog(0x73, FUN_00657DA0, 0);
    DAT_00A8ED9C = 1;
    DAT_0087F770->DoSomething();
    if (window) {
        int result;
        SetWindowLongA(window, DWL_USER, (LONG)&result);
        UI_FocusOnWindow(window);
        result = 0;
        while (result == 0) {
            if (UI::Updated()) {
                result = 0x423;
            }
        }
        FUN_00622720(window);
    }
    DAT_0087F770->DoSomething();
    DAT_00A8ED9C = DAT_00A8B230->unknown_35A2;
    DAT_0087F7E8.FUN_004F42F0(2);
}
