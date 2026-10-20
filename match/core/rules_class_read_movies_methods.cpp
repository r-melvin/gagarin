// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x674550.

#include "rules_class_read_movies_methods.h"

// FUNCTION: GAMEMD 0x674550  RulesClass::Read_Movies (__thiscall, ret 4)
//
// Read the [Movies] section: every key whose value is a movie name not yet
// in the global movie list gets a duplicated copy appended to it. Reports
// whether the section exists at all.
//
// The section test is CCINIClass::Exists with its key defaulted to null,
// written out in flag form (the banked Read_WallModel shape). The append is
// DynamicVectorClass::AddItem expanded inline from the header.
// STRING: GAMEMD 0x817474 ""
bool Rules_00674550::Read_Movies(CCINI_00674550* pINI)
{
    bool        ok  = false;
    const char* key = 0;

    if (key == 0) {
        ok = pINI->GetSection(MoviesSection_00674550) != 0;
    } else {
        ok = pINI->GetEntry(MoviesSection_00674550, key) != 0;
    }

    if (ok) {
        int count = pINI->GetKeyCount(MoviesSection_00674550);
        for (int i = 0; i < count; i++) {
            char buffer[0x20];
            if (pINI->ReadString(MoviesSection_00674550,
                                 pINI->GetKeyName(MoviesSection_00674550, i),
                                 "", buffer, 0x20) != 0) {
                if (FUN_0048DF30(buffer) == -1) {
                    DAT_00ABF390.AddItem(GameStrdup_00674550(buffer));
                }
            }
        }
        return true;
    }

    return false;
}
