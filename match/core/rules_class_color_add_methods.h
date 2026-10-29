// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
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
//   Names cross-checked against YRpp
//   (every offset reconfirmed above).
#ifndef GG_MATCH_CORE_RULES_CLASS_COLOR_ADD_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_COLOR_ADD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/rules_class.h"
#include "../platform/ccini_class_methods.h"

// ColorStruct — packed RGB triple (no padding; size = 3).
#include "../_layout/color_struct.h"
GG_STATIC_ASSERT(offsetof(ColorStruct, G) == 0x01);
GG_STATIC_ASSERT(sizeof(ColorStruct) == 3);



// YRpp's by-value ReadColor shape over the 0x474B50 reader (the canonical CCINIClass::ReadColor
// wrapper forwards to 0x474C70): the read buffer is the wrapper's own local and the default is
// bound by const reference and forwarded by address.
inline ColorStruct ReadColorViaRead3Bytes(CCINIClass* pINI, const char* pSection, const char* pKey,
                                          const ColorStruct& defValue)
{
    ColorStruct out;
    return *pINI->Read3Bytes(&out, pSection, pKey, defValue);
}

// GLOBAL: GAMEMD 0x7F0C98 — pointer to the "ColorAdd" section name.
extern char* ColorAddSection;

#endif  // GG_MATCH_CORE_RULES_CLASS_COLOR_ADD_METHODS_H
