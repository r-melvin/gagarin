// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Existing Value view extracted unchanged from economy/house_class_tib_methods.h.
// Retail 0x4F9610 and 0x684F3D read +0xB8; no complete object extent claimed.
#ifndef GG_MATCH_LAYOUT_TIBERIUM_CLASS_H
#define GG_MATCH_LAYOUT_TIBERIUM_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_type_class.h"
#include "cell.h"
#include "frame_timer.h"
// 8-byte queue entry: a cell and its float priority.
struct TiberiumQueueNode
{
    CellStruct Cell;    // +0x00
    float      Value;   // +0x04

    TiberiumQueueNode() {}
};
GG_STATIC_ASSERT(sizeof(TiberiumQueueNode) == 0x8);

// FUNCTION: GAMEMD 0x42B1F0 (decl; reloc) -- number of cells on the map surface.
int __stdcall TiberiumSurfaceCellCount();

// Binary min-heap of node pointers (1-based), tracking the lowest and highest
// node address.
struct TiberiumQueue
{
    int                 Count;      // +0x00
    unsigned int        Capacity;   // +0x04
    TiberiumQueueNode** Heap;       // +0x08
    TiberiumQueueNode*  RMost;      // +0x0C
    TiberiumQueueNode*  LMost;      // +0x10

    TiberiumQueue(int capacity)
    {
        RMost = 0;
        LMost = (TiberiumQueueNode*)-1;
        Count = 0;
        Capacity = capacity;
        Heap = new TiberiumQueueNode*[capacity + 1];
        for (int i = 0; i <= (int)Capacity; i++) {
            Heap[i] = 0;
        }
    }
    ~TiberiumQueue()
    {
        delete[] Heap;
    }
    void Clear()
    {
        for (int i = 0; i <= Count; i++) {
            Heap[i] = 0;
        }
        Count = 0;
    }
    bool Push(TiberiumQueueNode* node)
    {
        unsigned int i = Count + 1;
        unsigned int next = i >> 1;
        float key = node->Value;
        if (i >= Capacity) {
            return false;
        }
        while (i > 1) {
            TiberiumQueueNode* parent = Heap[next];
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
GG_STATIC_ASSERT(sizeof(TiberiumQueue) == 0x14);

// The spread or growth bookkeeping.
struct TiberiumLogic
{
    int                Count;                     // +0x00
    TiberiumQueue*     Queue;                     // +0x04
    unsigned char*     CellIndexesWithTiberium;   // +0x08
    TiberiumQueueNode* Nodes;                     // +0x0C
};
GG_STATIC_ASSERT(sizeof(TiberiumLogic) == 0x10);

class TiberiumClass : public AbstractTypeClass
{
public:
    // Stream overrides (vtable 0x7F5728); bodies in core/stream_w3_methods.cpp.
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);   // 6   0x7220D0
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);     // 7   0x7220A0
    virtual int vf_11();
    virtual int vf_12();
    // UIName (+0x60, read by CellClass::GetUIName 0x484FF0) is the AbstractTypeClass member.
    int            unknown_98;    // +0x98 compared with CellClass::GetContainedTiberiumIndex
    int            unknown_9C;    // +0x9C delay stored into the spread timer
    char           _padA0[0xA8 - 0xA0];
    int            unknown_A8;    // +0xA8 base growth delay
    char           _padAC[0xB8 - 0xAC];
    int            Value;         // +0xB8
    char           _padBC[0xC8 - 0xBC];
    int*           unknown_C8;    // +0xC8 one dword per entry
    char           unknown_CC[0xD4 - 0xCC];
    int            unknown_D4;    // +0xD4 entry count
    char           unknown_D8[0xF0 - 0xD8];
    TiberiumLogic  SpreadLogic;   // +0xF0
    CDTimerClass   SpreadTimer;   // +0x100
    TiberiumLogic  GrowthLogic;   // +0x10C
    CDTimerClass   GrowthTimer;   // +0x11C

    // FUNCTION: GAMEMD 0x722A20 -- free the spread logic's queue and arrays.
    void FreeSpreadLogic();
    // FUNCTION: GAMEMD 0x722770 -- rebuild the spread logic's arrays, then refill them.
    void ReinitSpreadLogic();
    // FUNCTION: GAMEMD 0x7228B0 -- refill the spread queue from the map.
    void BuildSpreadQueue();
    // FUNCTION: GAMEMD 0x722AF0 -- queue a cell for spreading.
    void RegisterForSpread(CellStruct* cell);
    // FUNCTION: GAMEMD 0x722240 -- rebuild the spread logic of every type.
    static void ReinitSpreadLogicAll();
    // FUNCTION: GAMEMD 0x722390 -- free the spread logic of every type.
    static void FreeSpreadLogicAll();

    // FUNCTION: GAMEMD 0x723510 -- free the growth logic's queue and arrays.
    void FreeGrowthLogic();
    // FUNCTION: GAMEMD 0x723260 -- rebuild the growth logic's arrays, then refill them.
    void ReinitGrowthLogic();
    // FUNCTION: GAMEMD 0x7233A0 -- refill the growth queue from the map.
    void BuildGrowthQueue();
    // FUNCTION: GAMEMD 0x722D00 -- rebuild the growth logic of every type.
    static void ReinitGrowthLogicAll();
    // FUNCTION: GAMEMD 0x722E50 -- free the growth logic of every type.
    static void FreeGrowthLogicAll();
};
GG_STATIC_ASSERT(offsetof(TiberiumClass, unknown_C8) == 0xC8);
GG_STATIC_ASSERT(offsetof(TiberiumClass, unknown_D4) == 0xD4);
GG_STATIC_ASSERT(offsetof(TiberiumClass, UIName) == 0x60);
GG_STATIC_ASSERT(offsetof(TiberiumClass, Value) == 0xB8);
GG_STATIC_ASSERT(offsetof(TiberiumClass, unknown_98) == 0x98);
GG_STATIC_ASSERT(offsetof(TiberiumClass, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(TiberiumClass, SpreadLogic) == 0xF0);
GG_STATIC_ASSERT(offsetof(TiberiumClass, SpreadTimer) == 0x100);
GG_STATIC_ASSERT(offsetof(TiberiumClass, GrowthLogic) == 0x10C);
GG_STATIC_ASSERT(offsetof(TiberiumClass, GrowthTimer) == 0x11C);
#endif
