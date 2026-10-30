// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each body read from the entry-bounded retail function in gamemd.exe v1.001.
//   Owners are placeholders (Obj_<ADDR>) declaring only the fields touched,
//   with offset asserts.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "header_init_shapes.h"

// A circular list whose sentinel sits at +0x0C; each node holds a key at +0x14
// and a payload pointer at +0x18.
struct Node_00401BB0
{
    Node_00401BB0* Next;   // +0x00
    char unknown_04[0x10];
    int Key;               // +0x14
    void* Payload;         // +0x18
};
struct Obj_00401BB0
{
    char unknown_00[0x0C];
    Node_00401BB0 Sentinel;   // +0x000C
    // FUNCTION: GAMEMD 0x401BB0
    Node_00401BB0* __fastcall FUN_00401BB0(int key);
};
GG_STATIC_ASSERT(offsetof(Node_00401BB0, Key) == 0x14);
GG_STATIC_ASSERT(offsetof(Node_00401BB0, Payload) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_00401BB0, Sentinel) == 0x0C);

// FUNCTION: GAMEMD 0x401BB0
// First node with the given key whose payload is set, or null.
Node_00401BB0* __fastcall Obj_00401BB0::FUN_00401BB0(int key)
{
    Node_00401BB0* head = &Sentinel;
    for (Node_00401BB0* node = Sentinel.Next; node != head; node = node->Next) {
        if (node->Key == key && node->Payload != 0) {
            return node;
        }
    }
    return 0;
}

// GLOBAL: GAMEMD 0x87E2A0 -- selects whether the per-object table is consulted.
extern int DAT_0087E2A0;
// GLOBAL: GAMEMD 0x816204 -- fallback record when the selector is clear.
extern char DAT_00816204[];
// GLOBAL: GAMEMD 0x816210 -- fallback record when the object has no table.
extern char DAT_00816210[];

struct Obj_00406340
{
    char unknown_00[0x24];
    char* unknown_24;   // +0x0024
    // FUNCTION: GAMEMD 0x406340
    char* FUN_00406340();
};
GG_STATIC_ASSERT(offsetof(Obj_00406340, unknown_24) == 0x24);

// FUNCTION: GAMEMD 0x406340
// The record at +0x6C of the table at +0x24, or one of two fallback records.
char* Obj_00406340::FUN_00406340()
{
    if (!DAT_0087E2A0) {
        return DAT_00816204;
    }
    if (!unknown_24) {
        return DAT_00816210;
    }
    return unknown_24 + 0x6C;
}

// An eight-byte key: a dword and two words.
struct Key_0042E640
{
    unsigned long unknown_00;    // +0x0000
    unsigned short unknown_04;   // +0x0004
    unsigned short unknown_06;   // +0x0006
    // FUNCTION: GAMEMD 0x42E640
    bool operator==(const Key_0042E640& other) const;
    // FUNCTION: GAMEMD 0x42E670
    bool operator!=(const Key_0042E640& other) const;
    // The equality test as retail inlines it into the inequality.
    int Same(const Key_0042E640& other) const
    {
        if (unknown_00 == other.unknown_00 && unknown_04 == other.unknown_04
            && unknown_06 == other.unknown_06) {
            return 1;
        }
        return 0;
    }
};
GG_STATIC_ASSERT(offsetof(Key_0042E640, unknown_06) == 0x06);
GG_STATIC_ASSERT(sizeof(Key_0042E640) == 8);

// FUNCTION: GAMEMD 0x42E640
// Field-wise equality.
bool Key_0042E640::operator==(const Key_0042E640& other) const
{
    return unknown_00 == other.unknown_00 && unknown_04 == other.unknown_04
        && unknown_06 == other.unknown_06;
}

// FUNCTION: GAMEMD 0x42E670
// The negation of the equality above.
bool Key_0042E640::operator!=(const Key_0042E640& other) const
{
    unsigned char same = Same(other);
    return !same;
}

// A bit stream cursor: byte pointer at +0x00, bit index at +0x04.
struct Obj_00433570
{
    unsigned char* unknown_00;   // +0x0000
    unsigned char unknown_04;    // +0x0004
    // FUNCTION: GAMEMD 0x433570
    bool FUN_00433570();
    // FUNCTION: GAMEMD 0x4335B0
    void __fastcall FUN_004335B0(unsigned char bit);
};
GG_STATIC_ASSERT(offsetof(Obj_00433570, unknown_04) == 4);

// FUNCTION: GAMEMD 0x433570
// Advance one bit and report whether it is set.
bool Obj_00433570::FUN_00433570()
{
    unknown_04++;
    if (unknown_04 == 8) {
        unknown_04 = 0;
        unknown_00++;
    }
    int mask = 1 << unknown_04;
    bool set = (*unknown_00 & mask) > 0;
    return set;
}

// FUNCTION: GAMEMD 0x4335B0
// Advance one bit (clearing the next byte on a wrap) and OR the bit in.
void __fastcall Obj_00433570::FUN_004335B0(unsigned char bit)
{
    unknown_04++;
    if (unknown_04 == 8) {
        unknown_04 = 0;
        unknown_00++;
        *unknown_00 = 0;
    }
    *unknown_00 |= (unsigned char)(bit << unknown_04);
}

// FUNCTION: GAMEMD 0x46F5E0
// Map a small index to a table base: 0 and 1 give two consecutive values, anything else -1.
int __fastcall FUN_0046F5E0(int index)
{
    if (index == 0) {
        return 0x411;
    }
    return index != 1 ? -1 : 0x412;
}

// FUNCTION: GAMEMD 0x49B450
// Value of one hexadecimal digit, or 0 for any other character.
int __fastcall FUN_0049B450(char c)
{
    if (c <= '9' && c >= '0') {
        return c - '0';
    }
    if (c <= 'f' && c >= 'a') {
        return c - 'W';
    }
    if (c <= 'F' && c >= 'A') {
        return c - '7';
    }
    return 0;
}

// Window starts held in globals; an object's value at +0x38 is tested against
// short runs beginning at each.
// GLOBAL: GAMEMD 0xABC1D8
extern int DAT_00ABC1D8;
// GLOBAL: GAMEMD 0xAA1058
extern int DAT_00AA1058;

struct Obj_004863A0
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x4863A0
    bool FUN_004863A0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004863A0, unknown_38) == 0x38);

// FUNCTION: GAMEMD 0x4863A0
// True when the value lies in either of two runs (0x14 and 0xC long).
bool Obj_004863A0::FUN_004863A0() const
{
    int v = unknown_38;
    if ((v >= DAT_00ABC1D8 && v < DAT_00ABC1D8 + 0x14)
        || (v >= DAT_00AA1058 && v < DAT_00AA1058 + 0xC)) {
        return true;
    }
    return false;
}

// Run starts held in globals for the two range tests below.
// GLOBAL: GAMEMD 0xABAD20
extern int DAT_00ABAD20;
// GLOBAL: GAMEMD 0xABC1D4
extern int DAT_00ABC1D4;
// GLOBAL: GAMEMD 0xAA10AC
extern int DAT_00AA10AC;
// GLOBAL: GAMEMD 0xABAD28
extern int DAT_00ABAD28;
// GLOBAL: GAMEMD 0xAA0738
extern int DAT_00AA0738;
// GLOBAL: GAMEMD 0xAA073C
extern int DAT_00AA073C;
// GLOBAL: GAMEMD 0xABB110
extern int DAT_00ABB110;
// GLOBAL: GAMEMD 0xAA1050
extern int DAT_00AA1050;
// GLOBAL: GAMEMD 0xAA10A0
extern int DAT_00AA10A0;

struct Obj_004865D0
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x4865D0
    bool FUN_004865D0() const;
    // FUNCTION: GAMEMD 0x486690
    bool FUN_00486690() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004865D0, unknown_38) == 0x38);

// FUNCTION: GAMEMD 0x4865D0
// True when the value at +0x38 lies in any of six runs.
bool Obj_004865D0::FUN_004865D0() const
{
    int v = unknown_38;
    if (v >= DAT_00ABAD28 && v < DAT_00ABAD28 + 0x2A) {
        return true;
    }
    if ((v >= DAT_00AA0738 && v < DAT_00AA0738 + 0xE)
        || (v >= DAT_00AA073C && v < DAT_00AA073C + 4)
        || (v >= DAT_00ABB110 && v < DAT_00ABB110 + 4)
        || (v >= DAT_00AA1050 && v < DAT_00AA1050 + 4)
        || (v >= DAT_00AA10A0 && v < DAT_00AA10A0 + 4)) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x486690
// True when the value at +0x38 lies in any of three runs.
bool Obj_004865D0::FUN_00486690() const
{
    int v = unknown_38;
    if ((v >= DAT_00ABAD20 && v < DAT_00ABAD20 + 0xB)
        || (v >= DAT_00ABC1D4 && v < DAT_00ABC1D4 + 0x18)
        || (v >= DAT_00AA10AC && v < DAT_00AA10AC + 0x42)) {
        return true;
    }
    return false;
}

// Four counters at +0x14..+0x20.
struct Obj_0048BAA0
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
    int unknown_18;   // +0x0018
    int unknown_1C;   // +0x001C
    int unknown_20;   // +0x0020
    // FUNCTION: GAMEMD 0x48BAA0
    void FUN_0048BAA0(bool clear);
};
GG_STATIC_ASSERT(offsetof(Obj_0048BAA0, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_0048BAA0, unknown_20) == 0x20);

// FUNCTION: GAMEMD 0x48BAA0
// Clear all four, or restart from the value at +0x1C.
void Obj_0048BAA0::FUN_0048BAA0(bool clear)
{
    if (clear) {
        unknown_14 = 0;
        unknown_18 = 0;
        unknown_1C = 0;
        unknown_20 = 0;
    } else {
        unknown_14 = unknown_1C;
        unknown_18 = 1;
        unknown_20 = unknown_1C;
    }
}

// Three colour slots (+0x10, +0x30, +0x50) each followed by an opaque alpha word.
struct Obj_004A35A0
{
    char unknown_00[0x10];
    unsigned long unknown_10;   // +0x0010
    unsigned long unknown_14;   // +0x0014
    char unknown_18[0x18];
    unsigned long unknown_30;   // +0x0030
    unsigned long unknown_34;   // +0x0034
    char unknown_38[0x18];
    unsigned long unknown_50;   // +0x0050
    unsigned long unknown_54;   // +0x0054
    // FUNCTION: GAMEMD 0x4A35A0
    void FUN_004A35A0(unsigned long r, unsigned long g, unsigned long b);
};
GG_STATIC_ASSERT(offsetof(Obj_004A35A0, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_004A35A0, unknown_54) == 0x54);

// FUNCTION: GAMEMD 0x4A35A0
// Set the three colour slots to one opaque RGB colour.
void Obj_004A35A0::FUN_004A35A0(unsigned long r, unsigned long g, unsigned long b)
{
    unsigned long color = (((r | 0xFFFFFF00) << 8 | (g & 0xFF)) << 8) | (b & 0xFF);
    unknown_50 = color;
    unknown_30 = color;
    unknown_10 = color;
    unknown_54 = 0xFF000000;
    unknown_34 = 0xFF000000;
    unknown_14 = 0xFF000000;
}

// GLOBAL: GAMEMD 0xA8ED84 -- the frame counter.
extern int DAT_00A8ED84;
// GLOBAL: GAMEMD 0x8209D8 -- the frame the counter below last ran in.
extern int DAT_008209D8;
// GLOBAL: GAMEMD 0x8A39FC -- per-frame call counter.
extern unsigned char DAT_008A39FC;

struct Obj_004C6570
{
    // FUNCTION: GAMEMD 0x4C6570
    unsigned char FUN_004C6570();
};

// FUNCTION: GAMEMD 0x4C6570
// Returns how many times this has run in the current frame, restarting the
// count whenever the frame differs from the recorded one. This is not used.
unsigned char Obj_004C6570::FUN_004C6570()
{
    if (DAT_00A8ED84 != DAT_008209D8) {
        DAT_008A39FC = 0;
    }
    return DAT_008A39FC++;
}

// Two shorts packed into a dword.
struct Pair16_004D28D0
{
    short unknown_00;
    short unknown_02;
};
struct Obj_004D28D0
{
    char unknown_00[0x34];
    int unknown_34;   // +0x0034
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x4D28D0
    Pair16_004D28D0 FUN_004D28D0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004D28D0, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(Obj_004D28D0, unknown_38) == 0x38);

// FUNCTION: GAMEMD 0x4D28D0
// The two coordinates at +0x34 / +0x38 scaled down by 256 into a short pair.
Pair16_004D28D0 Obj_004D28D0::FUN_004D28D0() const
{
    Pair16_004D28D0 result;
    result.unknown_00 = (short)(unknown_34 / 256);
    result.unknown_02 = (short)(unknown_38 / 256);
    return result;
}

// Bit-array helpers: the array pointer arrives in ECX and the bit index in EDX.
// FUNCTION: GAMEMD 0x54A900
// Set or clear one bit.
void __fastcall FUN_0054A900(unsigned char* bits, int index, int value)
{
    unsigned char mask = (unsigned char)(1 << (index % 8));
    if (value) {
        bits[index / 8] |= mask;
    } else {
        bits[index / 8] &= ~mask;
    }
}

// FUNCTION: GAMEMD 0x54A950
// Read one bit.
int __fastcall FUN_0054A950(unsigned char* bits, int index)
{
    unsigned char mask = (unsigned char)(1 << (index % 8));
    return (bits[index / 8] & mask) != 0;
}

// FUNCTION: GAMEMD 0x54A990
// Index of the first set bit, skipping whole zero bytes.
int __fastcall FUN_0054A990(unsigned char* bits)
{
    int byteIndex = 0;
    while (*bits == 0) {
        byteIndex++;
        bits++;
    }
    int bit;
    for (bit = 0; bit < 8; bit++) {
        unsigned char mask = (unsigned char)(1 << (bit % 8));
        if (bits[bit / 8] & mask) {
            break;
        }
    }
    return byteIndex * 8 + bit;
}

// FUNCTION: GAMEMD 0x54A9E0
// Index of the first clear bit, skipping whole 0xFF bytes.
int __fastcall FUN_0054A9E0(unsigned char* bits)
{
    int byteIndex = 0;
    while (*bits == 0xFF) {
        byteIndex++;
        bits++;
    }
    int bit;
    for (bit = 0; bit < 8; bit++) {
        unsigned char mask = (unsigned char)(1 << (bit % 8));
        if (!(bits[bit / 8] & mask)) {
            break;
        }
    }
    return byteIndex * 8 + bit;
}

// Five dwords of the map-math header group (a count at 0xABC554 and a four-int
// block at 0xAA1060) cleared in one go.
// GLOBAL: GAMEMD 0xABC554
extern int DAT_00ABC554;
// GLOBAL: GAMEMD 0xAA1060
extern int DAT_00AA1060;
// GLOBAL: GAMEMD 0xAA1064
extern int DAT_00AA1064;
// GLOBAL: GAMEMD 0xAA1068
extern int DAT_00AA1068;
// GLOBAL: GAMEMD 0xAA106C
extern int DAT_00AA106C;

// FUNCTION: GAMEMD 0x549B30
// Zero the count and the four-int block.
void FUN_00549B30()
{
    DAT_00ABC554 = 0;
    DAT_00AA1060 = 0;
    DAT_00AA1064 = 0;
    DAT_00AA1068 = 0;
    DAT_00AA106C = 0;
}

// A chained record: the next link is at +0x2BC, a table of short-pair pointers at +0x2A8,
// a link count at +0x2F0 and a cleared slot at +0x308.
struct Obj_00544E00
{
    char unknown_00[0x2A8];
    short** unknown_2A8;        // +0x02A8
    char unknown_2AC[0x10];
    Obj_00544E00* unknown_2BC;  // +0x02BC
    char unknown_2C0[0x8];
    int unknown_2C8;            // +0x02C8
    char unknown_2CC[0x24];
    int unknown_2F0;            // +0x02F0
    char unknown_2F4[0x14];
    int unknown_308;            // +0x0308
    // FUNCTION: GAMEMD 0x544E00
    Obj_00544E00* FUN_00544E00(int steps);
    // FUNCTION: GAMEMD 0x549DD0
    void FUN_00549DD0(int link, int unused);
    // FUNCTION: GAMEMD 0x549E20
    short FUN_00549E20(int row, int column, bool flag);
};
GG_STATIC_ASSERT(offsetof(Obj_00544E00, unknown_2A8) == 0x2A8);
GG_STATIC_ASSERT(offsetof(Obj_00544E00, unknown_2BC) == 0x2BC);
GG_STATIC_ASSERT(offsetof(Obj_00544E00, unknown_2C8) == 0x2C8);
GG_STATIC_ASSERT(offsetof(Obj_00544E00, unknown_2F0) == 0x2F0);
GG_STATIC_ASSERT(offsetof(Obj_00544E00, unknown_308) == 0x308);

// FUNCTION: GAMEMD 0x544E00
// PARTIAL: 89.5% -- same instructions; retail pops before `mov eax,ecx`.
// Follow the chain a number of steps, wrapping the count by the link count.
Obj_00544E00* Obj_00544E00::FUN_00544E00(int steps)
{
    int count = unknown_2F0;
    int n = steps;
    if (steps > count - 1) {
        n = steps % count;
    }
    Obj_00544E00* node = this;
    for (; n != 0; n--) {
        node = node->unknown_2BC;
    }
    return node;
}

// GLOBAL: GAMEMD 0x8B4154 -- table of link objects.
extern int* DAT_008B4154;

// FUNCTION: GAMEMD 0x549DD0
// Forget a link: clear the chain pointer and the table index when they refer to it.
void Obj_00544E00::FUN_00549DD0(int link, int unused)
{
    if ((int)unknown_2BC == link) {
        unknown_2BC = 0;
    }
    if (unknown_2C8 != -1 && DAT_008B4154[unknown_2C8] == link) {
        unknown_2C8 = -1;
    }
}

// FUNCTION: GAMEMD 0x549E20
// One entry of the short table: row pointer, then two shorts per column.
short Obj_00544E00::FUN_00549E20(int row, int column, bool flag)
{
    short* line = unknown_2A8[row];
    return line[column * 2 + (flag != 0)];
}

// GLOBAL: GAMEMD 0xA8F2CC
extern int DAT_00A8F2CC;

struct Obj_00524760
{
    // FUNCTION: GAMEMD 0x524760
    CoordStruct FUN_00524760();
};

// FUNCTION: GAMEMD 0x524760
// A coordinate at a fixed column and row, raised to twice the level in DAT_00A8F2CC.
// This is not used.
CoordStruct Obj_00524760::FUN_00524760()
{
    return HeaderCoordInit(0x55, 0x55, DAT_00A8F2CC * 2);
}

// GLOBAL: GAMEMD 0xA8ED38 -- number of chain heads.
extern int DAT_00A8ED38;
// GLOBAL: GAMEMD 0xA8ED2C -- the chain heads.
extern Obj_00544E00** DAT_00A8ED2C;

// FUNCTION: GAMEMD 0x547110
// Clear the +0x308 slot of every record on every chain.
void FUN_00547110()
{
    for (int i = 0; i < DAT_00A8ED38; i++) {
        Obj_00544E00* node = DAT_00A8ED2C[i];
        if (node != 0) {
            do {
                node->unknown_308 = 0;
                node = node->unknown_2BC;
            } while (node != 0);
        }
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8A39FC
unsigned char DAT_008A39FC;
// GLOBAL: GAMEMD 0xA8ED2C
Obj_00544E00** DAT_00A8ED2C;
// GLOBAL: GAMEMD 0xA8ED38
int DAT_00A8ED38;
// GLOBAL: GAMEMD 0xAA0738
int DAT_00AA0738;
// GLOBAL: GAMEMD 0xAA073C
int DAT_00AA073C;
// GLOBAL: GAMEMD 0xAA1050
int DAT_00AA1050;
// GLOBAL: GAMEMD 0xAA1058
int DAT_00AA1058;
// GLOBAL: GAMEMD 0xAA1060
int DAT_00AA1060;
// GLOBAL: GAMEMD 0xAA1064
int DAT_00AA1064;
// GLOBAL: GAMEMD 0xAA1068
int DAT_00AA1068;
// GLOBAL: GAMEMD 0xAA106C
int DAT_00AA106C;
// GLOBAL: GAMEMD 0xAA10A0
int DAT_00AA10A0;
// GLOBAL: GAMEMD 0xAA10AC
int DAT_00AA10AC;
// GLOBAL: GAMEMD 0xABAD20
int DAT_00ABAD20;
// GLOBAL: GAMEMD 0xABAD28
int DAT_00ABAD28;
// GLOBAL: GAMEMD 0xABB110
int DAT_00ABB110;
// GLOBAL: GAMEMD 0xABC1D4
int DAT_00ABC1D4;
// GLOBAL: GAMEMD 0xABC1D8
int DAT_00ABC1D8;
// GLOBAL: GAMEMD 0xABC554
int DAT_00ABC554;
// GLOBAL: GAMEMD 0x8209D8
int DAT_008209D8 = -1;
// GLOBAL: GAMEMD 0x87E2A0
int DAT_0087E2A0;
// END defined globals
