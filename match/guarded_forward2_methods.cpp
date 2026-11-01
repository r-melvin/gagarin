// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x433EF0 and 0x4340A0.

#include "guarded_forward2_methods.h"

// FUNCTION: GAMEMD 0x433EF0
void* Forwarder_00433EF0::FUN_00433EF0(void* first, void* second)
{
    if (Guard) {
        State = 2;

        FUN_00433CF0(first, &second, 0, second);

        State = 1;

        return second;
    }

    FUN_00433CF0(first, &second, 0, second);

    return second;
}

// FUNCTION: GAMEMD 0x4340A0
void Forwarder_00433EF0::FUN_004340A0(void* first, void* second, int third,
                                      void* fourth)
{
    if (Guard) {
        State = 2;

        FUN_00433CF0(first, second, third, fourth);

        State = 1;

        return;
    }

    FUN_00433CF0(first, second, third, fourth);
}
