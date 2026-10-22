// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x720B20 and 0x721140
//   (names from the YRpp method map).

#include "theme_class_queue_methods.h"

// FUNCTION: GAMEMD 0x720B20
//
// Queue a score to play next; the function's own trace names it
// Theme::QueueSong. Gated on scores being present, the audio engine
// being up and the suppress byte being clear; the request is recorded before
// the "no-op" indexes (-1 / -2 / already-last) are filtered out. With a live
// stream, a fade already in progress that has finished is cleared, and if the
// stream reports it is playing it is told to fade and the flag is set.
//
// The bool round-trip after the 0x408070 call (`TEST EAX,EAX; SETNZ AL; CMP
// AL,1; JNZ`) is a flag declared before the stream block, assigned inside it
// and compared `== true` after it; every same-block spelling folds to a bare
// TEST/JZ (61.7%). The engine probe 0x407000 returns int (retail tests EAX).
void ThemeClass::QueueSong(int theme)
{
    if (ScoresPresent_00A8EC74) {
        if (FUN_00407000() && !DAT_00A8ED64) {
            this->QueuedTheme = theme;
            if (theme != -1 && theme != -2 && theme != this->LastTheme) {
                // STRING: GAMEMD 0x8447D4
                FUN_004068E0("Theme::QueueSong(%d)\n", theme);
                bool playing = false;
                if (this->Stream != 0) {
                    if (this->IsFading) {
                        if (this->Stream->FUN_004080D0() == 0)
                            this->Stream->FUN_00407F40();
                    }
                    playing = this->Stream->FUN_00408070() != 0;
                }
                if (playing == true) {
                    if (this->Stream != 0)
                        this->Stream->FUN_004080C0();
                    this->IsFading = true;
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x721140
//
// Whether `theme` may be played now. The two sentinels (-3 / -2) are always
// available. A real index must be inside the vector (unsigned compare), the
// entry must exist and be a normal score, its side (if any) must match the
// current player's, and outside campaign mode its scenario gate must not
// exceed the scenario's counter.
bool ThemeClass::IsAvailable(int theme) const
{
    if (theme == -3 || theme == -2)
        return true;
    if ((unsigned int)theme >= (unsigned int)this->Themes.Count)
        return false;

    ThemeControl* control = this->Themes.Items[theme];
    if (!control->Exists)
        return false;
    if (!control->Normal)
        return false;
    if (CurrentPlayer_00A83D4C != 0 && control->Side != -1
        && CurrentPlayer_00A83D4C->Type->SideIndex != control->Side)
        return false;
    if (GameMode_00A8B238 == 0
        && ScenarioInstance_00A8B230->At_1254 < control->Scenario)
        return false;
    return true;
}
