// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The two __thiscall members of FlyLocomotionClass that drive the touchdown
//   spin and the landing switch. Bytes diffed against the user's retail
//   gamemd.exe v1.001; bodies ordered ascending by retail address.
#include <stdlib.h>
#include "fly_locomotion_spin_methods.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x87F7E8 — the map.

// MATCHED (second look): the earlier residual was the destination of the
// spin/facing addition. Reading the facing first into a named local and forming
// `base + unknown_54 * 256` as a separate int keeps the sum in 32 bits (the
// inlined form narrowed to 16-bit operations), and the negative-rate decay arm
// must re-read `unknown_54` (`unknown_54 = unknown_54 + step`) rather than reuse the
// `rate` local to get retail's `ADD ECX,EAX`.
//
// One frame of the touchdown spin: while the spin is running and the client
// still has travel left, either step the shared move and, once it reports
// arrival, stop spinning and touch the cell under the client, or turn the
// client by the current spin rate and decay that rate one step toward zero.
// FUNCTION: GAMEMD 0x4CE5A0
void FlyLocoSpin::ProcessSpin()
{
    if (IsSpinning == 0) {
        return;
    }
    if (LinkedTo->Remaining <= 0) {
        return;
    }

    if (((ILoco_004CE5A0*)&LocomotorVptr)->MoveStep() == 0) {
        DirValue_004C93D0 current;
        int base = LinkedTo->Facing.Current(&current)->Value;
        int turn = base + unknown_54 * 256;
        Facing_004C9300 turned;
        turned.Raw = (short)turn;
        Facing_004C9300 passed = turned;
        LinkedTo->Facing.Assign(&passed);

        int rate = unknown_54;
        int step = abs(rate);
        if (step >= 1) {
            step = 1;
        }
        if (rate < 0) {
            unknown_54 = unknown_54 + step;
            return;
        }
        unknown_54 = rate - step;
        return;
    }

    IsSpinning = 0;
    Coord_004CE5A0 where = LinkedTo->Location;
    Map_0087F7E8.GetCellAt(&where)->Touch();
}

// Switch the locomotor into its landing state. A client that is not a
// building-like object, or whose type does not carry the gate byte, or that
// is already standing on an occupied cell, simply flips the three flags and
// clears the travel; the one that passes every test is told to park instead.
// FUNCTION: GAMEMD 0x4CFA70
void FlyLocoSpin::BeginLanding()
{
    if ((LinkedTo->*LinkedTo->Vtbl->At_184)() == 7 ||
        ((FootGate_00705D60*)LinkedTo)->IsCarryingSomething() == 0) {
        if ((LinkedTo->*LinkedTo->Vtbl->At_2C)() == 2) {
            Foot_004CFA70* linked = LinkedTo;
            if (linked->Type->At_E0D != 0) {
                void* here = (linked->*linked->Vtbl->At_1BC)();
                void* cell = ((CellFinder_0047C520*)here)->ToCell();
                if (((FootOccupier_0065AD50*)LinkedTo)->IsOccupied(cell) == 0) {
                    (linked->*linked->Vtbl->At_484)(0, 1);
                    return;
                }
            }
        }

        IsTakingOff = 0;
        IsLanding = 1;
        Unknown52 = 0;
        FlightLevel = 0;
    }
}
