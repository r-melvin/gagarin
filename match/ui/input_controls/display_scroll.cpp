// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// ScrollClass entries (layout and evidence: display_scroll.h).
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//   /Ob2: retail's __xc entries point at the initialiser bodies themselves
//   (0x692080, 0x6920A0, 0x692220), with no forwarding stub.

#include "display_scroll.h"
#include "display_command.h"
#include "../../core/header_tuning_globals.h"

// FUNCTION: GAMEMD 0x63AB60 (decl; reloc) -- RET 8.
bool __stdcall FUN_0063AB60(int x, int y);

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0xB05660
extern double DAT_00B05660;
// GLOBAL: GAMEMD 0x7F1078
const double DAT_007F1078 = 60.0;

// SYNTHETIC: GAMEMD 0x692080
// GLOBAL: GAMEMD 0xB056B8
double DAT_00B056B8 = DAT_00B05660 / DAT_007F1078;
// SYNTHETIC: GAMEMD 0x6920A0
// GLOBAL: GAMEMD 0xB056A0
double DAT_00B056A0 = 1.0 / DAT_00B056B8;
// SYNTHETIC: GAMEMD 0x692220
// GLOBAL: GAMEMD 0xB056A8
TuningCoordInit DAT_00B056A8(128, 128, 0);

// FUNCTION: GAMEMD 0x692290
// Expansion row (neighbour, not an assigned address): VC6 emits the vtables and the scalar deleting destructor 0x6938F0
// only in a translation unit that defines a constructor, so the constructor is taken here.
ScrollClass::ScrollClass()
    : unknown_5548(0), unknown_554C(false), unknown_5550(0), unknown_5554(0), unknown_5558(false), unknown_5559(true), unknown_555A(false)
{
}

// SYNTHETIC: GAMEMD 0x6938F0
// ScrollClass scalar deleting destructor, emitted from the implicit destructor (ui_display_chain.h).

// FUNCTION: GAMEMD 0x6922E0
void ScrollClass::vf_10(int* key, Point2D* where)
{
    FUN_00692F30();
    TabClass::vf_10(key, where);
}

// FUNCTION: GAMEMD 0x692F30
void ScrollClass::FUN_00692F30()
{
    if (!DisplayFlag_00A8ED9C) {
        Point2D origin = DisplayViewRect_00886FA0.Origin;
        Point2D mouse;
        Point2D* position = WWMouseClassInstance->vf_13(&mouse);
        Point2D where;
        where.X = position->X - origin.X;
        where.Y = position->Y - origin.Y;
        if (!FUN_0063AB60(where.X, where.Y)) {
            if (unknown_555A == true) {
                if (DisplayCmdKeyboard_0087F770->FUN_0054F5C0(1)) {
                    Map_0087F7E8.vf_47(&where);
                } else if (DisplayCmdKeyboard_0087F770->FUN_0054F5C0(2)) {
                    Map_0087F7E8.FUN_00693440(&where);
                }
            } else {
                CellStruct cell;
                DisplayCmdVec3 coord;
                DisplayCmdAbstract* target;
                bool a5;
                bool a6;
                if (FUN_00692300(&where, &cell, &coord, &target, &a5, &a6)) {
                    Map_0087F7E8.vf_46(&cell, a6, target, FUN_00692610(&cell, target, true), false);
                }
                if (unknown_5559 && !DisplayFlag_00A8ED6B) {
                    FUN_00692B60(&where);
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x693060
bool ScrollClass::vf_26()
{
    if (!unknown_555A && !DisplayFlag_00A8ED9C)
    {
        if (!DisplayTactical_00887324 || DisplayTactical_00887324->unknown_0D8 == 0.0f)
            return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x693840
void ScrollClass::vf_49(int arg)
{
    if (unknown_5558)
    {
        vf_18(0, DisplayFlag_00884D44);
        unknown_5558 = false;
    }
    else
    {
        DisplayClass::vf_49(arg);
    }
}

// FUNCTION: GAMEMD 0x693880
void ScrollClass::vf_44(const Point2D* where)
{
    if (!DisplayFlag_00A8ED9C)
    {
        DisplayClass::vf_44(where);
        unknown_5550 = where->X;
        unknown_5554 = where->Y;
        unknown_5558 = false;
        WWMouseClassInstance->vf_4();
    }
}

// FUNCTION: GAMEMD 0x6938C0
void ScrollClass::vf_35()
{
    DisplayClass::vf_35();
    unknown_555A = false;
    if (GetCapture() == DisplayCaptureWindow_00B73550)
        ReleaseCapture();
}
