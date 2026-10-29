// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc2_methods.h"
#include "../audio/audio_stop_methods.h"
#include "dispatch_state_methods.h"
#include "leaf_accessor_methods.h"

// FUNCTION: GAMEMD 0x405BE0
void Obj_00405B00::FUN_00405BE0()
{
    unknown_0C = DAT_0087E294;
    unknown_00 = 0;
    unknown_04 = 0;
    unknown_08 = 0;
}

// FUNCTION: GAMEMD 0x405C00
void Obj_00405B00::FUN_00405C00()
{
    if (DAT_0087E2A0 != 0 && this->unknown_0C == (void*)DAT_0087E294) {
        Voice_00405D40* voice = this->unknown_00;
        if (voice != 0) {
            if (this->unknown_08 == voice->Token && this->unknown_04 == voice->Serial
                && (voice->Flags & 1) == 0) {
                Peer_00405D40* peer = voice->Peer;
                if (peer != 0 && voice == peer->Voice) {
                    if ((voice->FlagsWord & 2) != 0)
                        peer->FUN_004025B0();
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
            this->unknown_00 = 0;
        }
    }
    this->unknown_08 = 0;
    this->unknown_0C = 0;
}

// FUNCTION: GAMEMD 0x406650
// True only when the flag is set *and* the pointer is clear.
int Obj_00406600b::FUN_00406650() const
{
    return (Flags & 1) && unknown_4C == 0;
}

// FUNCTION: GAMEMD 0x4072D0
void Obj_004072D0::FUN_004072D0()
{
    a = this;
    b = this;
    c = 0;
}

// FUNCTION: GAMEMD 0x40A940
void __cdecl FUN_0040A940b()
{
    if (DAT_0087E8A0) {
        IFACE_CALL(DAT_0087E8A0, 0x48);
    }
}

// FUNCTION: GAMEMD 0x433040
void Obj_00433000::FUN_00433040()
{
    FUN_00432E40(unknown_0C, unknown_10, unknown_14);
}

// FUNCTION: GAMEMD 0x473960
const char* FUN_00473960(unsigned int index)
{
    if (index < 11) {
        return DAT_0081B7CC[index].Name;
    }

    return STR_00817474b;
}

// FUNCTION: GAMEMD 0x48ACE0
// Native ignores the three four-byte stack inputs and returns with RET 0xC.
int __stdcall FUN_0048ACE0(int, int, int)
{
    return -15;
}
