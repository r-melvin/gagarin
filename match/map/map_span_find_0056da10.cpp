// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x56DA10 and 0x56DAE0: the map keeps a
//   vector of 16-byte span records (array at +0x54, count at +0x60); each record holds a start
//   and an end cell (two dwords of X/Y shorts), a flag byte at +0x08 and a dword at +0x0C.
//
// Address index: 0x56DA10 0x56DAE0 0x56DB70
#include <stddef.h>
#include <stdlib.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/cell.h"

// One 16-byte span record.
struct Span_0056DA10
{
    CellStruct Start;        // +0x00
    CellStruct End;          // +0x04
    bool Active;             // +0x08
    unsigned char _pad09[3];
    int Locked;              // +0x0C
};
GG_STATIC_ASSERT(offsetof(Span_0056DA10, End) == 0x04);
GG_STATIC_ASSERT(offsetof(Span_0056DA10, Active) == 0x08);
GG_STATIC_ASSERT(offsetof(Span_0056DA10, Locked) == 0x0C);
GG_STATIC_ASSERT(sizeof(Span_0056DA10) == 0x10);

// Receiver view: the map object with its span vector.
struct Obj_0056DA10
{
    char _pad00[0x54];
    Span_0056DA10* Spans;  // +0x54
    char _pad58[8];
    int SpanCount;         // +0x60

    int FUN_0056DA10(const CellStruct* cell, int tolerance, int start);  // 0x56DA10
    bool FUN_0056DAE0(const CellStruct* cell);                          // 0x56DAE0
    bool FUN_0056DB70(const CellStruct* cell);                          // 0x56DB70
    // FUNCTION: GAMEMD 0x5851B0 (decl; reloc)
    void FUN_005851B0(Span_0056DA10* span);
    // FUNCTION: GAMEMD 0x56D100 (decl; reloc)
    bool FUN_0056D100(CellStruct* from, CellStruct* to, int a, int b, int c, int d);
    // FUNCTION: GAMEMD 0x56D6E0 (decl; reloc)
    void FUN_0056D6E0();
    // FUNCTION: GAMEMD 0x584E50 (decl; reloc)
    void FUN_00584E50(Span_0056DA10* span);
};
GG_STATIC_ASSERT(offsetof(Obj_0056DA10, Spans) == 0x54);
GG_STATIC_ASSERT(offsetof(Obj_0056DA10, SpanCount) == 0x60);

// FUNCTION: GAMEMD 0x56DA10
// Index of the first unlocked span from `start` on that passes within `tolerance` cells of `cell`
// (a vertical span is matched on X, a horizontal one on Y), or -1.
int Obj_0056DA10::FUN_0056DA10(const CellStruct* cell, int tolerance, int start)
{
    for (int i = start; i < SpanCount; i++) {
        Span_0056DA10* span = &Spans[i];
        if (span->Locked != 0)
            continue;
        CellStruct s = span->Start;
        CellStruct e = span->End;
        if (s.X - e.X == 0) {
            if (cell->Y < s.Y || cell->Y > e.Y)
                continue;
            if (abs(cell->X - s.X) <= tolerance)
                return i;
        } else {
            if (cell->X > e.X || cell->X < s.X)
                continue;
            if (abs(cell->Y - s.Y) <= tolerance)
                return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x56DAE0
// Fires every active span near `cell` (refreshing the span list once when none is found) and
// reports whether any was.
bool Obj_0056DA10::FUN_0056DAE0(const CellStruct* cell)
{
    int i = FUN_0056DA10(cell, 3, 0);
    if (i == -1) {
        FUN_0056D6E0();
        i = FUN_0056DA10(cell, 3, 0);
        if (i == -1)
            return false;
    }
    bool fired = false;
    while (i != -1) {
        if (Spans[i].Active) {
            FUN_00584E50(&Spans[i]);
            fired = true;
            Spans[i].Active = 0;
        }
        i = FUN_0056DA10(cell, 3, i + 1);
    }
    return fired;
}

// FUNCTION: GAMEMD 0x56DB70
// Raises every inactive span near `cell` (refreshing the span list once when none is found) and
// reports whether any of them could not be set up (0x56D100 failing).
bool Obj_0056DA10::FUN_0056DB70(const CellStruct* cell)
{
    int i = FUN_0056DA10(cell, 3, 0);
    if (i == -1) {
        FUN_0056D6E0();
        i = FUN_0056DA10(cell, 3, 0);
        if (i == -1)
            return false;
    }
    bool failed = false;
    while (i != -1) {
        if (!Spans[i].Active) {
            Spans[i].Active = 1;
            FUN_005851B0(&Spans[i]);
            if (!FUN_0056D100(&Spans[i].Start, &Spans[i].End, 0, 0, 0, 0))
                failed = true;
        }
        i = FUN_0056DA10(cell, 3, i + 1);
    }
    return failed;
}
