// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit SerialEd.cpp. The name is the source-file string at 0x83ec28
//   in retail gamemd.exe v1.001, passed by the assert at 0x695f23 inside this object's
//   code range (0x6954e0-0x696d1f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../core/mathtbl_init_shapes.h"
#include <windows.h>
#include "../ui/ui_updated_methods.h"
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7F1180
extern const double DAT_007F1180;
// GLOBAL: GAMEMD 0xB05768
extern double DAT_00B05768;
// GLOBAL: GAMEMD 0xB057A0
extern double DAT_00B057A0;
// GLOBAL: GAMEMD 0xB057B8
extern double DAT_00B057B8;

// SYNTHETIC: GAMEMD 0x00695510
// dynamic initializer for DAT_00B057B8

// GLOBAL: GAMEMD 0x00B057B8
double DAT_00B057B8 = DAT_00B05768 / DAT_007F1180;

// SYNTHETIC: GAMEMD 0x00695530
// dynamic initializer for DAT_00B057A0

// GLOBAL: GAMEMD 0x00B057A0
double DAT_00B057A0 = 1.0 / DAT_00B057B8;

// SYNTHETIC: GAMEMD 0x006956B0
// GLOBAL: GAMEMD 0x00B057A8
MathTblCoord DAT_00B057A8;

// The serial settings the dialog edits: 0x70 bytes starting at +0x88 of the dialog object.
struct SerialSettings_006956D0
{
    int unknown_00[0x1C];
};
GG_STATIC_ASSERT(sizeof(SerialSettings_006956D0) == 0x70);

// The serial-port editor dialog object.
struct SerialEdDialog_006956D0
{
    HWND Window;                            // +0x00
    int Result;                             // +0x04
    unsigned char unknown_08[0x80];         // +0x08
    SerialSettings_006956D0 Settings;       // +0x88
    // FUNCTION: GAMEMD 0x695FD0 (decl; reloc) -- fill the controls from the settings.
    void FUN_00695FD0(SerialSettings_006956D0* settings);
    // FUNCTION: GAMEMD 0x6956D0
    bool FUN_006956D0(SerialSettings_006956D0* settings);
};
GG_STATIC_ASSERT(offsetof(SerialEdDialog_006956D0, Result) == 0x4);
GG_STATIC_ASSERT(offsetof(SerialEdDialog_006956D0, Settings) == 0x88);

// FUNCTION: GAMEMD 0x622650 (decl; reloc) -- UI::BeginDialog.
HWND __fastcall UI_BeginDialog(unsigned short id, int (__stdcall* proc)(HWND, unsigned int, unsigned int, long),
                               int param);
// FUNCTION: GAMEMD 0x622800 (decl; reloc) -- UI::FocusOnWindow.
void __fastcall UI_FocusOnWindow(HWND window);
// FUNCTION: GAMEMD 0x622720 (decl; reloc)
void __fastcall FUN_00622720(HWND window);
// FUNCTION: GAMEMD 0x532100 (decl; reloc)
void __fastcall FUN_00532100(bool flag);
// FUNCTION: GAMEMD 0x695760 (decl; reloc) -- the dialog procedure.
int __stdcall FUN_00695760(HWND window, unsigned int message, unsigned int wParam, long lParam);

// FUNCTION: GAMEMD 0x6956D0
// Run the editor on a copy of the settings: the dialog stores its result (1 = accepted)
// in the object; on accept the edited settings are copied back to the caller.
bool SerialEdDialog_006956D0::FUN_006956D0(SerialSettings_006956D0* settings)
{
    Result = -1;
    Window = UI_BeginDialog(0xED, FUN_00695760, 0);
    if (Window) {
        SetWindowLongA(Window, DWL_USER, (LONG)this);
        FUN_00695FD0(settings);
        UI_FocusOnWindow(Window);
        while (Result < 0 && UI::Updated() != 1) {
            FUN_00532100(false);
        }
        FUN_00622720(Window);
        if (Result == 1) {
            *settings = Settings;
        }
    }
    bool accepted = Result == 1;
    return accepted;
}
