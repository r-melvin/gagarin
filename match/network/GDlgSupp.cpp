// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
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

#include <windows.h>
#include "../core/mathtbl_init_shapes.h"

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
#pragma intrinsic(strlen)

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
#pragma intrinsic(strcpy)
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

// FUNCTION: GAMEMD 0x004E4580
bool FUN_004E4580(int index)
{
    return DAT_008B4040[index].key != -1;
}

// FUNCTION: GAMEMD 0x004E4E20
int FUN_004E4E20(HWND dialog, int controlId, int index)
{
    if (index == -1)
        index = (int)SendDlgItemMessageA(dialog, controlId, CB_GETCURSEL, 0, 0);
    return (int)SendDlgItemMessageA(dialog, controlId, CB_GETITEMDATA, index, 0);
}

// FUNCTION: GAMEMD 0x4E4F30
// Calls other functions.
void __cdecl FUN_004E4F30()
{
    FUN_00734E60(DAT_00822B90, 0, DAT_008229C0, 0x2EB);
}

// FUNCTION: GAMEMD 0x004E50A0
bool FUN_004E50A0(int index)
{
    return DAT_008B3F38[index].key != -1;
}

// FUNCTION: GAMEMD 0x004E5900
int FUN_004E5900(HWND dialog, int controlId, int index)
{
    if (index == -1)
        index = (int)SendDlgItemMessageA(dialog, controlId, CB_GETCURSEL, 0, 0);
    return (int)SendDlgItemMessageA(dialog, controlId, CB_GETITEMDATA, index, 0);
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
