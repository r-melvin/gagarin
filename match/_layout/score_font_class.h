// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x0083E5A8 `.?AVScoreFontClass@@`; class hierarchy descriptor 0x00808DD8.
//   Bases in RTTI (declaration) order: none.
// VTABLE: GAMEMD 0x7F0EF0 (5 slots)
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_SCORE_FONT_CLASS_H
#define GG_MATCH_LAYOUT_SCORE_FONT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class ScoreFontClass
{
public:
    // Tag for the constructor retail expands inline inside the derived font constructors.
    struct InlineInit {};
    ScoreFontClass();                                           // 0x690580
    ScoreFontClass(const InlineInit&);                          // the 0x690580 body, expanded inline
    ScoreFontClass(int a1, int a2, int a3, int a4);             // 0x6905B0 (__thiscall, RET 0x10)
    virtual ~ScoreFontClass();                                  // 0  0x691040: scalar deleting destructor shape
    virtual int vf_1(unsigned short ch);                                // 1  0x6907E0: RET 0x4
    virtual int vf_2(const unsigned short* text);                                // 2  0x6907A0: RET 0x4
    virtual void vf_3(int a1, int a2, int a3, int a4, int a5);  // 3  0x690910: RET 0x14
    virtual void vf_4(int a1, int a2, int a3, int a4, int a5, int a6);// 4  0x690850: RET 0x18
    int unknown_04;  // +0x4 store at 0x690585
    int unknown_08;  // +0x8 store at 0x690588
    int unknown_0C;  // +0xC store at 0x69058B
    unsigned char unknown_10;  // +0x10 store at 0x691065
    unsigned char unknown_11[3];  // +0x11
    int unknown_14;  // +0x14 store at 0x69058E
};
GG_STATIC_ASSERT(offsetof(ScoreFontClass, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(ScoreFontClass, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(ScoreFontClass, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(ScoreFontClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(ScoreFontClass, unknown_14) == 0x14);

#endif  // GG_MATCH_LAYOUT_SCORE_FONT_CLASS_H
