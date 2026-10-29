// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: small routines read from retail gamemd.exe v1.001 by disassembly; owners that are
//   not yet named are free __fastcall functions pinned by their operand shapes.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "vector_class_operations.h"

struct Pair3 {
    int A;
    int B;
    int C;
    Pair3 operator-(const Pair3& o) const
    {
        Pair3 r;
        r.A = A - o.A;
        r.B = B - o.B;
        r.C = C - o.C;
        return r;
    }
};

struct Obj_006599C0 {
    char unknown_00[0x18];
    double Step;      // +0x18 length of one step
    char unknown_20[4];
    Pair3 From;       // +0x24
    Pair3 To;         // +0x30
    char unknown_3C[0x20];
    Pair3 Delta;      // +0x5C
    double Length;    // +0x68
    Pair3 Direction;  // +0x70
    char unknown_7C[0x10];
    int Steps;        // +0x8C
    // FUNCTION: GAMEMD 0x6599C0
    // Recomputes the delta between the two points and its length.
    void FUN_006599C0();
    // FUNCTION: GAMEMD 0x659E30
    // Recomputes the delta and its length, then the whole steps it spans and the per-step direction.
    void FUN_00659E30();
};
GG_STATIC_ASSERT(offsetof(Obj_006599C0, Step) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_006599C0, Direction) == 0x70);
GG_STATIC_ASSERT(offsetof(Obj_006599C0, Steps) == 0x8C);
GG_STATIC_ASSERT(offsetof(Obj_006599C0, From) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_006599C0, To) == 0x30);
GG_STATIC_ASSERT(offsetof(Obj_006599C0, Delta) == 0x5C);
GG_STATIC_ASSERT(offsetof(Obj_006599C0, Length) == 0x68);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- square root, __cdecl, the operand pushed as a double.
double __cdecl FUN_004CAC40(double value);

// FUNCTION: GAMEMD 0x6599C0
void Obj_006599C0::FUN_006599C0()
{
    Delta = To - From;
    Length = FUN_004CAC40((double)(Delta.A * Delta.A + Delta.B * Delta.B + Delta.C * Delta.C));
}

// FUNCTION: GAMEMD 0x659E30
void Obj_006599C0::FUN_00659E30()
{
    Delta = To - From;
    Length = FUN_004CAC40((double)(Delta.A * Delta.A + Delta.B * Delta.B + Delta.C * Delta.C));
    int steps = (int)(Length / Step);
    Pair3 direction;
    direction.A = Delta.A;
    direction.B = Delta.B;
    direction.C = Delta.C;
    Steps = steps;
    if (steps != 0) {
        direction.A /= steps;
        direction.B /= steps;
        direction.C /= steps;
    }
    Direction = direction;
}

struct Item16 {
    int A;
    int B;
    int C;
    int D;
};

struct Obj_00658910 {
    int unknown_00;
    Item16* Items;   // +0x04
    int Count;       // +0x08
    // FUNCTION: GAMEMD 0x658910
    // PARTIAL: 91% -- retail walks the second list through a pointer to the B word (lea ecx,[edx+4]); mine uses +8.
    // True when both lists hold the same number of entries and the first three words of each pair match.
    bool FUN_00658910(const Obj_00658910* other) const;
};
GG_STATIC_ASSERT(offsetof(Obj_00658910, Items) == 4);
GG_STATIC_ASSERT(offsetof(Obj_00658910, Count) == 8);

// FUNCTION: GAMEMD 0x658910
bool Obj_00658910::FUN_00658910(const Obj_00658910* other) const
{
    if (Count == other->Count) {
        for (int i = 0; i < Count; i++) {
            if (Items[i].A != other->Items[i].A || Items[i].B != other->Items[i].B || Items[i].C != other->Items[i].C) {
                return false;
            }
        }
        return true;
    }
    return false;
}

// GLOBAL: GAMEMD 0x7E1BCE -- second character of each 0x70-byte table entry.
extern char DAT_007E1BCE[];

// FUNCTION: GAMEMD 0x5F96B0
// If the text starts with a "ga"/"gt"/"na"/"nt"/"ca"/"ct"/"ya"/"yt" pair, replaces the second letter from the table.
void __fastcall FUN_005F96B0(char* text, int index)
{
    if (index != -1) {
        char first = text[0];
        char second = text[1];
        if (first >= 'A' && first <= 'Z') {
            first += ' ';
        }
        if (second >= 'A' && second <= 'Z') {
            second += ' ';
        }
        if ((first == 'g' || first == 'n' || first == 'c' || first == 'y') && (second == 'a' || second == 't')) {
            text[1] = DAT_007E1BCE[index * 0x70];
        }
    }
}

// A three-word record held by value in a growable list; the element type is not named by the binary.
struct Triple12 {
    int A;
    int B;
    int C;
    bool operator==(const Triple12& o) const { return A == o.A && B == o.B && C == o.C; }
    bool operator!=(const Triple12& o) const { return !(*this == o); }
};
GG_STATIC_ASSERT(sizeof(Triple12) == 0xC);

// FUNCTION: GAMEMD 0x58AF80
// Appends a record, growing the list by its increment when full.
template class DynamicVectorClass<Triple12>;
