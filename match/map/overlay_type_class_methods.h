// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// This compatibility header supplies the helper declarations needed by the two legacy methods that
// remain in overlay_type_class_methods.cpp. OverlayTypeClass and OverlayClass themselves are declared
// once in the terrain-object integration overlay.
#ifndef GG_MATCH_MAP_OVERLAY_TYPE_CLASS_METHODS_H
#define GG_MATCH_MAP_OVERLAY_TYPE_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "terrain_objects/overlay_type_class.h"

extern "C" int __cdecl gg_overlay_stricmp(const char* a, const char* b);
void* __cdecl operator new(unsigned int cb);
void __cdecl operator delete(void* p);
extern "C" void __cdecl _makepath(char* path, const char* drive, const char* dir, const char* fname, const char* ext);

struct Image_005FE620;
Image_005FE620* __fastcall FUN_005B40B0(const char* name, unsigned char flag);
void __fastcall FUN_005F96B0(char* name, int idxTheater);
void __fastcall FUN_005F9710(char* name);
extern const char STR_0081834C[];

struct Theater_005FE620 {
    char ID[0x10]; char UIName[0x20]; char ControlFileName[0xA]; char ArtFileName[0xA];
    char PaletteFileName[0xA]; char Extension[0x4]; char _pad52[0x70 - 0x52];
};
GG_STATIC_ASSERT(offsetof(Theater_005FE620, Extension) == 0x4E);
GG_STATIC_ASSERT(sizeof(Theater_005FE620) == 0x70);
extern Theater_005FE620 DAT_007E1B78[];

struct CellStruct_005FE530 { short X; short Y; };
GG_STATIC_ASSERT(offsetof(CellStruct_005FE530, Y) == 0x02);
GG_STATIC_ASSERT(sizeof(CellStruct_005FE530) == 0x04);
extern CellStruct_005FE530 DAT_00AC1608;
extern OverlayTypeClass** DAT_00A83D84;
extern int DAT_00A83D90;

#endif
