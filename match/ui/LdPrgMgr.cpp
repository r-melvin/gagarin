// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit LdPrgMgr.cpp. The name is the source-file string at 0x829ac8
//   in retail gamemd.exe v1.001, passed by the assert at 0x552ebc inside this object's
//   code range (0x552850-0x55442f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.

#include "../core/trivial_tu117_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/load_progress_mgr.h"
#include "../_layout/session_class.h"

// GLOBAL: GAMEMD 0x7ECF50
extern const double DAT_007ECF50;
// GLOBAL: GAMEMD 0xABC960
extern double DAT_00ABC960;
// GLOBAL: GAMEMD 0xABC9A0
extern int DAT_00ABC9A0;
// GLOBAL: GAMEMD 0xABC9A4
extern int DAT_00ABC9A4;
// GLOBAL: GAMEMD 0xABC9A8
extern int DAT_00ABC9A8;

// dynamic initializer for DAT_00ABC9B0
// GLOBAL: GAMEMD 0x00ABC9B0
extern double DAT_00ABC9B0;

// dynamic initializer for DAT_00ABC998
// GLOBAL: GAMEMD 0x00ABC998
extern double DAT_00ABC998;

GG_STATIC_ASSERT(sizeof(DAT_00ABC9B0) == 8);
GG_STATIC_ASSERT(sizeof(DAT_00ABC998) == 8);


// GLOBAL: GAMEMD 0xABC9BC
extern int DAT_00ABC9BC;

// FUNCTION: GAMEMD 0x554370 (decl; reloc)
void FUN_00554370(int, int);
// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc)
void __cdecl FUN_007C8B3D(int);


// FUNCTION: GAMEMD 0x552AA0
void FUN_00552AA0(int a1, int a2);

// FUNCTION: GAMEMD 0x552AA0
// Branching.
void FUN_00552AA0(int a1, int a2)
{
    if (DAT_00ABC9BC != 0)
    {
        FUN_00554370(DAT_00ABC9BC, a2);
        FUN_007C8B3D(DAT_00ABC9BC);
        DAT_00ABC9BC = 0;
    }
    DAT_00ABC9BC = 0;
}

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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x554350
// Branching.
void Obj_00554350::FUN_00554350(Arg1_00554350* a1)
{
    if (unknown_60 != 0)
    {
        a1->vf_1(unknown_60, 0, 1);
    }
}

// An object released through its virtual destructor (slot 0, flag 1).
struct Deletable_00554370
{
    virtual ~Deletable_00554370() {}
};

// FUNCTION: GAMEMD 0x72B460 (decl; reloc)
void FUN_0072B460();
// FUNCTION: GAMEMD 0x72B870 (decl; reloc)
void FUN_0072B870();

// FUNCTION: GAMEMD 0x554370
// Release the three owned buffers, shut down the screen helpers and delete
// the objects the manager holds.
void LoadProgressMgr::FUN_00554370()
{
    if (unknown_50 && unknown_44) {
        delete (char*)unknown_44;
    }
    unknown_44 = 0;
    if (unknown_51 && unknown_48) {
        delete (char*)unknown_48;
    }
    unknown_48 = 0;
    if (unknown_52 && unknown_4C) {
        delete (char*)unknown_4C;
    }
    unknown_4C = 0;
    FUN_0072B460();
    FUN_0072B870();
    if (unknown_04) {
        delete (Deletable_00554370*)unknown_04;
        unknown_04 = 0;
    }
    if (unknown_08) {
        delete (Deletable_00554370*)unknown_08;
        unknown_08 = 0;
    }
    if (unknown_60) {
        delete (Deletable_00554370*)unknown_60;
    }
    unknown_60 = 0;
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

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xABC9BC
int DAT_00ABC9BC;
// GLOBAL: GAMEMD 0x7F5BE0
int DAT_007F5BE0 = 640;
// GLOBAL: GAMEMD 0x7F5BE4
int DAT_007F5BE4 = 800;
// GLOBAL: GAMEMD 0x7F5BF0
int DAT_007F5BF0 = 600;
// END defined globals
