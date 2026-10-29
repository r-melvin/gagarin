// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Globals, strings and the callback convention read off retail gamemd.exe
//   v1.001 at 0x406760 via the local Ghidra CLI.

#include <stdio.h>

// GLOBAL: GAMEMD 0x87E28C -- live audio-event count.
extern int DAT_0087E28C;
// GLOBAL: GAMEMD 0x87E290 -- its high-water mark.
extern int DAT_0087E290;
// GLOBAL: GAMEMD 0x87E298 -- reporting enabled.
extern int DAT_0087E298;
// GLOBAL: GAMEMD 0xB1D3A8 -- live positional-voice count.
extern int DAT_00B1D3A8;
// GLOBAL: GAMEMD 0xB1D3AC -- its high-water mark.
extern int DAT_00B1D3AC;

// FUNCTION: GAMEMD 0x406760  (__fastcall; the sink arrives in ECX)
// Hand two formatted status lines to a text sink: the audio-event counters and
// the positional-voice counters. Does nothing unless reporting is enabled.
// STRING: GAMEMD 0x81624C "AudioEvents : %05d - Max: %05d"
// STRING: GAMEMD 0x81622C "StaticSounds: %05d - Max: %05d"
void __fastcall FUN_00406760(void (__fastcall *sink)(char* line))
{
    if (DAT_0087E298) {
        char line[200];
        sprintf(line, "AudioEvents : %05d - Max: %05d", DAT_0087E28C, DAT_0087E290);
        sink(line);
        sprintf(line, "StaticSounds: %05d - Max: %05d", DAT_00B1D3A8, DAT_00B1D3AC);
        sink(line);
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87E28C
int DAT_0087E28C;
// GLOBAL: GAMEMD 0x87E290
int DAT_0087E290;
// GLOBAL: GAMEMD 0x87E298
int DAT_0087E298;
// GLOBAL: GAMEMD 0xB1D3AC
int DAT_00B1D3AC;
// END defined globals
