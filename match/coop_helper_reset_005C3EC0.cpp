// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes read from retail gamemd.exe v1.001 at 0x5C3EC0.
//   PLACEMENT LEAD (inference): its caller 0x5C2040 in MPCoop.cpp reaches it by a real CALL. At /Ob2
//   cl inlines any body it can see, so the retail call implies the body was compiled in a different
//   original object than that caller. This file is that separate object; the original file name is
//   not known and is not claimed.
#include "FUNCTION.H"
#include "mp_cooperative.h"
#include "mp_game_mode_class_methods.h"

// TUSPLIT: GAMEMD 0x5C2040 same-file 9.4% separate 100.0%
// FUNCTION: GAMEMD 0x5C3EC0
// Replace the helper at +0x40 with a fresh one, run its 0x49CAF0(0), and with
// exactly two entries in the game-mode array hand both to 0x49B760. True when
// the helper exists.
bool MPCooperative::FUN_005C3EC0()
{
    if (unknown_40 != 0) {
        delete unknown_40;
    }
    unknown_40 = 0;
    unknown_40 = new CoopCampaignClass;
    unknown_40->FUN_0049CAF0(0);
    if (MPGameModeArray.Count == 2) {
        unknown_40->FUN_0049B760(((void**)MPGameModeArray.Items)[0],
                                 ((void**)MPGameModeArray.Items)[1]);
    }
    return unknown_40 ? true : false;
}

