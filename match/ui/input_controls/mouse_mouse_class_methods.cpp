// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Entry-point disassembly of retail gamemd.exe v1.001 at 0x40D280, 0x5BDA80, 0x5BDAA0, 0x5BDAB0, 0x5BDC80,
//   0x5BDDC0, 0x5BDF30 and 0x5BDF50, all reached through the MouseClass primary vtable 0x7E1964 (layout, slot and
//   global evidence: mouse_mouse_class.h). String: 'MOUSE.SHA' 0x82604C.

#include "../../FUNCTION.H"
#include "mouse_mouse_class.h"

// The hot-spot and frame step the cursor entries share: pick the first frame of the row (the alternate set when the
// flag is set and the row has one), derive the hot spot from the shape's extent and hand all three to the
// software cursor.
inline void MouseClass::ApplyCursorRow(int index, bool flag)
{
    const MouseCursorEntry& row = MouseCursorTable[index];
    int start;
    if (flag && row.AltStartFrame != -1)
        start = row.AltStartFrame;
    else
        start = row.StartFrame;
    int x = 0;
    int y = 0;
    if (row.unknown_14 == MouseHotCenter)
        x = DAT_00ABF294->unknown_02 / 2;
    if (row.unknown_14 == MouseHotFar)
        x = DAT_00ABF294->unknown_02;
    if (row.unknown_18 == MouseHotCenter)
        y = DAT_00ABF294->unknown_04 / 2;
    if (row.unknown_18 == MouseHotFar)
        y = DAT_00ABF294->unknown_04;
    Point2D hot(x, y);
    WWMouseClassInstance->SetCursor(&hot, DAT_00ABF294, CursorFrame + start);
}

// FUNCTION: GAMEMD 0x40D280
int MouseClass::vf_40()
{
    return RequestedCursor;
}

// FUNCTION: GAMEMD 0x5BDA80
void MouseClass::vf_18(int cursor, bool flag)
{
    RequestedCursor = cursor;
    vf_19(cursor, flag);
}

// FUNCTION: GAMEMD 0x5BDAA0
void MouseClass::vf_20()
{
    vf_19(RequestedCursor, 0);
}

// FUNCTION: GAMEMD 0x5BDAB0
void MouseClass::vf_21(bool flag)
{
    if (CursorFlag != flag) {
        CursorFlag = flag;
        ApplyCursorRow(CursorIndex, flag);
    }
}

// FUNCTION: GAMEMD 0x5BDC80
bool MouseClass::vf_19(int cursor, bool flag)
{
    const MouseCursorEntry& row = MouseCursorTable[cursor];
    if (row.AltStartFrame == -1)
        flag = false;
    if (MouseCursorApplied && (!DAT_00ABF294 || (cursor == CursorIndex && flag == CursorFlag)))
        return false;
    MouseCursorApplied = true;
    MouseTimer = MouseCursorTimer(row.Delay);
    CursorFrame = 0;
    ApplyCursorRow(cursor, flag);
    CursorIndex = cursor;
    CursorFlag = flag;
    return true;
}

// FUNCTION: GAMEMD 0x5BDDC0
// CAPPED at 92.6%: identical instruction multiset; retail keeps the row pointer in EBX and the remaining time in EDI,
// the compiled code has them the other way round (seven instructions). Variants tried without effect: remaining declared
// first / late, row via table index or pointer or reference, timer helper methods (Remaining / Expired), entry helper
// methods (NextFrame / IsAnimated), goto and flag shapes of the expiry test, base-call return types.
void MouseClass::vf_10(int* key, Point2D* where)
{
    const MouseCursorEntry* row = &MouseCursorTable[CursorIndex];
    if (row->Delay != 0) {
        int remaining = MouseTimer.Delay;
        if (MouseTimer.Timer.StartTime != -1) {
            int elapsed = MouseTimer.Timer.Clock.GetTime() - MouseTimer.Timer.StartTime;
            if (elapsed < remaining)
                remaining -= elapsed;
            else
                remaining = 0;
        }
        if (remaining == 0) {
            CursorFrame++;
            if (CursorFlag)
                CursorFrame %= row->AltFrameCount;
            else
                CursorFrame %= row->FrameCount;
            MouseTimer = MouseCursorTimer(row->Delay);
            ApplyCursorRow(CursorIndex, CursorFlag);
        }
    }
    ScrollClass::vf_10(key, where);
}

// FUNCTION: GAMEMD 0x5BDF30
void MouseClass::vf_05()
{
    ScrollClass::vf_05();
    DAT_00ABF294 = (Obj_0069E430*)FUN_004A38D0("MOUSE.SHA", &MouseShapeFlag);
}

// FUNCTION: GAMEMD 0x5BDF50
void MouseClass::vf_07()
{
    ScrollClass::vf_07();
    CursorFlag = false;
    RequestedCursor = 0;
}

// FUNCTION: GAMEMD 0x5BDA40
// Build the base scroll display, then clear the cursor state; the object's own vtables are seated
// as part of the construction.
MouseClass::MouseClass()
    : CursorFlag(false), CursorIndex(0), RequestedCursor(0), CursorFrame(0)
{
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xABF2DD
bool MouseCursorApplied;
// GLOBAL: GAMEMD 0xABF2DC
char MouseShapeFlag;
// END defined globals
