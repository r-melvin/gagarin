// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x7209D0 (name from the
//   YRpp method map, consult-only).

#include "theme_class_ai_methods.h"

// FUNCTION: GAMEMD 0x7209D0
//
// One tick of the score jukebox. Nothing happens unless the audio engine is
// up, the suppress byte is clear, scores are present and the volume is
// audible. With a live stream, a fade that has finished is stopped, and a
// stream that is still playing ends the tick. Otherwise a queued score (not
// the -1 / -3 sentinels, and not while the dword gate is set) is started: the
// "pick one" sentinel -2 is first resolved through the random picker and
// logged, then the score is played and the queue reset to -2.
//
// The "still playing" flag is a bool declared before the stream block, set
// inside it and tested after it: that merge is what makes retail materialise
// the stream call's int result (`TEST EAX,EAX; SETNZ AL; TEST AL,AL; JNZ`).
// Testing the call directly, a local inside the block, a cast, a ternary or
// an inline bool wrapper all fold to a bare `TEST EAX,EAX; JNZ`.
void ThemeClass::AI()
{
    if (FUN_00407000() && !DAT_00A8ED64 && ScoresPresent_00A8EC74
        && this->Volume > 0) {
        bool playing = false;
        if (this->Stream != 0) {
            if (this->IsFading) {
                if (this->Stream->FUN_004080D0() == 0)
                    this->Stream->FUN_00407F40();
            }
            playing = this->Stream->FUN_00408070() != 0;
        }
        if (playing)
            return;

        int theme = this->QueuedTheme;
        if (theme != -1 && theme != -3 && DAT_00A8E7AC == 0) {
            if (theme == -2) {
                this->QueuedTheme = this->GetRandomIndex(this->LastTheme);
                // STRING: GAMEMD 0x8447B8
                FUN_004068E0("Theme::AI(Next song = %d)\n", this->QueuedTheme);
            }
            this->PlaySong(this->QueuedTheme);
            this->QueuedTheme = -2;
        }
    }
}
