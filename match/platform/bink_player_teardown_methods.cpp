// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x432700 and 0x432A60.

#include "bink_player_teardown_methods.h"

// FUNCTION: GAMEMD 0x432700
//
// Three independent releases, each guarded by its own emptiness test and each
// writing the empty value back inside the guard - the clears are not shared and
// not unconditional, which is the opposite of the buffer-release family where
// only the free is guarded. The file handle's empty value is -1, so its guard
// is `CMP EAX,-1` rather than a `TEST`.
//
// Each pointer is read once into a local. Retail keeps the helper in EDI across
// both of its calls and reads the other two once each; going through the member
// directly makes VC6 re-read it for the argument after the test, which costs an
// instruction per block.
void BinkPlayer_00432700::FUN_00432700()
{
    void* helper = Helper;

    if (helper) {
        FUN_006C9AE0(helper);
        FUN_007C8B3D(helper);
        Helper = 0;
    }

    void* bink = Bink;

    if (bink) {
        BinkClose(bink);
        Bink = 0;
    }

    void* file = File;

    if (file != (void*)-1) {
        CloseHandle(file);
        File = (void*)-1;
    }
}

// FUNCTION: GAMEMD 0x432A60
//
// The second player's teardown. Byte-identical to the above apart from the
// call displacements; written out rather than shared.
void BinkPlayer_00432700::FUN_00432A60()
{
    void* helper = Helper;

    if (helper) {
        FUN_006C9AE0(helper);
        FUN_007C8B3D(helper);
        Helper = 0;
    }

    void* bink = Bink;

    if (bink) {
        BinkClose(bink);
        Bink = 0;
    }

    void* file = File;

    if (file != (void*)-1) {
        CloseHandle(file);
        File = (void*)-1;
    }
}
