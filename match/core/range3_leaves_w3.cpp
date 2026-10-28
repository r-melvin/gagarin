// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: small leaf functions spread over 0x6A0000-0x7C0000 of the user's gamemd.exe v1.001, each
//   disassembled from its entry point; the receiver types are placeholder views that declare only
//   the fields the bodies touch.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1748
extern const float DAT_007E1748;

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

// Unmatched (best 22%): retail moves AL to CL before masking; GAMEMD 0x75A810
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
