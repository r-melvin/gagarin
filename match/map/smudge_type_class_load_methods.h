// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 through
//   the local Ghidra CLI at 0x6B5490: the theater index arrives in ECX
//   (`MOV EDI,ECX`) and scales by 0x70 (`LEA ECX,[EDI*8]; SUB ECX,EDI;
//   SHL ECX,4`) onto 0x7E1BC6 == &TheaterArray[0].Extension, so the table
//   base is 0x7E1B78 with Extension at +0x4E; SmudgeTypeClass::Array.Items
//   at 0xA8EC1C and.Count at 0xA8EC28; per type the Theater byte
//   [ESI+0x22C], the ID at ESI+0x24 (pushed as the file-name argument) and
//   Image at [ESI+0xA4]. The five pushed arguments and `ADD ESP,0x14` give
//   the __cdecl CRT _makepath at 0x7C9FF0 (path, drive, dir, fname, ext);
//   the 0x200-byte path buffer sits at [ESP+0x78] and the 0x6C-byte file
//   object at [ESP+0x0C], constructed by CALL 0x4739F0, read through CALL
//   0x4A3890 and torn down inline (0x7E16B0 at +0, +0x64 zeroed, 0x43AE50
//   on +0x58, 0x7E1668 at +0, 0x431B80). Names cross-checked against YRpp
//   (every offset reconfirmed above). The file object agrees with
//   match/platform/file_system_load_whole_methods.h and the Theater record
//   with match/combat/veinhole_monster_class_methods.h (neither edited;
//   re-derived here so the TU stands alone).
#ifndef GG_MATCH_MAP_SMUDGE_TYPE_CLASS_LOAD_METHODS_H
#define GG_MATCH_MAP_SMUDGE_TYPE_CLASS_LOAD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "terrain_objects/smudge_type_class.h"

// LIBRARY: GAMEMD 0x7C9FF0 (decl; reloc) — CRT _makepath, __cdecl.
extern "C" void __cdecl _makepath(char* path, const char* drive, const char* dir,
                                  const char* fname, const char* ext);

// FUNCTION: GAMEMD 0x431B80 (decl; reloc) — the base destructor.
void FUN_00431B80(void* self);

extern char VT_007E16B0;   // VTABLE: GAMEMD 0x7E16B0 — CCFileClass
extern char VT_007E1668;   // VTABLE: GAMEMD 0x7E1668 — CDFileClass

// CCFileClass on the stack (0x6C): only the pieces the inline teardown
// touches are named.
struct File_006B5490
{
    char*  Vtbl;                      // +0x0000
    char   _pad004[0x58 - 0x04];
    char   Sub58[0x64 - 0x58];        // +0x0058  the released sub-object
    int    Reset64;                   // +0x0064
    char   _pad068[0x6C - 0x68];

    // FUNCTION: GAMEMD 0x4739F0 (decl; reloc) — constructor from a name.
    File_006B5490* FUN_004739F0(const char* name);
    // FUNCTION: GAMEMD 0x4A3890 (decl; reloc) — read the whole file.
    void* ReadWholeFile();
};
GG_STATIC_ASSERT(offsetof(File_006B5490, Sub58) == 0x58);
GG_STATIC_ASSERT(offsetof(File_006B5490, Reset64) == 0x64);
GG_STATIC_ASSERT(sizeof(File_006B5490) == 0x6C);

// Theater — one 0x70-byte record of the per-theater table; only the
// Extension field is read.
struct Theater_006B5490
{
    char ID[0x10];               // +0x00
    char UIName[0x20];           // +0x10
    char ControlFileName[0xA];   // +0x30
    char ArtFileName[0xA];       // +0x3A
    char PaletteFileName[0xA];   // +0x44
    char Extension[0x4];         // +0x4E
    char _pad52[0x70 - 0x52];
};
GG_STATIC_ASSERT(offsetof(Theater_006B5490, Extension) == 0x4E);
GG_STATIC_ASSERT(sizeof(Theater_006B5490) == 0x70);

// GLOBAL: GAMEMD 0x7E1B78 — the theater table (Extension of entry 0 is 0x7E1BC6).
extern Theater_006B5490 DAT_007E1B78[];

// Existing independent field aliases at the same retail vector are retained by other legacy views;
// this loader now uses the canonical packet object view for its own array access.
#define DAT_00A8EC1C ((SmudgeTypeClass**)SmudgeTypeArray.Items)
#define DAT_00A8EC28 (SmudgeTypeArray.Count)

#endif  // GG_MATCH_MAP_SMUDGE_TYPE_CLASS_LOAD_METHODS_H
