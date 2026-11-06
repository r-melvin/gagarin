// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Declarations used by ThemeClass::PlaySong (0x720BB0) and ThemeClass::FUN_00721040, read from the retail
//   gamemd.exe v1.001 with the local Ghidra CLI.
#ifndef GG_MATCH_AUDIO_THEME_CLASS_PLAY_METHODS_H
#define GG_MATCH_AUDIO_THEME_CLASS_PLAY_METHODS_H

#include "_layout/theme_class.h"
#include "display_objects_globals.h"
#include "game_options_class_methods.h"
#include "theme_class_scan_methods.h"
#include "trivial_tu002_methods.h"
#include "trivial_tu048_methods.h"

// STRING: GAMEMD 0x889F64  ""
extern const char STR_00889F64[];
// GLOBAL: GAMEMD 0xA8EB60
extern GameOptionsClass DAT_00A8EB60;
// GLOBAL: GAMEMD 0xA83D10 -- the jukebox instance.
extern ThemeClass DAT_00A83D10;
// GLOBAL: GAMEMD 0xB0F1F8 -- the path buffer the stream is handed.
extern char DAT_00B0F1F8[];

#endif  // GG_MATCH_AUDIO_THEME_CLASS_PLAY_METHODS_H
