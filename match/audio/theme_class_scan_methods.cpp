// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x7207F0.

#include "theme_class_scan_methods.h"

// FUNCTION: GAMEMD 0x7207F0
//
// Note which registered scores are actually present and how long they run.
// Each entry's sound name becomes a ".WAV" path, a stack file object answers
// whether it exists, and for the ones that do the sample header gives a
// length in milliseconds that is divided down into the entry's Length.
//
// Load-bearing: the element slot is taken into a pointer local before each
// call whose result is stored through it (retail computes the address
// first and keeps it in a callee-saved register across the call), the
// sample duration is bound before the divide so the call happens before
// the divisor is pushed, and the CRT 64-bit divide pops its own arguments
// (__stdcall) so no stack adjustment follows it.
void Theme_007207F0::Scan()
{
    if (DAT_00A8EC74 && FUN_00407000() && !DAT_00A8ED64) {
        for (int i = 0; i < Themes.Count; i++) {
            char path[0x200];
            gg_makepath(path, 0, 0, Themes.Items[i]->Sound, STR_00844768);

            File_007207F0 file;
            file.Construct(path);

            ThemeControl_007207F0** slot = &Themes.Items[i];
            (*slot)->Exists = file.Exists(0);

            if (Themes.Items[i]->Exists) {
                Audio_007207F0 audio;
                audio.Construct();
                file.Open(1);
                int length;
                if (FUN_00408610(&file, &audio, &length)) {
                    ThemeControl_007207F0** entry = &Themes.Items[i];
                    unsigned __int64 millis = FUN_00408560(&audio, length);
                    int seconds = (int)gg_aulldiv(millis, 1000);
                    (*entry)->Length = (float)seconds;
                }
            }
            file.Destruct();
        }
    }
}
