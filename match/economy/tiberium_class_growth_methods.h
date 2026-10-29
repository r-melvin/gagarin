// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x7235A0: the growth logic's Count `[ESI+0x10C]`,
//   Queue `[ESI+0x110]`, cell-index flag bytes `[ESI+0x114]` (indexed by the
//   0x42B1C0 result, stored 1) and Nodes `[ESI+0x118]` (8-byte nodes: the
//   cell dword at +0, the float priority at +4 via `FSTP [EAX+EDX*8+4]`); on
//   the queue Count `[EDI]`, Capacity `[EDI+4]`, the heap array `[EDI+8]`
//   (1-based, parent at `[EBX+EDX*4]`), RMost `[EDI+0xC]` and LMost
//   `[EDI+0x10]` (unsigned pointer compares); the cell's overlay data byte
//   `[EAX+0x11E]` (compared unsigned with 0xB); the map object 0x87F7E8 with
//   GetCellAt 0x5657A0; the surface index 0x42B1C0 (__fastcall, cell in
//   ECX) and count 0x42B1F0 (no args, minus 10); the scenario `[0xA8B230]`
//   randomizer at +0x218 (0x65C780), abs / % 50 (`CDQ; XOR; SUB; IDIV`) plus
//   the frame counter 0xA8ED84; the sibling 0x7233A0 called with `this`.
//   Names cross-checked against YRpp
//   (every offset reconfirmed here).
#ifndef GG_MATCH_ECONOMY_TIBERIUM_CLASS_GROWTH_METHODS_H
#define GG_MATCH_ECONOMY_TIBERIUM_CLASS_GROWTH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Cell_007235A0
{
    short X;   // +0x0000
    short Y;   // +0x0002
};
GG_STATIC_ASSERT(sizeof(Cell_007235A0) == 0x4);

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
#include "../core/frame_counter.h"


// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance (pointer).
#include "../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;

// CellClass — only the overlay data byte is read.
struct CellClass_007235A0
{
    char          _pad000[0x11E];   // +0x0000
    unsigned char OverlayData;      // +0x011E
};
GG_STATIC_ASSERT(offsetof(CellClass_007235A0, OverlayData) == 0x11E);

struct Map_007235A0
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    CellClass_007235A0* GetCellAt(const Cell_007235A0& cell);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer).
extern Map_007235A0 DAT_0087F7E8;

// PriorityQueueClassNode — a cell and its float priority.
struct QueueNode_007235A0
{
    Cell_007235A0 Cell;    // +0x0000
    float         Value;   // +0x0004
};
GG_STATIC_ASSERT(sizeof(QueueNode_007235A0) == 0x8);

// FUNCTION: GAMEMD 0x42B1C0 (decl; reloc) — PriorityQueueClassNode
// surface index of a cell (cell reference in ECX).
int ToSurfaceIndex_007235A0(const Cell_007235A0& cell);
// FUNCTION: GAMEMD 0x42B1F0 (decl; reloc) — PriorityQueueClassNode surface
// data count.
int __stdcall SurfaceDataCount_007235A0();

// PriorityQueueClass<PriorityQueueClassNode> — a 1-based binary min-heap of
// node pointers that also tracks the lowest and highest node address.
struct PriorityQueue_007235A0
{
    int                   Count;      // +0x0000
    unsigned int          Capacity;   // +0x0004
    QueueNode_007235A0**  Heap;       // +0x0008
    QueueNode_007235A0*   RMost;      // +0x000C
    QueueNode_007235A0*   LMost;      // +0x0010

    // Push, expanded inline at the call site: sift the new node up past
    // every parent with a larger priority, then widen the address range.
    bool Push(QueueNode_007235A0* node)
    {
        unsigned int i = Count + 1;
        unsigned int next = i >> 1;
        float key = node->Value;
        if (i >= Capacity) {
            return false;
        }
        while (i > 1) {
            QueueNode_007235A0* parent = Heap[next];
            if (parent->Value <= key) {
                break;
            }
            Heap[i] = parent;
            i = next;
            next = i >> 1;
        }
        Heap[i] = node;
        Count++;
        if (node > RMost) {
            RMost = node;
        }
        if (node < LMost) {
            LMost = node;
        }
        return true;
    }
};
GG_STATIC_ASSERT(offsetof(PriorityQueue_007235A0, Capacity) == 0x4);
GG_STATIC_ASSERT(offsetof(PriorityQueue_007235A0, Heap) == 0x8);
GG_STATIC_ASSERT(offsetof(PriorityQueue_007235A0, RMost) == 0xC);
GG_STATIC_ASSERT(offsetof(PriorityQueue_007235A0, LMost) == 0x10);

// TiberiumLogic — the growth (or spread) bookkeeping.
struct TiberiumLogic_007235A0
{
    int                      Count;                     // +0x0000
    PriorityQueue_007235A0*  Queue;                     // +0x0004
    unsigned char*           CellIndexesWithTiberium;   // +0x0008
    QueueNode_007235A0*      Nodes;                     // +0x000C
};
GG_STATIC_ASSERT(offsetof(TiberiumLogic_007235A0, Nodes) == 0xC);

struct Tiberium_007235A0
{
    char                    _pad000[0x10C];   // +0x0000
    TiberiumLogic_007235A0  GrowthLogic;      // +0x010C

    // FUNCTION: GAMEMD 0x7233A0 (decl; reloc) — rebuild the growth queue
    // from the map.
    void FUN_007233A0();

    // FUNCTION: GAMEMD 0x7235A0 — TiberiumClass::RegisterForGrowth.
    void RegisterForGrowth(Cell_007235A0* cell);
};
GG_STATIC_ASSERT(offsetof(Tiberium_007235A0, GrowthLogic.Count) == 0x10C);
GG_STATIC_ASSERT(offsetof(Tiberium_007235A0, GrowthLogic.Queue) == 0x110);
GG_STATIC_ASSERT(offsetof(Tiberium_007235A0, GrowthLogic.CellIndexesWithTiberium) == 0x114);
GG_STATIC_ASSERT(offsetof(Tiberium_007235A0, GrowthLogic.Nodes) == 0x118);

#endif  // GG_MATCH_ECONOMY_TIBERIUM_CLASS_GROWTH_METHODS_H
