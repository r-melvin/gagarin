// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
//   Measured: the two containers are scope objects with destructors, and
//   under /GX cl registers an unwind frame - five instructions of
//   `MOV EAX,FS:[0]` prologue - that retail bare `SUB ESP,0x30` rules out.
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The flyer's target pick. Bytes diffed against the user's retail
//   gamemd.exe v1.001.
#include "fly_locomotion_pick_target_methods.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// VTABLE: GAMEMD 0x7E192C — the base vector's vtable.
// VTABLE: GAMEMD 0x7E4F64 — the growing vector's vtable.
// GLOBAL: GAMEMD 0xA8EC7C — the scanned object array.
// GLOBAL: GAMEMD 0xA8EC88 — its count.
// GLOBAL: GAMEMD 0xA8022C — the house array.
// GLOBAL: GAMEMD 0xA8B230 — the scenario object.
// GLOBAL: GAMEMD 0xA8B238 — the mode gate.

// PARTIAL -- 95.6% (219 of 229 retail instructions exact or
// reloc-normalised). The allied test is written as plain
// `if (allied) continue;`; retail jumps INTO the shared code when the two are
// not allied and over it when they are, so that one JE/JNE polarity differs
// (it scored 98.3% with an empty then-arm, which is dropped as dead code).
// The rest of the residual is one
// commutative addition's destination register, in the inlined append, and it
// appears twice because the append is inlined once per container: retail
// accumulates the growth step into the capacity's register (`ADD ECX,EAX`)
// and pushes ECX, cl accumulates into the growth step's register and pushes
// EAX. Four bytes in 752. Three materially different spellings were measured
// against the control and all four score identically at 98.3%: the operands
// reversed, the capacity bound to a named local and used in all three of its
// places, and the sum written as a compound assignment on that local. Same
// family as the residual recorded in fly_locomotion_spin_methods.cpp.
//
// Levers that did fire, in the order they were found: dropping the exception
// flag, worth 0.4% to 92.6% because /GX wraps the two container scopes in an
// unwind frame retail's bare `SUB ESP,0x30` has no room for; the owner gate
// tested for ZERO rather than non-zero, which is what leaves the flag byte at
// one on the fall-through and is the opposite of the obvious reading; the
// allied test (see above); and two store orders inside the container's own
// constructor and destructor - the growth step before the count, the
// allocation flag before the capacity.
//
// ILocomotion slot +0x94 — pick something for the flyer to head at. The whole
// global object array is run backwards; everything the flyer is allowed to
// pick is sorted into one of two vectors, the preferred one being used when
// the mode gate is on and the candidate's owner allows it, and one entry is
// drawn at random out of whichever vector filled.
// FUNCTION: GAMEMD 0x4CFE80
// Complete retail span: 0x2F2 bytes, including RET immediate at 0x4D016F.
void __stdcall FlyLocoPick::PickTarget()
{
    if (this->LinkedTo->At_2B4 != 0) {
        return;
    }

    DynVec_004CFE80 plain(0, 0);
    DynVec_004CFE80 preferred(0, 0);

    char owned;
    if (Mode_00A8B238 != 0 &&
        this->LinkedTo->Owner->At_5600 != -1 &&
        this->LinkedTo->Owner->FUN_0050B730() == 0) {
        owned = 1;
    } else {
        owned = 0;
    }

    for (int i = ObjectCount_00A8EC88 - 1; i >= 0; i--) {
        Techno_004CFE80* candidate = ObjectArray_00A8EC7C[i];

        if (owned == 0) {
            if (this->LinkedTo->Owner->IsAlliedWith(candidate->Owner) != 0) {
                continue;
            }
        } else {
            if (candidate->Owner !=
                HouseArray_00A8022C[this->LinkedTo->Owner->At_5600]) {
                continue;
            }
        }

        if (candidate->At_6C <= 0) {
            continue;
        }
        if (candidate->At_81 != 0) {
            continue;
        }
        if (candidate->At_90 == 0) {
            continue;
        }
        if ((candidate->*candidate->Vtbl->At_84)()->At_C9A != 0) {
            continue;
        }
        if ((candidate->*candidate->Vtbl->At_84)()->At_231 == 0) {
            continue;
        }
        if ((Scenario_00A8B230->Flags & 0x800) != 0 &&
            (candidate->*candidate->Vtbl->At_2C)() == 1 &&
            candidate->Type->At_E0E != 0) {
            continue;
        }

        if (Mode_00A8B238 != 0 &&
            this->LinkedTo->Owner->FUN_0050B730() != 0 &&
            candidate->Owner->At_34->At_1A6 == 0 &&
            ((candidate->*candidate->Vtbl->At_2C)() == 1 ||
             (candidate->*candidate->Vtbl->At_2C)() == 6 ||
             (candidate->*candidate->Vtbl->At_2C)() == 0xF ||
             (candidate->*candidate->Vtbl->At_2C)() == 2)) {
            if (AddItem_004CFE80(preferred, candidate) == 0) {
                continue;
            }
        } else {
            if (AddItem_004CFE80(plain, candidate) == 0) {
                continue;
            }
        }
    }

    if (preferred.Count > 0) {
        int pick = Scenario_00A8B230->RandomNumber.RandomRanged(
            0, preferred.Count - 1);
        Foot_004CFE80* flyer = this->LinkedTo;
        (flyer->*flyer->Vtbl->At_3C8)(preferred.Items[pick]);
    } else if (plain.Count > 0) {
        int pick = Scenario_00A8B230->RandomNumber.RandomRanged(
            0, plain.Count - 1);
        Foot_004CFE80* flyer = this->LinkedTo;
        (flyer->*flyer->Vtbl->At_3C8)(plain.Items[pick]);
    }
}
