// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x406060.

#include "audio_end_looping_methods.h"

// FUNCTION: GAMEMD 0x406060
//
// Stop a looping voice through a handle, but only if the handle is still the
// live one: the handle's token and serial must match the voice's, the token
// must actually be looping (bit 0 set, +0x4C clear), and a voice already marked
// finished is left alone. On the live path the peer is notified on both sides
// of the finished-flag update.
//
// The handle's token is cleared on every exit; the voice pointer is cleared on
// every exit past the token/serial check except the not-looping one, which
// keeps the voice so a later call can still find it.
//
// Phrasing notes (each is load-bearing for the bytes):
//   * Every rejecting branch writes its own stores and returns. That is what
//     puts zero in EBX: VC6 decides the constant register by the source-level
//     use count (here 4 compares + 15 stores) before it cross-jumps the
//     identical `Token = 0; return` blocks into retail's shared exits at
//     0x4060E5/0x4060E7. The eight-use goto form (as at 0x405FD0) never gets
//     the register.
//   * The finished-bit test reads the byte alias `FlagsLow`, not `Flags`, so
//     the dword load is not CSE'd into the `|= 0x60` of the else path — retail
//     tests memory directly (`TEST byte ptr [EDI+0x18],0x20`).
//   * `voice == peer->Voice` (register first) gives retail's operand order.
//   * The two forwarders are __thiscall members of the peer.
//
// PARTIAL (35.2%, 19/54). Mnemonic multiset: retail has one extra MOV. Two
// residual deltas, both in the peer path at 0x406047..0x40606F:
//   1. Retail parks the peer in EAX (`MOV EAX,[EDI+0xB0]; CMP EAX,EBX; ...;
//      CMP EDI,[EAX+0xC0]; MOV ECX,EAX; CALL`) and pays the receiver copy; VC6
//      loads it straight into ECX and skips the MOV (the open "trailing object
//      parked in EAX" class in the methodology).
//   2. On the live path retail updates the flags in EDX and loads the peer
//      after the store (`MOV EDX,[EDI+0x18]; OR EDX,0x60; MOV [EDI+0x18],EDX;
//      MOV ECX,[EDI+0xB0]`); VC6 uses EAX (`OR AL,0x60`) and hoists the peer
//      load above the store.
// Everything from 0x406000 to 0x406045 and the whole finish/clear tail is
// byte-exact; the remaining DIFF rows are alignment after those nine.
// Variants tried: goto-CFG with a named `int zero` (1.9%, no EBX); natural
// nested ifs with fall-through exits (1.9%, no EBX); duplicated early returns
// with literal zeros / named zero / `goto finish` (29.5-33.3%); the byte-alias
// test plus if/else peer path (35.2%, kept); no `peer` local, re-reading
// voice->Peer for CSE (35.2%, same bytes); `peer` reused for the second call
// (3.5%: VC6 keeps it live in EBX and spills zero to EBP); __fastcall free
// functions instead of members (same bytes as members); 0x4026A0 declared
// int-returning (no change).
// Lift pass (2026-09-18): the peer read through a volatile pointer alias
// (`peer = *(Peer_00406060* volatile*)&voice->Peer;`) - 35.2%, identical
// stream. The twin at 0x405FD0 carries exactly the same two deltas and three
// further phrasings were rejected there this pass (in-class inline accessor,
// __thiscall member call, volatile), so the two sites are one open class:
// cl 8804 resolves the peer's home to ECX at the load and never materialises
// retail's `MOV ECX,EAX`; the EDX flags update is downstream of that.
void AudioController::EndLooping()
{
    AudioEvent* voice;
    AudioEventType* token;
    Peer_00405D40* peer;

    if (DAT_0087E2A0 == 0) { this->EventType = 0; return; }
    if (this->AudioIndex != &AudioIDXData_Instance) { this->EventType = 0; return; }
    voice = this->Event;
    if (voice == 0) { this->EventType = 0; return; }
    token = voice->EventType;
    if (this->EventType != token) { this->Event = 0; this->EventType = 0; return; }
    if (this->Stamp != voice->Serial) { this->Event = 0; this->EventType = 0; return; }
    if ((token->Control & 1) == 0) { this->EventType = 0; return; }
    if (token->Loop != 0) { this->EventType = 0; return; }
    if ((voice->FlagsLow & 0x20) != 0) { this->Event = 0; this->EventType = 0; return; }

    peer = voice->Peer;
    if (peer != 0 && voice == peer->Voice) {
        peer->FUN_004026A0();
        voice->Flags = voice->Flags | 0x60;
        voice->Peer->FUN_004026B0();
        this->Event = 0;
        this->EventType = 0;
        return;
    }

    voice->Flags = voice->Flags | 0x60;
    this->Event = 0;
    this->EventType = 0;
}
