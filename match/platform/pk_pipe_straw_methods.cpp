// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Relies on match/_layout/straw.h: the inline Straw() that zeroes +4/+8, and
// for 0x633050 the reference overload of SetChainTo that forwards to the
// virtual slot.
#include "pk_blow_pipes.h"

// SYNTHETIC: GAMEMD 0x5B45C0
// BlowStraw scalar deleting destructor (inline ~BlowStraw), emitted with the
// BlowStraw vtable that PKStraw's constructor needs.

// FUNCTION: GAMEMD 0x632CB0
PKPipe::PKPipe(PipeDirection control, Straw* random) :
    unknown_C(true),
    unknown_10(random),
    Cipher(control == PIPE_DIR_0 ? BlowPipe::PIPE_DIR_0 : BlowPipe::PIPE_DIR_1),
    Control(control),
    Key(0),
    Counter(0),
    unknown_140(0)
{
}

// FUNCTION: GAMEMD 0x632F30
int PKPipe::FUN_00632F30() const
{
    if (Key == 0) {
        return 0;
    }
    return Key->BlockCountFor(56) * Key->CipherBlockBytes();
}

// FUNCTION: GAMEMD 0x632F60
int PKPipe::FUN_00632F60() const
{
    if (Key == 0) {
        return 0;
    }
    return Key->BlockCountFor(56) * Key->PlainBlockBytes();
}

// SYNTHETIC: GAMEMD 0x632F90
// BlowPipe scalar deleting destructor (inline ~BlowPipe)

// FUNCTION: GAMEMD 0x632FE0
void PKPipe::FUN_00632FE0(Pipe* next)
{
    SetChainTo(next);
}

// SYNTHETIC: GAMEMD 0x632FF0
// PKPipe scalar deleting destructor (implicit ~PKPipe)

// FUNCTION: GAMEMD 0x633050
PKStraw::PKStraw(PipeDirection control, Straw* random) :
    unknown_C(true),
    unknown_10(random),
    Cipher(control == PIPE_DIR_0 ? BlowStraw::PIPE_DIR_0 : BlowStraw::PIPE_DIR_1),
    Control(control),
    Key(0),
    Counter(0),
    unknown_140(0)
{
    Straw::SetChainTo(Cipher);
}

// FUNCTION: GAMEMD 0x633110
void PKStraw::FUN_00633110(PKey_00632740* key)
{
    Key = key;
    if (key != 0) {
        unknown_C = true;
    }
    Counter = 0;
    unknown_140 = 0;
}

// FUNCTION: GAMEMD 0x633300
int PKStraw::FUN_00633300() const
{
    if (Key == 0) {
        return 0;
    }
    return Key->BlockCountFor(56) * Key->CipherBlockBytes();
}

// FUNCTION: GAMEMD 0x633330
int PKStraw::FUN_00633330() const
{
    if (Key == 0) {
        return 0;
    }
    return Key->BlockCountFor(56) * Key->PlainBlockBytes();
}

// FUNCTION: GAMEMD 0x633360
void PKStraw::FUN_00633360(Straw* next)
{
    SetChainTo(next);
}

// SYNTHETIC: GAMEMD 0x633370
// PKStraw scalar deleting destructor (implicit ~PKStraw)
