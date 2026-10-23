// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read off retail gamemd.exe v1.001 at 0x554D50: __fastcall (time budget in
//   ECX, a force flag in DL), plain RET. The queue is a dynamic vector object
//   at 0xABCA40 (items 0xABCA44, capacity 0xABCA48, allocated byte 0xABCA4D,
//   count 0xABCA50); cursor 0xABCA7C, pending count 0xABCA80, done flag byte
//   0xABCA84, frame counter 0xABCA74, last-adjust frame 0xABCA78, adjust
//   interval 0x829AE8. The clock is the object at 0x884D88 read through
//   0x5B1E40 (returns a double); cells come from the map object 0x87F7E8 via
//   0x5657A0 (cell coordinates by reference); 0x484050 reads six light values
//   (two dwords, four words) and 0x483E30 writes them back.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CellStruct_00554D50
{
    short X;   // +0x00
    short Y;   // +0x02
};

// One queued cell: the six saved light values and the cell coordinates.
struct LightQueueItem_00554D50
{
    int            Value0;   // +0x00
    int            Value1;   // +0x04
    unsigned short Value2;   // +0x08
    unsigned short Value3;   // +0x0A
    unsigned short Value4;   // +0x0C
    unsigned short Value5;   // +0x0E
    CellStruct_00554D50 Cell;   // +0x10
};
GG_STATIC_ASSERT(offsetof(LightQueueItem_00554D50, Value2) == 0x08);
GG_STATIC_ASSERT(offsetof(LightQueueItem_00554D50, Value5) == 0x0E);
GG_STATIC_ASSERT(offsetof(LightQueueItem_00554D50, Cell) == 0x10);

struct Cell_00554D50
{
    // FUNCTION: GAMEMD 0x484050 (decl; reloc)
    void GetLight(int* v0, int* v1, int* v2, int* v3, int* v4, int* v5);
    // FUNCTION: GAMEMD 0x483E30 (decl; reloc)
    void SetLight(int v0, int v1, int v2, int v3, int v4, int v5);
};

struct Map_00554D50
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    Cell_00554D50* GetCell(const CellStruct_00554D50& cell);
    // FUNCTION: GAMEMD 0x4F42F0 (decl; reloc)
    void Redraw(int flag);
};

struct Clock_00554D50
{
    // FUNCTION: GAMEMD 0x5B1E40 (decl; reloc)
    double Seconds();
};

// The queue object's observed fields (vector layout: vptr, items, capacity,
// two flag bytes, count).
struct LightQueue_00554D50
{
    void*                     _vtable;       // +0x00
    LightQueueItem_00554D50** Items;         // +0x04
    int                       Capacity;      // +0x08
    bool                      IsInitialized; // +0x0C
    bool                      IsAllocated;   // +0x0D
    int                       Count;         // +0x10
};
GG_STATIC_ASSERT(offsetof(LightQueue_00554D50, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(LightQueue_00554D50, Count) == 0x10);

// GLOBAL: GAMEMD 0x884D88
extern Clock_00554D50 DAT_00884D88;
// GLOBAL: GAMEMD 0x87F7E8
extern Map_00554D50 DAT_0087F7E8;
// GLOBAL: GAMEMD 0xABCA40
extern LightQueue_00554D50 DAT_00ABCA40;
// GLOBAL: GAMEMD 0xABCA74
extern unsigned int DAT_00ABCA74;
// GLOBAL: GAMEMD 0xABCA78
extern unsigned int DAT_00ABCA78;
// GLOBAL: GAMEMD 0xABCA7C
extern int DAT_00ABCA7C;
// GLOBAL: GAMEMD 0xABCA80
extern int DAT_00ABCA80;
// GLOBAL: GAMEMD 0xABCA84
extern bool DAT_00ABCA84;
// GLOBAL: GAMEMD 0x829AE8
extern unsigned int DAT_00829AE8;

// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc) -- operator delete.
void __cdecl operator delete(void* p);
// FUNCTION: GAMEMD 0x544FF0 (decl; reloc)
bool FUN_00544FF0(int value, bool flag);

// FUNCTION: GAMEMD 0x554D50
// Work through the light queue backwards within a time budget, sampling each
// queued cell's light values; once every cell is sampled (and, unless forced,
// enough budget is left) write them all back, free the queue and redraw.
// Finally, with time to spare, nudge the adjustment interval.
void FUN_00554D50(int budget, bool force)
{
    double start = DAT_00884D88.Seconds();
    DAT_00ABCA74++;

    if (DAT_00ABCA40.Count != 0 && !DAT_00ABCA84) {
        if (DAT_00ABCA7C <= 0) {
            DAT_00ABCA80 = DAT_00ABCA40.Count;
            DAT_00ABCA7C = DAT_00ABCA40.Count - 1;
        }
        while (DAT_00ABCA7C >= 0) {
            if (!force && (DAT_00ABCA7C & 0xF) == 0xF) {
                if (DAT_00884D88.Seconds() - start >= budget) {
                    break;
                }
            }
            if (DAT_00ABCA40.Items[DAT_00ABCA7C]->Value0 != 0) {
                DAT_00ABCA80--;
            } else {
                int v0;
                int v1;
                int v2;
                int v3;
                int v4;
                int v5;
                DAT_0087F7E8.GetCell(DAT_00ABCA40.Items[DAT_00ABCA7C]->Cell)->GetLight(&v0, &v1, &v2, &v3, &v4, &v5);
                DAT_00ABCA40.Items[DAT_00ABCA7C]->Value0 = v0;
                DAT_00ABCA40.Items[DAT_00ABCA7C]->Value1 = v1;
                DAT_00ABCA40.Items[DAT_00ABCA7C]->Value2 = v2;
                DAT_00ABCA40.Items[DAT_00ABCA7C]->Value3 = v3;
                DAT_00ABCA40.Items[DAT_00ABCA7C]->Value4 = v4;
                DAT_00ABCA40.Items[DAT_00ABCA7C]->Value5 = v5;
                DAT_00ABCA80--;
            }
            DAT_00ABCA7C--;
        }
        if (DAT_00ABCA80 <= 0) {
            DAT_00ABCA84 = true;
        }
    }

    double left = budget - (DAT_00884D88.Seconds() - start);
    if (DAT_00ABCA84) {
        if (force || left >= budget - 1) {
            for (int i = 0; i < DAT_00ABCA40.Count; i++) {
                LightQueueItem_00554D50* item = DAT_00ABCA40.Items[i];
                DAT_0087F7E8.GetCell(item->Cell)->SetLight(item->Value0, item->Value1,
                    item->Value2, item->Value3, item->Value4, item->Value5);
                delete item;
            }
            DAT_00ABCA40.Count = 0;
            if (DAT_00ABCA40.Items != 0 && DAT_00ABCA40.IsAllocated) {
                delete DAT_00ABCA40.Items;
                DAT_00ABCA40.Items = 0;
            }
            DAT_00ABCA40.IsAllocated = false;
            DAT_00ABCA40.Capacity = 0;
            DAT_00ABCA84 = false;
            DAT_0087F7E8.Redraw(1);
        }
    }

    double spare = budget - (DAT_00884D88.Seconds() - start);
    if (spare > 0.0 && DAT_00ABCA74 > DAT_00ABCA78 + DAT_00829AE8) {
        double half = spare * 0.5;
        if (!(half < 1.0)) {
            half = 1.0;
        }
        bool result = FUN_00544FF0((int)half, false);
        DAT_00ABCA78 = DAT_00ABCA74;
        DAT_00829AE8 = result ? 1 : 50;
    }
}
