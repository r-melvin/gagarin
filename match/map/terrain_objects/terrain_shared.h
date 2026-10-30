// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Retail globals, out-of-partition functions and small views only the TerrainClass /
//   TerrainTypeClass half of the terrain-objects module reads, bound by address. Module header: nothing
//   here is defined by the module. Each entry was read from the retail gamemd.exe v1.001 (the bodies of
//   0x71B920..0x71E40C). Everything the three families share (coordinates, the ObjectClass /
//   ObjectTypeClass base views, the map / cell / scenario / tactical / rules / anim / shape views and
//   their globals) lives in terrain_common_*.h.
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_SHARED_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_SHARED_H

#include "terrain_common_types.h"
#include "terrain_common_vectors.h"
#include "terrain_common_views.h"
#include "../../_layout/cell.h"
#include "../../_layout/cell_offset.h"
#include "../../core/frame_counter.h"
#include "../../core/abstract_index_cast_sweep.h"
#include "../../_layout/vector_class.h"

// The candidate view at 0xA8ED84 aliases the canonical frame-counter symbol.
#define TerrainFrame CurrentFrame

// GLOBAL: GAMEMD 0xA8E318 - the existing TerrainTypeClassArray storage.
extern DynamicVectorClassLayout TerrainTypeClassArray;
#define TerrainTypeArray (*((DynamicVectorClass<TerrainTypeClass*>*)&TerrainTypeClassArray))
// GLOBAL: GAMEMD 0xA8E988 - TerrainClass::Array, every live terrain object.
extern DynamicVectorClass<TerrainClass*> TerrainArray;

// GLOBAL: GAMEMD 0xB0ECF0 - the empty cell the placing constructor compares its cell against.
extern MapObjCell TerrainEmptyCellValue;

// The pointer index of every ObjectClass, keyed by the id the RTTI base hands out (global IndexClass at
// 0xB0E840: table, count, size, IsSorted at +0x0C, Archive cache at +0x10). Read-only here.
struct TerrainIndexNode
{
    int   ID;     // +0x00
    void* Data;   // +0x04

    // One C++ form that emits the observed growth-loop code is an empty default constructor:
    // `new TerrainIndexNode[n]` expands a vector constructor loop, and this body reduces it to a dead
    // decrement of the element count. This compiled form does not establish the retail source declaration.
    TerrainIndexNode() {}
};
GG_STATIC_ASSERT(sizeof(TerrainIndexNode) == 8);
// LIBRARY: GAMEMD 0x7C8B48 - qsort (base, count, width, compare; cdecl); GAMEMD 0x7C8E17 operator new;
// GAMEMD 0x7C8B3D operator delete; GAMEMD 0x7C9FF0 _makepath.
// FUNCTION: GAMEMD 0x41C610 (decl; reloc) - the index's qsort comparator, cdecl
int __cdecl TerrainIndexCompare(const void* a, const void* b);
// FUNCTION: GAMEMD 0x523440 (decl; reloc) - the sorted search the index uses: ECX = table, EDX =
// count, the key by pointer.
TerrainIndexNode* TerrainIndexSearch(TerrainIndexNode* table, int count, const int* key);
struct TerrainIndexView
{
    TerrainIndexNode* IndexTable;   // +0x00
    int               IndexCount;   // +0x04
    int               IndexSize;    // +0x08
    bool              IsSorted;     // +0x0C
    TerrainIndexNode* Archive;      // +0x10

    // FUNCTION: GAMEMD 0x41C500 (decl; reloc) - grows the table by `amount` entries.
    bool Grow(int amount);
    void RemoveIndex(const int& id);
    void AddIndexOutOfLine(const int& id, void* const& data);
    void AddIndexInline(const int& id, void* const& data);
};
GG_STATIC_ASSERT(sizeof(TerrainIndexView) == 0x14);
// The packet IndexClass-shaped view aliases the existing IndexClass global; no storage is added.
#define TerrainAbstractIndex (*((TerrainIndexView*)&AbstractIndex))

// The sorted-index removal, expanded in Load: sorts a stale table, searches it, shifts the tail down one
// slot, zeroes the freed last slot and drops the cache.
inline void TerrainIndexView::RemoveIndex(const int& id)
{
    if (IndexCount) {
        if (!IsSorted) {
            qsort(IndexTable, IndexCount, sizeof(TerrainIndexNode), TerrainIndexCompare);
            Archive = 0;
            IsSorted = true;
        }
        int key = id;
        TerrainIndexNode* node = TerrainIndexSearch(IndexTable, IndexCount, &key);
        if (node) {
            int found = node - IndexTable;
            if (found != -1) {
                for (int i = found + 1; i < IndexCount; i++) {
                    IndexTable[i - 1].ID = IndexTable[i].ID;
                    IndexTable[i - 1].Data = IndexTable[i].Data;
                }
                IndexCount--;
                IndexTable[IndexCount].ID = 0;
                IndexTable[IndexCount].Data = 0;
                Archive = 0;
            }
        }
    }
}

// The append, expanded in Load with the growth left as a call.
inline void TerrainIndexView::AddIndexOutOfLine(const int& id, void* const& data)
{
    if (IndexCount + 1 > IndexSize) {
        if (!Grow(IndexSize == 0 ? 10 : IndexSize))
            return;
    }
    IndexTable[IndexCount].ID = id;
    IndexTable[IndexCount].Data = data;
    IndexCount++;
    IsSorted = false;
}

// The append, expanded in the constructors with the growth inline.
inline void TerrainIndexView::AddIndexInline(const int& id, void* const& data)
{
    if (IndexCount + 1 > IndexSize) {
        int amount = IndexSize == 0 ? 10 : IndexSize;
        if (amount < 0)
            return;
        int newsize = IndexSize + amount;
        TerrainIndexNode* table = new TerrainIndexNode[newsize];
        if (table == 0)
            return;
        for (int i = 0; i < IndexCount; i++)
            table[i] = IndexTable[i];
        operator delete(IndexTable);
        IndexTable = table;
        IndexSize += amount;
        Archive = 0;
    }
    IndexTable[IndexCount].ID = id;
    IndexTable[IndexCount].Data = data;
    IndexCount++;
    IsSorted = false;
}

// GLOBAL: GAMEMD 0xB0ED7C - the cell handed to a terrain object created unplaced.
extern CellStruct TerrainDefaultCell;

// GLOBAL: GAMEMD 0xB0EDC0 - the foundation cell lists, 0x28 bytes (ten cells) per entry.
extern FoundationCell TerrainFoundationTable[22][10];

// GLOBAL: GAMEMD 0x87F6BC - the context handed to the shape drawer.
extern void* TerrainDrawContext;
// GLOBAL: GAMEMD 0x822CF1 - the shadow-drawing switch.
extern bool TerrainShadowsEnabled;
// GLOBAL: GAMEMD 0xB0ECE0 - the empty rectangle.
extern MapObjRect TerrainEmptyRect;

// GLOBAL: GAMEMD 0x7EF918 - the double constant (1e-6) the animation roll is scaled by.
extern const double TerrainMillionth;

// FUNCTION: GAMEMD 0x48ACE0 (decl; reloc) - stub returning -15; takes a coordinate by value.
int __cdecl TerrainFunc_48ACE0(MapObjCoord coord);
// FUNCTION: GAMEMD 0x48A4F0 (decl; reloc) - picks an anim type; __fastcall (count, table) + 2 stack.
void* TerrainPickAnimType(int count, void* table, int value, const MapObjCoord& coord);
// FUNCTION: GAMEMD 0x489280 (decl; reloc); __fastcall (coord, count) + 4 stack args.
void TerrainFunc_489280(const MapObjCoord& coord, int count, int a1, void* table, int a3, int a4);

// GLOBAL: GAMEMD 0xB73550 - flag tested by the terrain bodies.
extern int TerrainFlag_B73550;
// FUNCTION: GAMEMD 0x421B60 (decl; reloc) - intersects two rectangles: ECX = result, EDX = first,
// then second and two optional offset outputs on the stack.
MapObjRect* TerrainIntersect(MapObjRect* out, const MapObjRect* a, const MapObjRect* b,
                             int* dx, int* dy);
// FUNCTION: GAMEMD 0x422B80 (decl; reloc) - __fastcall (ECX = the burning object).
void TerrainFunc_422B80(void* object);

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_SHARED_H
