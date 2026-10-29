// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//   Dialog control-id lookups from GDlgSupp.cpp (original translation unit,
//   code range 0x4e3130-0x4e62cf): an index 0..7 selects one of eight
//   control ids, any other index gives -1.

#include <windows.h>
#include "../renderer/pcx_get_surface_methods.h"

// A handler object reached through a global; only virtual slot 10 is called.
struct Handler_004E4170
{
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual void vf_7();
    virtual void vf_8();
    virtual void vf_9();
    virtual int vf_10();
};
// GLOBAL: GAMEMD 0xA8B23C
extern Handler_004E4170* DAT_00A8B23C;

// FUNCTION: GAMEMD 0x4E4170
// Combo box item-data read (the current selection when the index is -1). A
// value outside -3..9 is handed to the handler object, or -2 without one.
int __fastcall FUN_004E4170(HWND dialog, int controlId, int index)
{
    if (index == -1)
        index = (int)SendDlgItemMessageA(dialog, controlId, CB_GETCURSEL, 0, 0);
    int data = (int)SendDlgItemMessageA(dialog, controlId, CB_GETITEMDATA, index, 0);
    if (data < -3 || data > 9) {
        if (DAT_00A8B23C) {
            return DAT_00A8B23C->vf_10();
        }
        return -2;
    }
    return data;
}

// FUNCTION: GAMEMD 0x4E3320
int __fastcall FUN_004E3320(int index)
{
    if (index == 0) return 0x6DA;
    if (index == 1) return 0x6DB;
    if (index == 2) return 0x6DC;
    if (index == 3) return 0x6DD;
    if (index == 4) return 0x6DE;
    if (index == 5) return 0x6DF;
    if (index == 6) return 0x6E0;
    return index == 7 ? 0x6E1 : -1;
}

// GLOBAL: GAMEMD 0xAC4848 -- the cache of loaded PCX pictures.
extern PCX DAT_00AC4848;
// GLOBAL: GAMEMD 0x844B18 -- the three ping indicator picture names (green, yellow, red).
extern const char* DAT_00844B18[3];

// FUNCTION: GAMEMD 0x4E33F0
// The ping indicator picture for a quality level (0 good, 1 fair, 2 poor), or 0 for any other level.
void* __fastcall FUN_004E33F0(int level)
{
    void* picture = 0;
    if (level == 0)
        return DAT_00AC4848.GetSurface(DAT_00844B18[0], 0);
    if (level == 1)
        return DAT_00AC4848.GetSurface(DAT_00844B18[1], 0);
    if (level == 2)
        picture = DAT_00AC4848.GetSurface(DAT_00844B18[2], 0);
    return picture;
}

// FUNCTION: GAMEMD 0x4E3440
int __fastcall FUN_004E3440(int index)
{
    if (index == 0) return 0x754;
    if (index == 1) return 0x755;
    if (index == 2) return 0x756;
    if (index == 3) return 0x757;
    if (index == 4) return 0x758;
    if (index == 5) return 0x759;
    if (index == 6) return 0x75A;
    return index == 7 ? 0x75B : -1;
}

// FUNCTION: GAMEMD 0x4E37D0
int __fastcall FUN_004E37D0(int index)
{
    if (index == 0) return 0x6A1;
    if (index == 1) return 0x510;
    if (index == 2) return 0x513;
    if (index == 3) return 0x51E;
    if (index == 4) return 0x514;
    if (index == 5) return 0x51F;
    if (index == 6) return 0x520;
    return index == 7 ? 0x521 : -1;
}

// FUNCTION: GAMEMD 0x4E41D0
int __fastcall FUN_004E41D0(int index)
{
    if (index == 0) return 0x6A2;
    if (index == 1) return 0x522;
    if (index == 2) return 0x523;
    if (index == 3) return 0x524;
    if (index == 4) return 0x525;
    if (index == 5) return 0x526;
    if (index == 6) return 0x527;
    return index == 7 ? 0x528 : -1;
}

// FUNCTION: GAMEMD 0x4E4E60
int __fastcall FUN_004E4E60(int index)
{
    if (index == 0) return 0x6A3;
    if (index == 1) return 0x6A4;
    if (index == 2) return 0x6A5;
    if (index == 3) return 0x6A6;
    if (index == 4) return 0x6A7;
    if (index == 5) return 0x6A8;
    if (index == 6) return 0x6AA;
    return index == 7 ? 0x6AB : -1;
}

// FUNCTION: GAMEMD 0x4E5940
int __fastcall FUN_004E5940(int index)
{
    if (index == 0) return 0x76D;
    if (index == 1) return 0x76E;
    if (index == 2) return 0x76F;
    if (index == 3) return 0x770;
    if (index == 4) return 0x771;
    if (index == 5) return 0x772;
    if (index == 6) return 0x773;
    return index == 7 ? 0x774 : -1;
}

// FUNCTION: GAMEMD 0x4E3830
int __fastcall FUN_004E3830(int id)
{
    if (id == 0x6A1) return 0;
    if (id == 0x510) return 1;
    if (id == 0x513) return 2;
    if (id == 0x51E) return 3;
    if (id == 0x514) return 4;
    if (id == 0x51F) return 5;
    if (id == 0x520) return 6;
    return id == 0x521 ? 7 : -1;
}

// FUNCTION: GAMEMD 0x4E4230
int __fastcall FUN_004E4230(int id)
{
    if (id == 0x6A2) return 0;
    if (id == 0x522) return 1;
    if (id == 0x523) return 2;
    if (id == 0x524) return 3;
    if (id == 0x525) return 4;
    if (id == 0x526) return 5;
    if (id == 0x527) return 6;
    return id == 0x528 ? 7 : -1;
}

// FUNCTION: GAMEMD 0x4E4EC0
int __fastcall FUN_004E4EC0(int id)
{
    if (id == 0x6A3) return 0;
    if (id == 0x6A4) return 1;
    if (id == 0x6A5) return 2;
    if (id == 0x6A6) return 3;
    if (id == 0x6A7) return 4;
    if (id == 0x6A8) return 5;
    if (id == 0x6AA) return 6;
    return id == 0x6AB ? 7 : -1;
}

// FUNCTION: GAMEMD 0x4E59A0
int __fastcall FUN_004E59A0(int id)
{
    if (id == 0x76D) return 0;
    if (id == 0x76E) return 1;
    if (id == 0x76F) return 2;
    if (id == 0x770) return 3;
    if (id == 0x771) return 4;
    if (id == 0x772) return 5;
    if (id == 0x773) return 6;
    return id == 0x774 ? 7 : -1;
}

#include "../_layout/rec12_008b3f38.h"
extern Rec12_008B3F38 DAT_008B3F38[];

// FUNCTION: GAMEMD 0x4E4FC0
// Mark the first `count` records used (-1) and every later one of the nine
// unavailable (-2).
void __fastcall FUN_004E4FC0(int count)
{
    int i;
    for (i = 0; i < count; i++) {
        DAT_008B3F38[i].key = -1;
    }
    for (i = count; i < 9; i++) {
        DAT_008B3F38[i].key = -2;
    }
}

#include "../_layout/rec12_008b4040.h"
extern Rec12_008B4040 DAT_008B4040[];

// FUNCTION: GAMEMD 0x4E44E0
// Position of the record whose key is the index of this control id, or -1.
int __fastcall FUN_004E44E0(int id)
{
    int index;
    if (id == 0x6A2) index = 0;
    else if (id == 0x522) index = 1;
    else if (id == 0x523) index = 2;
    else if (id == 0x524) index = 3;
    else if (id == 0x525) index = 4;
    else if (id == 0x526) index = 5;
    else if (id == 0x527) index = 6;
    else index = id == 0x528 ? 7 : -1;
    for (int i = 0; i < 9; i++) {
        if (DAT_008B4040[i].key == index) return i;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x4E5000
// Position of the record whose key is the index of this control id, or -1.
int __fastcall FUN_004E5000(int id)
{
    int index;
    if (id == 0x6A3) index = 0;
    else if (id == 0x6A4) index = 1;
    else if (id == 0x6A5) index = 2;
    else if (id == 0x6A6) index = 3;
    else if (id == 0x6A7) index = 4;
    else if (id == 0x6A8) index = 5;
    else if (id == 0x6AA) index = 6;
    else index = id == 0x6AB ? 7 : -1;
    for (int i = 0; i < 9; i++) {
        if (DAT_008B3F38[i].key == index) return i;
    }
    return -1;
}
