// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x66D480: `ADD EBP,0x1874` + `ADD EBP,3` per key
//   (RulesClass::ColorAdd, an array of 3-byte ColorStruct at 0x1874) and the
//   three-byte copy `MOV AX,[ECX]; MOV CL,[ECX+2]; MOV [EDX],AX; MOV [EDX+2],CL`.
//   The section-name pointer is the .data slot 0x7F0C98 (MOV EAX,[0x7F0C98]).
//   Callees: INIClass::GetSection 0x526810, GetKeyCount 0x526960, GetKeyName
//   0x526CC0 and CCINIClass::Read3Bytes 0x474B50 (__thiscall out, section,
//   key, default -> out).  The default is the 3-byte ctor at 0x4355B0
//   (matched in match/core/small_struct_ctor_methods.cpp; the sibling inlined
//   copy of this loop in Read_File 0x668C43 calls it out of line with
//   `PUSH 0` x3), inlined here as the three `MOV [ESP+0x2C..0x2E],BL`.
//   Names cross-checked against YRpp RulesClass.h / CCINIClass.h
//   (consult-only; every offset reconfirmed above).
#ifndef GG_MATCH_CORE_RULES_CLASS_COLOR_ADD_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_COLOR_ADD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ColorStruct — packed RGB triple (no padding; size = 3).
struct ColorStruct
{
    unsigned char R;   // +0x00
    unsigned char G;   // +0x01
    unsigned char B;   // +0x02

    ColorStruct() {}
    // FUNCTION: GAMEMD 0x4355B0 — the three-byte ctor, inlined here.
    ColorStruct(unsigned char r, unsigned char g, unsigned char b)
        : R(r), G(g), B(b) {}
};
GG_STATIC_ASSERT(offsetof(ColorStruct, G) == 0x01);
GG_STATIC_ASSERT(sizeof(ColorStruct) == 3);

// Opaque INI parser; the four out-of-line members are declared only, so cl
// emits reloc-normalised __thiscall CALLs.
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
    // FUNCTION: GAMEMD 0x474B50 (decl; reloc)
    ColorStruct* Read3Bytes(ColorStruct* pOut, const char* pSection,
                            const char* pKey, const ColorStruct& defValue);

    // Inline forwarding wrapper (YRpp's ReadColor shape): the default is
    // bound by const reference and forwarded by address; the read buffer is
    // the wrapper's own local, which is what leaves `out` at [ESP+0] and the
    // default in the caller's parameter home slot.
    ColorStruct ReadColor(const char* pSection, const char* pKey,
                          const ColorStruct& defValue)
    {
        ColorStruct out;
        return *Read3Bytes(&out, pSection, pKey, defValue);
    }

    // FUNCTION: GAMEMD 0x679F40 — CCINIClass::Exists (matched out of line in
    // match/platform/ccini_class_methods.cpp).  Here it is the header inline
    // VC6 expands at the section test: with the key defaulted to null the
    // entry branch folds away and the section probe survives as a
    // materialised bool (`TEST EAX,EAX; SETNZ AL`), which is retail's shape.
    bool Exists(const char* pSection, const char* pKey = 0)
    {
        if (pKey == 0) {
            return GetSection(pSection) != 0;
        }
        return GetEntry(pSection, pKey) != 0;
    }
};

struct RulesClass
{
    char        _pad000[0x1874];   // +0x0000
    ColorStruct ColorAdd[0x10];    // +0x1874

    // FUNCTION: GAMEMD 0x66D480
    bool Read_ColorAdd(CCINIClass* pINI);
};
GG_STATIC_ASSERT(offsetof(RulesClass, ColorAdd) == 0x1874);

// GLOBAL: GAMEMD 0x7F0C98 — pointer to the "ColorAdd" section name.
extern char* ColorAddSection;

#endif  // GG_MATCH_CORE_RULES_CLASS_COLOR_ADD_METHODS_H
