// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x720960 (constructor, 0x41 bytes) and 0x720770 (Clear, 0x71 bytes); layout and
//   vector instantiation in match/_layout/theme_class.h.
#include "../core/vector_class_operations.h"
#include "../_layout/theme_class.h"

// FUNCTION: GAMEMD 0x720960
// No score playing or queued, full volume, no flags, an empty score list and no stream.
ThemeClass::ThemeClass()
    : CurrentTheme(-1), LastTheme(-1), QueuedTheme(-1), Volume(0xFF),
      IsScoreRepeat(false), IsFading(false), IsScoreShuffle(false), Stream(0)
{
}

// FUNCTION: GAMEMD 0x720770
// Delete every registered score, then shut down and release the stream.
void ThemeClass::Clear()
{
    while (Themes.Count > 0) {
        delete Themes.Items[0];
        Themes.Delete(0);
    }
    if (Stream != 0) {
        Stream->FUN_004080C0();
        Stream->FUN_004080F0();
        Stream->FUN_00407F40();
        Stream->FUN_00407A90();
        Stream = 0;
    }
}
