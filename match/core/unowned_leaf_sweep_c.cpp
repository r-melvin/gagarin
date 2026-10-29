// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names. The imports are named
//   by the PE import table (CloseHandle 0x7E11E0; ImmAssociateContext through
//   its thunk at 0x7C8A1C).
//
// Small leaves (64 bytes or less) between 0x6B0000 and 0x7B0000 that other
// translation units already declared as callees but nothing defined.
#include <windows.h>
#include <imm.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// ---------------------------------------------------------------------------

#include "../_layout/quad_006c95e0.h"

// FUNCTION: GAMEMD 0x006C95E0
Quad_006C95E0::Quad_006C95E0()
{
    unknown_0 = 0;
    unknown_4 = 0;
    unknown_8 = 0;
    unknown_C = 0;
}

// GLOBAL: GAMEMD 0x00B0CB78
extern "C" int DAT_00B0CB78[];

// FUNCTION: GAMEMD 0x006CFD20
void FUN_006CFD20(int index, int value)
{
    DAT_00B0CB78[index] = value;
}

#include "../_layout/rect_006cfdb0.h"

// GLOBAL: GAMEMD 0x00B0FC60
extern "C" Rect_006CFDB0* DAT_00B0FC60;
// GLOBAL: GAMEMD 0x00B0FC68
extern "C" Rect_006CFDB0* DAT_00B0FC68;
// GLOBAL: GAMEMD 0x00B0FC6C
extern "C" Rect_006CFDB0* DAT_00B0FC6C;
// GLOBAL: GAMEMD 0x00B0CB54
extern "C" int DAT_00B0CB54;
// GLOBAL: GAMEMD 0x00B0CC2C
extern "C" int DAT_00B0CC2C;

// FUNCTION: GAMEMD 0x006CFDB0
// Record `count`, then set 0xB0CC2C to the 0xB0FC6C origin less `count` rows
// of the 0xB0FC68 size, no lower than the far edge of the 0xB0FC60 rect.
void FUN_006CFDB0(int count)
{
    DAT_00B0CB54 = count;
    int value = DAT_00B0FC6C->unknown_0 - DAT_00B0FC68->unknown_8 * count;
    int limit = DAT_00B0FC60->unknown_8 + DAT_00B0FC60->unknown_0;
    if (value > limit) {
        DAT_00B0CC2C = value;
    } else {
        DAT_00B0CC2C = limit;
    }
}

#include "../_layout/link_006ef5f0.h"

#include "../_layout/obj_006ef5f0.h"

// FUNCTION: GAMEMD 0x006EF5F0
// Store `value` at +0xF0 of every link of the chain at +0x54 (next at +0x5D8).
void Obj_006EF5F0::FUN_006EF5F0(int value)
{
    for (Link_006EF5F0* link = unknown_54; link != NULL; link = link->unknown_5D8) {
        link->unknown_F0 = value;
    }
}

#include "../_layout/obj_00705d20.h"


// GLOBAL: GAMEMD 0x00843108
extern "C" char DAT_00843108;


#include "../_layout/obj_00711eb0.h"

// FUNCTION: GAMEMD 0x00711EB0
int FUN_00711EB0(Obj_00711EB0* self)
{
    return self->unknown_610;
}

#include "../_layout/obj_00717880.h"

// FUNCTION: GAMEMD 0x00717880
int FUN_00717880(Obj_00717880* self)
{
    return self->unknown_808 > 0;
}

#include "../_layout/obj_00726910.h"

// FUNCTION: GAMEMD 0x00726910
int FUN_00726910(Obj_00726910* self)
{
    return self->unknown_2C;
}

// GLOBAL: GAMEMD 0x00B0FE54
extern "C" int DAT_00B0FE54;
// GLOBAL: GAMEMD 0x00B0FE58
extern "C" char DAT_00B0FE58;

// FUNCTION: GAMEMD 0x00731D00
void FUN_00731D00(int value)
{
    DAT_00B0FE54 = value;
    DAT_00B0FE58 = 0;
}

// GLOBAL: GAMEMD 0x008463B8 (eighteen string pointers)
extern "C" const char* const DAT_008463B8[18];

// FUNCTION: GAMEMD 0x0074FEF0
// Index of `name` in the eighteen-entry table at 0x8463B8, or -1.
int FUN_0074FEF0(const char* name)
{
    for (int i = 0; i < 18; i++) {
        if (_stricmp(DAT_008463B8[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x0074FF90
// Is the float in [1, 2).
int FUN_0074FF90(const float* value)
{
    if (*value >= 1.0f && *value < 2.0f) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x00750010
int FUN_00750010(const float* value)
{
    if (!(*value < 2.0f)) {
        return 1;
    }
    return 0;
}

#include "../_layout/item_00751040.h"

#include "../_layout/holder_00751040.h"

#include "../_layout/node_00751040.h"

#include "../_layout/list_00751040.h"

// GLOBAL: GAMEMD 0x00B1D320
extern "C" List_00751040 DAT_00B1D320;

// FUNCTION: GAMEMD 0x00751040
// Walk the list at 0xB1D320: bump each node's +0x30 and run 0x4053E0 on the
// item its +0x0C member yields.
void FUN_00751040()
{
    for (Node_00751040* node = DAT_00B1D320.FUN_004073C0(); node != NULL; node = node->FUN_004073E0()) {
        node->unknown_30++;
        Item_00751040* item = node->unknown_C.FUN_00406130();
        if (item != NULL) {
            item->FUN_004053E0();
        }
    }
}

#include "../_layout/named_00751590.h"

#include "../_layout/entry_00751590.h"

// GLOBAL: GAMEMD 0x00B1D37C
extern "C" Entry_00751590** DAT_00B1D37C;
// GLOBAL: GAMEMD 0x00B1D388
extern "C" int DAT_00B1D388;
// GLOBAL: GAMEMD 0x00846574
extern "C" const char DAT_00846574[];
// GLOBAL: GAMEMD 0x00817474
extern "C" const char DAT_00817474[];

// FUNCTION: GAMEMD 0x00751590
// Name of entry `index` of the vector at 0xB1D378, with fallbacks for an
// empty entry (0x846574) and an index out of range (0x817474).
const char* FUN_00751590(int index)
{
    if (index >= 0 && index < DAT_00B1D388) {
        Named_00751590* named = DAT_00B1D37C[index]->unknown_0;
        if (named != NULL) {
            return named->FUN_00405170();
        }
        return DAT_00846574;
    }
    return DAT_00817474;
}

#include "../_layout/obj_00753510.h"

// GLOBAL: GAMEMD 0x00B1D4D8
extern "C" Obj_00753510* DAT_00B1D4D8;
// GLOBAL: GAMEMD 0x00B1D4CC
extern "C" Obj_00753510* DAT_00B1D4CC;
// GLOBAL: GAMEMD 0x00B1D428
extern "C" int DAT_00B1D428;

// FUNCTION: GAMEMD 0x00753510
void FUN_00753510()
{
    if (DAT_00B1D4D8 != NULL) {
        DAT_00B1D4D8->FUN_00408000();
    }
}

// FUNCTION: GAMEMD 0x007535B0
int FUN_007535B0()
{
    if (DAT_00B1D4CC != NULL) {
        DAT_00B1D4CC->FUN_00407FB0();
    }
    return ++DAT_00B1D428;
}

// FUNCTION: GAMEMD 0x00753620
void FUN_00753620()
{
    if (DAT_00B1D4CC != NULL) {
        DAT_00B1D4CC->FUN_00408000();
    }
    if (DAT_00B1D428 != 0) {
        if (--DAT_00B1D428 < 0) {
            DAT_00B1D428 = 0;
        }
    }
}

#include "../movement/matrix3d_native_helpers.h"

// FUNCTION: GAMEMD 0x007559B0
// Native ECX is the hidden result, EDX is the full index; copy twelve dwords.
Matrix3D FUN_007559B0(int index)
{
    return DAT_00B45188[index];
}

// GLOBAL: GAMEMD 0x007E5210 (eleven string pointers)
extern "C" const char* const DAT_007E5210[11];

// FUNCTION: GAMEMD 0x00772A50
// Index of `name` in the eleven-entry table at 0x7E5210, or 0.
int FUN_00772A50(const char* name)
{
    if (name != NULL) {
        for (int i = 0; i < 11; i++) {
            if (_stricmp(DAT_007E5210[i], name) == 0) {
                return i;
            }
        }
    }
    return 0;
}

// GLOBAL: GAMEMD 0x008497A4
extern "C" const char DAT_008497A4[];

// 0x4068E0: cdecl text sink taking a format string (callee only).
void __cdecl FUN_004068E0(const char* format, ...);

#include "../_layout/obj_00774950.h"

// FUNCTION: GAMEMD 0x00774950
// Close the handle at +0x5C, if open, after logging the string at 0x8497A4.
void FUN_00774950(Obj_00774950* self)
{
    if (self->unknown_5C != INVALID_HANDLE_VALUE) {
        FUN_004068E0(DAT_008497A4);
        CloseHandle(self->unknown_5C);
        self->unknown_5C = INVALID_HANDLE_VALUE;
    }
}

// GLOBAL: GAMEMD 0x00B73550
extern "C" HWND DAT_00B73550;
// GLOBAL: GAMEMD 0x00B7355C
extern "C" HIMC DAT_00B7355C;

// FUNCTION: GAMEMD 0x00778180
void FUN_00778180()
{
    if (DAT_00B7355C != NULL) {
        ImmAssociateContext(DAT_00B73550, DAT_00B7355C);
    }
}

// FUNCTION: GAMEMD 0x007781A0
void FUN_007781A0()
{
    ImmAssociateContext(DAT_00B73550, NULL);
}

// GLOBAL: GAMEMD 0x00A8B238
extern "C" int DAT_00A8B238;
// GLOBAL: GAMEMD 0x00B76B24
extern "C" int DAT_00B76B24;
#include "../_layout/flags_0077d940.h"

// GLOBAL: GAMEMD 0x00B76B30
extern "C" Flags_0077D940 DAT_00B76B30;

// FUNCTION: GAMEMD 0x0077D940
bool FUN_0077D940()
{
    if (DAT_00A8B238 != 4) {
        return false;
    }
    if (DAT_00B76B24 == 0) {
        bool flag = DAT_00B76B30.unknown_8;
        if (!flag) {
            return false;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x0077D970
bool FUN_0077D970()
{
    if (DAT_00A8B238 != 4) {
        return false;
    }
    bool flag = DAT_00B76B30.unknown_8;
    return flag;
}
