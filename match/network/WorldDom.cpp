// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit WorldDom.cpp. The name is the source-file string at 0x84d818
//   in retail gamemd.exe v1.001, passed by the assert at 0x7af863 inside this object's
//   code range (0x7af0b0-0x7b0b9f). Functions are in ascending retail address order.

#include "../core/global_getter_family_methods.h"

#include "../core/trivial_tu289_methods.h"
#include "../core/string_class.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F7908
extern const double DAT_007F7908;
// GLOBAL: GAMEMD 0xB77EE8
extern double DAT_00B77EE8;
// GLOBAL: GAMEMD 0xB77F40
extern double DAT_00B77F40;
// GLOBAL: GAMEMD 0xB77F48
extern int DAT_00B77F48;
// GLOBAL: GAMEMD 0xB77F4C
extern int DAT_00B77F4C;
// GLOBAL: GAMEMD 0xB77F50
extern int DAT_00B77F50;
// GLOBAL: GAMEMD 0xB77F88
extern double DAT_00B77F88;

// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_007AF0E0()
{
    DAT_00B77F88 = DAT_00B77EE8 / DAT_007F7908;
}

// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_007AF100()
{
    DAT_00B77F40 = DAT_007E1718 / DAT_00B77F88;
}

// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_007AF280()
{
    DAT_00B77F50 = 0;
    DAT_00B77F48 = 0x80;
    DAT_00B77F4C = 0x80;
}

// FUNCTION: GAMEMD 0x7AF2A0
// The label text for an index: 1, 2 and 3 pick the first three strings, any
// other index the last. Each string is a function-local static, built on
// first use; the first three are built together before the index is tested.
Wstring* __fastcall FUN_007AF2A0(int index)
{
// SYNTHETIC: GAMEMD 0x7AF3C0 (the atexit stub that runs ~Wstring on first)
    static Wstring first("DIS");
// SYNTHETIC: GAMEMD 0x7AF3B0 (the atexit stub that runs ~Wstring on second)
    static Wstring second("ALL");
// SYNTHETIC: GAMEMD 0x7AF3A0 (the atexit stub that runs ~Wstring on third)
    static Wstring third("SOV");
    switch (index) {
    case 1:
        return &first;
    case 2:
        return &second;
    case 3:
        return &third;
    }
// SYNTHETIC: GAMEMD 0x7AF390 (the atexit stub that runs ~Wstring on other)
    static Wstring other("xx");
    return &other;
}

// FUNCTION: GAMEMD 0x7AF3D0
// The same shape over four more labels.
Wstring* __fastcall FUN_007AF3D0(int index)
{
// SYNTHETIC: GAMEMD 0x7AF4F0 (the atexit stub that runs ~Wstring on first)
    static Wstring first("NA");
// SYNTHETIC: GAMEMD 0x7AF4E0 (the atexit stub that runs ~Wstring on second)
    static Wstring second("EU");
// SYNTHETIC: GAMEMD 0x7AF4D0 (the atexit stub that runs ~Wstring on third)
    static Wstring third("AS");
    switch (index) {
    case 1:
        return &first;
    case 2:
        return &second;
    case 3:
        return &third;
    }
// SYNTHETIC: GAMEMD 0x7AF4C0 (the atexit stub that runs ~Wstring on other)
    static Wstring other("XX");
    return &other;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x007B0210
int FUN_007B0210()
{
    return (int)&DAT_00B77F58;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B0290
// Returns the address of a global.
void* __cdecl FUN_007B0290()
{
    return DAT_00B77F70;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B0310
// Returns a global (dword).
int __cdecl FUN_007B0310()
{
    return DAT_00B77F54;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B0340
// Returns a global (dword).
int __cdecl FUN_007B0340()
{
    return DAT_00B77F60;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x007B0370
int FUN_007B0370()
{
    return (int)&DAT_00B77F68;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B0380
// Returns the address of a global.
void* __cdecl FUN_007B0380()
{
    return DAT_00B77F78;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B0430
// Returns a constant boolean.
bool __cdecl FUN_007B0430()
{
    return true;
}
