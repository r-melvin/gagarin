// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at each annotated address below.

#include "small_misc43_methods.h"

// FUNCTION: GAMEMD 0x4053E0
// REGISTER-PRESSURE DELTA (status partial, 18.2%). With an ordinary state
// read VC6 folds the load into `CMP dword ptr [ESI+0x1C],2` where retail loads
// to EAX first; the volatile read that forced the load was removed as match
// steering (it had reached 27.3%). The other residual is the 64-bit subtract. Retail pushes EDI *inside* the branch and keeps both
// halves of the accumulator live at once (`MOV ECX,[+0x140]; MOV EDI,[+0x144];
// SUB ECX,EAX; SBB EDI,EDX;` then both stores). Ours never takes a
// callee-saved register: it loads the low half, subtracts, stores it, then
// reuses the same register for the high half - correct, because MOV does not
// disturb the borrow, but four instructions arranged differently. Eight
// phrasings were tried: `-=` inline, through a named `__int64` local, with the
// accumulator read before and after the call, `unsigned __int64` throughout,
// a volatile 64-bit store, and hand-splitting the halves (which adds a `SAR
// ECX,0x1F` and is worse). None persuades VC6 to hold both halves. The cause is
// NOT the toolchain: our objects stamp @comp.id 0x000b20ff, i.e. build 8447.
// A later pass added three more (all 27.3%): the subtract through an inline
// `Sub64(__int64, __int64)` helper taking both operands by value, a union of
// a two-int pair with the `__int64` so the accumulator is copied as a struct
// before the subtract, and named `acc`/`res` temporaries loaded after the
// call; hand-splitting into unsigned halves with an explicit borrow doubles
// the instruction count. Only inline asm would reach the register pair.
void __fastcall FUN_004053E0(Obj_004053E0* self)
{
    int count = self->PauseCount;

    if (count == 0) {
        int state = self->State;

        if (state == 2) {
            __int64 now = FUN_004093B0();

            self->Accumulated -= now;
        }
    }

    self->PauseCount++;
}

// FUNCTION: GAMEMD 0x405430
//
// REGISTER-PRESSURE DELTA (status partial, 14.3%). Retail loads +0x158 twice,
// once for the entry guard and once for the decrement; with ordinary reads VC6
// shares one load (the volatile guard read that forced two was removed as
// match steering). The other residual is the one shared with 0x4053E0 - retail keeps *both* halves of the
// accumulator live (`MOV ECX,[+0x140]; MOV EDI,[+0x144]; ADD EAX,ECX;
// ADC EDX,EDI`, pushing EDI for it) while VC6 reuses one register and never
// takes a callee-saved one. Two instances of the same delta now, on an add and
// on a subtract, which makes it a class rather than a one-off - see section 4.8.
void __fastcall FUN_00405430(Obj_004053E0* self)
{
    if (self->PauseCount != 0) {
        // Decrement written twice so the `TEST` survives - section 4.6.
        int count = self->PauseCount;

        self->PauseCount = count - 1;

        if (count - 1 < 0) {
            self->PauseCount = 0;
        }

        if (self->PauseCount == 0) {
            int state = self->State;

            if (state == 2) {
                self->Accumulated = FUN_004093B0() + self->Accumulated;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x405040
//
// REGISTER-PRESSURE DELTA (status partial, 13.9%). Every instruction is present
// with the same content and in the same order; the single difference is the
// `PUSH EBP` retail emits to hold the accumulator's high word across the 64-bit
// add - the open class in section 4.8, already seen on 0x4053E0 and 0x405430.
// That one missing instruction shifts everything after it, which is what the
// score reflects rather than any wrong code.
void __cdecl FUN_00405040()
{
    if (DAT_0087E2A0 == 0) {
        return;
    }

    Obj_004053E0* node = DAT_0087E180.Next;

    if (node == &DAT_0087E180) {
        return;
    }

    do {
        // Retail loads +0x158 twice here, as in 0x405430; not steered.
        if (node->PauseCount != 0) {
            int count = node->PauseCount;

            node->PauseCount = count - 1;

            if (count - 1 < 0) {
                node->PauseCount = 0;
            }

            if (node->PauseCount == 0 && node->State == 2) {
                node->Accumulated = FUN_004093B0() + node->Accumulated;
            }
        }

        node = node->Next;
    } while (node != &DAT_0087E180);
}
