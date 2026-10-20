// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
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
//   Names cross-checked against YRpp RulesClass.h / CCINIClass.h
//   (consult-only; every slot reconfirmed above).
#ifndef GG_MATCH_CORE_RULES_CLASS_COLORS_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_COLORS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ColorStruct -- packed RGB triple (no padding; size = 3).
struct ColorStruct
{
    unsigned char R;   // +0x00
    unsigned char G;   // +0x01
    unsigned char B;   // +0x02

    ColorStruct() {}
    // FUNCTION: GAMEMD 0x4355B0 -- the three-byte ctor, inlined here.
    ColorStruct(unsigned char r, unsigned char g, unsigned char b)
        : R(r), G(g), B(b) {}
};
GG_STATIC_ASSERT(offsetof(ColorStruct, G) == 0x01);
GG_STATIC_ASSERT(sizeof(ColorStruct) == 3);

// Opaque INI parser; the out-of-line members are declared only, so cl emits
// reloc-normalised __thiscall CALLs.
class CCINIClass
{
public:
    // FUNCTION: GAMEMD 0x526810 (decl; reloc)
    void*        GetSection(const char* pSection);
    // FUNCTION: GAMEMD 0x526B10 (decl; reloc)
    void*        GetEntry(const char* pSection, const char* pKey);
    // FUNCTION: GAMEMD 0x526960 (decl; reloc)
    int          GetKeyCount(const char* pSection);
    // FUNCTION: GAMEMD 0x526CC0 (decl; reloc)
    const char*  GetKeyName(const char* pSection, int index);
    // FUNCTION: GAMEMD 0x474C70 (decl; reloc) -- matched in
    // match/platform/ccini_class_read_color_methods.cpp.
    ColorStruct* ReadColor(ColorStruct* pOut, const char* pSection,
                           const char* pKey, const ColorStruct& defValue);

    // Inline forwarding wrapper (YRpp's by-value ReadColor shape): the read
    // buffer is the wrapper's own local and the result is copied out of it,
    // which is what puts the out buffer at [ESP+0x14] and the copy in the
    // pINI parameter's home slot.
    ColorStruct ReadColor(const char* pSection, const char* pKey,
                          const ColorStruct& defValue)
    {
        ColorStruct out;
        return *ReadColor(&out, pSection, pKey, defValue);
    }

    // FUNCTION: GAMEMD 0x679F40 -- CCINIClass::Exists (matched out of line in
    // match/platform/ccini_class_methods.cpp). Here it is the header inline
    // VC6 expands at the section test: with the key defaulted to null the
    // entry branch folds away and the section probe survives as a
    // materialised bool (`TEST EAX,EAX; SETNZ AL; TEST AL,AL`).
    bool Exists(const char* pSection, const char* pKey = 0)
    {
        if (pKey == 0) {
            return GetSection(pSection) != 0;
        }
        return GetEntry(pSection, pKey) != 0;
    }
};

// FUNCTION: GAMEMD 0x626AB0 (decl; reloc) -- register a named colour.
void __fastcall FUN_00626AB0(const char* name, ColorStruct* color);

struct HSVClass;
struct PaletteClass;

struct ColorScheme
{
    // FUNCTION: GAMEMD 0x68C9C0 (decl; reloc) -- find or make the scheme
    // (matched in match/renderer/color_scheme_find_methods.cpp).
    static int __fastcall FindByName(const char* name, ColorStruct* color,
                                     PaletteClass* pal1, PaletteClass* pal2,
                                     int shade);
};

// GLOBAL: GAMEMD 0x886380 -- the palette object passed as the first palette.
extern PaletteClass DAT_00886380;
// GLOBAL: GAMEMD 0x885780 -- the palette object passed as the second palette.
extern PaletteClass DAT_00885780;

// GLOBAL: GAMEMD 0x7F0C94 -- pointer to the "Colors" section name.
extern char* ColorsSection;

struct RulesClass
{
    // FUNCTION: GAMEMD 0x66D3A0
    bool Read_Colors(CCINIClass* pINI);
};

#endif  // GG_MATCH_CORE_RULES_CLASS_COLORS_METHODS_H
