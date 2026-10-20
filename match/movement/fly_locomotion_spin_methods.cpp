// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The two __thiscall members of FlyLocomotionClass that drive the touchdown
//   spin and the landing switch. Bytes diffed against the user's retail
//   gamemd.exe v1.001; bodies ordered ascending by retail address.
#include <stdlib.h>
#include "fly_locomotion_spin_methods.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x87F7E8 — the map.

// PARTIAL -- 87.3% (71 retail instructions, identical multiset, 62 exact).
// The whole residual is one commutative addition's destination register and
// the six instructions that cascade from it: retail accumulates the shifted
// spin rate into ECX (`ADD ECX,EAX`) and stores CX into the facing temporary,
// while cl accumulates into EAX and stores AX, which then moves the LEA of
// the temporary and the receiver load past one another. Measured across
// nineteen spellings in four batches: naming the reader's result as a local
// (69.0%), re-deriving it at the use site (87.3%, the spelling kept here),
// reversing the operands (87.3%), a compound `+=` in three placements (21.9%,
// 21.9%, 69.0%), folding the whole expression into the store (64.8%), taking
// the temporary's address early (31.0%), binding the facing slot to a local
// (84.5%), declaring the two temporaries in either order (87.3%), and both
// operand orders of the decay addition in the tail (no change). Everything
// else - both guards, the interface dispatch through the object's own +0x04
// vptr, the self-copy of the by-value facing temporary, the inline `abs`, the
// clamp, both decay arms with their own epilogues, and the whole cell-touch
// block - is byte-exact.
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
        int turn = (SpinRate << 8) +
                   LinkedTo->Facing.Current(&current)->Value;
        Facing_004C9300 turned;
        turned.Raw = (short)turn;
        Facing_004C9300 passed = turned;
        LinkedTo->Facing.Assign(&passed);

        int rate = SpinRate;
        int step = abs(rate);
        if (step >= 1) {
            step = 1;
        }
        if (rate < 0) {
            SpinRate = rate + step;
            return;
        }
        SpinRate = rate - step;
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
