// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Skirmish.cpp. The name is the source-file string at 0x83fc4c
//   in retail gamemd.exe v1.001, passed by the assert at 0x6acc2a inside this object's
//   code range (0x6ac970-0x6aef0f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "mathtbl_init_shapes.h"
#include "_rt/gg_static_assert.h"
#include "multiplayer_game_mode.h"

// GLOBAL: GAMEMD 0x7F3138
extern const double DAT_007F3138;
// GLOBAL: GAMEMD 0xB0B540
extern double DAT_00B0B540;
// GLOBAL: GAMEMD 0xB0B578
extern double DAT_00B0B578;
// GLOBAL: GAMEMD 0xB0B590
extern double DAT_00B0B590;

// SYNTHETIC: GAMEMD 0x006AC9A0
// dynamic initializer for DAT_00B0B590

// GLOBAL: GAMEMD 0x00B0B590
double DAT_00B0B590 = DAT_00B0B540 / DAT_007F3138;

// SYNTHETIC: GAMEMD 0x006AC9C0
// dynamic initializer for DAT_00B0B578

// GLOBAL: GAMEMD 0x00B0B578
double DAT_00B0B578 = 1.0 / DAT_00B0B590;

// SYNTHETIC: GAMEMD 0x006ACB40
// GLOBAL: GAMEMD 0x00B0B580
MathTblCoord DAT_00B0B580;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F3138
extern const double DAT_007F3138 = 60.0;
// END defined globals

struct HWND__;

// GLOBAL: GAMEMD 0xA8B23C
extern MultiplayerGameMode* DAT_00A8B23C;

// FUNCTION: GAMEMD 0x4E5940 (decl; reloc) -- the team control of a slot index.
int __fastcall FUN_004E5940(int index);
// FUNCTION: GAMEMD 0x4E5ED0 (decl; reloc) -- set the team control, RET 4.
void __fastcall FUN_004E5ED0(HWND__* dialog, int control, int value);

// FUNCTION: GAMEMD 0x6ACE80
void __fastcall FUN_006ACE80(HWND__* dialog, int count)
{
    if (dialog && DAT_00A8B23C) {
        int first = 1;
        int last = 8;
        if (count > 0 && count < last) {
            first = count;
            last = count + 1;
        }
        for (int i = first; i < last; i++) {
            int control = FUN_004E5940(i);
            if (DAT_00A8B23C && DAT_00A8B23C->AlliesAllowed)
                FUN_004E5ED0(dialog, control, 3);
            else
                FUN_004E5ED0(dialog, control, -2);
        }
    }
}
