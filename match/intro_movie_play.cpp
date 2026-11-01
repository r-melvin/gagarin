// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// One stand-alone routine at 0x539320 (no direct callers found by Ghidra's x-ref): when bit 2
// of the byte 0xA8E960 is set it looks up the movie named "INTRO" (string at 0x8263A8) and
// plays it. Both callees are __fastcall: the name arrives in ECX, and the player takes the
// movie index in ECX, -1 in EDX and three pushed flags.

// GLOBAL: GAMEMD 0xA8E960
extern unsigned char DAT_00A8E960;

// FUNCTION: GAMEMD 0x48DF30 (decl; reloc) - index of a movie by name, -1 when absent.
int FUN_0048DF30(const char* name);
// FUNCTION: GAMEMD 0x5BF260 (decl; reloc) - plays the movie with the given index.
void FUN_005BF260(int movie, int a2, bool a3, bool a4, bool a5);

// FUNCTION: GAMEMD 0x539320
void FUN_00539320()
{
    if (DAT_00A8E960 & 4)
        FUN_005BF260(FUN_0048DF30("INTRO"), -1, false, true, true);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8E960
unsigned char DAT_00A8E960;
// END defined globals
