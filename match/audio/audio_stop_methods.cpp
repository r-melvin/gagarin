// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x405D40.

#include "audio_stop_methods.h"

// FUNCTION: GAMEMD 0x405D40
//
// Stop a playing voice through a handle. The handle only acts if it is still
// the live one — the audio system must be up, the handle's owner must be the
// sample table, and its token and serial must still agree with the voice's —
// and a voice already marked stopped (flag bit 0) is left alone. On the live
// path the peer is detached (optionally notified first when flag bit 1 is set),
// its seven back-links are cleared, every sub-object in the +0x28 array is
// released, and the voice is reset to state 4 and marked stopped.
//
// Unlike EndLooping at 0x406060 this one is a fall-through CFG: every reject
// lands on the same two-store tail, so the guards nest and the zero lives in
// one callee-saved register for the whole body.
//
// Phrasing notes (load-bearing):
//   * The two flag tests must read the word through *different-width* union
//     aliases (`Flags` dword for bit 0, `FlagsWord` word for bit 1). With both
//     spelled at the same width cl 8804 CSEs them into one `MOV reg,[ESI+0x18]`
//     plus two register tests, which costs an extra MOV and moves the deferred
//     PUSH EBX/PUSH EDI up into the peer guard (20.7%). With the widths split,
//     both come out as retail's `TEST byte ptr [ESI+0x18],imm` straight from
//     memory and the pushes fall back to their retail positions.
//   * Nested guards with a single fall-through tail, not per-branch returns:
//     that is what shares the zero register across all four compares and the
//     fifteen stores.
//
// PARTIAL (64.2%, 52/81). The mnemonic multiset is identical (81 vs 81) — the
// residual is register naming plus one scheduling hoist:
//   1. Retail allocates the shared zero to EBP and the loop counter to EBX
//      (push order EBP, ESI, EBX, EDI); cl 8804 picks the opposite pair
//      (EBX, ESI, EBP, EDI). Every affected instruction is otherwise
//      byte-identical. This is the recorded EBX/EBP tie-break class (0x50D440).
//   2. In the reset tail retail emits the four stores first and then
//      `MOV ECX,[ESI+0x18]; OR ECX,1; MOV [ESI+0x18],ECX`; cl hoists the load
//      to the top of the block and interleaves the OR after the first store
//      (the recorded "member load hoisted over unrelated stores" class).
// Variants tried: `FlagsLow` byte alias for both tests (20.7%); two same-width
// byte aliases in the union (20.7%); plain `Flags` dword for both (20.7%);
// mixed dword/word aliases (64.2%, kept); the flags update split into
// `unsigned int flags = voice->Flags; voice->Flags = flags | 1;` (64.2%,
// byte-identical to the one-line form); and, this pass, the flags update and
// then the two preceding scalar stores routed through inline member setters
// (the "route the store through an inline setter" lever) — both 64.2%, cl
// hoists the +0x18 load regardless.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply. Both sides
// push two callee-saved registers in the prologue and sink two more at the
// same instructions, and both mid-function pops land at the same offsets; the
// block structure is identical and only the names EBX and EBP are exchanged.
// There is no merged return block to split.
void AudioHandle_00405D40::Stop()
{
    if (DAT_0087E2A0 != 0 && this->Owner == (void*)DAT_0087E294) {
        Voice_00405D40* voice = this->Voice;
        if (voice != 0) {
            if (this->Token == voice->Token && this->Serial == voice->Serial
                && (voice->Flags & 1) == 0) {
                Peer_00405D40* peer = voice->Peer;
                if (peer != 0 && voice == peer->Voice) {
                    if ((voice->FlagsWord & 2) != 0) {
                        peer->FUN_004025B0();
                    }
                    voice->Peer->FUN_004026F0();
                    voice->Peer->Voice = 0;
                    voice->Peer->At_BC = 0;
                    voice->Peer->At_B4 = 0;
                    voice->Peer->At_B8 = 0;
                    voice->Peer->At_90 = 0;
                    voice->Peer->At_98 = 0;
                    voice->Peer->At_9C = 0;
                    voice->Peer = 0;
                }

                for (int i = 0; i < voice->SubCount; ++i) {
                    FUN_00401F90(voice->Subs[i]);
                    voice->Subs[i] = 0;
                }

                voice->SubCount = 0;
                voice->State = 4;
                voice->Serial = 0;
                voice->At_278 = 0;
                voice->Flags = voice->Flags | 1;
            }

            this->Voice = 0;
        }
    }

    this->Token = 0;
}
