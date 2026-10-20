// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6CC2B0.

#include "super_class_readiness_methods.h"

// FUNCTION: GAMEMD 0x6CC2B0
//
// The sidebar caption for a superweapon's state. A suspended weapon reads
// "on hold" whatever else is true. A charge-drain weapon (Yuri's Psychic
// Dominator style) names its drain state - charging, ready, or firing - and has
// no caption for any other state. A plain weapon reads "ready" once charged and
// nothing before.
//
// The drain state is a real `switch`: retail lowers the three dense cases to
// `SUB ECX,0 / DEC ECX / DEC ECX` and places the case bodies 2, 1, 0 after
// the fall-through default. Two shape points matter: the "on hold" caption is
// the trailing block (the IsSuspended test jumps forward over everything, so
// the body sits under `if (!IsSuspended)`), and the switch carries its own
// `default: return 0;` - without it VC6 sinks the shared `XOR EAX,EAX; RET`
// to the end and turns the last case test into a `JNE default` (34.7%).
gg_wchar* SuperClass::NameReadiness() const
{
    if (!this->IsSuspended) {
        if (this->Type->UseChargeDrain) {
            switch (this->ChargeDrainState) {
            case 0:
                return FUN_00734E60(DAT_008424EC, 0, DAT_00842510, 0x397);
            case 1:
                return FUN_00734E60(DAT_0081B454, 0, DAT_00842510, 0x39A);
            case 2:
                return FUN_00734E60(DAT_008424FC, 0, DAT_00842510, 0x39D);
            default:
                return 0;
            }
        } else if (this->IsReady) {
            return FUN_00734E60(DAT_0081B454, 0, DAT_00842510, 0x3B0);
        }
        return 0;
    }

    return FUN_00734E60(DAT_0083FB2C, 0, DAT_00842510, 0x3B6);
}
