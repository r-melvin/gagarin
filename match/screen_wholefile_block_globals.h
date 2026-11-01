// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The four whole-file block pointers of the shell screens resource block that the dialog control lookup in
//   ownrdraw.cpp also reads (0xB0FAD0, 0xB0FB10, 0xB0FB30, 0xB0FB48). One declaration site: screen_resource_globals.h
//   includes this header, and ownrdraw.cpp includes it without taking the rest of that header (its own
//   FileSystem_LoadWholeFileEx prototype and local views of neighbouring globals conflict with the full one).
//   The definitions live where the blocks are loaded and freed: DAT_00B0FAD0 and DAT_00B0FB30 in
//   screen_resource_methods.cpp, DAT_00B0FB10 and DAT_00B0FB48 in screen_palette_mgr_r21_4_methods.cpp.
#ifndef GG_MATCH_SCREEN_WHOLEFILE_BLOCK_GLOBALS_H
#define GG_MATCH_SCREEN_WHOLEFILE_BLOCK_GLOBALS_H

struct WholeFileBlock;

// GLOBAL: GAMEMD 0xB0FAD0
extern WholeFileBlock* DAT_00B0FAD0;
// GLOBAL: GAMEMD 0xB0FB10
extern WholeFileBlock* DAT_00B0FB10;
// GLOBAL: GAMEMD 0xB0FB30
extern WholeFileBlock* DAT_00B0FB30;
// GLOBAL: GAMEMD 0xB0FB48
extern WholeFileBlock* DAT_00B0FB48;

#endif  // GG_MATCH_SCREEN_WHOLEFILE_BLOCK_GLOBALS_H
