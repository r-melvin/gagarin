// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x690580, 0x6905B0 and 0x6905F0 in the user's gamemd.exe v1.001. Both
//   constructors store the ScoreFontClass vtable (0x7F0EF0), run the shared glyph-table loader
//   0x690640 and count the instance in 0xB0558C; the destructor undoes both.
//
// ScoreFontClass construction. Address index: 0x690580 default constructor, 0x6905B0 constructor
// with four values, 0x6905F0 destructor.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2

#include "../_layout/score_font_class.h"

// FUNCTION: GAMEMD 0x690640 (decl; reloc) -- loads the shared glyph tables, ECX = font.
void __fastcall FUN_00690640(ScoreFontClass* font);

// GLOBAL: GAMEMD 0xB0558C -- number of live fonts.
extern int DAT_00B0558C;

struct SharedGlyphSlot_00B05590
{
    void* Table;     // +0x00
    bool Loaded;     // +0x04
    char unknown_05[3];
};
// GLOBAL: GAMEMD 0xB05590 -- the three shared glyph tables.
extern SharedGlyphSlot_00B05590 DAT_00B05590[3];

// FUNCTION: GAMEMD 0x690580
ScoreFontClass::ScoreFontClass()
    : unknown_04(0), unknown_08(0), unknown_0C(0), unknown_14(0)
{
    FUN_00690640(this);
    DAT_00B0558C++;
}

// FUNCTION: GAMEMD 0x6905B0
ScoreFontClass::ScoreFontClass(int a1, int a2, int a3, int a4)
    : unknown_04(a1), unknown_08(a2), unknown_0C(a3), unknown_14(a4)
{
    FUN_00690640(this);
    DAT_00B0558C++;
}

// FUNCTION: GAMEMD 0x6905F0
ScoreFontClass::~ScoreFontClass()
{
    if (unknown_0C != 0 && unknown_10 == 1) {
        operator delete((void*)unknown_0C);
        unknown_0C = 0;
        unknown_10 = 0;
    }
    DAT_00B0558C--;
    if (DAT_00B0558C == 0) {
        for (int i = 0; i < 3; i++) {
            DAT_00B05590[i].Table = 0;
            DAT_00B05590[i].Loaded = false;
        }
    }
}
// SYNTHETIC: GAMEMD 0x691040 -- ScoreFontClass::`scalar deleting destructor' (vtable 0x7F0EF0 slot 0).
