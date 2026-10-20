// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the four addresses below.

#include "small_misc48_methods.h"

// FUNCTION: GAMEMD 0x406570
void __fastcall Obj_00406570::FUN_00406570(int flags)
{
    this->Flags = flags;

    if (flags & 0x20) {
        if (this->LatchA == 0) {
            this->LatchA = 1;
        }
    } else {
        this->LatchA = 0;
    }

    if (flags & 0x40) {
        if (this->LatchB == 0) {
            this->LatchB = 1;
        }
    } else {
        this->LatchB = 0;
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
void Obj_00407FB0::FUN_00408000()
{
    if (*(volatile int*)&this->Entered != 0) {
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

// FUNCTION: GAMEMD 0x409360
void __cdecl FUN_00409360()
{
    __int64 frequency;

    if (QueryPerformanceFrequency(&frequency)) {
        DAT_0087E828 = frequency / 1000;
        DAT_0087E848 = (void*)FUN_004093C0;

        return;
    }

    DAT_0087E848 = (void*)FUN_004093F0;
}

// FUNCTION: GAMEMD 0x44EB10
int BuildingClass_0044EB10::FUN_0044EB10()
{
    if (!Suppressed
        && DAT_00A8B230->Counter.FUN_0065C7E0(0, 0x63) < 0x19
        && Settings->Mode == 7) {

        return RulesInstance->Fallback;
    }

    return FUN_00707D20();
}
