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

struct Quad_006C95E0
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;

    Quad_006C95E0();
};

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
void __fastcall FUN_006CFD20(int index, int value)
{
    DAT_00B0CB78[index] = value;
}

struct Rect_006CFDB0
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;
};

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
void __fastcall FUN_006CFDB0(int count)
{
    DAT_00B0CB54 = count;
    int value = DAT_00B0FC6C->unknown_0 - DAT_00B0FC68->unknown_8 * count;
    int limit = DAT_00B0FC60->unknown_8 + DAT_00B0FC60->unknown_0;
    DAT_00B0CC2C = value;
    if (value <= limit) {
        DAT_00B0CC2C = limit;
    }
}

struct Link_006EF5F0
{
    char Pad_00[0xF0];
    int unknown_F0;
    char Pad_F4[0x5D8 - 0xF4];
    Link_006EF5F0* unknown_5D8;
};
GG_STATIC_ASSERT(offsetof(Link_006EF5F0, unknown_F0) == 0xF0);
GG_STATIC_ASSERT(offsetof(Link_006EF5F0, unknown_5D8) == 0x5D8);

struct Obj_006EF5F0
{
    char Pad_00[0x54];
    Link_006EF5F0* unknown_54;

    void FUN_006EF5F0(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_006EF5F0, unknown_54) == 0x54);

// FUNCTION: GAMEMD 0x006EF5F0
// Store `value` at +0xF0 of every link of the chain at +0x54 (next at +0x5D8).
void Obj_006EF5F0::FUN_006EF5F0(int value)
{
    for (Link_006EF5F0* link = unknown_54; link != NULL; link = link->unknown_5D8) {
        link->unknown_F0 = value;
    }
}

struct Obj_00705D20
{
    char Pad_00[0x514];
    int unknown_514;
};
GG_STATIC_ASSERT(offsetof(Obj_00705D20, unknown_514) == 0x514);

// FUNCTION: GAMEMD 0x00705D20
int __fastcall FUN_00705D20(Obj_00705D20* self)
{
    return self->unknown_514;
}

// GLOBAL: GAMEMD 0x00843108
extern "C" char DAT_00843108;

// FUNCTION: GAMEMD 0x0070D180
void __fastcall FUN_0070D180(char value)
{
    DAT_00843108 = value;
}

// FUNCTION: GAMEMD 0x0070E240
// True when `slot` is non-null and holds a non-zero value.
int __stdcall FUN_0070E240(const int* slot)
{
    if (slot != NULL && *slot != 0) {
        return 1;
    }
    return 0;
}

struct Obj_00711EB0
{
    char Pad_00[0x610];
    int unknown_610;
};
GG_STATIC_ASSERT(offsetof(Obj_00711EB0, unknown_610) == 0x610);

// FUNCTION: GAMEMD 0x00711EB0
int __fastcall FUN_00711EB0(Obj_00711EB0* self)
{
    return self->unknown_610;
}

struct Obj_00717880
{
    char Pad_00[0x808];
    int unknown_808;
};
GG_STATIC_ASSERT(offsetof(Obj_00717880, unknown_808) == 0x808);

// FUNCTION: GAMEMD 0x00717880
int __fastcall FUN_00717880(Obj_00717880* self)
{
    return self->unknown_808 > 0;
}

struct Obj_00726910
{
    char Pad_00[0x2C];
    int unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Obj_00726910, unknown_2C) == 0x2C);

// FUNCTION: GAMEMD 0x00726910
int __fastcall FUN_00726910(Obj_00726910* self)
{
    return self->unknown_2C;
}

// GLOBAL: GAMEMD 0x00B0FE54
extern "C" int DAT_00B0FE54;
// GLOBAL: GAMEMD 0x00B0FE58
extern "C" char DAT_00B0FE58;

// FUNCTION: GAMEMD 0x00731D00
void __fastcall FUN_00731D00(int value)
{
    DAT_00B0FE54 = value;
    DAT_00B0FE58 = 0;
}

// GLOBAL: GAMEMD 0x008463B8 (eighteen string pointers)
extern "C" const char* const DAT_008463B8[18];

// FUNCTION: GAMEMD 0x0074FEF0
// Index of `name` in the eighteen-entry table at 0x8463B8, or -1.
int __fastcall FUN_0074FEF0(const char* name)
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
int __fastcall FUN_0074FF90(const float* value)
{
    if (*value >= 1.0f && *value < 2.0f) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x00750010
int __fastcall FUN_00750010(const float* value)
{
    if (!(*value < 2.0f)) {
        return 1;
    }
    return 0;
}

struct Item_00751040
{
    void FUN_004053E0();
};

struct Holder_00751040
{
    Item_00751040* FUN_00406130();
};

struct Node_00751040
{
    char Pad_00[0x0C];
    Holder_00751040 unknown_C;
    char Pad_0D[0x30 - 0x0D];
    int unknown_30;

    Node_00751040* FUN_004073E0();
};
GG_STATIC_ASSERT(offsetof(Node_00751040, unknown_30) == 0x30);

struct List_00751040
{
    Node_00751040* FUN_004073C0();
};

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

struct Named_00751590
{
    const char* FUN_00405170();
};

struct Entry_00751590
{
    Named_00751590* unknown_0;
};

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
const char* __fastcall FUN_00751590(int index)
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

struct Obj_00753510
{
    void FUN_00407FB0();
    void FUN_00408000();
};

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

struct Record_007559B0
{
    int unknown_0[12];
};

// GLOBAL: GAMEMD 0x00B45188 (48-byte records)
extern "C" Record_007559B0 DAT_00B45188[];

// FUNCTION: GAMEMD 0x007559B0
// Copy record `index` out; the destination arrives in ECX and is returned.
Record_007559B0* __fastcall FUN_007559B0(Record_007559B0* out, int index)
{
    *out = DAT_00B45188[index];
    return out;
}

// GLOBAL: GAMEMD 0x007E5210 (eleven string pointers)
extern "C" const char* const DAT_007E5210[11];

// FUNCTION: GAMEMD 0x00772A50
// Index of `name` in the eleven-entry table at 0x7E5210, or 0.
int __fastcall FUN_00772A50(const char* name)
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

struct Obj_00774950
{
    char Pad_00[0x5C];
    HANDLE unknown_5C;
};
GG_STATIC_ASSERT(offsetof(Obj_00774950, unknown_5C) == 0x5C);

// FUNCTION: GAMEMD 0x00774950
// Close the handle at +0x5C, if open, after logging the string at 0x8497A4.
void __fastcall FUN_00774950(Obj_00774950* self)
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
struct Flags_0077D940
{
    unsigned int unknown_0 : 8;
    unsigned int unknown_8 : 1;
};

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
    return DAT_00B76B30.unknown_8;
}
