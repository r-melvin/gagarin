// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//
// The saved-game header constructor at 0x680FF0: clears the header's counters, the three
// short/byte flags, the -1 id at +0x188 and the six-word block at +0x3D8. It lives in its own
// unit so that LoadDlg.cpp keeps calling it out of line, as retail does.
#include "input_controls/menus_load_options.h"

// The fields the constructor touches; the rest of the 0x3F4 bytes are left alone.
struct SaveHeaderFields_00680FF0 {
    int unknown_00;
    int unknown_04;
    unsigned short unknown_08;
    char pad_0A[0x108 - 0x0A];
    unsigned short unknown_108;
    char pad_10A[0x188 - 0x10A];
    int unknown_188;
    int unknown_18C;
    unsigned char unknown_190;
    char pad_191[0x294 - 0x191];
    unsigned char unknown_294;
    char pad_295[0x2D4 - 0x295];
    unsigned char unknown_2D4;
    char pad_2D5[0x3D8 - 0x2D5];
    int unknown_3D8[6];
    int unknown_3F0;
};
GG_STATIC_ASSERT(offsetof(SaveHeaderFields_00680FF0, unknown_188) == 0x188);
GG_STATIC_ASSERT(offsetof(SaveHeaderFields_00680FF0, unknown_3D8) == 0x3D8);
GG_STATIC_ASSERT(offsetof(SaveHeaderFields_00680FF0, unknown_3F0) == 0x3F0);
GG_STATIC_ASSERT(sizeof(SaveHeaderFields_00680FF0) == sizeof(MenusSaveHeader));

// FUNCTION: GAMEMD 0x680FF0
MenusSaveHeader::MenusSaveHeader()
{
    SaveHeaderFields_00680FF0* f = (SaveHeaderFields_00680FF0*)this;
    f->unknown_00 = 0;
    f->unknown_04 = 0;
    f->unknown_188 = -1;
    f->unknown_18C = 0;
    f->unknown_3F0 = 0;
    f->unknown_08 = 0;
    f->unknown_108 = 0;
    f->unknown_190 = 0;
    f->unknown_294 = 0;
    f->unknown_2D4 = 0;
    f->unknown_3D8[0] = 0;
    f->unknown_3D8[1] = 0;
    f->unknown_3D8[2] = 0;
    f->unknown_3D8[3] = 0;
    f->unknown_3D8[4] = 0;
    f->unknown_3D8[5] = 0;
}
