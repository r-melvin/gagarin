// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// TD 0x81BFB0 identifies Straw; its three-slot table at 0x7E61F0 and observed
// member offsets are documented in _layout/straw.h. Full entry-origin spans:
//   0x6C9850 (0x32), ev_3388e8a6a9a2268601c03555517c6f5b0e5dc9dd1ce374790e7d2b3d6aadb27c
//   0x6C9890 (0x43), ev_ce62afab57774f6c733eb02fcbd74dd4ff4951c7cbe805d70c2b32f1af856ce3
//   0x6C98E0 (0x1E), ev_374417b444875b135008026bce07f2144c62d447df1e6d1a04a391fc11b3b26a
// The 0x4AEC10 deleting entry calls this ordinary destructor then the library
// operator delete target; its relocation closure was verified in GX and no-GX
// probes. Original high-level names/types for slot 2 remain unknown.
#include "../_layout/straw.h"

// The Straw scalar deleting destructor 0x4AEC10 is emitted by the
// RandomStraw constructor's TU (platform/tu196_random_straw.cpp), where only
// the Straw destructor declaration is visible; under /Ob2 it would otherwise
// inline the body below instead of calling it.

// FUNCTION: GAMEMD 0x6C9850
Straw::~Straw()
{
    Straw* next = ChainTo;
    if (next != 0) {
        next->ChainFrom = ChainFrom;
    }
    Straw* previous = ChainFrom;
    if (previous != 0) {
        previous->SetChainTo(ChainTo);
    }
    ChainFrom = 0;
    ChainTo = 0;
}

// FUNCTION: GAMEMD 0x6C9890
void Straw::SetChainTo(Straw* next)
{
    if (ChainTo == next) {
        return;
    }
    if (next != 0) {
        Straw* previous = next->ChainFrom;
        if (previous != 0) {
            previous->SetChainTo(0);
            next->ChainFrom = 0;
        }
    }
    if (ChainTo != 0) {
        ChainTo->ChainFrom = 0;
    }
    ChainTo = next;
    if (next != 0) {
        next->ChainFrom = this;
    }
}

// FUNCTION: GAMEMD 0x6C98E0
int Straw::FUN_006C98E0(void* first, int second)
{
    Straw* next = ChainTo;
    if (next != 0) {
        return next->FUN_006C98E0(first, second);
    }
    return 0;
}
