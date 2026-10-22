// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x720EA0 (name from
//   the YRpp method map).

#include "theme_class_stop_methods.h"

// FUNCTION: GAMEMD 0x720EA0  ThemeClass::Stop (__thiscall, ret 0x4)
//
// Stop the current score. Gated on scores being present, the audio engine
// being up, the suppress byte being clear and a score actually being current.
// With `fade` and a live stream, a finished fade is first cleared, and if the
// stream reports it is playing it is told to fade out and the fading flag is
// set; otherwise the stream is stopped outright. Either way the current, last
// and queued indexes are reset.
//
// The bool round-trip after the 0x408070 call (`TEST EAX,EAX; SETNZ AL; CMP
// AL,1; JNZ`) is a flag declared before the fade block, assigned inside it
// and compared `== true` after it; every same-block spelling folds to a bare
// TEST/JZ (41.4%). The three -1 stores are one tail reached by `goto`; a
// duplicated copy makes VC6 hoist -1 into EDI.
void ThemeClass::Stop(bool fade)
{
    if (!ScoresPresent_00A8EC74) {
        return;
    }
    if (!FUN_00407000()) {
        return;
    }
    if (DAT_00A8ED64) {
        return;
    }
    if (this->CurrentTheme == -1) {
        return;
    }

    bool playing = false;
    if (fade && this->Stream != 0) {
        if (this->IsFading) {
            if (this->Stream->FUN_004080D0() == 0) {
                this->Stream->FUN_00407F40();
            }
        }
        playing = this->Stream->FUN_00408070() != 0;
    }
    if (playing == true) {
        // STRING: GAMEMD 0x844830
        FUN_004068E0("Theme::Stop(%d) - Fading\n", this->LastTheme);
        if (this->Stream != 0) {
            this->Stream->FUN_004080C0();
        }
        this->IsFading = true;
        goto reset;
    }

    // STRING: GAMEMD 0x84481C
    FUN_004068E0("Theme::Stop(%d)\n", this->LastTheme);
    if (this->Stream != 0) {
        this->Stream->FUN_00407F40();
    }

reset:
    this->CurrentTheme = -1;
    this->LastTheme = -1;
    this->QueuedTheme = -1;
}
