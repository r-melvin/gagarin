// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names. The two imports are
//   named by the PE import table (GetAsyncKeyState 0x7E13E0, SendMessageA
//   0x7E14A4).
//
// Small leaves (64 bytes or less) between 0x500000 and 0x6B0000 that other
// translation units already declared as callees but nothing defined.
#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// A two-short cell value copied as one dword.
struct Cell_0050DEF0
{
    short X;
    short Y;

    Cell_0050DEF0() {}
    bool operator==(const Cell_0050DEF0& other) const
    {
        return X == other.X && Y == other.Y;
    }
};
GG_STATIC_ASSERT(sizeof(Cell_0050DEF0) == 4);

// GLOBAL: GAMEMD 0x008B40F8
extern "C" int DAT_008B40F8;
// GLOBAL: GAMEMD 0x00A8EF98
extern "C" Cell_0050DEF0 DAT_00A8EF98;
// GLOBAL: GAMEMD 0x00A9FAB0
extern "C" int DAT_00A9FAB0;
// GLOBAL: GAMEMD 0x00AA0444
extern "C" int DAT_00AA0444;
// GLOBAL: GAMEMD 0x00AA0168 (256 key-state words)
extern "C" short DAT_00AA0168[256];
// GLOBAL: GAMEMD 0x00B45B68
extern "C" int DAT_00B45B68;
// GLOBAL: GAMEMD 0x008B4130
extern "C" int DAT_008B4130;

// ---------------------------------------------------------------------------

struct Team_005095D0
{
    char Pad_00[0x24];
    int unknown_24;
    char Pad_28[4];
    void* unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Team_005095D0, unknown_2C) == 0x2C);

// GLOBAL: GAMEMD 0x008B40EC
extern "C" Team_005095D0** DAT_008B40EC;

struct Obj_005095D0
{
    int FUN_005095D0(int kind);
};


struct Obj_0050DA10
{
    char Pad_00[0x5490];
    Cell_0050DEF0 unknown_5490;
    Cell_0050DEF0 unknown_5494;
    char Pad_5498[0x54F0 - 0x5498];
    Cell_0050DEF0 unknown_54F0;
    Cell_0050DEF0 unknown_54F4;
    Cell_0050DEF0 unknown_54F8;
    int unknown_54FC;
    char Pad_5500[0x577C - 0x5500];
    int unknown_577C;

    void FUN_0050DA10();
    void FUN_0050DA50();
    int FUN_0050DA80() const;
    Cell_0050DEF0 FUN_0050DEF0() const;
    void FUN_0050DFF0();
};
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_5490) == 0x5490);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_54F0) == 0x54F0);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_54FC) == 0x54FC);
GG_STATIC_ASSERT(offsetof(Obj_0050DA10, unknown_577C) == 0x577C);


// FUNCTION: GAMEMD 0x0053EC90
// Live key state, or the recorded word for the key's low byte.
short __fastcall FUN_0053EC90(int key)
{
    if (DAT_00AA0444 == 0) {
        return GetAsyncKeyState(key);
    }
    return DAT_00AA0168[key & 0xFF];
}

struct Obj_0053ECB0
{
    unsigned char unknown_0[10];

    Obj_0053ECB0();
};

// FUNCTION: GAMEMD 0x0053ECB0
Obj_0053ECB0::Obj_0053ECB0()
{
    unknown_0[0] = 0xFF;
    unknown_0[1] = 0xFF;
    unknown_0[2] = 0xFF;
    unknown_0[3] = 0xFF;
    unknown_0[4] = 0xFF;
    unknown_0[5] = 0xFF;
    unknown_0[6] = 0xFF;
    unknown_0[7] = 0xFF;
    unknown_0[8] = 0xFF;
    unknown_0[9] = 0xFF;
}

struct Triple_0053EDA0
{
    short unknown_0;
    short unknown_2;
    short unknown_4;
};
GG_STATIC_ASSERT(sizeof(Triple_0053EDA0) == 6);

struct Obj_0053EDA0
{
    int unknown_0;
    Triple_0053EDA0 unknown_4;

    void FUN_0053EDA0(int* first, Triple_0053EDA0* rest) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0053EDA0, unknown_4) == 4);

// FUNCTION: GAMEMD 0x0053EDA0
void Obj_0053EDA0::FUN_0053EDA0(int* first, Triple_0053EDA0* rest) const
{
    *rest = unknown_4;
    *first = unknown_0;
}

struct Obj_005402B0
{
    void FUN_005402B0(int value);
};

struct Obj_00542FC0
{
    char Pad_00[0x48];
    Obj_005402B0* unknown_48;

    void FUN_00542FC0(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00542FC0, unknown_48) == 0x48);

// FUNCTION: GAMEMD 0x00542FC0
void Obj_00542FC0::FUN_00542FC0(int value)
{
    if (unknown_48 != NULL) {
        unknown_48->FUN_005402B0(value);
    }
}

struct Entry_005657A0
{
    char Pad_00[0x24];
    Cell_0050DEF0 unknown_24;
};

// GLOBAL: GAMEMD 0x00ABDC50
extern "C" Entry_005657A0 DAT_00ABDC50;

struct Obj_005657A0
{
    char Pad_00[0x13C];
    Entry_005657A0** unknown_13C;

    Entry_005657A0* FUN_005657A0(const Cell_0050DEF0& cell) const;
};
GG_STATIC_ASSERT(offsetof(Obj_005657A0, unknown_13C) == 0x13C);

// FUNCTION: GAMEMD 0x005657A0
// The entry for `cell` in the 512-wide table at +0x13C; out of range or empty
// gives the shared entry at 0xABDC50 with the cell stored into its +0x24.
Entry_005657A0* Obj_005657A0::FUN_005657A0(const Cell_0050DEF0& cell) const
{
    int index = (cell.Y << 9) + cell.X;
    if (index >= 0 && index < 0x40000) {
        Entry_005657A0* entry = unknown_13C[index];
        if (entry != NULL) {
            return entry;
        }
    }
    DAT_00ABDC50.unknown_24 = cell;
    return &DAT_00ABDC50;
}

// FUNCTION: GAMEMD 0x0056BC50
int __stdcall FUN_0056BC50(const Cell_0050DEF0* cell)
{
    return cell->X / 4 + (cell->Y / 4) * 130 + 0x83;
}

struct Obj_005B3700
{
    int unknown_0;
    char unknown_4;
    char unknown_5;
    char unknown_6;
    char unknown_7;
    char unknown_8;
    char unknown_9;
    char Pad_0A[6];
    double unknown_10;
    double unknown_18;

    Obj_005B3700();
};
GG_STATIC_ASSERT(offsetof(Obj_005B3700, unknown_10) == 0x10);

// FUNCTION: GAMEMD 0x005B3700
Obj_005B3700::Obj_005B3700()
{
    unknown_0 = -1;
    unknown_4 = 0;
    unknown_5 = 0;
    unknown_6 = 1;
    unknown_7 = 0;
    unknown_8 = 1;
    unknown_9 = 1;
    unknown_10 = 0.016;
    unknown_18 = 0.016;
}

struct Slot_005B3A00
{
    char Bytes[0x20];
};

// GLOBAL: GAMEMD 0x00A8E3A8 (32-byte records)
extern "C" Slot_005B3A00 DAT_00A8E3A8[];

struct Obj_005B3A00
{
    char Pad_00[0xAC];
    int unknown_AC;
};
GG_STATIC_ASSERT(offsetof(Obj_005B3A00, unknown_AC) == 0xAC);

// FUNCTION: GAMEMD 0x005B3A00
Slot_005B3A00* __fastcall FUN_005B3A00(Obj_005B3A00* self)
{
    return &DAT_00A8E3A8[self->unknown_AC];
}

struct Iface_005BF500
{
    virtual void vf_0() = 0;
    virtual void vf_1() = 0;
    virtual void vf_2() = 0;
    virtual void vf_3(int value) = 0;
};

// GLOBAL: GAMEMD 0x00B45B5C
extern "C" Iface_005BF500** DAT_00B45B5C;

// FUNCTION: GAMEMD 0x005BF500
// Forward `value` to slot 3 of the first entry of the vector at 0xB45B58.
void __fastcall FUN_005BF500(int value)
{
    if (DAT_00B45B68 > 0) {
        DAT_00B45B5C[0]->vf_3(value);
    }
}

struct Vector_005C6120
{
    virtual void vf_0() = 0;
    virtual void vf_1() = 0;
    virtual void vf_2() = 0;
    virtual void vf_3() = 0;

    void** unknown_4;
    int Pad_08;
    int Pad_0C;
    int unknown_10;

    void FUN_005C6120();
};

// FUNCTION: GAMEMD 0x005C6120
// Free every pointer held, then slot 3.
void Vector_005C6120::FUN_005C6120()
{
    for (int i = 0; i < unknown_10; i++) {
        operator delete(unknown_4[i]);
    }
    vf_3();
}

struct Obj_005F9710
{
    char unknown_0;
    char unknown_1;
};

// FUNCTION: GAMEMD 0x005F9710
void __fastcall FUN_005F9710(Obj_005F9710* self)
{
    self->unknown_1 = 0x47;
}

// FUNCTION: GAMEMD 0x00623840
// Delete every string of the combo box `window`, last first.
int __fastcall FUN_00623840(HWND window)
{
    int count = SendMessageA(window, CB_GETCOUNT, 0, 0);
    while (count--) {
        SendMessageA(window, CB_DELETESTRING, count, 0);
    }
    return 0;
}

struct Quad_00645C30
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;

    Quad_00645C30(int a, int b, int c, int d);
};

// FUNCTION: GAMEMD 0x00645C30
Quad_00645C30::Quad_00645C30(int a, int b, int c, int d)
{
    unknown_0 = a;
    unknown_4 = b;
    unknown_8 = c;
    unknown_C = d;
}

struct Record_00656580
{
    char Bytes[0x18];
};

struct Key_00656580
{
    char Pad_00[0xEF0];
    int unknown_EF0;
};
GG_STATIC_ASSERT(offsetof(Key_00656580, unknown_EF0) == 0xEF0);

struct Obj_00656580
{
    Record_00656580 unknown_0[1];

    Record_00656580* FUN_00656580(const Key_00656580* key);
};

// FUNCTION: GAMEMD 0x00656580
// Record number (key +0xEF0) + 197 of the 24-byte records at `this`.
Record_00656580* Obj_00656580::FUN_00656580(const Key_00656580* key)
{
    return &unknown_0[key->unknown_EF0 + 0xC5];
}

struct Obj_0065AD30
{
    char Pad_00[0xE4];
    int* unknown_E4;

    int FUN_0065AD30(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0065AD30, unknown_E4) == 0xE4);

// FUNCTION: GAMEMD 0x0065AD30
int Obj_0065AD30::FUN_0065AD30(int index) const
{
    return unknown_E4[index];
}

struct Pair_0065C890
{
    int unknown_0;
    int unknown_4;

    Pair_0065C890(int a, int b);
};

// FUNCTION: GAMEMD 0x0065C890
Pair_0065C890::Pair_0065C890(int a, int b)
{
    unknown_0 = a;
    unknown_4 = b;
}

struct Obj_0068BCB0
{
    char Pad_00[0x214];
    int unknown_214;
};
GG_STATIC_ASSERT(offsetof(Obj_0068BCB0, unknown_214) == 0x214);

// FUNCTION: GAMEMD 0x0068BCB0
int __fastcall FUN_0068BCB0(Obj_0068BCB0* self)
{
    return ++self->unknown_214;
}

struct Obj_0068C030
{
    char Pad_00[0x1180];
    int unknown_1180[16];

    int FUN_0068C030(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0068C030, unknown_1180) == 0x1180);

// FUNCTION: GAMEMD 0x0068C030
// Entry `index` of the sixteen at +0x1180, or -1 out of range.
int Obj_0068C030::FUN_0068C030(int index) const
{
    if (index >= 0 && index < 16) {
        return unknown_1180[index];
    }
    return -1;
}

struct Owner_006915D0
{
    char Pad_00[0xA0];
    unsigned int unknown_A0;
};
GG_STATIC_ASSERT(offsetof(Owner_006915D0, unknown_A0) == 0xA0);

struct Cursor_006915D0
{
    char Pad_00[0x24];
    Owner_006915D0* unknown_24;
    char Pad_28[4];
    unsigned int unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Cursor_006915D0, unknown_2C) == 0x2C);

// FUNCTION: GAMEMD 0x006915D0
bool __fastcall FUN_006915D0(Cursor_006915D0* self)
{
    return self->unknown_2C < self->unknown_24->unknown_A0;
}

#pragma pack(push, 1)
struct Obj_00696F10
{
    char Pad_00[0x4B];
    int unknown_4B;
    int unknown_4F;
    int unknown_53;
    int unknown_57;
    int unknown_5B;
    int unknown_5F;
    int unknown_63;
    int unknown_67;

    int FUN_00696F10() const;
    int FUN_00696F20() const;
    int FUN_00696F50() const;
    int FUN_00696F70() const;
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_4B) == 0x4B);
GG_STATIC_ASSERT(offsetof(Obj_00696F10, unknown_67) == 0x67);

// FUNCTION: GAMEMD 0x00696F10
int Obj_00696F10::FUN_00696F10() const
{
    if (unknown_4F == -2) {
        return -2;
    }
    return unknown_4B;
}

// FUNCTION: GAMEMD 0x00696F20
int Obj_00696F10::FUN_00696F20() const
{
    if (unknown_57 == -2) {
        return -2;
    }
    return unknown_53;
}

// FUNCTION: GAMEMD 0x00696F50
int Obj_00696F10::FUN_00696F50() const
{
    if (unknown_5F == -2 && unknown_5B == -1) {
        return -2;
    }
    return unknown_5B;
}

// FUNCTION: GAMEMD 0x00696F70
int Obj_00696F10::FUN_00696F70() const
{
    if (unknown_67 == -2 && unknown_63 == -1) {
        return -2;
    }
    return unknown_63;
}

struct Obj_0069B540
{
    char Pad_00[0x24];
    int unknown_24;
    char Pad_28[0x4C - 0x28];
    int unknown_4C[8];
    int unknown_6C[8];
};
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_6C) == 0x6C);

// FUNCTION: GAMEMD 0x0069B540
void __fastcall FUN_0069B540(Obj_0069B540* self)
{
    self->unknown_24 = 0;
    for (int i = 0; i < 8; i++) {
        self->unknown_4C[i] = -1;
        self->unknown_6C[i] = -1;
    }
}

struct Obj_0069BBE0
{
    char Pad_00[0x30D8];
    char unknown_30D8;
};
GG_STATIC_ASSERT(offsetof(Obj_0069BBE0, unknown_30D8) == 0x30D8);

// FUNCTION: GAMEMD 0x0069BBE0
char __fastcall FUN_0069BBE0(Obj_0069BBE0* self)
{
    return self->unknown_30D8;
}

struct Type_006A46D0
{
    char Pad_00[0x24];
    char unknown_24[1];
};

// GLOBAL: GAMEMD 0x008B4124
extern "C" Type_006A46D0** DAT_008B4124;

// FUNCTION: GAMEMD 0x006A46D0
// Index of the entry of the vector at 0x8B4120 whose name at +0x24 is `name`,
// or -1.
int __fastcall FUN_006A46D0(const char* name)
{
    for (int i = 0; i < DAT_008B4130; i++) {
        if (_stricmp(DAT_008B4124[i]->unknown_24, name) == 0) {
            return i;
        }
    }
    return -1;
}
