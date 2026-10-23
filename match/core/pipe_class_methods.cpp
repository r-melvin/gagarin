// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Pipe is identified by TD 0x81BF80 (.?AVPipe@@), primary table 0x7E6218,
// and the five raw slot targets documented in _layout/pipe.h. Complete
// entry-origin spans were checked with focused REA evidence:
//   0x631C80 (0x32), ev_57f6257ee3428a2d31a9fe35de15bdea18d8b59d85e75f3459565b830688f8af
//   0x631CC0 (0x4B), ev_207183581f137a53791de0e9bbb876d8f96300e4374ce045d055ffbe2fd37be9
//   0x631D10 (0x20), ev_2ef7ebb1fe11b3b23b1abc6143ec6df4a7df0f941bc979015f71b81f75fe257b
//   0x631D30 (0x0F), ev_cc333ec8557c46b96e006406ea670e08e51fa7c8a0ab5d8e66d3a3c2b72508ad
//   0x477740 (0x05), ev_4a9cd5dbe1074d1eb48699074f0b082367d6c831e005bfaf6e6455e0a9916913
#include "../_layout/pipe.h"

// FUNCTION: GAMEMD 0x477740
int Pipe::FUN_00477740()
{
    return FUN_00631D30();
}

// SYNTHETIC: GAMEMD 0x4AEC80 -- Pipe scalar deleting destructor.

// FUNCTION: GAMEMD 0x631C80
Pipe::~Pipe()
{
    Pipe* next = ChainTo;
    if (next != 0) {
        next->ChainFrom = ChainFrom;
    }
    Pipe* previous = ChainFrom;
    if (previous != 0) {
        previous->SetChainTo(ChainTo);
    }
    ChainFrom = 0;
    ChainTo = 0;
}

// FUNCTION: GAMEMD 0x631CC0
void Pipe::SetChainTo(Pipe* next)
{
    if (ChainTo == next) {
        return;
    }
    if (next != 0) {
        Pipe* previous = next->ChainFrom;
        if (previous != 0) {
            previous->SetChainTo(0);
            next->ChainFrom = 0;
        }
    }
    if (ChainTo != 0) {
        ChainTo->ChainFrom = 0;
        ChainTo->FUN_00631D30();
    }
    ChainTo = next;
    if (next != 0) {
        next->ChainFrom = this;
    }
}

// FUNCTION: GAMEMD 0x631D10
int Pipe::FUN_00631D10(int first, int second)
{
    Pipe* next = ChainTo;
    if (next != 0) {
        return next->FUN_00631D10(first, second);
    }
    return second;
}

// FUNCTION: GAMEMD 0x631D30
int Pipe::FUN_00631D30()
{
    Pipe* next = ChainTo;
    if (next != 0) {
        return next->FUN_00631D30();
    }
    return 0;
}
