// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// Constructor and destructor of the path-search singleton at 0x87E8B8
// (constructed by the static initialiser thunk 0x40AFA0, destroyed through
// the atexit thunk 0x40AFC0, which tail-jumps to the destructor). No /GX:
// neither body carries an exception frame.
//
// The object owns two binary heaps (0x14-byte headers whose slot arrays are
// allocated by the inline constructor), two large node pools, three
// DynamicVectorClass members (+0x74, stride 0x18), three 1000-byte scratch
// grids (+0xBC) and a block allocated at the end of construction (+0x64).

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "vector_class.h"

// Retail calls the VectorClass capacity constructors out of line (0x42DC50,
// 0x42DD60) and expands DynamicVectorClass's own constructor around them, so
// only the latter is given a body here (same body as
// vector_class_operations.h).
template<> inline DynamicVectorClass<unsigned>::DynamicVectorClass(int capacity, unsigned* pMem)
    : VectorClass<unsigned>(capacity, pMem)
{
    this->CapacityIncrement = 10;
    this->Count = 0;
}

template<> inline DynamicVectorClass<unsigned short>::DynamicVectorClass(int capacity, unsigned short* pMem)
    : VectorClass<unsigned short>(capacity, pMem)
{
    this->CapacityIncrement = 10;
    this->Count = 0;
}


// operator new is retail 0x7C8E17, operator delete 0x7C8B3D.

// Binary heap header: slot array of Size + 1 entries.
struct PathHeap
{
    PathHeap(int size)
    {
        unknown_0C = 0;
        unknown_10 = -1;
        Count = 0;
        Size = size;
        Nodes = (void**)operator new((size + 1) * sizeof(void*));
        for (int i = 0; i <= Size; i++)
        {
            Nodes[i] = 0;
        }
    }
    ~PathHeap()
    {
        operator delete(Nodes);
    }
    void Clear()
    {
        for (int i = 0; i <= Count; i++)
        {
            Nodes[i] = 0;
        }
        Count = 0;
    }

    int    Count;        // +0x00
    int    Size;         // +0x04
    void** Nodes;        // +0x08
    int    unknown_0C;   // +0x0C
    int    unknown_10;   // +0x10
};
GG_STATIC_ASSERT(sizeof(PathHeap) == 0x14);   // operator new(0x14) at 0x42A741

struct Obj_0042A6D0
{
    Obj_0042A6D0()
    {
        unknown_0C = 0;
        unknown_08 = 0;
        unknown_04 = 0;
    }

    int unknown_00;   // +0x00
    int unknown_04;   // +0x04
    int unknown_08;   // +0x08
    int unknown_0C;   // +0x0C
};

struct PathNodePool_0042A6D0
{
    PathNodePool_0042A6D0() : Used(0) {}
    ~PathNodePool_0042A6D0() {}

    Obj_0042A6D0 Nodes[0x10000];   // +0x000000
    int      Used;             // +0x100000
};
GG_STATIC_ASSERT(sizeof(PathNodePool_0042A6D0) == 0x100004);   // operator new(0x100004) at 0x42A7E8

struct PathCellRecord
{
    char unknown_00[0x18];
};

struct PathCellPool
{
    PathCellPool() : Used(0) {}
    ~PathCellPool() {}

    PathCellRecord Records[0x10000];   // +0x000000
    int            Used;               // +0x180000
};
GG_STATIC_ASSERT(sizeof(PathCellPool) == 0x180004);   // operator new(0x180004) at 0x42A81C

// Cell coordinate pair with the by-value addition the path walkers use.
struct PathCell
{
    short X;   // +0x0
    short Y;   // +0x2
};

inline PathCell operator+(PathCell const& a, PathCell const& b)
{
    PathCell r;
    r.X = a.X + b.X;
    r.Y = a.Y + b.Y;
    return r;
}

// GLOBAL: GAMEMD 0x89F688 -- the eight one-cell steps, indexed by facing.
#define PathAdjacent (reinterpret_cast<PathCell const*>(0x89F688))

inline PathCell const& StepForFacing(int facing)
{
    return PathAdjacent[facing & 7];
}

inline int MaxInt(int a, int b)
{
    return a > b ? a : b;
}

inline int OppositeFacing(int facing)
{
    return (facing - 4) & 7;
}

// A cell that starts out at the origin.
struct PathOrigin : PathCell
{
    PathOrigin()
    {
        X = 0;
        Y = 0;
    }
};

// Packs an unordered pair of zone ids as (smaller << 16) | larger.
inline unsigned PackEdge(unsigned a, unsigned b)
{
    if (a < b)
    {
        unsigned t = a;
        a = b;
        b = t;
    }
    return (b << 16) | a;
}

// The three edge queues are DynamicVectorClass instances over a 4-byte key
// (vtables 0x7E37CC / 0x7E37EC). AddItem is the canonical growth-then-store
// body (out-of-line copy at 0x42D830).
// Written as a free inline: including the canonical inline AddItem
// (vector_class_operations.h) also instantiates the vectors' out-of-line
// members in this TU and changes the 0x42CCD0/0x42CF80 bodies.
typedef DynamicVectorClass<unsigned> PathEdgeQueue;

template<class T> bool QueueAdd(DynamicVectorClass<T>& queue, T const& item)
{
    if (queue.Count >= queue.Capacity)
    {
        if ((queue.IsAllocated || queue.Capacity == 0) && queue.CapacityIncrement > 0)
        {
            if (!queue.SetCapacity(queue.Capacity + queue.CapacityIncrement, 0))
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    queue.Items[queue.Count++] = item;
    return true;
}

// One zone record of the map's per-layer zone lists (0x24-byte stride): the
// first member is a dynamic vector of 8-byte links.
struct PathZoneLink
{
    int Zone;         // +0x0
    int unknown_04;   // +0x4
};

struct PathZone
{
    void*         vftable;      // +0x00
    PathZoneLink* Items;        // +0x04
    int           Capacity;     // +0x08
    int           unknown_0C;   // +0x0C
    int           Count;        // +0x10
    char          unknown_14[0x10];
};
GG_STATIC_ASSERT(offsetof(PathZone, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(PathZone, Count) == 0x10);

struct PathZoneList
{
    void*     vftable;   // +0x00
    PathZone* Items;     // +0x04
    char      unknown_08[0x10];
};

struct PathZoneIds
{
    unsigned short Id[5];
};

// View of the map singleton (0x87F7E8): the per-cell zone id table and the
// three per-layer zone lists.
struct PathMapView
{
    int   FUN_0056d3f0(PathCell const& cell);   // 0x56D3F0
    void* GetCellAt(PathCell const& cell);      // 0x5657A0
    bool  FUN_005840c0(void* cell, int zone, DynamicVectorClass<unsigned short>* zones, int arg);   // 0x5840C0

    char         unknown_00[0x70];
    PathZoneIds* ZoneIds;       // +0x70
    char         unknown_74[0x18];
    PathZoneList Zones[3];      // +0x8C
};
GG_STATIC_ASSERT(offsetof(PathMapView, ZoneIds) == 0x70);
GG_STATIC_ASSERT(offsetof(PathMapView, Zones) == 0x8C);

// GLOBAL: GAMEMD 0x87F7E8
extern PathMapView DAT_0087F7E8;

inline unsigned short* InlineZoneIds_0042CCD0(PathCell const& cell)
{
    return DAT_0087F7E8.ZoneIds[DAT_0087F7E8.FUN_0056d3f0(cell)].Id;
}

class PathSearchClass
{
public:
    PathSearchClass();
    ~PathSearchClass();
    void FUN_0042bca0(int* path, int start, int end, int* out_index, PathCell* cell);
    void FUN_0042ccd0(int arg);
    void FUN_0042cf80(int value, int zone);

    void AddZoneEdge(int zone, unsigned a, unsigned b)
    {
        if (a != b)
        {
            QueueAdd(Queues[zone], PackEdge(a, b));
        }
    }

    bool          unknown_00;        // +0x00
    bool          unknown_01;        // +0x01
    bool          unknown_02;        // +0x02
    bool          unknown_03;        // +0x03
    float         unknown_04;        // +0x04
    bool          unknown_08;        // +0x08
    char          unknown_09[3];
    PathCellPool* CellPool;          // +0x0C
    PathNodePool_0042A6D0* unknown_10;          // +0x10
    PathHeap*     OpenHeap;          // +0x14
    void*         unknown_18;        // +0x18
    void*         unknown_1C;        // +0x1C
    void*         unknown_20;        // +0x20
    void*         unknown_24;        // +0x24
    int           unknown_28;        // +0x28
    int           unknown_2C;        // +0x2C
    char          unknown_30[8];
    bool          unknown_38;        // +0x38
    char          unknown_39[3];
    int           unknown_3C;        // +0x3C
    void*         BlockA[3];         // +0x40
    void*         BlockB[3];         // +0x4C
    void*         BlockC[3];         // +0x58
    void*         unknown_64;        // +0x64
    PathHeap*     SecondHeap;        // +0x68
    int           unknown_6C;        // +0x6C
    PathOrigin    Cell70;            // +0x70
    PathEdgeQueue Queues[3];   // +0x74
    unsigned short Grid[3][500];     // +0xBC
    int           GridState[3];      // +0xC74
};
GG_STATIC_ASSERT(offsetof(PathSearchClass, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(PathSearchClass, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(PathSearchClass, CellPool) == 0x0C);
GG_STATIC_ASSERT(offsetof(PathSearchClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(PathSearchClass, OpenHeap) == 0x14);
GG_STATIC_ASSERT(offsetof(PathSearchClass, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(PathSearchClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(PathSearchClass, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(PathSearchClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(PathSearchClass, BlockA) == 0x40);
GG_STATIC_ASSERT(offsetof(PathSearchClass, BlockB) == 0x4C);
GG_STATIC_ASSERT(offsetof(PathSearchClass, BlockC) == 0x58);
GG_STATIC_ASSERT(offsetof(PathSearchClass, unknown_64) == 0x64);
GG_STATIC_ASSERT(offsetof(PathSearchClass, SecondHeap) == 0x68);
GG_STATIC_ASSERT(offsetof(PathSearchClass, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(PathSearchClass, Cell70) == 0x70);
GG_STATIC_ASSERT(offsetof(PathSearchClass, Queues) == 0x74);
GG_STATIC_ASSERT(offsetof(PathSearchClass, Grid) == 0xBC);
GG_STATIC_ASSERT(offsetof(PathSearchClass, GridState) == 0xC74);

// FUNCTION: GAMEMD 0x42A6D0
PathSearchClass::PathSearchClass()
    : unknown_00(false),
      unknown_01(false),
      unknown_02(false),
      unknown_03(true),
      unknown_04(1.0f),
      unknown_08(true),
      unknown_18(0),
      unknown_1C(0),
      unknown_20(0),
      unknown_24(0),
      unknown_28(-1),
      unknown_2C(-1),
      unknown_38(true),
      unknown_3C(0),
      unknown_6C(-1)
{
    OpenHeap = new PathHeap(0x10000);
    SecondHeap = new PathHeap(10000);
    unknown_10 = new PathNodePool_0042A6D0;
    CellPool = new PathCellPool;
    CellPool->Used = 0;
    unknown_10->Used = 0;
    OpenHeap->Clear();
    SecondHeap->Clear();
    for (int i = 0; i < 3; i++)
    {
        BlockA[i] = 0;
        BlockB[i] = 0;
        BlockC[i] = 0;
        Queues[i].Clear();
        memset(Grid[i], 0, sizeof(Grid[i]));
        GridState[i] = 0;
    }
    unknown_64 = operator new(0x27100);
}

// FUNCTION: GAMEMD 0x42A900
PathSearchClass::~PathSearchClass()
{
    delete OpenHeap;
    OpenHeap = 0;
    delete SecondHeap;
    SecondHeap = 0;
    delete unknown_10;
    unknown_10 = 0;
    delete CellPool;
    CellPool = 0;
    if (unknown_18 != 0)
    {
        operator delete(unknown_18);
        unknown_18 = 0;
    }
    if (unknown_1C != 0)
    {
        operator delete(unknown_1C);
        unknown_1C = 0;
    }
    if (unknown_24 != 0)
    {
        operator delete(unknown_24);
        unknown_24 = 0;
    }
    if (unknown_20 != 0)
    {
        operator delete(unknown_20);
        unknown_20 = 0;
    }
    for (int i = 0; i < 3; i++)
    {
        if (BlockA[i] != 0)
        {
            operator delete(BlockA[i]);
            BlockA[i] = 0;
        }
        if (BlockB[i] != 0)
        {
            operator delete(BlockB[i]);
            BlockB[i] = 0;
        }
        if (BlockC[i] != 0)
        {
            operator delete(BlockC[i]);
            BlockC[i] = 0;
        }
    }
    operator delete(unknown_64);
}

// FUNCTION: GAMEMD 0x42BCA0
void PathSearchClass::FUN_0042bca0(int* path, int start, int end, int* out_index, PathCell* cell)
{
    int best = 0;
    int i = start;
    PathCell offset;
    offset.X = 0;
    offset.Y = 0;
    PathCell at = *cell;
    bool shrinking = false;
    while (i >= end)
    {
        if (path[i] == -2)
        {
            i--;
            continue;
        }
        int facing = OppositeFacing(path[i]);
        offset = offset + StepForFacing(facing);
        at = at + StepForFacing(facing);
        int dist = MaxInt(abs(offset.X), abs(offset.Y));
        if (dist > best)
        {
            if (shrinking)
            {
                *out_index = i + 1;
                *cell = at + StepForFacing(OppositeFacing(facing));
                return;
            }
            best = dist;
        }
        else
        {
            shrinking = true;
        }
        i--;
    }
    *out_index = end;
    *cell = at;
}

// FUNCTION: GAMEMD 0x42CCD0
void PathSearchClass::FUN_0042ccd0(int arg)
{
    unsigned short* ids = InlineZoneIds_0042CCD0(Cell70);
    for (int zone = 0; zone < 3; zone++)
    {
        unsigned short id = ids[zone];
        DynamicVectorClass<unsigned short> zones;
        zones.Clear();
        if (DAT_0087F7E8.FUN_005840c0(DAT_0087F7E8.GetCellAt(Cell70), zone, &zones, arg))
        {
            FUN_0042cf80(InlineZoneIds_0042CCD0(Cell70)[zone], zone);
            continue;
        }
        for (int i = zones.GetCount() - 1; i >= 0; i--)
        {
            AddZoneEdge(zone, zones.Items[i], id);
        }
    }
}

// FUNCTION: GAMEMD 0x42CF80
void PathSearchClass::FUN_0042cf80(int value, int zone)
{
    int count = GridState[zone];
    if (count <= 1)
    {
        unknown_38 = false;
        return;
    }
    int pos = -1;
    for (int i = 0; i < count; i++)
    {
        if (Grid[zone][i] == value)
        {
            pos = i;
            break;
        }
    }
    if (pos == -1)
    {
        unknown_38 = false;
        return;
    }
    unsigned short a;
    unsigned short b;
    if (pos == count - 1)
    {
        b = Grid[zone][pos];
        a = Grid[zone][pos - 1];
    }
    else
    {
        a = Grid[zone][pos];
        b = Grid[zone][pos + 1];
    }
    AddZoneEdge(zone, a, b);
    PathZone& zb = DAT_0087F7E8.Zones[zone].Items[b];
    PathZone& za = DAT_0087F7E8.Zones[zone].Items[a];
    for (int j = zb.Count - 1; j >= 0; j--)
    {
        unsigned short n = (unsigned short)zb.Items[j].Zone;
        if (n == a)
        {
            continue;
        }
        for (int k = za.Count - 1; k >= 0; k--)
        {
            if (za.Items[k].Zone == n)
            {
                AddZoneEdge(zone, n, a);
            }
        }
    }
}
