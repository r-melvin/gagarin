// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x66D3A0.

#include "rules_class_colors_methods.h"

// FUNCTION: GAMEMD 0x66D3A0
//
// Read the [Colors] section: every key names a colour, read as "r,g,b" with
// black as the default, registered under that name and then materialised as
// two colour schemes (the normal shade and the 0x35 one). Reports whether the
// section exists at all.
//
// PARTIAL (79.5%, 58/73). Mnemonic multiset identical, frame and every slot
// exact (default at [ESP+0x10], wrapper buffer at [ESP+0x14], the copy in the
// pINI home slot at [ESP+0x1C]); every remaining diff is register naming in
// the three section-name argument groups after the inlined Exists bool.
// Retail loads the section into ECX for GetKeyCount and EDX for GetKeyName
// where cl 8804 picks EAX/ECX (the systematic EAX-avoidance already recorded
// on Read_WallModel 0x66D1F0, Read_ElevationModel 0x66D150 and Read_ColorAdd
// 0x66D480), and for the ReadColor call retail evaluates section (ECX), then
// key (ESI), then the default `LEA EAX` and the wrapper buffer `LEA EDX`
// before the four pushes, where cl 8804 evaluates the default LEA first, the
// section into EAX, and takes the buffer address only after three pushes.
// Replacing the Exists inline with a bare pointer test restores retail's
// ECX/EDX choice in the first two groups (but loses the SETNZ/TEST AL
// round-trip, 8 fewer matches), which pins the remaining delta on how the
// materialised bool perturbs allocation in this compiler build. Variants
// tried on top of the Exists inline: a named `black` default local, the
// pointer-form ReadColor with a caller buffer, the wrapper binding `&out` to
// a pointer first, the YRpp call-then-return-local wrapper, a free __inline
// wrapper, the wrapper with a `const ColorStruct*` default, assignment
// instead of copy-init in the caller, a per-iteration `section` local, and
// the probe as a bool local, an int local, `== true`, an early return and an
// Exists body written through a local. Recorded as a candidate for the
// 8447-vs-8804 list.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (a single prologue
// EBP on both sides, five sunk on both), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
bool RulesClass::Read_Colors(CCINIClass* pINI)
{
    if (pINI->INIClass::Exists(ColorsSection, 0)) {
        int count = pINI->GetKeyCount(ColorsSection);
        for (int i = 0; i < count; i++) {
            const char* key = pINI->GetKeyName(ColorsSection, i);
            ColorStruct color = pINI->ReadColor(ColorsSection, key,
                                                ColorStruct(0, 0, 0));
            FUN_00626AB0(key, &color);
            ColorScheme::FindByName(key, &color, &DAT_00886380, &DAT_00885780, 1);
            ColorScheme::FindByName(key, &color, &DAT_00886380, &DAT_00885780, 0x35);
        }
        return true;
    }
    return false;
}
