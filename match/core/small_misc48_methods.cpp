// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at the four addresses below.

#include "small_misc48_methods.h"

// FUNCTION: GAMEMD 0x406570
void AudioEventType::FUN_00406570(int flags)
{
    this->Control = flags;

    if (flags & 0x20) {
        if (this->Attack == 0) {
            this->Attack = 1;
        }
    } else {
        this->Attack = 0;
    }

    if (flags & 0x40) {
        if (this->Decay == 0) {
            this->Decay = 1;
        }
    } else {
        this->Decay = 0;
    }
}

// FUNCTION: GAMEMD 0x407FB0
void Obj_00407FB0::FUN_00407FB0()
{
    if (this->Entered == 0 && this->Subject != 0) {
        EnterCriticalSection(&DAT_0087E7F8);

        FUN_00402600(this->Subject);

        if (this->Flags & 1) {
            this->Flags = (this->Flags & ~1) | 2;
        }

        LeaveCriticalSection(&DAT_0087E7F8);
    }

    this->Entered++;
}

// FUNCTION: GAMEMD 0x408000
// PARTIAL: the entry guard is an ordinary read; retail loads the counter again
// for the decrement. The volatile guard read that forced it was removed as
// match steering.
void Obj_00407FB0::FUN_00408000()
{
    if (this->Entered != 0) {
        // Decrement written twice so the `TEST` survives - section 4.6.
        int entered = this->Entered;

        this->Entered = entered - 1;

        if (entered - 1 < 0) {
            this->Entered = 0;
        }

        if (this->Entered == 0 && this->Subject != 0) {
            EnterCriticalSection(&DAT_0087E7F8);

            if (this->Flags & 2) {
                this->Flags = (this->Flags & ~2) | 1;
            }

            FUN_00402650(this->Subject);

            LeaveCriticalSection(&DAT_0087E7F8);
        }
    }
}

// GLOBAL: GAMEMD 0x87E828
__int64 DAT_0087E828;

// FUNCTION: GAMEMD 0x409360
void __cdecl FUN_00409360()
{
    __int64 frequency;

    if (QueryPerformanceFrequency(&frequency)) {
        DAT_0087E828 = frequency / 1000;
        AudioTimeHook = FUN_004093C0;

        return;
    }

    AudioTimeHook = FUN_004093F0;
}
