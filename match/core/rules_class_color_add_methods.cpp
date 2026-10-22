// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x66D480.

#include "rules_class_color_add_methods.h"

// FUNCTION: GAMEMD 0x66D480
//
// Read the [ColorAdd] section: every key in order becomes the next entry of
// the ColorAdd table, defaulting to black when the value does not parse.
// Reports whether the section exists at all.
//
// PARTIAL (81.8%, 54/66; was 63.6%). Mnemonic multiset identical. The lever is
// a named three-byte `black` default plus a named `c` copy of the read colour
// that is then assigned into the table: that alone reproduces retail's zero in
// EBX (`CMP AL,BL`, `CMP EAX,EBX`, the three `MOV [ESP+0x2C..0x2E],BL` stores
// and the `count` spill), so the old four-byte padding-store hack is gone. What
// remains: (1) retail loads the section name into ECX/EDX where cl picks
// EAX/ECX after the inlined bool probe (the EAX-avoidance already recorded on
// Read_ElevationModel 0x66D150); (2) the wrapper's read buffer and the spilled
// `count` sit in swapped halves of the 8-byte local area (count at [ESP+0x10]
// here, at [ESP+0x14] in retail). Variants tried on top: a temporary default
// inline in the call, the default declared above the loop, per-byte copy of the
// result, direct assignment from the wrapper (1.5%), `key` and `black` order.
bool RulesClass::Read_ColorAdd(CCINIClass* pINI)
{
    if (pINI->Exists(ColorAddSection)) {
        int count = pINI->GetKeyCount(ColorAddSection);
        for (int i = 0; i < count; i++) {
            const char* key = pINI->GetKeyName(ColorAddSection, i);
            ColorStruct black(0, 0, 0);
            ColorStruct c = pINI->ReadColor(ColorAddSection, key, black);
            this->ColorAdd[i] = c;
        }
        return true;
    }
    return false;
}
