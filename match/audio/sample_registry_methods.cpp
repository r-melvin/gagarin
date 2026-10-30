// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x405FD0 and 0x4064A0.
//
// STRING: GAMEMD 0x816218  "Missing sample %s\n"

#include "sample_registry_methods.h"

// FUNCTION: GAMEMD 0x405FD0
//
// Release a voice through a handle, but only if the handle is still the live
// one: the voice's token and serial both have to match what the handle was
// issued with, and a voice already marked finished is left alone.
//
// The handle's token slot is cleared on every path, including the ones that
// reject it, and the voice pointer on every path that got past the first
// guard. Every rejecting branch writes its own stores and returns rather than
// jumping to a shared tail: VC6 decides whether to hold the zero in a
// register (`XOR EBX,EBX` at 0x405FD6) on the source-level use count, and then
// cross-jumps the identical exits itself into retail's three tails. The
// finished-bit test reads the low byte of Flags, not the dword, so the load
// is not CSE'd into the `| 0x60` of the else path — retail tests memory
// directly (`TEST byte ptr [ESI+0x18],0x20`). Both idioms are the ones that
// carry the sibling 0x406060.
//
// PARTIAL (34.0%, 17/50). Mnemonic multiset: retail has one extra MOV. The
// prologue, all six guards, the byte test and the whole finish/clear tail
// from 0x406042 are byte-exact; the residual is the peer path at
// 0x40603C..0x406039, the same two deltas the sibling carries:
//   1. Retail parks the peer in EAX (`MOV EAX,[ESI+0xB0]; CMP EAX,EBX; ...;
//      CMP ESI,[EAX+0xC0]; MOV ECX,EAX; CALL`) and pays the receiver copy;
//      cl 8804 loads it straight into ECX (the open "trailing object parked
//      in EAX" class).
//   2. On the live path retail updates the flags in EDX after the call and
//      loads the peer after the store (`MOV EDX,[ESI+0x18]; OR EDX,0x60;
//      MOV [ESI+0x18],EDX; MOV ECX,[ESI+0xB0]`); cl 8804 uses EAX
//      (`OR AL,0x60`) and hoists the peer load above the store.
// Variants tried this pass: goto-CFG with a named `int zero` (4.0%, no EBX);
// per-branch store-and-return blocks in flat form (10.5%: handle gets ESI,
// voice EDI, and the exits are not cross-jumped); three flat blocks plus
// gotos (32.0%); nested ifs with explicit exits and a dword flags test
// (48.0% — a higher positional score only because the hoisted dword load
// realigns the epilogue; structurally further, the byte test is kept); no
// `peer` local; `peer->Voice == voice`; if/else peer path; 0x4026A0
// int-returning; the callee typed on a zero-offset base of the peer; the
// peer predicate as an inlined helper — all 34.0% with the same bytes.
// Lift pass (2026-09-18): two more rejected, both still 34.0% with an
// identical stream - a genuine in-class inline accessor `voice->GetPeer()`
// (the "inline pins its return value to EAX" lever), and declaring 0x4026A0
// as a __thiscall member of Peer_00405FD0 and calling `peer->FUN_004026A0()`.
// cl 8804 decides at the load that the peer's final home is ECX and never
// materialises retail's `MOV ECX,EAX` copy; delta 2 (the EDX flags update) is
// a consequence of delta 1, since retail only needs EDX because EAX is taken.
// Lift pass 2 (2026-09-18): classified, not re-chased. Everything through the
// finished-bit test at 0x40600A is byte-exact and the sole real delta is the
// single retail-only `MOV ECX,EAX`; this is the banked 8447-vs-8804
// "receiver parked in EAX" class. Best measured form kept at 34.0% (17/50).
void FUN_00405FD0(Handle_00405FD0* handle)
{
    Voice_00405FD0* voice;
    Peer_00405FD0* peer;

    if (DAT_0087E2A0 != 0 && handle->Owner == (void*)&DAT_0087E294) {
        voice = handle->Voice;
        if (voice != 0) {
            if (handle->Token == voice->Token
                && handle->Serial == voice->Serial
                && (*(unsigned char*)&voice->Flags & 0x20) == 0) {
                peer = voice->Peer;
                if (peer != 0 && voice == peer->Voice) {
                    FUN_004026A0(peer);
                    voice->Flags = voice->Flags | 0x60;
                    FUN_004026B0(voice->Peer);
                    handle->Voice = 0;
                    handle->Token = 0;
                    return;
                }
                voice->Flags = voice->Flags | 0x60;
                handle->Voice = 0;
                handle->Token = 0;
                return;
            }
            handle->Voice = 0;
            handle->Token = 0;
            return;
        }
        handle->Token = 0;
        return;
    }
    handle->Token = 0;
}

// FUNCTION: GAMEMD 0x4064A0
//
// Append a sample to the queue by name. The queue is full at 0x20 entries and
// says so by returning 0; every other outcome — appended, or the name did not
// resolve — returns 1.
//
// Leading '$' and '#' are stripped before the lookup. They are prefixes the
// caller may pass through verbatim, not part of any sample's name.
int AudioEventType::FUN_004064A0(const char* name)
{
    if (this->SampleCount == 0x20) {
        return 0;
    }

    if (DAT_0087E2A0 != 0 && DAT_0087E294 != 0) {
        while (*name == '$' || *name == '#') {
            name++;
        }

        unsigned int index = FUN_004015C0(DAT_0087E294, name);
        if (index != 0xFFFFFFFF) {
            this->Sounds[this->SampleCount] = index;
            this->SampleCount = this->SampleCount + 1;
            return 1;
        }

        FUN_004068E0("Missing sample %s\n", name);
        this->unknown_0C = 0;
    }

    return 1;
}
