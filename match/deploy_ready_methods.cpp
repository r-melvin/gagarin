// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x41B890.

#include "deploy_ready_methods.h"

// FUNCTION: GAMEMD 0x41B890
//
// Whether this object may deploy: it must either have nothing at +0x2B4 or be in
// state 0x1F, its own enable byte must be set, and neither of the two mission
// values 0x1A and 0x1B may be current. The final permission comes from the linked
// type if there is one, and from the local byte at +0x3D4 if there is not.
//
// MATCHED (100.0%, 37/37; raw bytes identical apart from the one verified
// call relocation). The linked-type permission is spelled as the two-sided
// `(link == 0 && local byte) || (link != 0 && check(link))`: the second term
// re-tests the link register after the first term's byte test fails, which is
// the `TEST ECX,ECX; JZ` retail has. The slot at +0x184 is called twice and
// compared twice (0x41B8B4 and 0x41B8C3), so the two comparisons are separate
// short-circuit terms. The repeated `link != 0` is the ordinary guard that keeps
// the type check off a null link; it is not an alias, volatile or cast.
bool AircraftClass_0041B890::FUN_0041B890()
{
    if ((this->At_2B4 == 0 || this->At_AC == 0x1F)
        && this->At_3D5 != 0
        && (this->*this->Vtbl->At_184)() != 0x1A
        && (this->*this->Vtbl->At_184)() != 0x1B) {

        if ((this->At_5D4 == 0 && this->At_3D4 != 0)
            || (this->At_5D4 != 0 && FUN_006EC300(this->At_5D4))) {
            return true;
        }
    }

    return false;
}
