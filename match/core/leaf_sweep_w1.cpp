// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   The owning classes are not bound by RTTI or a binary string at these addresses,
//   so each receiver keeps a placeholder name derived from its address.
//
// Small unowned leaves between 0x401000 and 0x540000: accessors, flag setters,
// zeroing initialisers and one-line forwarders. Ordered ascending by retail address.
#include <windows.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A 36-byte element of a pointer-and-count table (Items at +0x00, Count at +0x04).
struct Elem_004011B0
{
    char Data[0x14];
    int  Field14;
    char Rest[0x24 - 0x18];
};
GG_STATIC_ASSERT(sizeof(Elem_004011B0) == 0x24);
GG_STATIC_ASSERT(offsetof(Elem_004011B0, Field14) == 0x14);

struct Table_004011B0
{
    Elem_004011B0* Items;   // +0x00
    int            Count;   // +0x04
};
GG_STATIC_ASSERT(offsetof(Table_004011B0, Count) == 0x04);

// GLOBAL: GAMEMD 0x815E88 -- fallback element returned for an out-of-range index.
extern Elem_004011B0 DAT_00815E88;

// FUNCTION: GAMEMD 0x4011B0
// Address of element `index`, unchecked (index in EDX).
Elem_004011B0* __fastcall FUN_004011B0(Table_004011B0* table, int index)
{
    return &table->Items[index];
}

// FUNCTION: GAMEMD 0x401600
// Address of element `index`, or the fallback element when out of range.
Elem_004011B0* __fastcall FUN_00401600(Table_004011B0* table, int index)
{
    if (index >= 0 && index < table->Count)
        return &table->Items[index];
    return &DAT_00815E88;
}

// FUNCTION: GAMEMD 0x401620
// The +0x14 field of element `index`, or zero when out of range.
int __fastcall FUN_00401620(Table_004011B0* table, int index)
{
    if (index >= 0 && index < table->Count)
        return table->Items[index].Field14;
    return 0;
}

struct Obj_004A52E0
{
    char Pad_00[0x18];
    char unknown_18;
    char unknown_19;
    // FUNCTION: GAMEMD 0x4A5110
    bool BothSet();
    // FUNCTION: GAMEMD 0x4A52E0
    void ClearBoth();
};
GG_STATIC_ASSERT(offsetof(Obj_004A52E0, unknown_19) == 0x19);

// FUNCTION: GAMEMD 0x4A5110
bool Obj_004A52E0::BothSet()
{
    if (unknown_18 && unknown_19)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x4A52E0
void Obj_004A52E0::ClearBoth()
{
    unknown_18 = 0;
    unknown_19 = 0;
}

// Circular list whose sentinel node sits at +0x0C of its owner.
struct ListNode_00401BE0
{
    ListNode_00401BE0* Next;    // +0x00
    char               Pad_04[0x14];
    int                unknown_18;
};
GG_STATIC_ASSERT(offsetof(ListNode_00401BE0, unknown_18) == 0x18);

struct Obj_00401BE0
{
    char               Pad_00[0x0C];
    ListNode_00401BE0  Sentinel;    // +0x0C
    // FUNCTION: GAMEMD 0x401BE0
    void ClearNodeFlags();
};
GG_STATIC_ASSERT(offsetof(Obj_00401BE0, Sentinel) == 0x0C);

// FUNCTION: GAMEMD 0x401BE0
// Zeroes the +0x18 field of every node in the list.
void Obj_00401BE0::ClearNodeFlags()
{
    for (ListNode_00401BE0* node = Sentinel.Next; node != &Sentinel; node = node->Next)
        node->unknown_18 = 0;
}

struct Block32_004031B0
{
    int Words[8];
};

struct Obj_004031B0
{
    char            Pad_00[0x44];
    Block32_004031B0 unknown_44;
};
GG_STATIC_ASSERT(offsetof(Obj_004031B0, unknown_44) == 0x44);

// FUNCTION: GAMEMD 0x4031B0
// Copies a 32-byte block into this object (source in EDX).
void __fastcall FUN_004031B0(Obj_004031B0* self, const Block32_004031B0* source)
{
    self->unknown_44 = *source;
}

struct Obj_00426A50
{
    char Pad_00[0xA6];
    char unknown_A6;
    char Pad_A7[0xCC - 0xA7];
    int  unknown_CC;
    // FUNCTION: GAMEMD 0x426A50
    int AdjustedCount();
};
GG_STATIC_ASSERT(offsetof(Obj_00426A50, unknown_CC) == 0xCC);

// FUNCTION: GAMEMD 0x426A50
// The +0xCC count, one less when the +0xA6 flag is set.
int Obj_00426A50::AdjustedCount()
{
    int count = unknown_CC;
    if (unknown_A6)
        count--;
    return count;
}

struct Obj_0042E100
{
    char Pad_00[8];
    int  unknown_08;
    int  unknown_0C;
    // FUNCTION: GAMEMD 0x42E100
    bool IsOver();
};

// FUNCTION: GAMEMD 0x42E100
bool Obj_0042E100::IsOver()
{
    bool over = unknown_08 > unknown_0C;
    return over;
}

struct Obj_0042E800
{
    char  Pad_00[8];
    char* unknown_08;
    // FUNCTION: GAMEMD 0x42E800
    char ByteAt(int index);
};

// FUNCTION: GAMEMD 0x42E800
// First payload byte of the 16-byte record `index` of the +0x08 array.
char Obj_0042E800::ByteAt(int index)
{
    return unknown_08[index * 16 + 8];
}

struct Obj_004305E0
{
    char          Pad_00[0x0C];
    unsigned char unknown_0C_0 : 1;
    unsigned char unknown_0C_1 : 1;
    // FUNCTION: GAMEMD 0x4305E0
    void SetFlag1(bool value);
};

// FUNCTION: GAMEMD 0x4305E0
void Obj_004305E0::SetFlag1(bool value)
{
    unknown_0C_1 = value;
}

struct Obj_00432BF0Inner
{
    char         Pad_00[0x14];
    unsigned int unknown_14;
    unsigned int unknown_18;
};

struct Obj_00432BF0
{
    char               Pad_00[4];
    Obj_00432BF0Inner* unknown_04;
    // FUNCTION: GAMEMD 0x432BF0
    unsigned int PerSecond();
};

// FUNCTION: GAMEMD 0x432BF0
// 1000 divided by the (integer) ratio of the inner object's two counters.
unsigned int Obj_00432BF0::PerSecond()
{
    return 1000 / (unknown_04->unknown_14 / unknown_04->unknown_18);
}

struct Obj_004333E0Inner
{
    char Pad_00[0x0C];
    int  unknown_0C;
};

struct Obj_004333E0
{
    char               Pad_00[4];
    Obj_004333E0Inner* unknown_04;
    char               Pad_08[0x24 - 0x08];
    int                unknown_24;
    // FUNCTION: GAMEMD 0x4333E0
    int Product();
};
GG_STATIC_ASSERT(offsetof(Obj_004333E0, unknown_24) == 0x24);

// FUNCTION: GAMEMD 0x4333E0
int Obj_004333E0::Product()
{
    return unknown_04->unknown_0C * unknown_24;
}

// FUNCTION: GAMEMD 0x4799B0
// CloseHandle result as a bool.
bool __stdcall FUN_004799B0(HANDLE handle)
{
    return CloseHandle(handle) ? true : false;
}

// FUNCTION: GAMEMD 0x47A6D0
// Same, the handle being the second argument.
bool __stdcall FUN_0047A6D0(int unused, HANDLE handle)
{
    return CloseHandle(handle) ? true : false;
}

struct Obj_00487110
{
    char Pad_00[0x78];
    unsigned int unknown_78;
    // FUNCTION: GAMEMD 0x487110
    void SetBit(int bit);
};

// FUNCTION: GAMEMD 0x487110
void Obj_00487110::SetBit(int bit)
{
    unknown_78 |= 1 << bit;
}

struct Obj_00487C80
{
    char Pad_00[0xF8];
    int  unknown_F8;
    // FUNCTION: GAMEMD 0x487C80
    int Get_F8();
};

// FUNCTION: GAMEMD 0x487C80
int Obj_00487C80::Get_F8()
{
    return unknown_F8;
}

struct Obj_00487D50
{
    char         Pad_00[0x11B];
    signed char  unknown_11B;
    char         Pad_11C[0x140 - 0x11C];
    unsigned int unknown_140;
    // FUNCTION: GAMEMD 0x487D50
    int Combined();
};
GG_STATIC_ASSERT(offsetof(Obj_00487D50, unknown_140) == 0x140);

// FUNCTION: GAMEMD 0x487D50
int Obj_00487D50::Combined()
{
    return unknown_11B + ((unknown_140 >> 7) & 1) * 4;
}

struct Obj_00430910
{
    char Block[0x60];   // +0x00
    int  unknown_60;
    char Pad_64[0x7C - 0x64];
    int  unknown_7C;
    // FUNCTION: GAMEMD 0x430910
    Obj_00430910* Clear();
};
GG_STATIC_ASSERT(offsetof(Obj_00430910, unknown_7C) == 0x7C);

// FUNCTION: GAMEMD 0x430910
// Zeroes the leading 0x60 bytes and the two later words; returns this.
Obj_00430910* Obj_00430910::Clear()
{
    for (int i = 0; i < 0x60; i++)
        Block[i] = 0;
    unknown_60 = 0;
    unknown_7C = 0;
    return this;
}

struct Obj_00479710
{
    int Words[0x1A];
    // FUNCTION: GAMEMD 0x479710
    Obj_00479710* Clear();
};

// FUNCTION: GAMEMD 0x479710
Obj_00479710* Obj_00479710::Clear()
{
    for (int i = 0; i < 0x1A; i++)
        Words[i] = 0;
    return this;
}

struct Obj_004A2350
{
    int  unknown_00;
    int  unknown_04;
    char unknown_08;
    char unknown_09;
    char unknown_0A;
    int  unknown_0C;
    // FUNCTION: GAMEMD 0x4A2350
    Obj_004A2350* Reset();
};
GG_STATIC_ASSERT(offsetof(Obj_004A2350, unknown_0C) == 0x0C);

// FUNCTION: GAMEMD 0x4A2350
Obj_004A2350* Obj_004A2350::Reset()
{
    unknown_00 = 0;
    unknown_04 = 0;
    unknown_08 = 0;
    unknown_09 = 0;
    unknown_0A = 0;
    unknown_0C = 0;
    return this;
}

struct Obj_004B9BD0
{
    char unknown_00;
    char unknown_01;
    char unknown_02;
    // FUNCTION: GAMEMD 0x4B9BD0
    Obj_004B9BD0* Reset();
};

// FUNCTION: GAMEMD 0x4B9BD0
Obj_004B9BD0* Obj_004B9BD0::Reset()
{
    unknown_00 = 0;
    unknown_01 = 0;
    unknown_02 = 0;
    return this;
}

struct Obj_004AEB10
{
    char          Pad_00[0x119C];
    char          unknown_119C;
    char          Pad_119D[3];
    void*         unknown_11A0;
    // FUNCTION: GAMEMD 0x4AEB10
    void* Selected();
};
GG_STATIC_ASSERT(offsetof(Obj_004AEB10, unknown_11A0) == 0x11A0);

// FUNCTION: GAMEMD 0x4AEB10
// The +0x11A0 pointer while the +0x119C flag is set, else null.
void* Obj_004AEB10::Selected()
{
    if (unknown_119C && unknown_11A0)
        return unknown_11A0;
    return 0;
}

struct Obj_004C3CE0
{
    char Pad_00[8];
    int  unknown_08;
    // FUNCTION: GAMEMD 0x4C3CE0
    bool Subtract(int amount);
};

// FUNCTION: GAMEMD 0x4C3CE0
// Subtracts from the +0x08 counter; true once it has fallen below -20.
bool Obj_004C3CE0::Subtract(int amount)
{
    unknown_08 -= amount;
    bool below = unknown_08 < -20;
    return below;
}

// GLOBAL: GAMEMD 0xA83CD9 / 0xA83CDA / 0xA83CDB
extern char DAT_00A83CD9;
extern char DAT_00A83CDA;
extern char DAT_00A83CDB;

// FUNCTION: GAMEMD 0x4E8120
void FUN_004E8120()
{
    DAT_00A83CD9 = 0;
    DAT_00A83CDA = 0;
    DAT_00A83CDB = 0;
}

struct Obj_004F3AB0
{
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5(char value);  // slot 5
    char Pad_04[5];
    char unknown_09;
    // FUNCTION: GAMEMD 0x4F3AB0
    void Set(char value);
};
GG_STATIC_ASSERT(offsetof(Obj_004F3AB0, unknown_09) == 0x09);

// FUNCTION: GAMEMD 0x4F3AB0
// Stores the +0x09 byte and notifies through slot 5 when it changed.
void Obj_004F3AB0::Set(char value)
{
    if (value != unknown_09) {
        unknown_09 = value;
        vf_5(value);
    }
}

// FUNCTION: GAMEMD 0x4F4DA0
// Clears the low three bits of each of count*3 bytes (count in EDX).
void __fastcall FUN_004F4DA0(unsigned char* bytes, unsigned int count)
{
    for (unsigned int n = count * 3; n > 0; n--) {
        *bytes &= 0xF8;
        bytes++;
    }
}

// GLOBAL: GAMEMD 0xA9FF80 / 0xA9FFA8 -- two-word values copied from the first to the second.
extern int DAT_00A9FF80[2];
extern int DAT_00A9FFA8[2];

// FUNCTION: GAMEMD 0x53CA50
void FUN_0053CA50()
{
    DAT_00A9FFA8[0] = DAT_00A9FF80[0];
    DAT_00A9FFA8[1] = DAT_00A9FF80[1];
}

// A six-byte value copied as a dword and a word.
struct Bytes6_0053EDC0
{
    unsigned char Bytes[6];
};

struct Obj_0053EDC0
{
    char           Pad_00[4];
    Bytes6_0053EDC0 unknown_04;
    // FUNCTION: GAMEMD 0x53EDC0
    void Get(Bytes6_0053EDC0* out);
    // FUNCTION: GAMEMD 0x53EDE0
    void Set(const Bytes6_0053EDC0* in);
};

// FUNCTION: GAMEMD 0x53EDC0
void Obj_0053EDC0::Get(Bytes6_0053EDC0* out)
{
    *out = unknown_04;
}

// FUNCTION: GAMEMD 0x53EDE0
void Obj_0053EDC0::Set(const Bytes6_0053EDC0* in)
{
    unknown_04 = *in;
}

// GLOBAL: GAMEMD 0x828140
extern int DAT_00828140;

struct Obj_0053F200
{
    short unknown_00;
    // FUNCTION: GAMEMD 0x53F200
    void SetIfMode2(short value);
};

// FUNCTION: GAMEMD 0x53F200
void Obj_0053F200::SetIfMode2(short value)
{
    if (DAT_00828140 == 2)
        unknown_00 = value;
}

struct Obj_00424CB0
{
    char Pad_00[0xC8];
    char* unknown_C8;
    int   unknown_CC;
    // FUNCTION: GAMEMD 0x424CB0
    int Kind();
};
GG_STATIC_ASSERT(offsetof(Obj_00424CB0, unknown_CC) == 0xCC);

// FUNCTION: GAMEMD 0x424CB0
// 2 when +0xCC is set, else the +0x364 value of the +0xC8 object, or 3 without one.
int Obj_00424CB0::Kind()
{
    if (unknown_CC)
        return 2;
    if (unknown_C8)
        return *(int*)(unknown_C8 + 0x364);
    return 3;
}

struct Obj_00465930Item
{
    char Pad_00[0xEE4];
    int  unknown_EE4;
};
GG_STATIC_ASSERT(offsetof(Obj_00465930Item, unknown_EE4) == 0xEE4);

struct Obj_00465930
{
    void*             Vtbl;
    Obj_00465930Item** Items;       // +0x04
    char              Pad_08[8];
    int               Count;        // +0x10
    // FUNCTION: GAMEMD 0x465930
    int MaxValue();
};
GG_STATIC_ASSERT(offsetof(Obj_00465930, Count) == 0x10);

// FUNCTION: GAMEMD 0x465930
// Largest +0xEE4 value over the items (0 when empty or all non-positive).
int Obj_00465930::MaxValue()
{
    int best = 0;
    for (int i = 0; i < Count; i++) {
        if (Items[i]->unknown_EE4 > best)
            best = Items[i]->unknown_EE4;
    }
    return best;
}

struct Obj_00487130
{
    char         Pad_00[0x78];
    unsigned int unknown_78;
    // FUNCTION: GAMEMD 0x487130
    void ClearBit(int bit);
};

// FUNCTION: GAMEMD 0x487130
void Obj_00487130::ClearBit(int bit)
{
    unknown_78 &= ~(1 << bit);
}

// FUNCTION: GAMEMD 0x49B430
// ASCII hex digit for 0..15, else 0.
char __fastcall FUN_0049B430(int value)
{
    if (value >= 0 && value <= 15) {
        if (value < 10)
            return (char)(value + '0');
        return (char)(value + '7');
    }
    return 0;
}

struct Obj_0049FB40
{
    void* Vtbl;
    int*  Items;        // +0x04
    int   Capacity;     // +0x08
    char  Pad_0C[4];
    int   Count;        // +0x10
    // FUNCTION: GAMEMD 0x49FB40
    void ZeroAndEmpty();
};
GG_STATIC_ASSERT(offsetof(Obj_0049FB40, Count) == 0x10);

// FUNCTION: GAMEMD 0x49FB40
// Zeroes every slot of the array and resets the count.
void Obj_0049FB40::ZeroAndEmpty()
{
    for (int i = 0; i < Capacity; i++)
        Items[i] = 0;
    Count = 0;
}

struct Pair_0049FF40
{
    int First;      // +0x00
    int Second;     // +0x04
};

// FUNCTION: GAMEMD 0x49FF40
// Inequality of two pairs (second fields compared first; second pair in EDX).
int __fastcall FUN_0049FF40(const Pair_0049FF40* a, const Pair_0049FF40* b)
{
    if (a->Second == b->Second && a->First == b->First)
        return 0;
    return 1;
}

// FUNCTION: GAMEMD 0x49FF60
// Equality of two pairs.
int __fastcall FUN_0049FF60(const Pair_0049FF40* a, const Pair_0049FF40* b)
{
    if (a->Second == b->Second && a->First == b->First)
        return 1;
    return 0;
}

struct Obj_004C9680
{
    char  Pad_00[0x14];
    short unknown_14;
    // FUNCTION: GAMEMD 0x4C9680
    void SetHigh(int value);
};

// FUNCTION: GAMEMD 0x4C9680
// Stores `value` (capped at 127) in the high byte of the +0x14 word.
void Obj_004C9680::SetHigh(int value)
{
    if (value >= 127)
        value = 127;
    unknown_14 = (short)(value << 8);
}

struct Obj_004E0080
{
    char Pad_00[0x68F];
    char unknown_68F;
    char unknown_690;
    char unknown_691;
    // FUNCTION: GAMEMD 0x4E0080
    int AnySet();
};
GG_STATIC_ASSERT(offsetof(Obj_004E0080, unknown_691) == 0x691);

// FUNCTION: GAMEMD 0x4E0080
int Obj_004E0080::AnySet()
{
    if (unknown_68F || unknown_690 || unknown_691)
        return 1;
    return 0;
}

struct Obj_0048BAD0
{
    char Pad_00[0x44];
    int  unknown_44;
    int  unknown_48;
    int  unknown_4C;
    int  unknown_50;
    int  unknown_54;
    // FUNCTION: GAMEMD 0x48BAD0
    void Set(int a, int b, int c, int d, int e);
};
GG_STATIC_ASSERT(offsetof(Obj_0048BAD0, unknown_54) == 0x54);

// FUNCTION: GAMEMD 0x48BAD0
void Obj_0048BAD0::Set(int a, int b, int c, int d, int e)
{
    unknown_44 = a;
    unknown_48 = b;
    unknown_4C = c;
    unknown_50 = d;
    unknown_54 = e;
}
