// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// File-scope timer objects, one per retail unit, each initialised by an inline constructor
// that stamps the start tick from the clock at +4 (GameClockClass::GetTime, 0x6C8C40) and
// registers an empty exit stub with atexit. The eight-byte form has start tick and clock;
// the twelve-byte form adds a zeroed duration at +8. Each is a separate retail unit; they
// share this file only to share the class views.
#include "../_layout/elapsed_timer.h"

struct StaticElapsedTimer : ScenarioElapsedTimer { ~StaticElapsedTimer() {} };
struct StaticGameTimer : GameTimerClass { ~StaticGameTimer() {} };

// SYNTHETIC: GAMEMD 0x005DAEE0 -- initialiser of DAT_00AC0230
// GLOBAL: GAMEMD 0x00AC0230
StaticElapsedTimer DAT_00AC0230;
// SYNTHETIC: GAMEMD 0x00646D90 -- initialiser of DAT_00AC6648
// GLOBAL: GAMEMD 0x00AC6648
StaticGameTimer DAT_00AC6648;
// SYNTHETIC: GAMEMD 0x00683280 -- initialiser of DAT_00B05478
// GLOBAL: GAMEMD 0x00B05478
StaticElapsedTimer DAT_00B05478;
// SYNTHETIC: GAMEMD 0x00692240 -- initialiser of DAT_00B05638
// GLOBAL: GAMEMD 0x00B05638
StaticElapsedTimer DAT_00B05638;
// SYNTHETIC: GAMEMD 0x006C6AD0 -- initialiser of DAT_00B0BD28 (the game timer, see game_timing_methods.h)
// GLOBAL: GAMEMD 0x00B0BD28
StaticGameTimer DAT_00B0BD28;
