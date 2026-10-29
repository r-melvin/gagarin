// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x595680 (0x8C bytes): base constructor 0x558740, field stores, vptr 0x7ED8E4,
//   Extension "SED" (0x82BA60), description buffer at +0x78 and the localised-string copy (0x734E60, wcscpy).
#include "../_layout/map_seed_class.h"

// FUNCTION: GAMEMD 0x734FD0 (decl; reloc) -- returns a global (0xB1CF80); non-zero once localised text is loaded.
int FUN_00734FD0();
// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- localised string lookup(label, index-out, file, line); __fastcall, RET 8.
unsigned short* FUN_00734E60(char* a1, int a2, char* a3, int a4);
// LIBRARY: GAMEMD 0x7CA489 -- CRT wcscpy (__cdecl).
extern "C" unsigned short* __cdecl FUN_007CA489(unsigned short* a1, unsigned short* a2);
// GLOBAL: GAMEMD 0x82BA2C -- "TXT_RANDOM_MAP_DESCRIPTION"
extern char DAT_0082BA2C[];
// GLOBAL: GAMEMD 0x82BA48 -- "D:\ra2mdpost\MapGen.cpp"
extern char DAT_0082BA48[];

// STRING: GAMEMD 0x82BA60 -- "SED"
// FUNCTION: GAMEMD 0x595680
// Set up the random-map save/load driver: default flags, the "SED" file extension and an empty
// description buffer, filled from the localised text when one is loaded.
MapSeedClass::MapSeedClass()
    : unknown_38(0), unknown_3C(1), unknown_40(1), unknown_44(0), unknown_48(1), unknown_4C(0),
      unknown_50(2), unknown_54(0), unknown_58(0), unknown_5C(0), unknown_60(0), unknown_64(0),
      unknown_68(0), unknown_6C(0), unknown_70(0), unknown_74(-1)
{
    Extension = "SED";
    unknown_78 = 0;
    Description = (const wchar_t*)&unknown_78;
    if (FUN_00734FD0())
        FUN_007CA489(&unknown_78, FUN_00734E60(DAT_0082BA2C, 0, DAT_0082BA48, 0xF5E));
}
