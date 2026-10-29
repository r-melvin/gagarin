// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: small leaf functions spread over 0x6D0000-0x7C0000 of the user's gamemd.exe v1.001, each
//   disassembled from its entry point; receiver types are placeholder views that declare only the
//   fields the bodies touch.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "voxel_shade_palette.h"
#include "string_class.h"
#include "../network/world_domination_tour.h"

// GLOBAL: GAMEMD 0xB1D4E0
extern unsigned char DAT_00B1D4E0[256];
// GLOBAL: GAMEMD 0xB45990
extern unsigned char DAT_00B45990[256];

// 0x74BEE0 / 0x74BF10: reset the cursor and fill the byte buffer.
struct FillBuf_0074BEE0
{
    char           unknown_00[0x08];
    int            Cursor;   // +0x08
    char           unknown_0C[0x04];
    unsigned char* Data;     // +0x10
    int            Size;     // +0x14

    // FUNCTION: GAMEMD 0x74BEE0 (__thiscall)
    void ClearZero();
    // FUNCTION: GAMEMD 0x74BF10 (__thiscall)
    void ClearOnes();
};
GG_STATIC_ASSERT(offsetof(FillBuf_0074BEE0, Cursor) == 0x08);
GG_STATIC_ASSERT(offsetof(FillBuf_0074BEE0, Data) == 0x10);
GG_STATIC_ASSERT(offsetof(FillBuf_0074BEE0, Size) == 0x14);

// FUNCTION: GAMEMD 0x74BEE0
// PARTIAL: 87.5%. Retail stores the cursor before loading the size; plain C++ loads the size first.
void FillBuf_0074BEE0::ClearZero()
{
    Cursor = -1;
    if (Size > 0)
        memset(Data, 0, Size);
}

// FUNCTION: GAMEMD 0x74BF10
// PARTIAL: 87.5%. Retail stores the cursor before loading the size; plain C++ loads the size first.
void FillBuf_0074BEE0::ClearOnes()
{
    Cursor = -1;
    if (Size > 0)
        memset(Data, -1, Size);
}

// FUNCTION: GAMEMD 0x753BD0
// Fills the identity byte table.
void __fastcall FUN_00753BD0()
{
    for (int i = 0; i < 256; ++i)
        DAT_00B1D4E0[i] = (unsigned char)i;
}

// FUNCTION: GAMEMD 0x758930
// Fills the shade table with 0x10.
void __fastcall FUN_00758930()
{
    memset(DAT_00B45990, 0x10, 256);
}

// GLOBAL: GAMEMD 0x7E37B4 / 0x7E2AC8 - float thresholds.
extern const float DAT_007E37B4;
extern const float DAT_007E2AC8;

// 0x750030: classifies the float against two thresholds (0 = high, 1 = middle, 2 = low).
struct Float_00750030
{
    float Value;

    // FUNCTION: GAMEMD 0x750030 (__thiscall)
    int Classify() const;
};

// FUNCTION: GAMEMD 0x750030
int Float_00750030::Classify() const
{
    if (!(Value < DAT_007E37B4))
        return 0;
    return (Value >= DAT_007E2AC8) ? 1 : 2;
}

// 0x7C3910..0x7C3990: a playback position object; Pos is a per-object function pointer
// (called cdecl with the object) returning a sample count, Rate the samples per second/60 divisor.
struct PlayPos_007C3910
{
    char unknown_00[0x50];
    int (__cdecl* Pos)(PlayPos_007C3910*);   // +0x50
    char unknown_54[0x24];
    unsigned int Rate;                        // +0x78
    char unknown_7C[0xCC];
    int Offset;                               // +0x148

    // FUNCTION: GAMEMD 0x7C3910 (__fastcall)
    void __fastcall Seek(int target);
    // FUNCTION: GAMEMD 0x7C3960 (__thiscall)
    int Current();
    // FUNCTION: GAMEMD 0x7C3990 (__thiscall)
    int CurrentRated();
};
GG_STATIC_ASSERT(offsetof(PlayPos_007C3910, Pos) == 0x50);
GG_STATIC_ASSERT(offsetof(PlayPos_007C3910, Rate) == 0x78);
GG_STATIC_ASSERT(offsetof(PlayPos_007C3910, Offset) == 0x148);

// FUNCTION: GAMEMD 0x7C3910
void __fastcall PlayPos_007C3910::Seek(int target)
{
    Offset = 0;
    unsigned int t = (unsigned int)(Pos(this) * 60) / Rate;
    target -= t;
    Offset = target - Offset;
}

// FUNCTION: GAMEMD 0x7C3960
int PlayPos_007C3910::Current()
{
    unsigned int t = (unsigned int)(Pos(this) * 60) / Rate;
    return Offset + t;
}

// FUNCTION: GAMEMD 0x7C3990
int PlayPos_007C3910::CurrentRated()
{
    unsigned int r = Rate;
    unsigned int t = (unsigned int)(Pos(this) * 60) / r;
    return Offset + t;
}

// 0x7C36D0: two-field extent reader; the wide fields win when present.
#pragma pack(push, 1)
struct Extent_007C36D0
{
    char           unknown_00[0x02];
    unsigned short A;        // +0x02
    unsigned short B;        // +0x04
    char           unknown_06[0x10C];
    unsigned int   WideA;    // +0x112
    unsigned int   WideB;    // +0x116
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Extent_007C36D0, WideA) == 0x112);
GG_STATIC_ASSERT(offsetof(Extent_007C36D0, WideB) == 0x116);

// FUNCTION: GAMEMD 0x7C36D0
int __fastcall FUN_007C36D0(Extent_007C36D0* e, unsigned int* outA, unsigned int* outB)
{
    if (e->WideA > 0) {
        *outA = e->WideA;
        *outB = e->WideB;
        return -1;
    }
    *outA = e->A;
    *outB = e->B;
    return -1;
}

// 0x764FC0: true when the selection stamp differs from the campaign's, or slot idx differs.
struct Pick_00764FC0
{
    char unknown_00[0x0C];
    WorldDominationTour::CampaignProperties* Props;   // +0x0C
    char unknown_10[0x20];
    int  Stamp;                                       // +0x30
    int  Slots[1];                                    // +0x34

    // FUNCTION: GAMEMD 0x764FC0 (__thiscall)
    bool Differs(int idx);
};
GG_STATIC_ASSERT(offsetof(Pick_00764FC0, Props) == 0x0C);
GG_STATIC_ASSERT(offsetof(Pick_00764FC0, Stamp) == 0x30);
GG_STATIC_ASSERT(offsetof(Pick_00764FC0, Slots) == 0x34);

// FUNCTION: GAMEMD 0x764FC0
bool Pick_00764FC0::Differs(int idx)
{
    if (Stamp != Props->FUN_0076BFA0())
        return true;
    bool r = Slots[idx] != Props->FUN_0076BFE0();
    return r;
}

// 0x710700: divides a three-int vector by a scalar (zero divisor gives the zero vector).
struct Int3_00710700
{
    int X, Y, Z;

    // FUNCTION: GAMEMD 0x710700 (__thiscall, hidden result)
    Int3_00710700 Div(int d) const;
};
GG_STATIC_ASSERT(sizeof(Int3_00710700) == 0x0C);

// FUNCTION: GAMEMD 0x710700
Int3_00710700 Int3_00710700::Div(int d) const
{
    Int3_00710700 r;
    if (d == 0) {
        r.X = 0;
        r.Y = 0;
        r.Z = d;
        return r;
    }
    r.X = X / d;
    r.Y = Y / d;
    r.Z = Z / d;
    return r;
}

// 256x256 byte planes cleared by rectangle.
// GLOBAL: GAMEMD 0xB2FF78 / 0xB1D5E0
extern unsigned char DAT_00B2FF78[0x10000];
extern unsigned char DAT_00B1D5E0[0x10000];

struct Rect_007547C0
{
    int X, Y, W, H;
};
GG_STATIC_ASSERT(sizeof(Rect_007547C0) == 0x10);

// FUNCTION: GAMEMD 0x754740
// Clears a rectangle of the plane at 0xB2FF78; an out-of-bounds rectangle clears the whole plane.
void __fastcall FUN_00754740(int x, int y, int w, int h)
{
    if (x < 0 || y < 0 || x + w > 255 || h + y > 255) {
        memset(DAT_00B2FF78, 0, 0x10000);
        return;
    }
    int bottom = h + y;
    for (int r = y; r <= bottom; r++)
        memset(&DAT_00B2FF78[(r << 8) + x], 0, w);
}

// FUNCTION: GAMEMD 0x7547C0
void __fastcall FUN_007547C0(Rect_007547C0* rc)
{
    if (rc->X < 0 || rc->Y < 0 || rc->W + rc->X > 255 || rc->H + rc->Y > 255) {
        memset(DAT_00B2FF78, 0, 0x10000);
        return;
    }
    for (int r = rc->Y; r <= rc->Y + rc->H; r++)
        memset(&DAT_00B2FF78[(r << 8) + rc->X], 0, rc->W + 1);
}

// FUNCTION: GAMEMD 0x754860
void __fastcall FUN_00754860(int x, int y, int w, int h)
{
    int bottom = h + y;
    for (int r = y; r <= bottom; r++)
        memset(&DAT_00B1D5E0[(r << 8) + x], 0, w);
}

// FUNCTION: GAMEMD 0x7548B0
void __fastcall FUN_007548B0(Rect_007547C0* rc)
{
    for (int r = rc->Y; r <= rc->Y + rc->H; r++)
        memset(&DAT_00B1D5E0[(r << 8) + rc->X], 0, rc->W + 1);
}

// 0x74B8F0: drops every back-reference to the given object.
struct RefHolder_0074B8F0
{
    char  unknown_00[0x2D4];
    void* Ref2D4;      // +0x2D4
    char  unknown_2D8[0x0C];
    void* Ref2E4;      // +0x2E4
    void* Ref2E8;      // +0x2E8
    void* Ref2EC;      // +0x2EC
    char  unknown_2F0[0x08];
    void* Ref2F8;      // +0x2F8
    void* Ref2FC;      // +0x2FC

    // FUNCTION: GAMEMD 0x74B8F0 (__thiscall)
    void Forget(void* obj, int unused);
};
GG_STATIC_ASSERT(offsetof(RefHolder_0074B8F0, Ref2D4) == 0x2D4);
GG_STATIC_ASSERT(offsetof(RefHolder_0074B8F0, Ref2E4) == 0x2E4);
GG_STATIC_ASSERT(offsetof(RefHolder_0074B8F0, Ref2F8) == 0x2F8);
GG_STATIC_ASSERT(offsetof(RefHolder_0074B8F0, Ref2FC) == 0x2FC);

// FUNCTION: GAMEMD 0x74B8F0
void RefHolder_0074B8F0::Forget(void* obj, int)
{
    if (Ref2F8 == obj)
        Ref2F8 = 0;
    if (Ref2E4 == obj)
        Ref2E4 = 0;
    if (Ref2E8 == obj)
        Ref2E8 = 0;
    if (Ref2EC == obj)
        Ref2EC = 0;
    if (Ref2D4 == obj)
        Ref2D4 = 0;
    if (Ref2FC == obj)
        Ref2FC = 0;
}

// Shape draws of a global shape file at a position copied from a global point (flag 0x400, z adjust
// 0x3E8); the surface and rectangle arrive in ECX / EDX and are passed straight through.
struct Point_0072E860 {
    int x;
    int y;
};
struct Surface_0072E860;
struct Rect_0072E860;
struct Shape_0072E860;
struct Convert_0072E860;

// GLOBAL: GAMEMD 0xB0FC14 / 0xB0FC1C / 0xB0FC20 - positions.
extern Point_0072E860* DAT_00B0FC14;
extern Point_0072E860* DAT_00B0FC1C;
extern Point_0072E860* DAT_00B0FC20;
// GLOBAL: GAMEMD 0xB0F9DC / 0xB0FB1C / 0xB0FAF8 / 0xB0FB34 / 0xB0FB00 - shapes.
extern Shape_0072E860* DAT_00B0F9DC;
extern Shape_0072E860* DAT_00B0FB1C;
extern Shape_0072E860* DAT_00B0FAF8;
extern Shape_0072E860* DAT_00B0FB34;
extern Shape_0072E860* DAT_00B0FB00;
// GLOBAL: GAMEMD 0xB0FBCC / 0xB0FBB4 / 0xB0FBA8 - converts.
extern Convert_0072E860* DAT_00B0FBCC;
extern Convert_0072E860* DAT_00B0FBB4;
extern Convert_0072E860* DAT_00B0FBA8;
// GLOBAL: GAMEMD 0x8A00A4 - screen width.
extern int DAT_008A00A4;

// FUNCTION: GAMEMD 0x4AED70 (decl; reloc) -- shape draw, __fastcall: surface in ECX, convert in EDX, fourteen stack words.
void FUN_004AED70(Surface_0072E860* surface, Convert_0072E860* convert, Shape_0072E860* shape,
                  int frame, Point_0072E860* position, Rect_0072E860* clip, int flags,
                  int a6, int a7, int a8, int zAdjust, int a10, int a11, int a12,
                  Point_0072E860 offset);

// FUNCTION: GAMEMD 0x72E860
void __fastcall FUN_0072E860(Surface_0072E860* self, Rect_0072E860* rect)
{
    Point_0072E860 position = {0, 0};
    position = *DAT_00B0FC14;
    Point_0072E860 offset = {0, 0};
    FUN_004AED70(self, DAT_00B0FBCC, DAT_00B0F9DC, 0, &position, rect, 0x400, 0, 0, 0, 0x3E8, 0, 0, 0, offset);
}

// FUNCTION: GAMEMD 0x72E8C0
void __fastcall FUN_0072E8C0(Surface_0072E860* self, Rect_0072E860* rect)
{
    Point_0072E860 position = {0, 0};
    position = *DAT_00B0FC20;
    Point_0072E860 offset = {0, 0};
    FUN_004AED70(self, DAT_00B0FBCC, DAT_00B0FAF8, 1, &position, rect, 0x400, 0, 0, 0, 0x3E8, 0, 0, 0, offset);
}

// FUNCTION: GAMEMD 0x72E990
void __fastcall FUN_0072E990(Surface_0072E860* self, Rect_0072E860* rect)
{
    Point_0072E860 position = {0, 0};
    position = *DAT_00B0FC1C;
    Point_0072E860 offset = {0, 0};
    FUN_004AED70(self, DAT_00B0FBA8, DAT_00B0FB34, 0, &position, rect, 0x400, 0, 0, 0, 0x3E8, 0, 0, 0, offset);
}

// FUNCTION: GAMEMD 0x72EA70
void __fastcall FUN_0072EA70(Surface_0072E860* self, Rect_0072E860* rect)
{
    Point_0072E860 position = {0, 0};
    position = *DAT_00B0FC1C;
    Point_0072E860 offset = {0, 0};
    FUN_004AED70(self, DAT_00B0FBB4, DAT_00B0FB1C, 0, &position, rect, 0x400, 0, 0, 0, 0x3E8, 0, 0, 0, offset);
}

// 0x7B8250: true when the string holds characters the other text does not cover.
extern "C++" unsigned int __cdecl FUN_007CA405(const wchar_t* s);   // GAMEMD 0x7CA405 (decl; reloc) -- wcslen
extern "C++" unsigned int __cdecl FUN_007CD7CE(const wchar_t* a, const wchar_t* b);   // GAMEMD 0x7CD7CE (decl; reloc)

struct WStr_007B8250
{
    const wchar_t* Str;   // +0x00

    // FUNCTION: GAMEMD 0x7B8250 (__thiscall)
    bool HasUnmatched(const wchar_t* other) const;
};

// FUNCTION: GAMEMD 0x7B8250
bool WStr_007B8250::HasUnmatched(const wchar_t* other) const
{
    if (other != 0 && Str != 0) {
        unsigned int n = FUN_007CA405(Str);
        return FUN_007CD7CE(Str, other) < n;
    }
    return false;
}

// 0x7533B0: writes the two four-byte markers ("SxVo", then "ExVo" when the first write succeeded).
struct OutStream_007533B0
{
    virtual long __stdcall Slot0();
    virtual long __stdcall Slot1();
    virtual long __stdcall Slot2();
    virtual long __stdcall Slot3();
    virtual long __stdcall Write(const void* buf, unsigned long len, unsigned long* written);   // +0x10
};

// FUNCTION: GAMEMD 0x7533B0
void __fastcall FUN_007533B0(OutStream_007533B0* s)
{
    unsigned long tag = 0x566F7853;
    if (s->Write(&tag, 4, 0) >= 0) {
        tag = 0x566F7845;
        s->Write(&tag, 4, 0);
    }
}

// 0x77A4A0: stores a new name and marks the record dirty when it differs from the current one.
struct NamedRec_0077A4A0
{
    char    unknown_00[0x08];
    bool    Dirty;       // +0x08
    char    unknown_09[0x03];
    Wstring Name;        // +0x0C

    // FUNCTION: GAMEMD 0x77A4A0 (__thiscall)
    void SetName(const Wstring& name);
};
GG_STATIC_ASSERT(offsetof(NamedRec_0077A4A0, Dirty) == 0x08);
GG_STATIC_ASSERT(offsetof(NamedRec_0077A4A0, Name) == 0x0C);

// FUNCTION: GAMEMD 0x77A4A0
void NamedRec_0077A4A0::SetName(const Wstring& name)
{
    if (!(name == Name)) {
        Name = name;
        Dirty = true;
    }
}

// 0x777B80: three-byte tag read from the first byte of the table string and the byte after its '_'.
// GLOBAL: GAMEMD 0x822D20
extern char DAT_00822D20[];
char* __cdecl P_strchr(const char* s, int c);   // GAMEMD 0x7CAF30 (decl; reloc)

struct Tag3_00777B80
{
    char A;   // +0x00
    char B;   // +0x01
    char C;   // +0x02

    // FUNCTION: GAMEMD 0x777B80 (__thiscall)
    Tag3_00777B80* Init();
};

// FUNCTION: GAMEMD 0x777B80
Tag3_00777B80* Tag3_00777B80::Init()
{
    A = DAT_00822D20[0];
    B = 0;
    C = 0;
    char* p = P_strchr(DAT_00822D20, '_');
    if (p)
        B = p[1];
    return this;
}
