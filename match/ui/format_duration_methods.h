// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x46D360. The clamp constant 0x57E3F is 359999 = 99*3600 +
//   59*60 + 59, which fixes the unit as seconds and the cap as 99:59:59; the two
//   magic multiplies are the signed divisions by 3600 and 60.
#ifndef GG_MATCH_UI_FORMAT_DURATION_METHODS_H
#define GG_MATCH_UI_FORMAT_DURATION_METHODS_H

// VC6 has no built-in wchar_t; it is a typedef for unsigned short.
typedef unsigned short gg_wchar;

// GLOBAL: GAMEMD 0x81B304 — the build path the lookup is told to blame. Declared
// rather than transcribed: it is data out of the retail image, and referencing it
// by address produces the same relocation the literal would.
extern const char DAT_0081B304[];

// FUNCTION: GAMEMD 0x734E60 — resolve a label to its localised text. __fastcall
// with two further arguments on the stack, which it pops itself.
gg_wchar* __fastcall FUN_00734E60(const char* label, int flags,
                                 const char* file, int line);
// LIBRARY: GAMEMD 0x7CA564 — swprintf.
extern "C" int __cdecl FUN_007CA564(gg_wchar* buffer, const gg_wchar* format, ...);

// FUNCTION: GAMEMD 0x46D360
void __fastcall FUN_0046D360(gg_wchar* buffer, int seconds);
// FUNCTION: GAMEMD 0x470C90
void __fastcall FUN_00470C90(gg_wchar* buffer, int seconds);

#endif  // GG_MATCH_UI_FORMAT_DURATION_METHODS_H
