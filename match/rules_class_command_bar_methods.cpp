// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x674650.

#include "rules_class_command_bar_methods.h"

// FUNCTION: GAMEMD 0x674650
//
// Read the advanced command bar layout from the single-player or multiplayer
// section. Every one of the 25 command slots is first reset to the not-found
// index; the comma-separated ButtonList value is then walked with strtok and
// each recognised command name records its position in the bar, after which
// the bar is sized to the number of names seen. Reports whether the section
// exists at all.
bool RulesClass::Read_AdvancedCommandBar(CCINIClass* pINI, bool multiplayer)
{
    const char* section = multiplayer ? MultiplayerAdvancedCommandBarSection
                                      : AdvancedCommandBarSection;
    if (pINI->INIClass::Exists(section, 0)) {
        for (int i = 0; i < 25; i++) {
            FUN_006CFD20(i, DefaultCommandIndex);
        }

        char buffer[512];
        if (pINI->ReadString(section, ButtonListKey, ButtonListDefault,
                             buffer, sizeof(buffer))) {
            int count = 0;
            int position = 0;
            for (char* token = strtok(buffer, ","); token != 0;
                 token = strtok(0, ",")) {
                int index = FUN_006CFCC0(token);
                if (index != DefaultCommandIndex) {
                    FUN_006CFD20(index, position);
                }
                count++;
                position++;
            }
            FUN_006CFDB0(count);
        }
        return true;
    }
    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8427CC
int DefaultCommandIndex = -1;
// GLOBAL: GAMEMD 0x839D10
extern const char STR_00839D10[] = "ButtonList";
// GLOBAL: GAMEMD 0x839D1C
extern const char STR_00839D1C[] = "MultiplayerAdvancedCommandBar";
// GLOBAL: GAMEMD 0x839D3C
extern const char STR_00839D3C[] = "AdvancedCommandBar";
// GLOBAL: GAMEMD 0x839D10
extern const char STR_00839D10[];
// GLOBAL: GAMEMD 0x839D1C
extern const char STR_00839D1C[];
// GLOBAL: GAMEMD 0x839D3C
extern const char STR_00839D3C[];
// END defined globals
