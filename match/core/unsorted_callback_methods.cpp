// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x48D080.

#include "unsorted_callback_methods.h"

// FUNCTION: GAMEMD 0x48D080
//
// The per-frame callback: service audio, run the first pump object, do the
// in-game half when a game is running, drain the message queue playing a
// blip for every chat line from somebody else, and once a second poke the
// two devices that keep the screensaver away.
//
// PARTIAL (43.6%, 99 of 101 instructions of the same kinds). Everything
// matches in form, including the mode branch laid out with the equal-to-one
// body out of line, the packed message record whose payload int sits one
// byte into the sender word, the drain loop with its peeled entry test and
// the once-a-second device guard. The residual is retail materialising the
// two sentinel arguments into dead registers (`OR ECX,-1` / `OR EAX,-1`
// then pushing them) where cl 8804 pushes the immediates, which shifts
// every later instruction by two. Tried: the sentinels as immediates and
// through named locals, and both orders for the mode tests. Same
// materialised-push-constant class recorded for the NearByLocation sites.
void __cdecl Unsorted_CallBack()
{
    FUN_00406F70();

    if (DAT_00B45B68 > 0 && *DAT_00B45B5C != 0) {
        Pump_0048D080* pump = *DAT_00B45B5C;
        (pump->*pump->Vptr->At_08)();
    }

    if (DAT_00A8B238 == 3 || DAT_00A8B238 == 4) {
        FUN_0048D1E0();
    }

    if (DAT_00A8B238 != 1) {
        if (DAT_00A8B238 != 2) {
            goto guard;
        }
    } else if (!(DAT_00A8DAB8 & 1)) {
        return;
    }

    DAT_00A8EA70.FUN_005F1C60();
    if (DAT_00A8B230->At_3598) {
        Message_0048D080 message;
        int flag;
        while (DAT_00A8EA70.FUN_005F1C30(&message, &flag) > 0) {
            if (message.Kind == 0x6C && (message.SenderWord & 0xFF) != DAT_00A8DB30) {
                DAT_00AC4F58.FUN_00643C50(1, (double)message.Packed.Payload, -1, -1);
            }
        }
    }

guard:
    if (DAT_00A8B238 == 4 && !DAT_00B77DC2 && gg_time(0) != DAT_0089E9B0) {
        if (DAT_00AC116C != 0 && DAT_00B77DCC == 0) {
            DAT_00AC116C->Vptr->At_0C(DAT_00AC116C);
        }
        if (DAT_00AC1170 != 0) {
            DAT_00AC1170->Vptr->At_1C(DAT_00AC1170);
        }
        DAT_0089E9B0 = gg_time(0);
    }
}
