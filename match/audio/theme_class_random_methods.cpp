// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x720A80. Name from
//   YRpp ThemeClass.h (consult-only).

#include "theme_class_random_methods.h"

// FUNCTION: GAMEMD 0x720A80
//
// Pick the next score after `index`. A valid index whose score (or the whole
// jukebox) is set to repeat is handed straight back. Otherwise, in shuffle
// mode, up to 1000 random draws are made until one differs from `index` and
// is available (0 if none was found); in sequential mode the list is walked
// forward with wrap-around, at most Count+1 steps, until an available score
// turns up (again 0 if none).
//
// The `last` local is load-bearing: written inline as the call argument the
// Count-1 temporary lands in EDX, through a named local it takes EAX as retail.
int ThemeClass::GetRandomIndex(int index)
{
    if ((index > -1 && !this->Themes.Items[index]->Repeat && !this->IsScoreRepeat)
        || index < 0)
    {
        if (this->IsScoreShuffle == true)
        {
            int tries = 0;
            int pick;
            do {
                int last = this->Themes.Count - 1;
                pick = DAT_00886B88.RandomRanged(0, last);
                tries++;
            } while (tries < 1000 && (pick == index || !this->IsAvailable(pick)));

            if (tries == 1000)
                pick = 0;
            return pick;
        }

        int tries = this->Themes.Count + 1;
        do {
            index++;
            if (index >= this->Themes.Count)
                index = 0;
            tries--;
            if (tries == 0)
                return 0;
        } while (!this->IsAvailable(index));
    }
    return index;
}
