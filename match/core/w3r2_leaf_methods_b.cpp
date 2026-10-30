// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Small leaf bodies from
//   the 0x6E0000-0x724000 range; the receivers are placeholder views of the members touched.
//
// Address index: 0x6EC220 0x70C250 0x71DD80 0x720440 0x7211E0 0x721290
//                0x723CA0 0x723CE0

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "vector_class_operations.h"

// A link up a chain of owners (the link lives at +0x54 here and at +0x5D8 in the owner).
struct Owned_006EC220
{
    unsigned char unknown_00[0x54];
    struct Chain_006EC220* Owner;   // +0x54

    bool FUN_006EC220(Chain_006EC220* ancestor) const;
};
struct Chain_006EC220
{
    unsigned char unknown_00[0x5D8];
    Chain_006EC220* Parent;         // +0x5D8
};
GG_STATIC_ASSERT(offsetof(Owned_006EC220, Owner) == 0x54);
GG_STATIC_ASSERT(offsetof(Chain_006EC220, Parent) == 0x5D8);

// FUNCTION: GAMEMD 0x6EC220
// True when the given object is the owner or one of the owner's parents.
bool Owned_006EC220::FUN_006EC220(Chain_006EC220* ancestor) const
{
    for (Chain_006EC220* p = Owner; p; p = p->Parent) {
        if (p == ancestor) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x65AC40 (decl; reloc)
void __stdcall FUN_0065AC40(int a, int b, int c);


// LIBRARY: GAMEMD 0x7C8D20 -- CRT string compare (cdecl, two pointers).
extern "C" int __cdecl FUN_007C8D20(const char* a, const char* b);

struct Obj_0071DD80
{
    unsigned char unknown_00[0x24];
    char ID[1];                     // +0x24, name buffer
};
extern DynamicVectorClass<Obj_0071DD80*> DAT_00A8E318;

// FUNCTION: GAMEMD 0x71DD80
// Index of the global entry with the given name, or -1.
int __fastcall FUN_0071DD80(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_00A8E318.Count; ++i) {
            if (FUN_007C8D20(name, DAT_00A8E318.Items[i]->ID) == 0)
                return i;
        }
    }
    return -1;
}

// A record with a 0x290-byte tail of small state.
struct Record_00720440
{
    unsigned char Flag0;           // +0x000
    unsigned char unknown_001[0xFF];
    unsigned char Flag100;         // +0x100
    unsigned char unknown_101[0xFF];
    unsigned short Word200;        // +0x200
    unsigned char unknown_202[0x7E];
    int Field280;                  // +0x280
    int Field284;                  // +0x284
    unsigned char Active;          // +0x288
    unsigned char Flag289;         // +0x289
    unsigned char Flag28A;         // +0x28A
    unsigned char unknown_28B;
    int Field28C;                  // +0x28C

    Record_00720440* FUN_00720440();
};
GG_STATIC_ASSERT(offsetof(Record_00720440, Word200) == 0x200);
GG_STATIC_ASSERT(offsetof(Record_00720440, Field280) == 0x280);
GG_STATIC_ASSERT(offsetof(Record_00720440, Active) == 0x288);
GG_STATIC_ASSERT(offsetof(Record_00720440, Field28C) == 0x28C);

// FUNCTION: GAMEMD 0x720440
// Clears the record, marking it active.
Record_00720440* Record_00720440::FUN_00720440()
{
    Field280 = 0;
    Field284 = 0;
    Active = 1;
    Flag289 = 0;
    Flag28A = 0;
    Field28C = -1;
    Flag0 = 0;
    Flag100 = 0;
    Word200 = 0;
    return this;
}

// A list of the records above, held as a pointer array and a count.
struct RecordList_007211E0
{
    unsigned char unknown_00[0x18];
    Record_00720440** Items;   // +0x18
    unsigned char unknown_1C[8];
    unsigned int Count;        // +0x24

    bool FUN_007211E0(unsigned int index) const;
};
GG_STATIC_ASSERT(offsetof(RecordList_007211E0, Items) == 0x18);
GG_STATIC_ASSERT(offsetof(RecordList_007211E0, Count) == 0x24);

// FUNCTION: GAMEMD 0x7211E0
// Whether the record at the index (not the two reserved indices) is active.
bool RecordList_007211E0::FUN_007211E0(unsigned int index) const
{
    if (index == (unsigned int)-3 || index == (unsigned int)-2 || index >= Count) {
        return false;
    }
    bool r = Items[index]->Active != 0;
    return r;
}

struct Level_00721290
{
    unsigned char unknown_00[0xC];
    int Value;   // +0x0C

    void FUN_00721290(int value);
};
GG_STATIC_ASSERT(offsetof(Level_00721290, Value) == 0xC);

// FUNCTION: GAMEMD 0x721290
// Stores the value, capped at 255.
void Level_00721290::FUN_00721290(int value)
{
    if (value >= 0xFF) {
        value = 0xFF;
    }
    Value = value;
}

// A pair of dwords written as "%d,%d".
struct IntPair_00723CA0
{
    int First;    // +0x00
    int Second;   // +0x04

    void FUN_00723CA0(const char* text);
    int FUN_00723CE0(char* out) const;
};
GG_STATIC_ASSERT(offsetof(IntPair_00723CA0, Second) == 0x04);

// FUNCTION: GAMEMD 0x723CA0
// Reads the pair from "x,y" text.
void IntPair_00723CA0::FUN_00723CA0(const char* text)
{
    int x;
    int y;
    if (text) {
        sscanf(text, "%d,%d", &x, &y);
        First = x;
        Second = y;
    }
}

// FUNCTION: GAMEMD 0x723CE0
// Writes the pair as "x,y" and returns the length (zero when there is no buffer).
int IntPair_00723CA0::FUN_00723CE0(char* out) const
{
    if (out) {
        sprintf(out, "%d,%d", First, Second);
        return strlen(out);
    }
    return 0;
}
