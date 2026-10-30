// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Bytes, globals and argument slots read off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x66D3A0: the section-name pointer is
//   the .data slot 0x7F0C94 (MOV EAX,[0x7F0C94]); the callees are
//   INIClass::GetSection 0x526810, GetKeyCount 0x526960, GetKeyName 0x526CC0
//   and CCINIClass::ReadColor 0x474C70 (__thiscall out, section, key,
//   default -> out; matched in match/platform/ccini_class_read_color_methods),
//   the default being the three immediate byte stores `MOV [ESP+0x20..0x22],0`
//   (the inlined three-byte ctor 0x4355B0). Each colour is then handed to
//   0x626AB0 (__fastcall name, colour) and twice to ColorScheme::FindByName
//   0x68C9C0 (__fastcall name, colour, 0x886380, 0x885780, shade) with the
//   shades 1 and 0x35. `this` is never touched (RET 4 with ECX unused).
//   Names cross-checked against YRpp
//   (every slot reconfirmed above).
#ifndef GG_MATCH_CORE_RULES_CLASS_COLORS_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_COLORS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../platform/ccini_class_methods.h"

// ColorStruct -- packed RGB triple (no padding; size = 3).
#include "../_layout/color_struct.h"
GG_STATIC_ASSERT(offsetof(ColorStruct, G) == 0x01);
GG_STATIC_ASSERT(sizeof(ColorStruct) == 3);


// FUNCTION: GAMEMD 0x626AB0 (decl; reloc) -- register a named colour.
void FUN_00626AB0(const char* name, ColorStruct* color);

class HSVClass;
struct PaletteClass;

struct ColorScheme
{
    // FUNCTION: GAMEMD 0x68C9C0 (decl; reloc) -- find or make the scheme
    // (matched in match/renderer/color_scheme_find_methods.cpp).
    static int FindByName(const char* name, ColorStruct* color,
                          PaletteClass* pal1, PaletteClass* pal2,
                          int shade);
};

// GLOBAL: GAMEMD 0x886380 -- the palette object passed as the first palette.
extern PaletteClass DAT_00886380;
// GLOBAL: GAMEMD 0x885780 -- the palette object passed as the second palette.
extern PaletteClass DAT_00885780;

// GLOBAL: GAMEMD 0x7F0C94 -- pointer to the "Colors" section name.
extern char* ColorsSection;

#include "../_layout/rules_class.h"

#endif  // GG_MATCH_CORE_RULES_CLASS_COLORS_METHODS_H
