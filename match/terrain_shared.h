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
#include "_layout/cell.h"
#include "_layout/cell_offset.h"
#include "frame_counter.h"
#include "abstract_index_cast_sweep.h"
#include "vector_class.h"

// The candidate view at 0xA8ED84 aliases the canonical frame-counter symbol.
#define TerrainFrame CurrentFrame

// GLOBAL: GAMEMD 0xA8E318 - the existing TerrainTypeClassArray storage.
extern DynamicVectorClass<TerrainTypeClass*> TerrainTypeClassArray;
// GLOBAL: GAMEMD 0xA8E988 - TerrainClass::Array, every live terrain object.
extern DynamicVectorClass<TerrainClass*> TerrainArray;

// GLOBAL: GAMEMD 0xB0ECF0 - the empty cell the placing constructor compares its cell against.
extern MapObjCell TerrainEmptyCellValue;

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
