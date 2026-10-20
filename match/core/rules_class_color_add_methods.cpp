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
// PARTIAL (63.6%, 42/66). Mnemonic multiset identical; every remaining diff is
// register naming plus one extra byte store of my own making. Retail holds a
// zero in EBX for the whole body (`XOR EBX,EBX` right after the inlined
// section probe) and spends it on `CMP AL,BL`, `CMP EAX,EBX` (count > 0) and
// the three default-colour bytes `MOV [ESP+0x2C..0x2E],BL`; `count` is then
// spilled to [ESP+0x14] and reloaded per iteration. cl 8804 only grants the
// register from FOUR live zero stores (three keep byte immediates and the
// compares fold to TEST, scoring 3.0%), so the default is written here as a
// four-byte zero block whose fourth byte lands in the otherwise unused padding
// of the parameter home slot — that is the one extra `MOV [ESP+0x2F],BL`.
// With the register in place the prologue, the probe, the guard, the loop
// pushes, the three stores and both epilogues are byte-exact; what is left is
// (1) retail loading the section name into ECX/EDX where cl 8804 picks EAX/ECX
// after the inlined bool (the systematic EAX-avoidance already recorded on
// Read_ElevationModel 0x66D150) and (2) retail parking the Read3Bytes result
// in ECX (`MOV ECX,EAX; MOV EDX,EBP`) before the three-byte copy where cl 8804
// copies straight from EAX (the open "trailing object parked in EAX" class).
// Variants tried for the zero: aggregate `{0,0,0}` / member stores / chained
// assignment / one- and three-arg inline ctors (init-list, body, int params)
// as a named local, a const-ref temporary and a copy-initialised local; a
// byte or int zero variable at function or loop scope with the compares
// written against it; explicit `count > 0` / `count <= 0` guards, `while`
// and `do` loops; `!= false`, `== false`, `!`, bool/uchar locals for the
// probe; dead zero initialisers; an intrinsic memset; /O1, /Os, /Ox, /Ob0,
// /Oy- flag checks. The `key` local (retail evaluates GetKeyName before
// building the default) and the Exists inline are the two phrasings that
// moved the shape.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, EBP,
// EDI on both sides), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
bool RulesClass::Read_ColorAdd(CCINIClass* pINI)
{
    if (pINI->Exists(ColorAddSection)) {
        int count = pINI->GetKeyCount(ColorAddSection);
        for (int i = 0; i < count; i++) {
            const char* key = pINI->GetKeyName(ColorAddSection, i);
            // Retail: ColorStruct(0, 0, 0) — see the PARTIAL note above for
            // why the zero block is four bytes here.
            unsigned char black[4] = { 0, 0, 0, 0 };
            this->ColorAdd[i] = pINI->ReadColor(ColorAddSection, key,
                                                *(ColorStruct*)black);
        }
        return true;
    }
    return false;
}
