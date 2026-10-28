// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: small leaf functions spread over 0x6A0000-0x7C0000 of the user's gamemd.exe v1.001, each
//   disassembled from its entry point; the receiver types are placeholder views that declare only
//   the fields the bodies touch.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 - the engine frame counter.
extern int CurrentFrame;
// GLOBAL: GAMEMD 0x7E1748
extern const float DAT_007E1748;

// 0x6B10D0: stores a mode and the frame limit it applies until (frame counter, or never).
struct Obj_006B10D0
{
    char unknown_00[0x5C];
    int Mode;            // +0x5C
    int Until;           // +0x60

    // FUNCTION: GAMEMD 0x6B10D0 (__thiscall)
    void FUN_006B10D0(int mode);
};
GG_STATIC_ASSERT(offsetof(Obj_006B10D0, Until) == 0x60);

// FUNCTION: GAMEMD 0x6B10D0
void Obj_006B10D0::FUN_006B10D0(int mode)
{
    Mode = mode;
    if (mode == 0)
        Until = CurrentFrame;
    else
        Until = 0x7FFFFFFF;
}

// 0x6C87D0: count of slots up to and including the last non-null one (receiver in ECX, count in EDX).
// FUNCTION: GAMEMD 0x6C87D0
int __fastcall FUN_006C87D0(const int* slots, int count)
{
    int result = 0;
    for (int i = 0; i < count; ++slots) {
        if (*slots != 0)
            result = i + 1;
        ++i;
    }
    return result;
}

// 0x6C9820: first of four floats above the threshold, or -1.
struct Obj_006C9820
{
    float V[4];

    // FUNCTION: GAMEMD 0x6C9820 (__thiscall)
    int FUN_006C9820();
};

// FUNCTION: GAMEMD 0x6C9820
int Obj_006C9820::FUN_006C9820()
{
    for (int i = 0; i < 4; ++i) {
        if (V[i] > DAT_007E1748)
            return i;
    }
    return -1;
}

// 0x6C9940: packs three bytes into the 24-bit value at +8.
struct Obj_006C9940
{
    char unknown_00[8];
    int Packed;          // +0x08

    // FUNCTION: GAMEMD 0x6C9940 (__thiscall)
    void FUN_006C9940(unsigned char a, unsigned char b, unsigned char c);
};
GG_STATIC_ASSERT(offsetof(Obj_006C9940, Packed) == 0x08);

// FUNCTION: GAMEMD 0x6C9940
void Obj_006C9940::FUN_006C9940(unsigned char a, unsigned char b, unsigned char c)
{
    Packed = (((a << 8) | b) << 8) | c;
}

// 0x6CE2C0: starts the timer if it is not already running.
struct Obj_006CE2C0
{
    int StartTime;       // +0x00 (-1 when stopped)

    // FUNCTION: GAMEMD 0x6CE2C0 (__thiscall)
    void FUN_006CE2C0();
};

// FUNCTION: GAMEMD 0x6CE2C0
void Obj_006CE2C0::FUN_006CE2C0()
{
    if (StartTime == -1)
        StartTime = CurrentFrame;
}

// 0x6D1810: zeroes a 0x19-byte record.
struct Obj_006D1810
{
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0C;
    int unknown_10;
    int unknown_14;
    unsigned char unknown_18;

    // FUNCTION: GAMEMD 0x6D1810 (__thiscall)
    Obj_006D1810* FUN_006D1810();
};

// FUNCTION: GAMEMD 0x6D1810
Obj_006D1810* Obj_006D1810::FUN_006D1810()
{
    unknown_00 = 0;
    unknown_04 = 0;
    unknown_08 = 0;
    unknown_0C = 0;
    unknown_10 = 0;
    unknown_14 = 0;
    unknown_18 = 0;
    return this;
}

// 0x6C89B0: allocates a buffer of the given size and records it twice.
struct Obj_006C89B0
{
    int Size;            // +0x00
    void* Buffer;        // +0x04
    void* Cursor;        // +0x08

    // FUNCTION: GAMEMD 0x6C89B0 (__thiscall)
    Obj_006C89B0* FUN_006C89B0(int size);
    // FUNCTION: GAMEMD 0x6C89D0 (__thiscall)
    void FUN_006C89D0();
};

// FUNCTION: GAMEMD 0x6C89B0
Obj_006C89B0* Obj_006C89B0::FUN_006C89B0(int size)
{
    Size = size;
    void* p = operator new(size);
    Buffer = p;
    Cursor = p;
    return this;
}

// FUNCTION: GAMEMD 0x6C89D0
void Obj_006C89B0::FUN_006C89D0()
{
    if (Buffer != 0)
        operator delete(Buffer);
}

// 0x6CA670 / 0x6CA680: store the result of the helper at 0x6CA5A0 (receiver in ECX, destination in EDX).
unsigned int __fastcall FUN_006CA5A0(void* self);

// FUNCTION: GAMEMD 0x6CA670
void __fastcall FUN_006CA670(void* self, unsigned int* out)
{
    *out = FUN_006CA5A0(self);
}

// FUNCTION: GAMEMD 0x6CA680
void __fastcall FUN_006CA680(void* self, unsigned int* out)
{
    unsigned int r = FUN_006CA5A0(self);
    if (r > 0)
        out[1] = r;
}

// 0x6BA120: forwards to 0x6B9D00 with both flags set.
void __stdcall FUN_006B9D00(int a, int b, int c);

// FUNCTION: GAMEMD 0x6BA120
void __stdcall FUN_006BA120(int a)
{
    FUN_006B9D00(a, 1, 1);
}

// 0x6D9910: calls the 0x4D1890 method on its argument.
struct Obj_004D1890
{
    void FUN_004D1890();
};

// FUNCTION: GAMEMD 0x6D9910
void __stdcall FUN_006D9910(Obj_004D1890* p)
{
    p->FUN_004D1890();
}

// 0x70C250: forwards its three arguments to 0x65AC40 and returns 0.
int __stdcall FUN_0065AC40(int a, int b, int c);

// FUNCTION: GAMEMD 0x70C250
int __stdcall FUN_0070C250(int a, int b, int c)
{
    FUN_0065AC40(a, b, c);
    return 0;
}

// 0x6EC220: true when the argument is on the chain starting at this->+0x54 and following +0x5D8.
struct Obj_006EC220_Link
{
    char unknown_00[0x5D8];
    Obj_006EC220_Link* Next;   // +0x5D8
};
GG_STATIC_ASSERT(offsetof(Obj_006EC220_Link, Next) == 0x5D8);

struct Obj_006EC220
{
    char unknown_00[0x54];
    Obj_006EC220_Link* Head;   // +0x54

    // FUNCTION: GAMEMD 0x6EC220 (__thiscall)
    bool FUN_006EC220(Obj_006EC220_Link* target) const;
};
GG_STATIC_ASSERT(offsetof(Obj_006EC220, Head) == 0x54);

// FUNCTION: GAMEMD 0x6EC220
bool Obj_006EC220::FUN_006EC220(Obj_006EC220_Link* target) const
{
    Obj_006EC220_Link* p = Head;
    while (p != 0) {
        if (p == target)
            return true;
        p = p->Next;
    }
    return false;
}

// 0x6CE240 / 0x6C9740: small vector sums.
struct Vec3_w3
{
    int X, Y, Z;
    Vec3_w3(int x, int y, int z) : X(x), Y(y), Z(z) {}
};

struct Vec3Op_006CE240
{
    int X, Y, Z;

    // FUNCTION: GAMEMD 0x6CE240 (__thiscall)
    Vec3_w3 FUN_006CE240(const Vec3_w3& rhs) const;
};

// FUNCTION: GAMEMD 0x6CE240
Vec3_w3 Vec3Op_006CE240::FUN_006CE240(const Vec3_w3& rhs) const
{
    return Vec3_w3(rhs.X + X, rhs.Y + Y, rhs.Z + Z);
}

struct Vec4_w3
{
    float V[4];
};

struct Vec4Op_006C9740
{
    float V[4];

    // FUNCTION: GAMEMD 0x6C9740 (__thiscall)
    Vec4_w3 FUN_006C9740(const Vec4_w3& rhs);
    // FUNCTION: GAMEMD 0x6C97E0 (__thiscall)
    Vec4_w3 FUN_006C97E0(const Vec4_w3& rhs);
};

// FUNCTION: GAMEMD 0x6C9740
Vec4_w3 Vec4Op_006C9740::FUN_006C9740(const Vec4_w3& rhs)
{
    for (int i = 0; i < 4; ++i)
        V[i] = rhs.V[i] + V[i];
    return *reinterpret_cast<Vec4_w3*>(this);
}

// FUNCTION: GAMEMD 0x6C97E0
Vec4_w3 Vec4Op_006C9740::FUN_006C97E0(const Vec4_w3& rhs)
{
    for (int i = 0; i < 4; ++i)
        V[i] = V[i] - rhs.V[i];
    return *reinterpret_cast<Vec4_w3*>(this);
}

// 0x721290: stores a value, capped at 255.
struct Obj_00721290
{
    char unknown_00[0x0C];
    int Value;           // +0x0C

    // FUNCTION: GAMEMD 0x721290 (__thiscall)
    void FUN_00721290(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00721290, Value) == 0x0C);

// FUNCTION: GAMEMD 0x721290
void Obj_00721290::FUN_00721290(int value)
{
    if (value >= 0xFF)
        value = 0xFF;
    Value = value;
}

// 0x7211E0: whether the indexed entry has its flag byte set (two reserved indices and out-of-range read as false).
struct Obj_007211E0_Entry
{
    char unknown_00[0x288];
    unsigned char Flag;        // +0x288
};
GG_STATIC_ASSERT(offsetof(Obj_007211E0_Entry, Flag) == 0x288);

struct Obj_007211E0
{
    char unknown_00[0x18];
    Obj_007211E0_Entry** Items;   // +0x18
    char unknown_1C[8];
    unsigned int Count;           // +0x24

    // FUNCTION: GAMEMD 0x7211E0 (__thiscall)
    bool FUN_007211E0(unsigned int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_007211E0, Items) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_007211E0, Count) == 0x24);

// FUNCTION: GAMEMD 0x7211E0
bool Obj_007211E0::FUN_007211E0(unsigned int index) const
{
    if (index != 0xFFFFFFFD && index != 0xFFFFFFFE && index < Count) {
        bool r = Items[index]->Flag != 0;
        return r;
    }
    return false;
}

// 0x74FFF0: true when the float is below the 0x7E1748 threshold.
struct Obj_0074FFF0
{
    float Value;

    // FUNCTION: GAMEMD 0x74FFF0 (__thiscall)
    int FUN_0074FFF0() const;
};

// FUNCTION: GAMEMD 0x74FFF0
int Obj_0074FFF0::FUN_0074FFF0() const
{
    if (Value < DAT_007E1748)
        return 1;
    return 0;
}

// EVA voice table helpers (the table is VoxClass::Array at 0xB1D4A0; the entries' name is at +0).
struct VoxArrayType
{
    char  unknown_00[0x04];
    char** Items;     // +0x04  == 0xB1D4A4
    char  unknown_08[0x08];
    int   Count;      // +0x10  == 0xB1D4B0
};
GG_STATIC_ASSERT(offsetof(VoxArrayType, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(VoxArrayType, Count) == 0x10);

// GLOBAL: GAMEMD 0xB1D4A0
extern VoxArrayType VoxArray;
// GLOBAL: GAMEMD 0xB1D4C8 - EVA voice language/set selector.
extern int DAT_00B1D4C8;
// GLOBAL: GAMEMD 0x817474 / 0x817694 - the placeholder entries returned for a bad index.
extern char DAT_00817474[];
extern char DAT_00817694[];

extern "C" int __cdecl Vox_strcmpi(const char* a, const char* b);

// FUNCTION: GAMEMD 0x752460
// The voice entry at the index, or the placeholder entry for -1 / out of range.
char* __fastcall FUN_00752460(int index)
{
    if (index != -1 && index >= 0 && index < VoxArray.Count)
        return VoxArray.Items[index];
    return DAT_00817694;
}

// FUNCTION: GAMEMD 0x753330
char* __fastcall FUN_00753330(int index)
{
    if (index != -1 && index < VoxArray.Count)
        return VoxArray.Items[index];
    return DAT_00817474;
}

// FUNCTION: GAMEMD 0x753350
// Index of the given entry in the table, or -1.
int __fastcall FUN_00753350(char* entry)
{
    int n = VoxArray.Count;
    for (int i = 0; i < n; ++i) {
        if (VoxArray.Items[i] == entry)
            return i;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x753380
// Address of the selector's name inside the record.
char* __fastcall FUN_00753380(char* record)
{
    if (DAT_00B1D4C8 == 0)
        return record + 0x3E;
    if (DAT_00B1D4C8 == 1)
        return record + 0x35;
    return record + 0x2C;
}

// Bit table at 0xB45BA8 (one bit per index; bit n lives in byte n>>3, mask 1<<(n&7)).
// GLOBAL: GAMEMD 0xB45BA8
extern unsigned char DAT_00B45BA8[];

// FUNCTION: GAMEMD 0x75A7D0
void __fastcall FUN_0075A7D0(int bit)
{
    int i = bit >> 3;
    unsigned char mask = (unsigned char)(1 << (bit & 7));
    DAT_00B45BA8[i] |= mask;
}

// FUNCTION: GAMEMD 0x75A7F0
void __fastcall FUN_0075A7F0(int bit)
{
    unsigned char mask = (unsigned char)(1 << (bit & 7));
    int i = bit >> 3;
    DAT_00B45BA8[i] &= ~mask;
}

// FUNCTION: GAMEMD 0x75A810
bool __fastcall FUN_0075A810(int bit)
{
    unsigned char mask = (unsigned char)(1 << (bit & 7));
    int i = bit >> 3;
    bool r = (DAT_00B45BA8[i] & mask) != 0;
    return r;
}

// Table of 8-byte (key, value) pairs at 0xB72D28 with its entry count at 0xB72F50.
struct Pair_00B72D28
{
    int First;
    int Second;
};
// GLOBAL: GAMEMD 0xB72D28
extern Pair_00B72D28 DAT_00B72D28[];
// GLOBAL: GAMEMD 0xB72F50
extern int DAT_00B72F50;

// FUNCTION: GAMEMD 0x775910
// Whether the key is present.
int __fastcall FUN_00775910(int key)
{
    for (int i = 0; i < DAT_00B72F50; ++i) {
        if (DAT_00B72D28[i].First == key)
            return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x775940
// The key of the last entry whose value matches, or 0.
int __fastcall FUN_00775940(int value)
{
    for (int i = DAT_00B72F50 - 1; i >= 0; --i) {
        if (value == DAT_00B72D28[i].Second)
            return DAT_00B72D28[i].First;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x775970
// The key following the first entry with the given key, or 0.
int __fastcall FUN_00775970(int key)
{
    for (int i = 0; i < DAT_00B72F50; ++i) {
        if (key == DAT_00B72D28[i].First && i < DAT_00B72F50 - 1)
            return DAT_00B72D28[i + 1].First;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7759B0
// The key preceding the last entry with the given key, or 0.
int __fastcall FUN_007759B0(int key)
{
    for (int i = DAT_00B72F50 - 1; i >= 0; --i) {
        if (key == DAT_00B72D28[i].First && i > 0)
            return DAT_00B72D28[i - 1].First;
    }
    return 0;
}

// 0x772AC0: whether the weapon's warhead is set and has its +0x144 flag (Wall) raised.
struct Obj_00772AC0_Warhead
{
    char unknown_00[0x144];
    bool Wall;            // +0x144
};
GG_STATIC_ASSERT(offsetof(Obj_00772AC0_Warhead, Wall) == 0x144);

struct Obj_00772AC0
{
    char unknown_00[0xAC];
    Obj_00772AC0_Warhead* Warhead;   // +0xAC

    // FUNCTION: GAMEMD 0x772AC0 (__thiscall)
    bool FUN_00772AC0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00772AC0, Warhead) == 0xAC);

// FUNCTION: GAMEMD 0x772AC0
bool Obj_00772AC0::FUN_00772AC0() const
{
    if (Warhead != 0 && Warhead->Wall)
        return true;
    return false;
}

// 0x771970 / 0x771980 / 0x7719D0: stubs that run the helper at 0x771620 on the member at +0x1C.
struct Obj_00771620
{
    void FUN_00771620();
};

struct Obj_00771970
{
    char unknown_00[0x1C];
    Obj_00771620* Inner;   // +0x1C

    // FUNCTION: GAMEMD 0x771970 (__thiscall)
    bool FUN_00771970(int a, int b);
    // FUNCTION: GAMEMD 0x771980 (__thiscall)
    void FUN_00771980(int a, int b);
    // FUNCTION: GAMEMD 0x7719D0 (__thiscall)
    void FUN_007719D0(int a);
};
GG_STATIC_ASSERT(offsetof(Obj_00771970, Inner) == 0x1C);

// FUNCTION: GAMEMD 0x771970
bool Obj_00771970::FUN_00771970(int, int)
{
    Inner->FUN_00771620();
    return false;
}

// FUNCTION: GAMEMD 0x771980
void Obj_00771970::FUN_00771980(int, int)
{
    Inner->FUN_00771620();
}

// FUNCTION: GAMEMD 0x7719D0
void Obj_00771970::FUN_007719D0(int)
{
    Inner->FUN_00771620();
}

// 0x777B30 / 0x777B60: fill the caller's buffer from the globals at 0x822D1C / 0x822D20.
// GLOBAL: GAMEMD 0x822D1C
extern int DAT_00822D1C;
// GLOBAL: GAMEMD 0x822D20
extern char DAT_00822D20[];
// STRING: GAMEMD 0x817F6C
extern const char DAT_00817F6C[];
extern "C" int __cdecl FUN_007C8EF4(char* buffer, const char* format, ...);
extern "C" char* __cdecl FUN_007C91D0(char* dest, const char* src, unsigned int count);

// FUNCTION: GAMEMD 0x777B30
char* __fastcall FUN_00777B30(char* buffer)
{
    FUN_007C8EF4(buffer, DAT_00817F6C, DAT_00822D1C);
    return buffer;
}

// FUNCTION: GAMEMD 0x777B60
char* __fastcall FUN_00777B60(char* buffer)
{
    FUN_007C91D0(buffer, DAT_00822D20, 0x20);
    return buffer;
}

// 0x77E780: xor of three consecutive globals.
// GLOBAL: GAMEMD 0xB77E00
extern int DAT_00B77E00;
// GLOBAL: GAMEMD 0xB77E04
extern int DAT_00B77E04;
// GLOBAL: GAMEMD 0xB77E08
extern int DAT_00B77E08;

// FUNCTION: GAMEMD 0x77E780
int __cdecl FUN_0077E780()
{
    return DAT_00B77E00 ^ DAT_00B77E08 ^ DAT_00B77E04;
}
