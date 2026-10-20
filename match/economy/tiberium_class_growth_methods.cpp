// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x7235A0.

#include "tiberium_class_growth_methods.h"

#include <stdlib.h>

// FUNCTION: GAMEMD 0x7235A0
//
// Queue a cell for tiberium growth. Cells whose overlay is already at the
// top growth stages (data byte 11 and up) are ignored. When the node array
// is within ten of the surface size the growth queue is rebuilt first. The
// cell gets the next node with a priority of the current frame plus a random
// 0..49 delay, the node is pushed onto the priority queue, and the cell's
// surface index is flagged as holding tiberium.
//
// Phrasing that matters: the priority is one expression with the frame
// counter named first — that keeps the sum in the IDIV remainder register
// (`ADD EDX,ECX`) and loads Nodes before Count for the FSTP; any form with
// a named delay local lands the sum in the freshly loaded frame register,
// and `abs(...) % 50 + frame` hoists the frame load above the abs into EBP
// (81.9% / 47.9%). In the inlined Push (header) the parent index is a named
// local computed before the capacity test and refreshed at the loop bottom
// (retail's `MOV EDX,ECX; SHR EDX,1` before `CMP ECX,EAX`), and it is
// declared before the float key copy so the key travels through EAX and
// Capacity is loaded after the spill.
void Tiberium_007235A0::RegisterForGrowth(Cell_007235A0* cell)
{
    int index = ToSurfaceIndex_007235A0(*cell);
    if (DAT_0087F7E8.GetCellAt(*cell)->OverlayData < 0xB) {
        if (this->GrowthLogic.Count > SurfaceDataCount_007235A0() - 10) {
            this->FUN_007233A0();
        }
        this->GrowthLogic.Nodes[this->GrowthLogic.Count].Cell = *cell;
        this->GrowthLogic.Nodes[this->GrowthLogic.Count].Value =
            (float)(DAT_00A8ED84 + abs(DAT_00A8B230->Random.Random()) % 50);
        QueueNode_007235A0* node = &this->GrowthLogic.Nodes[this->GrowthLogic.Count];
        this->GrowthLogic.Count++;
        this->GrowthLogic.Queue->Push(node);
        this->GrowthLogic.CellIndexesWithTiberium[index] = 1;
    }
}
