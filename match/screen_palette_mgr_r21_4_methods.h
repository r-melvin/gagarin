// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Declarations used by screen_palette_mgr_r21_4_methods.cpp: the module-scope globals and the functions it calls.
#ifndef GG_MATCH_SCREEN_PALETTE_MGR_R21_4_METHODS_H
#define GG_MATCH_SCREEN_PALETTE_MGR_R21_4_METHODS_H

#include "screen_palette_mgr_methods.h"
#include "scenario_class_methods.h"
#include "scenario_session_globals.h"

// GLOBAL: GAMEMD 0xB0FBE0 -- the screen resources are loaded.
extern char DAT_00B0FBE0_r21_4;
// GLOBAL: GAMEMD 0xB0FC10 -- eight raw blocks, stride 4.
extern void* DAT_00B0FC10_r21_4[8];
// GLOBAL: GAMEMD 0xA8B230 -- the scenario.
extern ScenarioClass* ScenarioInstance;
// GLOBAL: GAMEMD 0xB0FBE4 -- palette sets of the sidebar screen (stride 8).
extern PaletteSet DAT_00B0FBE4;
// GLOBAL: GAMEMD 0xB0FBEC
extern PaletteSet DAT_00B0FBEC;
// GLOBAL: GAMEMD 0xB0FBF4
extern PaletteSet DAT_00B0FBF4;
// GLOBAL: GAMEMD 0xB0FBFC
extern PaletteSet DAT_00B0FBFC;
// GLOBAL: GAMEMD 0xB0FC04
extern PaletteSet DAT_00B0FC04;
// GLOBAL: GAMEMD 0xB0FC0C -- the sidebar palettes are loaded.
extern char DAT_00B0FC0C_r21_4;
// GLOBAL: GAMEMD 0x844BF0 -- sidebar palette file names.
extern const char* DAT_00844BF0;
// GLOBAL: GAMEMD 0x844BF4
extern const char* DAT_00844BF4;
// GLOBAL: GAMEMD 0x844BF8
extern const char* DAT_00844BF8;
// GLOBAL: GAMEMD 0x844BFC
extern const char* DAT_00844BFC;
// GLOBAL: GAMEMD 0x844C00
extern const char* DAT_00844C00;
// GLOBAL: GAMEMD 0x844C04
extern const char* DAT_00844C04;
// GLOBAL: GAMEMD 0x844C08
extern const char* DAT_00844C08;
// FUNCTION: GAMEMD 0x72FA10 (decl; reloc)
void __cdecl FUN_0072FA10();
// FUNCTION: GAMEMD 0x72FC60 (decl; reloc)
void __fastcall FUN_0072FC60(int a, int b);
// GLOBAL: GAMEMD 0xB0FC30 -- sixteen raw blocks, stride 4.
extern void* DAT_00B0FC30_r21_4[16];
// GLOBAL: GAMEMD 0xB0FCC8 -- the four menu file blocks and their allocated flags.
extern bool DAT_00B0FCC8;
// GLOBAL: GAMEMD 0xB0FCCA
extern bool DAT_00B0FCCA;
// GLOBAL: GAMEMD 0xB0FCCB
extern bool DAT_00B0FCCB;
// GLOBAL: GAMEMD 0xB0FCCC
extern bool DAT_00B0FCCC;
// GLOBAL: GAMEMD 0xB0FB48
extern WholeFileBlock* DAT_00B0FB48;
// GLOBAL: GAMEMD 0xB0FB10
extern WholeFileBlock* DAT_00B0FB10;
// GLOBAL: GAMEMD 0xB0F9F8
extern WholeFileBlock* DAT_00B0F9F8;
// GLOBAL: GAMEMD 0xB0FA6C
extern WholeFileBlock* DAT_00B0FA6C;
// GLOBAL: GAMEMD 0x844CB8 -- file names for the 640-wide menu blocks.
extern const char* DAT_00844CB8;
// GLOBAL: GAMEMD 0x844CC4
extern const char* DAT_00844CC4;
// GLOBAL: GAMEMD 0x844CC8
extern const char* DAT_00844CC8;
// GLOBAL: GAMEMD 0x844CD0
extern const char* DAT_00844CD0;
// GLOBAL: GAMEMD 0x844D4C -- file names for the other menu resolutions.
extern const char* DAT_00844D4C;
// GLOBAL: GAMEMD 0x844D54
extern const char* DAT_00844D54;
// GLOBAL: GAMEMD 0x844CCC
extern const char* DAT_00844CCC;
// GLOBAL: GAMEMD 0x844D5C
extern const char* DAT_00844D5C;
// GLOBAL: GAMEMD 0x844BE0 -- menu palette file names.
extern const char* DAT_00844BE0;
// GLOBAL: GAMEMD 0x844D50
extern const char* DAT_00844D50;
// GLOBAL: GAMEMD 0x844D58
extern const char* DAT_00844D58;
// GLOBAL: GAMEMD 0x844D60
extern const char* DAT_00844D60;
// GLOBAL: GAMEMD 0x844CD4
extern const char* DAT_00844CD4;
// GLOBAL: GAMEMD 0x844CD8
extern const char* DAT_00844CD8;
// GLOBAL: GAMEMD 0x844CDC
extern const char* DAT_00844CDC;
// GLOBAL: GAMEMD 0x844CE0
extern const char* DAT_00844CE0;
// GLOBAL: GAMEMD 0x844CE4
extern const char* DAT_00844CE4;
// GLOBAL: GAMEMD 0x844CE8
extern const char* DAT_00844CE8;
// GLOBAL: GAMEMD 0x844CEC
extern const char* DAT_00844CEC;
// GLOBAL: GAMEMD 0x844CF0
extern const char* DAT_00844CF0;
// GLOBAL: GAMEMD 0x844CF4
extern const char* DAT_00844CF4;
// GLOBAL: GAMEMD 0x844CF8
extern const char* DAT_00844CF8;
// GLOBAL: GAMEMD 0xB0FAC4
extern WholeFileBlock* DAT_00B0FAC4;
// GLOBAL: GAMEMD 0xB0F9DC
extern WholeFileBlock* DAT_00B0F9DC;
// GLOBAL: GAMEMD 0xB0FAC0
extern WholeFileBlock* DAT_00B0FAC0;
// GLOBAL: GAMEMD 0xB0FB50
extern WholeFileBlock* DAT_00B0FB50;
// GLOBAL: GAMEMD 0xB0FA04
extern WholeFileBlock* DAT_00B0FA04;
// GLOBAL: GAMEMD 0xB0FAF8
extern WholeFileBlock* DAT_00B0FAF8;
// GLOBAL: GAMEMD 0xB0FA74
extern WholeFileBlock* DAT_00B0FA74;
// GLOBAL: GAMEMD 0xB0FA38
extern WholeFileBlock* DAT_00B0FA38;
// GLOBAL: GAMEMD 0xB0FAE8
extern WholeFileBlock* DAT_00B0FAE8;
// GLOBAL: GAMEMD 0xB0FA54
extern WholeFileBlock* DAT_00B0FA54;
// GLOBAL: GAMEMD 0xB0FC95
extern bool DAT_00B0FC95;
// GLOBAL: GAMEMD 0xB0FC96
extern bool DAT_00B0FC96;
// GLOBAL: GAMEMD 0xB0FC97
extern bool DAT_00B0FC97;
// GLOBAL: GAMEMD 0xB0FC98
extern bool DAT_00B0FC98;
// GLOBAL: GAMEMD 0xB0FC99
extern bool DAT_00B0FC99;
// GLOBAL: GAMEMD 0xB0FC9A
extern bool DAT_00B0FC9A;
// GLOBAL: GAMEMD 0xB0FC9B
extern bool DAT_00B0FC9B;
// GLOBAL: GAMEMD 0xB0FC9C
extern bool DAT_00B0FC9C;
// GLOBAL: GAMEMD 0xB0FC9D
extern bool DAT_00B0FC9D;
// GLOBAL: GAMEMD 0xB0FC9E
extern bool DAT_00B0FC9E;
// GLOBAL: GAMEMD 0x844FFC
extern const char STR_00844FFC[];
// GLOBAL: GAMEMD 0x84500C
extern const char STR_0084500C[];
// GLOBAL: GAMEMD 0x84501C
extern const char STR_0084501C[];
// GLOBAL: GAMEMD 0x845028
extern const char STR_00845028[];
// GLOBAL: GAMEMD 0x845034
extern const char STR_00845034[];
// GLOBAL: GAMEMD 0x845104
extern const char STR_00845104[];
// GLOBAL: GAMEMD 0x845110
extern const char STR_00845110[];
// GLOBAL: GAMEMD 0x84511C
extern const char STR_0084511C[];
// GLOBAL: GAMEMD 0x845128
extern const char STR_00845128[];
// GLOBAL: GAMEMD 0x845138
extern const char STR_00845138[];
// GLOBAL: GAMEMD 0x845144
extern const char STR_00845144[];
// GLOBAL: GAMEMD 0x845150
extern const char STR_00845150[];
// GLOBAL: GAMEMD 0x84515C
extern const char STR_0084515C[];
// GLOBAL: GAMEMD 0x84516C
extern const char STR_0084516C[];
// GLOBAL: GAMEMD 0x845178
extern const char STR_00845178[];
// GLOBAL: GAMEMD 0x845188
extern const char STR_00845188[];
// GLOBAL: GAMEMD 0x845198
extern const char STR_00845198[];
// GLOBAL: GAMEMD 0x8451A4
extern const char STR_008451A4[];
// GLOBAL: GAMEMD 0x8451C8
extern const char STR_008451C8[];
// GLOBAL: GAMEMD 0x8453E8
extern const char STR_008453E8[];
// GLOBAL: GAMEMD 0x8453F4
extern const char STR_008453F4[];
// GLOBAL: GAMEMD 0x845404
extern const char STR_00845404[];
// GLOBAL: GAMEMD 0x845414
extern const char STR_00845414[];
// GLOBAL: GAMEMD 0x845420
extern const char STR_00845420[];
// GLOBAL: GAMEMD 0x84542C
extern const char STR_0084542C[];
// GLOBAL: GAMEMD 0x845460
extern const char STR_00845460[];

#endif  // GG_MATCH_SCREEN_PALETTE_MGR_R21_4_METHODS_H
