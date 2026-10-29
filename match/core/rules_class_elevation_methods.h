// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x66D150:
//     0x007F0C8C  char* section-name global -> "ElevationModel" (string at 0x839E70)
//     0x0083B370  "ElevationIncrement"
//     0x0083B358  "ElevationIncrementBonus"
//     0x0083B344  "ElevationBonusCap"
//     0x00526810  INIClass::GetSection(const char*)
//     0x005276D0  INIClass::ReadInteger(section, key, int def)
//     0x005283D0  INIClass::ReadDouble(section, key, double def)
//   Members: `[ESI+0x1838]` int, `FSTP qword [ESI+0x1840]`, `FSTP qword
//   [ESI+0x1848]`. Names cross-checked against YRpp.
#ifndef GG_MATCH_CORE_RULES_CLASS_ELEVATION_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_ELEVATION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/rules_class.h"
#include "../platform/ccini_class_methods.h"


// GLOBAL: GAMEMD 0x7F0C8C — holds the "ElevationModel" section name.
extern char* ElevationModelSection;


#endif  // GG_MATCH_CORE_RULES_CLASS_ELEVATION_METHODS_H
