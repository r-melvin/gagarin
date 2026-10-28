// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Small leaf routines read from retail gamemd.exe v1.001 that touch only their arguments and
// a few globals (named by retail address, typed only as far as the instructions show).
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern int DAT_00ABC1D4;
extern int DAT_00ABBEC0;
extern int DAT_00ABED04;
extern int DAT_00ABED08;
extern int DAT_00B45B68;
extern int DAT_00A8ED84;
struct Rec28_0082D028 { int f00; int f04; int unknown_08; int f0C; int unknown_10[3]; };
extern Rec28_0082D028 DAT_0082D028[];

// FUNCTION: GAMEMD 0x005AC1C0
// Map a value inside one of two ranges to a combined slot index; 0 when in neither.
int FUN_005AC1C0(int value)
{
    int first = DAT_00ABC1D4;
    if (value >= first && value < first + 0x65) {
        return value - first;
    }
    int second = DAT_00ABBEC0;
    if (value >= second && value < second + 8) {
        return value - second + 0x65;
    }
    return 0;
}

struct CellXY_005AC230 {
    short X;
    short Y;
};

// FUNCTION: GAMEMD 0x005AC230
// Whether the cell lies inside the diamond bounds held in two globals.
bool FUN_005AC230(const CellXY_005AC230* cell)
{
    int x = cell->X;
    int y = cell->Y;
    int sum = y + x;
    int limit = DAT_00ABED04;
    if (sum > limit && x - y < limit && y - x < limit && sum <= DAT_00ABED08) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x005BF520
int FUN_005BF520()
{
    int positive = DAT_00B45B68 > 0;
    return positive;
}

struct Obj_005B3A20 {
    unsigned char unknown_00[0xC8];
    int Start;                      // +0xC8
    unsigned char unknown_CC[4];
    int Duration;                   // +0xD0
    int FUN_005B3A20();
};
GG_STATIC_ASSERT(offsetof(Obj_005B3A20, Start) == 0xC8);
GG_STATIC_ASSERT(offsetof(Obj_005B3A20, Duration) == 0xD0);

// FUNCTION: GAMEMD 0x005B3A20
// Frames remaining of a timer started at Start (the full duration if unstarted, 0 if expired).
int Obj_005B3A20::FUN_005B3A20()
{
    int start = Start;
    int duration = Duration;
    if (start == -1) {
        return duration;
    }
    int elapsed = DAT_00A8ED84 - start;
    if (elapsed < duration) {
        return duration - elapsed;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x005BDB90
// Table value for the entry, preferring the alternate (+0xC) one when asked and present.
int __stdcall FUN_005BDB90(int index, bool alternate)
{
    const Rec28_0082D028* rec = &DAT_0082D028[index];
    if (alternate) {
        int value = rec->f0C;
        if (value != -1) {
            return value;
        }
    }
    return rec->f00;
}

struct Obj_005BDBC0 {
    unsigned char unknown_00[0x5568];
    int Base;                       // +0x5568
    int FUN_005BDBC0(int index, bool alternate);
};
GG_STATIC_ASSERT(offsetof(Obj_005BDBC0, Base) == 0x5568);

// FUNCTION: GAMEMD 0x005BDBC0
int Obj_005BDBC0::FUN_005BDBC0(int index, bool alternate)
{
    const Rec28_0082D028* rec = &DAT_0082D028[index];
    int value;
    if (alternate) {
        value = rec->f0C;
        if (value == -1) {
            value = rec->f00;
        }
    } else {
        value = rec->f00;
    }
    return Base + value;
}

struct Node_005B4020 {
    Node_005B4020* Low;             // +0x00
    Node_005B4020* High;            // +0x04
    int Key;                        // +0x08
    int Flag;                       // +0x0C
};
GG_STATIC_ASSERT(offsetof(Node_005B4020, Key) == 0x08);
GG_STATIC_ASSERT(offsetof(Node_005B4020, Flag) == 0x0C);

// FUNCTION: GAMEMD 0x005B4020
// Find the node holding the key whose flag is set.
Node_005B4020* FUN_005B4020(int key, Node_005B4020* root)
{
    Node_005B4020* node = root;
    while (node) {
        int current = node->Key;
        if (current == key && node->Flag != 0) {
            return node;
        }
        if (current < key) {
            node = node->High;
        } else {
            node = node->Low;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x005B4050
// As above, and clear the found node's flag.
Node_005B4020* FUN_005B4050(int key, Node_005B4020* root)
{
    Node_005B4020* node = root;
    while (node) {
        int current = node->Key;
        if (current == key && node->Flag != 0) {
            node->Flag = 0;
            break;
        }
        if (current < key) {
            node = node->High;
        } else {
            node = node->Low;
        }
    }
    return node;
}

struct Obj_005980A0 {
    unsigned char Byte00;           // +0x00
    unsigned char unknown_01[7];
    int Field08;                    // +0x08
    int Field0C;                    // +0x0C
    int Field10;                    // +0x10
    Obj_005980A0* FUN_005980A0(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_005980A0, Field08) == 0x08);
GG_STATIC_ASSERT(offsetof(Obj_005980A0, Field10) == 0x10);

// FUNCTION: GAMEMD 0x005980A0
Obj_005980A0* Obj_005980A0::FUN_005980A0(int value)
{
    Field08 = 0;
    Byte00 = 0;
    Field0C = 0;
    Field10 = value;
    return this;
}

struct Obj_005A99F0 {
    int A;
    int B;
    int C;
    int D;
    int E;
    Obj_005A99F0* FUN_005A99F0(const Obj_005A99F0* other);
};

// FUNCTION: GAMEMD 0x005A99F0
// Copy the 20-byte value, field by field.
Obj_005A99F0* Obj_005A99F0::FUN_005A99F0(const Obj_005A99F0* other)
{
    A = other->A;
    B = other->B;
    C = other->C;
    D = other->D;
    E = other->E;
    return this;
}

struct Block48_005AFC00 {
    int Words[12];
};

// FUNCTION: GAMEMD 0x005AFC00
// Copy a 48-byte block.
Block48_005AFC00* FUN_005AFC00(Block48_005AFC00* dst, const Block48_005AFC00* src)
{
    *dst = *src;
    return dst;
}

struct Target_005D4410 {
    unsigned char unknown_00[0x34];
    int Field34;                    // +0x34
};

struct Obj_005D4410 {
    unsigned char unknown_00[0x19];
    unsigned char Active;           // +0x19
    unsigned char unknown_1A[0x0A];
    Target_005D4410* Target;        // +0x24
    void FUN_005D4410(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_005D4410, Active) == 0x19);
GG_STATIC_ASSERT(offsetof(Obj_005D4410, Target) == 0x24);

// FUNCTION: GAMEMD 0x005D4410
void Obj_005D4410::FUN_005D4410(int value)
{
    if (Active) {
        Target->Field34 = value;
    }
}

struct Obj_005FB310 {
    unsigned char unknown_00[0x38];
    float Scale;                    // +0x38
    int FUN_005FB310(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_005FB310, Scale) == 0x38);

// FUNCTION: GAMEMD 0x005FB310
int Obj_005FB310::FUN_005FB310(int value)
{
    return (int)(value * Scale);
}

struct Obj_005AC340 {
    unsigned char unknown_00[8];
    void* Buffer;                   // +0x08
    Obj_005AC340* FUN_005AC340(unsigned int flags);
};

// FUNCTION: GAMEMD 0x005AC340
// Scalar deleting destructor: free the buffer, then the object itself when asked.
Obj_005AC340* Obj_005AC340::FUN_005AC340(unsigned int flags)
{
    operator delete(Buffer);
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

struct House_005D7550 {
    unsigned char unknown_00[0x1605C];
    int Field1605C;                 // +0x1605C
};
GG_STATIC_ASSERT(offsetof(House_005D7550, Field1605C) == 0x1605C);
extern House_005D7550** DAT_00A8022C;

// FUNCTION: GAMEMD 0x005D7550
int __stdcall FUN_005D7550(int index)
{
    return DAT_00A8022C[index]->Field1605C;
}

#pragma pack(push, 1)
struct Item_005D8CE0 {
    unsigned char unknown_00[0x6B];
    int Key;                        // +0x6B
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Item_005D8CE0, Key) == 0x6B);
extern int DAT_00A8DA84;
extern Item_005D8CE0** DAT_00A8DA78;

struct Obj_005D8CE0 {
    unsigned char unknown_00[8];
    int Key;                        // +0x08
    int FUN_005D8CE0();
};
GG_STATIC_ASSERT(offsetof(Obj_005D8CE0, Key) == 0x08);

// FUNCTION: GAMEMD 0x005D8CE0
// Count the list entries whose key equals this object's key.
int Obj_005D8CE0::FUN_005D8CE0()
{
    int count = 0;
    for (int i = 0; i < DAT_00A8DA84; i++) {
        if (DAT_00A8DA78[i]->Key == Key) {
            count++;
        }
    }
    return count;
}
