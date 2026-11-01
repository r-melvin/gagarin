// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x56E7C0; REA ev_36a69509d0f920d5a6813f53a488c6ceb8fb8269d92fd46f724b06264e8f9bd6.
//
// Block clearance test: every cell of a width x height block from `origin` must pass the cell's
// clear-to-move query (and, when asked, must carry no overlay).
//
// Address index: 0x56E7C0 0x57B790

#include "_layout/cell_class.h"
#include "ui_display_chain.h"

// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
extern MapClass DAT_0087F7E8;
// GLOBAL: GAMEMD 0xABDC50 -- the cell returned for an out-of-range lookup.
extern CellClass DAT_00ABDC50;
// GLOBAL: GAMEMD 0xABDC74 -- the coordinate that failed the last lookup.
extern CellStruct DAT_00ABDC74;

// MapClass::GetCellAt written out inline by retail: the flat-array lookup, falling back to the invalid cell.
static inline CellClass* GetCell(CellStruct c)
{
    int idx = (c.Y << 9) + c.X;
    if (idx >= 0 && idx < 0x40000) {
        CellClass* p = DAT_0087F7E8.Owned.Items[idx];
        if (p)
            return p;
    }
    DAT_00ABDC74 = c;
    return &DAT_00ABDC50;
}



// The same lookup taking the coordinate by pointer: the miss path re-reads it from the caller's cell.
static inline CellClass* CellAtPtr(const CellStruct* c)
{
    int idx = (c->Y << 9) + c->X;
    if (idx >= 0 && idx < 0x40000) {
        CellClass* p = DAT_0087F7E8.Owned.Items[idx];
        if (p)
            return p;
    }
    DAT_00ABDC74 = *c;
    return &DAT_00ABDC50;
}


// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- square root, __cdecl.
double __cdecl FUN_004CAC40(double value);

// FUNCTION: GAMEMD 0x56E7C0
bool MapClass::FUN_0056E7C0(const CellStruct* origin, int width, int height, int speedType, int zone, int movementZone,
                            int level, bool isBridge, bool requireNoOverlay)
{
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            CellStruct at;
            at.X = origin->X + x;
            at.Y = origin->Y + y;
            CellClass* cell = GetCell(at);
            if (requireNoOverlay && cell->OverlayTypeIndex != -1)
                return false;
            if (!cell->IsClearToMove(speedType, false, false, zone, movementZone, level, isBridge))
                return false;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x57B790
void MapClass::FUN_0057B790(const CellStruct* cell)
{
    for (int a = -5; a <= 5; ++a) {
        for (int b = -5; b <= 5; ++b) {
            CellStruct t;
            t.X = cell->X + a;
            t.Y = cell->Y + b;
            short dx = cell->X - t.X;
            short dy = cell->Y - t.Y;
            if ((short)(int)FUN_004CAC40((double)dx * (double)dx + (double)dy * (double)dy) <= 5) {
                CellClass* c = CellAtPtr(cell);
                if (c)
                    c->FUN_00480A80(1);
            }
        }
    }
}
