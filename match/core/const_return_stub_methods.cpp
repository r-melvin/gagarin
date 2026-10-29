// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Constant-return and identity leaves, ordered ascending by retail address.

#include "const_return_stub_methods.h"
#include "../_layout/frame_timer.h"

// FUNCTION: GAMEMD 0x410300
int __stdcall FUN_00410300(int)
{
    return 1;
}

// FUNCTION: GAMEMD 0x410310
int __stdcall FUN_00410310(int)
{
    return 1;
}

// FUNCTION: GAMEMD 0x4125F0
int __cdecl FUN_004125F0()
{
    return 1;
}

// FUNCTION: GAMEMD 0x412600
int __cdecl FUN_00412600()
{
    return 1;
}

// FUNCTION: GAMEMD 0x413490
// Accepts an argument and does nothing with it — an overridable no-op.
void __stdcall FUN_00413490(int)
{
}


// FUNCTION: GAMEMD 0x426620
CDTimerClass::CDTimerClass(const AbstractNoInit&)
{
}

// FUNCTION: GAMEMD 0x426630
// Frames left on the timer. A start of -1 means it has not been started yet,
// and that path returns the *full duration* rather than zero — retail's `JZ`
// there lands on the shared RET with the duration still in EAX, two bytes past
// the `XOR EAX,EAX` that the expired path uses. Reading it as a zero return
// cost one instruction in the diff and would have been a live behaviour bug.
int Obj_00426600::FUN_00426630() const
{
    int start = unknown_00;
    int duration = unknown_08;

    if (start != -1) {
        int elapsed = CurrentFrame - start;

        if (elapsed < duration) {
            duration -= elapsed;
        } else {
            return 0;
        }
    }

    return duration;
}

