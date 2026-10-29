// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x552AD0, 0x552C90, 0x554100, 0x554150 and
//   0x554400 (vtable 0x7ECF64; the screen-size globals at 0x8A00A4/0x8A00A8 against the
//   reference sizes 0x7F5BE0/0x7F5BE4/0x7F5BF0).
//
// Address index: 0x552AD0 0x552C90 0x554100 0x554150 0x554400

#include "../_layout/load_progress_mgr.h"
#include "../_layout/session_class.h"
#include "../core/trivial_tu117_methods.h"

// GLOBAL: GAMEMD 0x8A00A4 / 0x8A00A8 -- current screen width and height.
extern int DAT_008A00A4;
extern int DAT_008A00A8;
// GLOBAL: GAMEMD 0x7F5BE0 / 0x7F5BE4 / 0x7F5BF0 -- reference sizes the layouts are written for.
extern int DAT_007F5BE0;
extern int DAT_007F5BE4;
extern int DAT_007F5BF0;
// GLOBAL: GAMEMD 0x88730C -- the object that closes the progress screen.
extern Arg1_00554350* DAT_0088730C;

// FUNCTION: GAMEMD 0x552AD0
// Clears every member.
LoadProgressMgr::LoadProgressMgr()
{
    unknown_04 = 0;
    unknown_08 = 0;
    unknown_3C = 0;
    unknown_40 = 0;
    unknown_44 = 0;
    unknown_48 = 0;
    unknown_4C = 0;
    unknown_50 = 0;
    unknown_51 = 0;
    unknown_52 = 0;
    unknown_54 = 0;
    unknown_58 = 0;
    unknown_5C = 0;
    unknown_60 = 0;
}

// FUNCTION: GAMEMD 0x552C90
// Vertical position for the progress bar, 0x50 lower unless the screen is the reference size;
// -1 when no progress screen is shown.
int LoadProgressMgr::FUN_00552C90()
{
    int y = -1;
    if (Session_00A8B238.GameMode)
        y = (DAT_008A00A4 != DAT_007F5BE0 ? 0x50 : 0) + 0x146;
    return y;
}

// A 2D point and a rectangle, as these layout helpers fill them in.
struct Point_00554100 { int X; int Y; };
struct Rect_00554150 { int X; int Y; int Width; int Height; };

// FUNCTION: GAMEMD 0x554100
// Centres a point offset on screens larger than the reference size.
void __fastcall FUN_00554100(Point_00554100* p)
{
    int sw = DAT_008A00A4;
    int rw = DAT_007F5BE4;
    if (sw >= rw) {
        int dy = (DAT_008A00A8 - DAT_007F5BF0) / 2;
        int dx = (sw - rw) / 2;
        p->X += dx;
        p->Y += dy;
    }
}

// FUNCTION: GAMEMD 0x554150
// Fills the progress bar rectangle (200 by 20), placed for the reference size or the larger
// layout and centred on bigger screens.
Rect_00554150* __fastcall FUN_00554150(Rect_00554150* r)
{
    int sw = DAT_008A00A4;
    int x;
    int y;
    if (sw == DAT_007F5BE0) {
        x = 0x10;
        y = 0xEB;
    } else {
        x = 0x14;
        y = 0x12C;
    }
    int rw = DAT_007F5BE4;
    Rect_00554150 q;
    q.Width = 0xC8;
    q.Height = 0x14;
    if (sw >= rw) {
        x += (sw - rw) / 2;
        y += (DAT_008A00A8 - DAT_007F5BF0) / 2;
    }
    q.X = x;
    q.Y = y;
    *r = q;
    return r;
}

// FUNCTION: GAMEMD 0x554400
// Handles notice 0x11AE by closing the progress screen; reports whether it was handled.
bool LoadProgressMgr::Notice(int id, int arg)
{
    if (id == 0x11AE) {
        Arg1_00554350* closer = DAT_0088730C;
        if (unknown_60)
            closer->vf_1(unknown_60, 0, 1);
        return true;
    }
    return false;
}
