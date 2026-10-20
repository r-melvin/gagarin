// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x445F00.

#include "damage_flags_methods.h"

// FUNCTION: GAMEMD 0x445F00
//
// Fold the two slotted entries' flag masks into the caller's flags, set bit 0
// unconditionally, and apply the result.
//
// The accumulator is the `incoming` parameter itself. Retail loads it into its
// register only when it is first needed — `MOV EDI,[ESP+0xC]; OR EDI,EAX` in
// the hit arm and a bare `MOV EDI,[ESP+0xC]` in the miss arm (0x445F26 /
// 0x445F2E) — which is what a parameter enregistered in EDI and OR-ed in place
// gives. Any separate `flags` local, whatever the operand order, makes VC6
// move the call result out of EAX first (`MOV EDI,EAX; MOV EAX,[ESP+0xC]; OR
// EDI,EAX`, 30.2%).
//
// Each slot is fetched twice — once to test its leading word and again to read
// it — rather than being held across the test. Retail does that on both halves
// (0x445F08/0x445F19 and 0x445F38/0x445F49), so the double call is in the source.
void BuildingClass_00445F00::FUN_00445F00(unsigned int incoming, int b, int c)
{
    if ((this->*this->Vtbl->At_3F8)(0)->First != 0) {
        incoming |= FUN_00772A90((this->*this->Vtbl->At_3F8)(0)->First);
    }
    if ((this->*this->Vtbl->At_3F8)(1)->First != 0) {
        incoming |= FUN_00772A90((this->*this->Vtbl->At_3F8)(1)->First);
    }
    this->FUN_006F8DF0(incoming | 1, b, c);
}
