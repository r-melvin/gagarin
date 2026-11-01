// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x7773C0 and its log strings (0x849E94, 0x849E70) in the user's
//   gamemd.exe v1.001.
//
// Address index: 0x7773C0

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- debug log.
void FUN_004068E0(const char* format, ...);
// FUNCTION: GAMEMD 0x5BF500 (decl; reloc)
void __fastcall FUN_005BF500(bool value);
// FUNCTION: GAMEMD 0x407020 (decl; reloc)
void FUN_00407020();

// The mouse/view object at 0x887640 (only the slots used here are named).
class FocusView_007773C0
{
public:
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual bool vf_7();
};
// GLOBAL: GAMEMD 0x887640
extern FocusView_007773C0* DAT_00887640_focus;
// GLOBAL: GAMEMD 0xB73560 -- whether the mouse was captured when focus was lost.
extern bool DAT_00B73560;

// FUNCTION: GAMEMD 0x7773C0
// The window lost focus: log it, drop the capture and remember whether the mouse was captured.
void FUN_007773C0()
{
    FUN_004068E0("Focus_Loss()\n");
    FUN_005BF500(true);
    FUN_00407020();
    if (DAT_00887640_focus != 0) {
        DAT_00B73560 = DAT_00887640_focus->vf_7();
        FUN_004068E0("Focus_Loss(): _MouseCaptured = %s\n", DAT_00B73560 ? "true" : "false");
        DAT_00887640_focus->vf_5();
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB73560
bool DAT_00B73560;
// END defined globals
