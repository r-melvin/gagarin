// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x66D1F0.
//
//   0x007F0C90  char* section-name global -> "WallModel" (string at 0x839E64)
//   0x0083B39C  "AlliedWallTransparency"
//   0x0083B384  "WallPenetratorThreshold"
//   0x00526810  INIClass::GetSection(const char*)
//   0x005295F0  INIClass::ReadBool(section, key, bool def)
//   0x005283D0  INIClass::ReadDouble(section, key, double def)
//
// A third INI-reader shape beside the two list-parser TUs: this one reads
// scalars out of a single section instead of enumerating keys.
#ifndef GG_MATCH_CORE_RULES_CLASS_WALLMODEL_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_WALLMODEL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/rules_class.h"
#include "../platform/ccini_class_methods.h"


// GLOBAL: GAMEMD 0x007F0C90 — holds the "WallModel" section name.
extern char* WallModelSection;


#endif  // GG_MATCH_CORE_RULES_CLASS_WALLMODEL_METHODS_H
