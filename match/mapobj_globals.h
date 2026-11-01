// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Map object, layer, cell and vector globals in the 0x8A0000 data block.
#ifndef GG_MATCH_MAPOBJ_GLOBALS_H
#define GG_MATCH_MAPOBJ_GLOBALS_H
#include "vector_class.h"

class BuildingClass;


class TagClass;


struct CellStruct;


struct Cell_004A8BF0;


// GLOBAL: GAMEMD 0x8A03F8 -- the "no cell" sentinel pair MarkFoundation refuses.
extern Cell_004A8BF0 DAT_008A03F8;
// GLOBAL: GAMEMD 0x8A3838 -- this unit's copy of the "no cell" value.
extern CellStruct DAT_008A3838;
// GLOBAL: GAMEMD 0x008B40C8
extern DynamicVectorClass<TagClass* > LogicArray;
// GLOBAL: GAMEMD 0x8B4148
extern int TunnelArrayCount;
// GLOBAL: GAMEMD 0x8A0DD8
extern int DAT_008A0DD8;
// GLOBAL: GAMEMD 0x8A0DE0
extern int DAT_008A0DE0;
// GLOBAL: GAMEMD 0x8B3CAC
extern int DAT_008B3CAC;
// GLOBAL: GAMEMD 0x008B41E0
extern DynamicVectorClass<BuildingClass* > DAT_008B41E0;

#endif  // GG_MATCH_MAPOBJ_GLOBALS_H
