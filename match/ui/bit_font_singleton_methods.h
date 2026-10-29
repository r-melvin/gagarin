// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; retail entries 0x4354D0, 0x435500, 0x435530.
#ifndef GG_BIT_FONT_SINGLETON_METHODS_H
#define GG_BIT_FONT_SINGLETON_METHODS_H
#include "../renderer/bit_font.h"
#include "bit_text_ctor_methods.h"
// FUNCTION: GAMEMD 0x4354D0 (decl)
void CreateBitFontSingleton();
// FUNCTION: GAMEMD 0x435500 (decl)
void DestroyBitFontSingleton();
// FUNCTION: GAMEMD 0x435530 (decl)
void __stdcall DestroyBitFontIfSingleton(BitFont* font);
#endif
