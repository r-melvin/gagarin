// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x449BC0.

#include "small_misc54_methods.h"

// FUNCTION: GAMEMD 0x449BC0
bool Obj_00449BC0::FUN_00449BC0()
{
    // All seven refusals share the one `XOR AL,AL; POP ESI; RET` at 0x449C23,
    // so they are a single trailing `return false` reached by one condition
    // chain. There are two `MOV AL,0x1` sites though, so the early yes is its
    // own statement. Written as seven early returns VC6 emits seven epilogues
    // and scores 12.0%.
    Settings_00449BC0* settings = Settings;

    if (settings->Mode != 0) {
        if (!settings->Strict) {
            return true;
        }

        if (Session_00A8B238.GameMode != 0
            && Subject != 0
            && FUN_0050B730(Owner)
            && Session_00A8B238.GameMode != 0
            && DAT_00A8B320
            && Blocker == 0) {

            return true;
        }
    }

    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8B320
char DAT_00A8B320;
// END defined globals
