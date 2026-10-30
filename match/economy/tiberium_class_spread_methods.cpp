// SPDX-License-Identifier: GPL-3.0-or-later
//   (/Ob2: retail expands the free step 0x722A20 into the re-initialisers.)
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below. The spread
//   logic is at TiberiumClass+0xF0 (Count, Queue, cell-index flags, Nodes) with its
//   timer at +0x100; the growth logic at +0x10C repeats the same code (see the
//   growth methods). Queue, node and logic types are in _layout/tiberium_class.h.
//
//   Address index: 0x722240, 0x722D00, 0x722E50, 0x723260, 0x7233A0, 0x722390, 0x722770, 0x7228B0, 0x722AF0.

#include "../_layout/tiberium_class.h"
#include "../_layout/cell_class.h"
#include "../core/scenario_class_methods.h"
#include "../core/frame_counter.h"
#include "../core/vector_class.h"
#include <stdlib.h>

#include "../_layout/scenario_ptr_00a8b230.h"

// GLOBAL: GAMEMD 0xB0F4E8 -- TiberiumClass::Array.
extern DynamicVectorClass<TiberiumClass*> DAT_00B0F4E8;

// FUNCTION: GAMEMD 0x42B1C0 (decl; reloc) -- the surface index of a cell.
int __fastcall TiberiumCellSurfaceIndex(CellStruct* cell);

// 0x722A20 is retail's out-of-line copy of this body (no callers). VC6 only expands it
// into the re-initialisers when it is declared inline, and an inline body is not emitted
// on its own, so that copy stays unmatched here.
// Free the spread queue, the node array and the cell-index flags, and empty
// the node count.
inline void TiberiumClass::FreeSpreadLogic()
{
    if (SpreadLogic.Queue) {
        SpreadLogic.Queue->Clear();
        delete SpreadLogic.Queue;
        SpreadLogic.Queue = 0;
    }
    if (SpreadLogic.Nodes) {
        delete SpreadLogic.Nodes;
        SpreadLogic.Nodes = 0;
    }
    if (SpreadLogic.CellIndexesWithTiberium) {
        delete SpreadLogic.CellIndexesWithTiberium;
        SpreadLogic.CellIndexesWithTiberium = 0;
    }
    SpreadLogic.Count = 0;
}

// FUNCTION: GAMEMD 0x722770
// Free the spread logic, allocate fresh node, flag and queue storage sized to
// the map surface, then refill the queue from the map.
void TiberiumClass::ReinitSpreadLogic()
{
    FreeSpreadLogic();
    SpreadLogic.Nodes = new TiberiumQueueNode[TiberiumSurfaceCellCount()];
    SpreadLogic.CellIndexesWithTiberium = new unsigned char[TiberiumSurfaceCellCount()];
    SpreadLogic.Queue = new TiberiumQueue(TiberiumSurfaceCellCount());
    BuildSpreadQueue();
}

// FUNCTION: GAMEMD 0x7228B0
// Empty the spread queue and the cell-index flags, then queue every map cell
// that holds this tiberium type and can spread.
void TiberiumClass::BuildSpreadQueue()
{
    SpreadLogic.Count = 0;
    SpreadLogic.Queue->Clear();
    for (int i = TiberiumSurfaceCellCount() - 1; i >= 0; i--) {
        SpreadLogic.CellIndexesWithTiberium[i] = 0;
    }
    MapInstance.IteratorBegin_578350();
    for (CellClass* cell = MapInstance.IteratorNext_578290(); cell; cell = MapInstance.IteratorNext_578290()) {
        if (cell->GetContainedTiberiumIndex() == unknown_98 && cell->FUN_00483690()) {
            SpreadLogic.Nodes[SpreadLogic.Count].Cell = cell->MapCoords;
            SpreadLogic.Nodes[SpreadLogic.Count].Value = 0;
            TiberiumQueueNode* node = &SpreadLogic.Nodes[SpreadLogic.Count];
            SpreadLogic.Count++;
            SpreadLogic.Queue->Push(node);
            SpreadLogic.CellIndexesWithTiberium[TiberiumCellSurfaceIndex(&cell->MapCoords)] = 1;
        }
    }
}

// FUNCTION: GAMEMD 0x722AF0
// Queue a cell that can spread and is not queued yet, at the current frame
// plus a random 0..49 delay; rebuild the queue first when the node array is
// nearly full.
void TiberiumClass::RegisterForSpread(CellStruct* cell)
{
    int index = TiberiumCellSurfaceIndex(cell);
    if (MapInstance.FUN_005657A0(cell)->FUN_00483690() && SpreadLogic.CellIndexesWithTiberium[index] == 0) {
        if (SpreadLogic.Count >= TiberiumSurfaceCellCount() - 20) {
            BuildSpreadQueue();
        }
        SpreadLogic.Nodes[SpreadLogic.Count].Cell = *cell;
        SpreadLogic.Nodes[SpreadLogic.Count].Value =
            (float)(CurrentFrame + abs(DAT_00A8B230->unknown_0218.Random()) % 50);
        SpreadLogic.Queue->Push(&SpreadLogic.Nodes[SpreadLogic.Count++]);
        SpreadLogic.CellIndexesWithTiberium[TiberiumCellSurfaceIndex(cell)] = 1;
    }
}

// FUNCTION: GAMEMD 0x722390
// Free the spread logic of every tiberium type.
void TiberiumClass::FreeSpreadLogicAll()
{
    for (int i = 0; i < DAT_00B0F4E8.Count; i++) {
        DAT_00B0F4E8.Items[i]->FreeSpreadLogic();
    }
}

// FUNCTION: GAMEMD 0x722240
// Rebuild the spread logic of every tiberium type.
void TiberiumClass::ReinitSpreadLogicAll()
{
    for (int i = 0; i < DAT_00B0F4E8.Count; i++) {
        DAT_00B0F4E8.Items[i]->ReinitSpreadLogic();
    }
}

// 0x723510 is retail's out-of-line copy of the body below (no callers); like the spread
// version it is only expanded into the re-initialiser when declared inline.
// Free the growth queue, the node array and the cell-index flags, and empty
// the node count.
inline void TiberiumClass::FreeGrowthLogic()
{
    if (GrowthLogic.Queue) {
        GrowthLogic.Queue->Clear();
        delete GrowthLogic.Queue;
        GrowthLogic.Queue = 0;
    }
    if (GrowthLogic.Nodes) {
        delete GrowthLogic.Nodes;
        GrowthLogic.Nodes = 0;
    }
    if (GrowthLogic.CellIndexesWithTiberium) {
        delete GrowthLogic.CellIndexesWithTiberium;
        GrowthLogic.CellIndexesWithTiberium = 0;
    }
    GrowthLogic.Count = 0;
}

// FUNCTION: GAMEMD 0x723260
// Free the growth logic, allocate fresh node, flag and queue storage sized to
// the map surface, then refill the queue from the map.
void TiberiumClass::ReinitGrowthLogic()
{
    FreeGrowthLogic();
    GrowthLogic.Nodes = new TiberiumQueueNode[TiberiumSurfaceCellCount()];
    GrowthLogic.CellIndexesWithTiberium = new unsigned char[TiberiumSurfaceCellCount()];
    GrowthLogic.Queue = new TiberiumQueue(TiberiumSurfaceCellCount());
    BuildGrowthQueue();
}

// FUNCTION: GAMEMD 0x7233A0
// Empty the growth queue and the cell-index flags, then queue every map cell
// that holds this tiberium type and can grow.
void TiberiumClass::BuildGrowthQueue()
{
    GrowthLogic.Count = 0;
    GrowthLogic.Queue->Clear();
    for (int i = TiberiumSurfaceCellCount() - 1; i >= 0; i--) {
        GrowthLogic.CellIndexesWithTiberium[i] = 0;
    }
    MapInstance.IteratorBegin_578350();
    for (CellClass* cell = MapInstance.IteratorNext_578290(); cell; cell = MapInstance.IteratorNext_578290()) {
        if (cell->GetContainedTiberiumIndex() == unknown_98 && cell->FUN_00483620()) {
            GrowthLogic.Nodes[GrowthLogic.Count].Cell = cell->MapCoords;
            GrowthLogic.Nodes[GrowthLogic.Count].Value = 0;
            TiberiumQueueNode* node = &GrowthLogic.Nodes[GrowthLogic.Count];
            GrowthLogic.Count++;
            GrowthLogic.Queue->Push(node);
            GrowthLogic.CellIndexesWithTiberium[TiberiumCellSurfaceIndex(&cell->MapCoords)] = 1;
        }
    }
}

// FUNCTION: GAMEMD 0x722E50
// Free the growth logic of every tiberium type.
void TiberiumClass::FreeGrowthLogicAll()
{
    for (int i = 0; i < DAT_00B0F4E8.Count; i++) {
        DAT_00B0F4E8.Items[i]->FreeGrowthLogic();
    }
}

// FUNCTION: GAMEMD 0x722D00
// Rebuild the growth logic of every tiberium type.
void TiberiumClass::ReinitGrowthLogicAll()
{
    for (int i = 0; i < DAT_00B0F4E8.Count; i++) {
        DAT_00B0F4E8.Items[i]->ReinitGrowthLogic();
    }
}
