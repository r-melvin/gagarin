// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit GDlgSupp.cpp. The name is the source-file string at 0x8229c0
//   in retail gamemd.exe v1.001, passed by the assert at 0x4e38aa inside this object's
//   code range (0x4e3130-0x4e62cf). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Combo box item-data read, repeated unchanged at three addresses: when the
// index is -1 the current selection (0x147) is queried first, then the item
// data (0x150) at that index is returned. Both messages go through the
// SendDlgItemMessageA import (0x7E1490).
//
// Leaf bodies that repeat byte for byte at several addresses and touch only
// globals: store of the ECX argument, indexed table reads, constant stores,
// and a two-value test. Each address binds to its own global (named by
// retail address, typed only as far as the instructions show) and was
// verified separately. Record structs name only the fields the bodies read.
//
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names.
//
// Small leaves (64 bytes or less) between 0x470000 and 0x500000 that other
// translation units already declared as callees but nothing defined.

#include "../economy/netshare_win.h"
#include "../_layout/session_class.h"
#include "../economy/netshare_slot_nodes.h"
#include "../core/mathtbl_init_shapes.h"
#include <windows.h>
#include "../renderer/pcx_get_surface_methods.h"
#include "../_layout/rec12_008b3f38.h"
#include "../_layout/rec12_008b4040.h"

extern int DAT_00816108;
#include "../_layout/rec12_008b4040.h"
extern Rec12_008B4040 DAT_008B4040[];
#include "../_layout/rec12_008b3f38.h"
extern Rec12_008B3F38 DAT_008B3F38[];
#include "../_layout/rec12_008b3fc8.h"
extern Rec12_008B3FC8 DAT_008B3FC8[];
extern unsigned char DAT_00A9FAB4;
extern unsigned char DAT_00ABCD58;
extern int DAT_00ABED0C;
extern int DAT_00ABF168[];
#include "../_layout/rec28_0082d028.h"
extern Rec28_0082D028 DAT_0082D028[];
extern int DAT_00AC4B80;
extern int DAT_00AC4C90;
extern int DAT_00AC4C38;
extern int DAT_00AC4BF0;
extern int DAT_007F0248[];
#include "../_layout/rec16_007f0998.h"
extern Rec16_007F0998 DAT_007F0998[];
extern int DAT_00B0CB78[];
extern int DAT_008449F8[];
extern unsigned char DAT_00B0FE58;
extern unsigned char DAT_008464AC;
extern int DAT_00B780A0;

#include "../core/trivial_tu090_methods.h"

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);
extern "C" size_t __cdecl strlen(const char* s);

// GLOBAL: GAMEMD 0x00A8ED84
extern "C" int DAT_00A8ED84;
// GLOBAL: GAMEMD 0x00AA0738
extern "C" int DAT_00AA0738;
// GLOBAL: GAMEMD 0x007E1B60 (five string pointers)
extern "C" const char* const DAT_007E1B60[5];
// GLOBAL: GAMEMD 0x007E523C (nineteen string pointers)
extern "C" const char* const DAT_007E523C[19];
// GLOBAL: GAMEMD 0x0081DA28 (twelve string pointers)
extern "C" const char* const DAT_0081DA28[12];
// GLOBAL: GAMEMD 0x00817474
extern "C" const char DAT_00817474[];

// 0x4CAC40: x87 helper taking one double and returning one (callee only).
double __cdecl FUN_004CAC40(double value);
// 0x5117D0: name -> index, -1 when absent (callee only).
int FUN_005117D0(const char* name);

// ---------------------------------------------------------------------------

#include "../_layout/obj_00483460.h"

#include "../_layout/obj_00485060.h"

#include "../_layout/obj_004870b0.h"

#include "../_layout/pair_00487f20.h"

#include "../_layout/obj_0048ba80.h"

#include "../_layout/obj_004a1d30.h"

#include "../_layout/obj_004a50f0.h"

#include "../_layout/pair_004c1b50.h"

#include "../_layout/obj_004c91c0.h"

#include "../_layout/obj_004ca160.h"

// GLOBAL: GAMEMD 0x0085D0A4 (4096-entry float table)
extern "C" const float DAT_0085D0A4[4096];

#include "../_layout/obj_004e1100.h"

struct Obj_004D2790;

struct Vtbl_004D2790;

#include "../_layout/obj_004d2790.h"


#include "../_layout/vtbl_004d2790.h"

#include "../_layout/record_004d2790.h"

// 0x7C5F3D and 0x7C5FFF: runtime-library helpers with no binary name; the
// first returns a byte (callees only).
extern "C" char __cdecl FUN_007C5F3D();
extern "C" void __cdecl FUN_007C5FFF();
extern "C" char* __cdecl strncpy(char* dst, const char* src, size_t count);

// GLOBAL: GAMEMD 0x0084E863
extern "C" signed char DAT_0084E863;
// GLOBAL: GAMEMD 0x0084E865
extern "C" const char DAT_0084E865[];

extern "C" char* __cdecl strcpy(char* dst, const char* src);
extern "C" char* __cdecl _strupr(char* text);

#include "../_layout/text_004f4cb0.h"

#include "../_layout/obj_004f4c20.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E94E0
extern const double DAT_007E94E0;
// GLOBAL: GAMEMD 0x8B3FA8
extern double DAT_008B3FA8;

// SYNTHETIC: GAMEMD 0x004E3160
// dynamic initializer for DAT_008B40B8
// GLOBAL: GAMEMD 0x008B40B8
double DAT_008B40B8 = DAT_008B3FA8 / DAT_007E94E0;

// SYNTHETIC: GAMEMD 0x004E3180
// dynamic initializer for DAT_008B40A0
// GLOBAL: GAMEMD 0x008B40A0
double DAT_008B40A0 = 1.0 / DAT_008B40B8;

GG_STATIC_ASSERT(sizeof(DAT_008B40B8) == 8);
GG_STATIC_ASSERT(sizeof(DAT_008B40A0) == 8);

// SYNTHETIC: GAMEMD 0x004E3300
// GLOBAL: GAMEMD 0x008B40A8
MathTblCoord DAT_008B40A8;

// STRING: GAMEMD 0x8229A8..0x8228AC -- the twelve side captions, "STT:PlayerSide...".
extern char DAT_008229A8[];
extern char DAT_00822990[];
extern char DAT_00822978[];
extern char DAT_00822964[];
extern char DAT_0082294C[];
extern char DAT_00822934[];
extern char DAT_0082291C[];
extern char DAT_00822908[];
extern char DAT_008228F4[];
extern char DAT_008228E0[];
extern char DAT_008228C8[];
extern char DAT_008228AC[];

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

// FUNCTION: GAMEMD 0x4E38A0
// Localised caption of a side index: -2 random, -3 observer, 0..9 the countries.
const wchar_t* __fastcall FUN_004E38A0(int index)
{
    if (index == -2)
        return FUN_00734E60(DAT_008229A8, 0, DAT_008229C0, 0xED);
    if (index == -3)
        return FUN_00734E60(DAT_00822990, 0, DAT_008229C0, 0xEF);
    if (index == 0)
        return FUN_00734E60(DAT_00822978, 0, DAT_008229C0, 0xF1);
    if (index == 1)
        return FUN_00734E60(DAT_00822964, 0, DAT_008229C0, 0xF3);
    if (index == 2)
        return FUN_00734E60(DAT_0082294C, 0, DAT_008229C0, 0xF5);
    if (index == 3)
        return FUN_00734E60(DAT_00822934, 0, DAT_008229C0, 0xF7);
    if (index == 4)
        return FUN_00734E60(DAT_0082291C, 0, DAT_008229C0, 0xF9);
    if (index == 5)
        return FUN_00734E60(DAT_00822908, 0, DAT_008229C0, 0xFB);
    if (index == 6)
        return FUN_00734E60(DAT_008228F4, 0, DAT_008229C0, 0xFD);
    if (index == 7)
        return FUN_00734E60(DAT_008228E0, 0, DAT_008229C0, 0xFF);
    if (index == 8)
        return FUN_00734E60(DAT_008228C8, 0, DAT_008229C0, 0x101);
    if (index == 9)
        return FUN_00734E60(DAT_008228AC, 0, DAT_008229C0, 0x103);
    return 0;
}

// STRING: GAMEMD 0x822AC4..0x8229FC -- the ten colour captions, "STT:PlayerColor...".
extern char DAT_00822AC4[];
extern char DAT_00822AB0[];
extern char DAT_00822A9C[];
extern char DAT_00822A88[];
extern char DAT_00822A70[];
extern char DAT_00822A58[];
extern char DAT_00822A40[];
extern char DAT_00822A28[];
extern char DAT_00822A14[];
extern char DAT_008229FC[];

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

// FUNCTION: GAMEMD 0x4E42A0
// Localised caption of a colour index: -2 random, 0..7 the colours, 8 observer.
const wchar_t* __fastcall FUN_004E42A0(int index)
{
    if (index == -2)
        return FUN_00734E60(DAT_00822AC4, 0, DAT_008229C0, 0x1C1);
    if (index == 0)
        return FUN_00734E60(DAT_00822AB0, 0, DAT_008229C0, 0x1C3);
    if (index == 1)
        return FUN_00734E60(DAT_00822A9C, 0, DAT_008229C0, 0x1C5);
    if (index == 2)
        return FUN_00734E60(DAT_00822A88, 0, DAT_008229C0, 0x1C7);
    if (index == 3)
        return FUN_00734E60(DAT_00822A70, 0, DAT_008229C0, 0x1C9);
    if (index == 4)
        return FUN_00734E60(DAT_00822A58, 0, DAT_008229C0, 0x1CB);
    if (index == 5)
        return FUN_00734E60(DAT_00822A40, 0, DAT_008229C0, 0x1CD);
    if (index == 6)
        return FUN_00734E60(DAT_00822A28, 0, DAT_008229C0, 0x1CF);
    if (index == 7)
        return FUN_00734E60(DAT_00822A14, 0, DAT_008229C0, 0x1D1);
    if (index == 8)
        return FUN_00734E60(DAT_008229FC, 0, DAT_008229C0, 0x1D3);
    return 0;
}

#include "../_layout/rec12_008b4038.h"
extern Rec12_008B4038 DAT_008B4038[];
// STRING: GAMEMD 0x822B68..0x822ADC -- the nine colour abbreviations, "GUI:...Abbrev".
extern char DAT_00822B68[];
extern char DAT_00822B58[];
extern char DAT_00822B48[];
extern char DAT_00822B38[];
extern char DAT_00822B24[];
extern char DAT_00822B10[];
extern char DAT_00822AFC[];
extern char DAT_00822AEC[];
extern char DAT_00822ADC[];
// GLOBAL: GAMEMD 0x8316A8 -- the nine colour values.
extern int DAT_008316A8[9];

// FUNCTION: GAMEMD 0x4E43C0
// Fetch the nine colour abbreviations, then give each record its colour value and mark it used (-1).
void __fastcall FUN_004E43C0()
{
    DAT_008B4038[0].name = FUN_00734E60(DAT_00822B68, 0, DAT_008229C0, 0x1DB);
    DAT_008B4038[1].name = FUN_00734E60(DAT_00822B58, 0, DAT_008229C0, 0x1DC);
    DAT_008B4038[2].name = FUN_00734E60(DAT_00822B48, 0, DAT_008229C0, 0x1DD);
    DAT_008B4038[3].name = FUN_00734E60(DAT_00822B38, 0, DAT_008229C0, 0x1DE);
    DAT_008B4038[4].name = FUN_00734E60(DAT_00822B24, 0, DAT_008229C0, 0x1DF);
    DAT_008B4038[5].name = FUN_00734E60(DAT_00822B10, 0, DAT_008229C0, 0x1E0);
    DAT_008B4038[6].name = FUN_00734E60(DAT_00822AFC, 0, DAT_008229C0, 0x1E1);
    DAT_008B4038[7].name = FUN_00734E60(DAT_00822AEC, 0, DAT_008229C0, 0x1E2);
    DAT_008B4038[8].name = FUN_00734E60(DAT_00822ADC, 0, DAT_008229C0, 0x1E3);
    for (int i = 0; i < 9; i++) {
        DAT_008B4038[i].colour = DAT_008316A8[i];
        DAT_008B4038[i].key = -1;
    }
}

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

// FUNCTION: GAMEMD 0x004E4580
bool FUN_004E4580(int index)
{
    return DAT_008B4040[index].key != -1;
}

// GLOBAL: GAMEMD 0xA8DA90 / 0xAC11B4 are NodeNameType slots (netshare_slot_nodes.h).

// FUNCTION: GAMEMD 0x4E48E0
// Refresh the house control of lobby slot `index` (ECX is the dialog, passed on unchanged).
void __fastcall FUN_004E48E0(HWND dialog, int index)
{
    int state = Session_00A8B238.unknown_17C;
    if (Session_00A8B238.unknown_180 == -2)
        state = -2;
    int control;
    if (index == 0) control = 0x6A2;
    else if (index == 1) control = 0x522;
    else if (index == 2) control = 0x523;
    else if (index == 3) control = 0x524;
    else if (index == 4) control = 0x525;
    else if (index == 5) control = 0x526;
    else if (index == 6) control = 0x527;
    else control = index == 7 ? 0x528 : -1;
    if (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) {
        if (Slots[index] == ObserverNode && Slots[index]->unknown_6B == -1)
            state = 8;
    }
    FUN_004E49A0(dialog, control, state);
}

// FUNCTION: GAMEMD 0x004E4E20
int FUN_004E4E20(HWND dialog, int controlId, int index)
{
    if (index == -1)
        index = (int)SendDlgItemMessageA(dialog, controlId, CB_GETCURSEL, 0, 0);
    return (int)SendDlgItemMessageA(dialog, controlId, CB_GETITEMDATA, index, 0);
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

// FUNCTION: GAMEMD 0x4E4F30
// Calls other functions.
void __cdecl FUN_004E4F30()
{
    FUN_00734E60(DAT_00822B90, 0, DAT_008229C0, 0x2EB);
}

#include "../_layout/rec12_008b3f30.h"
extern Rec12_008B3F30 DAT_008B3F30[];
#include "../_layout/rec12_008b3fc0.h"
extern Rec12_008B3FC0 DAT_008B3FC0[];
// STRING: GAMEMD 0x822BA4..0x822BC4 -- the wide captions L"0".."8"; 0x822BC8..0x822BEC "LETTER_x".
extern wchar_t DAT_00822BA4[];
extern wchar_t DAT_00822BA8[];
extern wchar_t DAT_00822BAC[];
extern wchar_t DAT_00822BB0[];
extern wchar_t DAT_00822BB4[];
extern wchar_t DAT_00822BB8[];
extern wchar_t DAT_00822BBC[];
extern wchar_t DAT_00822BC0[];
extern wchar_t DAT_00822BC4[];
extern char DAT_00822BC8[];
extern char DAT_00822BD4[];
extern char DAT_00822BE0[];
extern char DAT_00822BEC[];

// FUNCTION: GAMEMD 0x4E4F50
// Name the nine start-position records "1".."8","0" and mark them used (-1).
void FUN_004E4F50()
{
    DAT_008B3F30[0].name = DAT_00822BC4;
    DAT_008B3F30[1].name = DAT_00822BC0;
    DAT_008B3F30[2].name = DAT_00822BBC;
    DAT_008B3F30[3].name = DAT_00822BB8;
    DAT_008B3F30[4].name = DAT_00822BB4;
    DAT_008B3F30[5].name = DAT_00822BB0;
    DAT_008B3F30[6].name = DAT_00822BAC;
    DAT_008B3F30[7].name = DAT_00822BA8;
    DAT_008B3F30[8].name = DAT_00822BA4;
    for (int i = 0; i < 9; i++)
        DAT_008B3F30[i].key = -1;
}

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

// FUNCTION: GAMEMD 0x004E50A0
bool FUN_004E50A0(int index)
{
    return DAT_008B3F38[index].key != -1;
}

// FUNCTION: GAMEMD 0x4E53D0
// Refresh the colour control of lobby slot `index` (ECX is the dialog, passed on unchanged).
void __fastcall FUN_004E53D0(HWND dialog, int index)
{
    int state = -2;
    int control;
    if (index == 0) control = 0x6A3;
    else if (index == 1) control = 0x6A4;
    else if (index == 2) control = 0x6A5;
    else if (index == 3) control = 0x6A6;
    else if (index == 4) control = 0x6A7;
    else if (index == 5) control = 0x6A8;
    else if (index == 6) control = 0x6AA;
    else control = index == 7 ? 0x6AB : -1;
    if (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) {
        if (Slots[index] == ObserverNode && Slots[index]->unknown_6B == -1)
            state = 8;
    }
    FUN_004E5480(dialog, control, state);
}

// FUNCTION: GAMEMD 0x004E5900
int FUN_004E5900(HWND dialog, int controlId, int index)
{
    if (index == -1)
        index = (int)SendDlgItemMessageA(dialog, controlId, CB_GETCURSEL, 0, 0);
    return (int)SendDlgItemMessageA(dialog, controlId, CB_GETITEMDATA, index, 0);
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

// FUNCTION: GAMEMD 0x4E5AC0
// Fetch the captions of the four letter choices and name the fifth "0".
void FUN_004E5AC0()
{
    DAT_008B3FC0[0].name = FUN_00734E60(DAT_00822BEC, 0, DAT_008229C0, 0x437);
    DAT_008B3FC0[1].name = FUN_00734E60(DAT_00822BE0, 0, DAT_008229C0, 0x438);
    DAT_008B3FC0[2].name = FUN_00734E60(DAT_00822BD4, 0, DAT_008229C0, 0x439);
    DAT_008B3FC0[3].name = FUN_00734E60(DAT_00822BC8, 0, DAT_008229C0, 0x43A);
    DAT_008B3FC0[4].name = DAT_00822BA4;
}

// FUNCTION: GAMEMD 0x004E5B40
bool FUN_004E5B40(int index)
{
    return DAT_008B3FC8[index].key != -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x004E6030
int FUN_004E6030(HWND dialog, int controlId, int index)
{
    if (index == -1)
        index = (int)SendDlgItemMessageA(dialog, controlId, CB_GETCURSEL, 0, 0);
    return (int)SendDlgItemMessageA(dialog, controlId, CB_GETITEMDATA, index, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4E6140
// Empty function.
void __cdecl FUN_004E6140()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x004E6150
// Report the 0x7C5F3D byte and the signed byte at 0x84E863, and copy up to
// `count` characters of the text at 0x84E865 when a buffer is given.
void FUN_004E6150(int* value, char* code, char* buffer, int count)
{
    *code = FUN_007C5F3D();
    FUN_007C5FFF();
    *value = DAT_0084E863;
    if (buffer != NULL) {
        strncpy(buffer, DAT_0084E865, count);
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E94E0
extern const double DAT_007E94E0 = 60.0;
// GLOBAL: GAMEMD 0xAC4848
PCX DAT_00AC4848;
// GLOBAL: GAMEMD 0x835C90
extern const char STR_00835C90[] = "pingr.pcx";
// GLOBAL: GAMEMD 0x835C9C
extern const char STR_00835C9C[] = "pingy.pcx";
// GLOBAL: GAMEMD 0x835CA8
extern const char STR_00835CA8[] = "pingg.pcx";
// GLOBAL: GAMEMD 0x844B18
extern const char* DAT_00844B18[3] = {STR_00835CA8, STR_00835C9C, STR_00835C90};
// END defined globals
