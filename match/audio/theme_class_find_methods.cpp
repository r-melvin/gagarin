// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Name
//   cross-checked against YRpp (each
//   offset/global reconfirmed against the user's binary below).
//
// Translation unit: ThemeClass::FindIndex. Linear search of the Themes vector
// for a score whose ID matches the (case-insensitive) query string.
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x721210   ThemeClass::FindIndex  (__thiscall)
//   LIBRARY:  GAMEMD 0x7C8D20   _stricmp  (CRT case-insensitive compare)
//
// Codegen notes (from the disasm):
//   * The leading null guard + inlined REPNE SCASB is `id && strlen(id)` — VC6
//     /O2 expands the strlen intrinsic to the OR ECX,-1 / XOR EAX,EAX / REPNE
//     SCASB / NOT ECX / DEC ECX sequence, with the JZ folding strlen==0 onto the
//     shared "return -1" tail.
//   * Items[i] is pushed unmodified as the first _stricmp arg because ID lives at
//     ThemeControl+0, so &Items[i]->ID == Items[i].

#include "theme_class_find_methods.h"
#include <string.h>  // strlen (intrinsic under /O2), _stricmp

// FUNCTION: GAMEMD 0x721210  (__thiscall)
int ThemeClass::FindIndex(const char* id) const
{
    if (id != 0 && strlen(id) != 0) {
        for (int i = 0; i < this->Themes.Count; ++i) {
            if (_stricmp(this->Themes.Items[i]->ID, id) == 0)
                return i;
        }
    }
    return -1;
}
