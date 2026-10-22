// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The class name comes from the RTTI of the vectors this unit instantiates
//   (".?AV?$DynamicVectorClass@PAVEgoClass@@@@" at 0x4207B0). The layout is
//   read off the constructor 0x4C3C90 (text copy at +0x00, the three dword
//   arguments at +0x04/+0x08/+0x0C) and the two draw bodies.
#ifndef GG_MATCH_UI_EGO_CLASS_H
#define GG_MATCH_UI_EGO_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class EgoClass
{
public:
    // FUNCTION: GAMEMD 0x4C3C90 (declaration) -- RET 0x10.
    EgoClass(int unknown_04, int y, const wchar_t* text, int flags);
    // FUNCTION: GAMEMD 0x4C3D00 (declaration) -- RET 4.
    void FUN_004C3D00(bool force);
    // FUNCTION: GAMEMD 0x4C3DD0 (declaration) -- RET 4.
    void FUN_004C3DD0(void* surface);

    wchar_t* Text;          // +0x00 heap copy of the constructor's text
    int      unknown_04;    // +0x04
    int      Y;             // +0x08 the line's screen row
    int      Flags;         // +0x0C 0x100 / 0x200 pick the print alignment; also the font selector
};
GG_STATIC_ASSERT(offsetof(EgoClass, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(EgoClass, Y) == 0x08);
GG_STATIC_ASSERT(offsetof(EgoClass, Flags) == 0x0C);
GG_STATIC_ASSERT(sizeof(EgoClass) == 0x10);

#endif  // GG_MATCH_UI_EGO_CLASS_H
