// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu139_b_methods.h"
#include "runtime_misc_globals.h"
#include "coordinate_005bcb60.h"

// GLOBAL: GAMEMD 0xABF110
extern int DAT_00ABF110;
// GLOBAL: GAMEMD 0xABF128
extern int DAT_00ABF128;
// GLOBAL: GAMEMD 0xABF23C
extern int DAT_00ABF23C;
// GLOBAL: GAMEMD 0xABF244
extern int DAT_00ABF244;

extern "C" __declspec(dllimport) int __stdcall GetDC(int window);
extern "C" __declspec(dllimport) int __stdcall ReleaseDC(int window, int dc);
extern "C" __declspec(dllimport) int __stdcall SetBkMode(int dc, int mode);
extern "C" __declspec(dllimport) int __stdcall SetBkColor(int dc, int color);
extern "C" __declspec(dllimport) int __stdcall SetTextColor(int dc, int color);
extern "C" __declspec(dllimport) int __stdcall SelectObject(int dc, int object);
extern "C" __declspec(dllimport) int __stdcall TextOutA(int dc, int x, int y, const char* text, int length);

// FUNCTION: GAMEMD 0x5BC400
// Branching.
void __cdecl FUN_005BC400()
{
    DAT_00ABF239 = 0;
    if (DAT_00ABF240 != 0)
    {
        DAT_00ABF23A = 0;
        ShowWindow(DAT_00ABF240, 0);
    }
}

// FUNCTION: GAMEMD 0x5BCC40
// Stores several members; pops its stack arguments.
void Obj_005BCC40::FUN_005BCC40(int a1, int a2)
{
    unknown_271C = a1;
    unknown_2720 = a2;
}

// FUNCTION: GAMEMD 0x5BCC60
// Stores several members; pops its stack arguments.
void Obj_005BCC60::FUN_005BCC60(int a1, int a2, int a3, int a4)
{
    unknown_2724 = a1;
    unknown_2728 = a2;
    unknown_272C = a3;
    unknown_2730 = a4;
}

// FUNCTION: GAMEMD 0x5BCE10
// Scrolls the window one row up (dir > 0) or down (dir < 0), blanking the vacated row.
void Obj_005BCC40::FUN_005BCE10(int dir)
{
    if (DAT_00ABF23A) {
        int x = unknown_2724;
        int y = unknown_2728;
        int h = unknown_2730;
        int w = unknown_272C;
        if (dir > 0) {
            for (int i = x; i < x + w; i++) {
                for (int j = y; j < y + h - 1; j++) {
                    cells[i][j] = cells[i][j + 1];
                    attrs[i][j] = attrs[i][j + 1];
                }
                cells[i][y + h - 1] = ' ';
                attrs[i][y + h - 1] = 0;
            }
        } else if (dir < 0) {
            for (int i = x; i < x + w; i++) {
                for (int j = y + h - 1; j > y; j--) {
                    cells[i][j] = cells[i][j - 1];
                    attrs[i][j] = attrs[i][j - 1];
                }
                cells[i][y] = ' ';
                attrs[i][y] = 0;
            }
        }
        FUN_005BD490(0, 0, 80, 25);
    }
}

// FUNCTION: GAMEMD 0x5BCF90
// Scrolls the window one column left (dir > 0) or right (dir < 0), blanking the vacated column.
void Obj_005BCC40::FUN_005BCF90(int dir)
{
    if (DAT_00ABF23A) {
        int x = unknown_2724;
        int w = unknown_272C;
        int y = unknown_2728;
        int h = unknown_2730;
        if (dir > 0) {
            for (int j = y; j < y + h; j++) {
                for (int i = x; i < x + w - 1; i++) {
                    cells[i][j] = cells[i + 1][j];
                    attrs[i][j] = attrs[i + 1][j];
                }
                cells[x + w - 1][j] = ' ';
                attrs[x + w - 1][j] = 0;
            }
        } else if (dir < 0) {
            for (int j = y; j < y + h; j++) {
                for (int i = x + w - 1; i > x; i--) {
                    cells[i][j] = cells[i - 1][j];
                    attrs[i][j] = attrs[i - 1][j];
                }
                cells[x][j] = ' ';
                attrs[x][j] = 0;
            }
        }
        FUN_005BD490(0, 0, 80, 25);
    }
}

// FUNCTION: GAMEMD 0x5BD3D0
// Draws one cell, switching the device-context colours when its attribute changes.
void Obj_005BCC40::FUN_005BD3D0(int hdc, int x, int y)
{
    int attr = attrs[x][y];
    if (attr != unknown_2714) {
        if (attr == 1) {
            SetBkColor(hdc, DAT_00ABF110);
            SetTextColor(hdc, DAT_00ABF128);
        } else {
            SetBkColor(hdc, DAT_00ABF128);
            SetTextColor(hdc, DAT_00ABF110);
        }
        unknown_2714 = attr;
    }
    char ch = cells[x][y];
    Point_005BCB60 pt;
    pt.X = x * ABF1E0 + 10;
    pt.Y = y * (ABF1C8 + ABF1D8) + 10;
    TextOutA(hdc, pt.X, pt.Y, &ch, 1);
}

// FUNCTION: GAMEMD 0x5BD490
// Redraws a rectangle of cells when this is the active grid.
void Obj_005BCC40::FUN_005BD490(int x, int y, int w, int h)
{
    if (DAT_00ABF23A && (int)this == DAT_00ABF23C) {
        int hdc = GetDC(DAT_00ABF240);
        SetBkMode(hdc, 2);
        SetBkColor(hdc, DAT_00ABF128);
        SetTextColor(hdc, DAT_00ABF110);
        if (hdc != 0) {
            int old = SelectObject(hdc, DAT_00ABF244);
            for (int j = y; j < y + h; j++) {
                for (int i = x; i < x + w; i++) {
                    FUN_005BD3D0(hdc, i, j);
                }
            }
            SelectObject(hdc, old);
            ReleaseDC(DAT_00ABF240, hdc);
        }
    }
}

// BEGIN defined globals (define_globals.py)
// END defined globals
