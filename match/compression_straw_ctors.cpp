// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Relies on match/_layout/straw.h: the inline Straw() that zeroes +4/+8, and
// for 0x633050 the reference overload of SetChainTo that forwards to the
// virtual slot.
// /Ob2 emits the native inlined scalar-deleting LCW destructor.
#include "compression_straws.h"

// FUNCTION: GAMEMD 0x5523E0
LCWStraw::LCWStraw(CompControl control, int blocksize) :
    Control(control),
    Counter(0),
    Buffer(0),
    Buffer2(0),
    BlockSize(blocksize),
    SafetyMargin(blocksize / 128 + 1)
{
    Buffer = new char[blocksize + SafetyMargin];
    if (control == COMPRESS) {
        Buffer2 = new char[BlockSize + SafetyMargin];
    }
}

// SYNTHETIC: GAMEMD 0x5525F0 -- LCWStraw scalar deleting destructor.
// FUNCTION: GAMEMD 0x552450
LCWStraw::~LCWStraw()
{
    delete[] Buffer;
    Buffer = 0;
    delete[] Buffer2;
    Buffer2 = 0;
}

// FUNCTION: GAMEMD 0x55C2B0
LZOPipe::LZOPipe(CompControl control, int blocksize) :
    Control(control),
    Counter(0),
    Buffer(0),
    Buffer2(0),
    BlockSize(blocksize)
{
    SafetyMargin = blocksize;
    Buffer = new char[blocksize * 2];
    Buffer2 = new char[BlockSize + SafetyMargin];
    BlockHeader.CompCount = 0xFFFF;
}

// FUNCTION: GAMEMD 0x55C310
LZOPipe::~LZOPipe()
{
    delete [] Buffer;
    Buffer = 0;
    delete [] Buffer2;
    Buffer2 = 0;
}

// SYNTHETIC: GAMEMD 0x55C6D0 -- LZOPipe scalar deleting destructor.

// FUNCTION: GAMEMD 0x55C720
LZOStraw::LZOStraw(CompControl control, int blocksize) :
    Control(control),
    Counter(0),
    Buffer(0),
    Buffer2(0),
    BlockSize(blocksize),
    SafetyMargin(blocksize)
{
    Buffer = new char[blocksize * 2];
    if (control == COMPRESS) {
        Buffer2 = new char[BlockSize + SafetyMargin];
    }
}

// FUNCTION: GAMEMD 0x55C780
LZOStraw::~LZOStraw()
{
    delete[] Buffer;
    Buffer = 0;
    delete[] Buffer2;
    Buffer2 = 0;
}

// SYNTHETIC: GAMEMD 0x55C990 -- LZOStraw scalar deleting destructor.
