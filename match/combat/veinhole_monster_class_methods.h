// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/globals derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x74CD60-0x74D48A), cross-
//   checked against YRpp (
//   reconfirmed numerically here).
//
// VeinholeMonsterClass static helpers: two cell-lookups over the global
// VeinholeMonster::Array and the theater-art loader that builds the
// "VEINHOLE.<ext>" filename and caches its SHP.
#ifndef GG_MATCH_COMBAT_VEINHOLE_MONSTER_CLASS_H
#define GG_MATCH_COMBAT_VEINHOLE_MONSTER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

// CellStruct - map cell coordinate (short X, short Y); 4 bytes.
// GetVeinholeMonsterFrom reads pCell->X @[ecx] and pCell->Y @[ecx+2].
struct CellStruct
{
    short X;
    short Y;
};

// Theater - per-theater data table, a 6-entry array of 0x70-byte records at
// GAMEMD 0x007E1B78 (YRpp). LoadVeinholeArt only touches the
// Extension field @+0x4E ("TEM"/"SNO"/...); &Array[0].Extension == 0x007E1BC6,
// the folded ADD constant seen in the disasm. The rest is laid out to fix
// sizeof == 0x70 (the *112 stride the codegen strength-reduces).
struct Theater
{
    char  ID[0x10];              // +0x00
    char  UIName[0x20];          // +0x10
    char  ControlFileName[0xA];  // +0x30
    char  ArtFileName[0xA];      // +0x3A
    char  PaletteFileName[0xA];  // +0x44
    char  Extension[0x4];        // +0x4E
    char  MMExtension[0x4];      // +0x52
    char  Letter[0x2];           // +0x56
    float RadarTerrainBrightness;// +0x58
    float unknown_float_5C;      // +0x5C
    float unknown_float_60;      // +0x60
    float unknown_float_64;      // +0x64
    int   unknown_int_68;        // +0x68
    int   unknown_int_6C;        // +0x6C
};

GG_STATIC_ASSERT(offsetof(Theater, Extension) == 0x4E);
GG_STATIC_ASSERT(sizeof(Theater) == 0x70);

// The global theater table @0x007E1B78.
extern Theater TheaterArray[6];

// The global vein-monster registry: DynamicVectorClass<VeinholeMonsterClass*>
// @0x00B1D290 (Items @+0x04 == 0x00B1D294, Count @+0x10 == 0x00B1D2A0).
extern DynamicVectorClassLayout VeinholeArray;

// VeinholeMonster::VeinSHPData cache pointer @0x00B1D2EC.
extern void* VeinSHPData;

// CellStruct -> linear cell index (GAMEMD 0x0042B1C0, __fastcall); used to
// probe a monster's per-cell affection map.
int __fastcall CellStructToIndex(CellStruct* pCell);

// SHP loader (GAMEMD 0x005B40B0, __fastcall(name, fileType)) returning the
// cached SHPStruct*.
void* __fastcall LoadVeinholeSHP(const char* name, char fileType);

extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

class VeinholeMonsterClass
{
public:
    static VeinholeMonsterClass* __fastcall GetVeinholeMonsterFrom(CellStruct* pCell);
    static VeinholeMonsterClass* __fastcall GetVeinholeMonsterAt(CellStruct* pCell);
    static void __fastcall LoadVeinholeArt(int idxTheatre);

    // Only the two members the lookups touch are modelled (full layout is P2):
    //   SpreadData (CellIndexesWithVeins) bool* @0xC4, Position CellStruct @0xF8.
    char       _base0[0xC4];   // +0x00
    char*      SpreadData;     // +0xC4  bool array, indexed by cell index
    char       _pad1[0xF8 - 0xC8]; // +0xC8
    CellStruct Position;       // +0xF8
};

GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, SpreadData) == 0xC4);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, Position)   == 0xF8);

#endif  // GG_MATCH_COMBAT_VEINHOLE_MONSTER_CLASS_H
