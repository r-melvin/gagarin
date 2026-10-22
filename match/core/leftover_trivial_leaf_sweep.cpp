// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The trivial leaves the big shape sweeps left behind: four loads of a
// container's +0x10 field, five loads of its +0x04 storage pointer, five
// constant-true returns with no arguments, three with one argument, three
// one-argument no-ops, and three stores of the ECX argument into a fixed
// global. Ordered ascending by retail address.

#include "leftover_trivial_leaf_sweep.h"

// FUNCTION: GAMEMD 0x484F10
bool __stdcall FUN_00484F10(int)
{
    return true;
}

// FUNCTION: GAMEMD 0x49FB60
int FUN_0049FB60(LeafObj_0x10* self)
{
    return self->unknown_10;
}

// FUNCTION: GAMEMD 0x4A3BF0
bool __cdecl FUN_004A3BF0()
{
    return true;
}


// FUNCTION: GAMEMD 0x53F1F0
void FUN_0053F1F0(int value)
{
    DAT_00828140 = value;
}

// FUNCTION: GAMEMD 0x55AF40
void FUN_0055AF40(int value)
{
    DAT_00829FF4 = value;
}

// FUNCTION: GAMEMD 0x55AF50
void FUN_0055AF50(int value)
{
    DAT_00829FF8 = value;
}

// FUNCTION: GAMEMD 0x5B43E0
bool __cdecl FUN_005B43E0()
{
    return true;
}

// FUNCTION: GAMEMD 0x5B43F0
bool __stdcall FUN_005B43F0(int)
{
    return true;
}


// FUNCTION: GAMEMD 0x67A730
int FUN_0067A730(LeafObj_0x10* self)
{
    return self->unknown_10;
}

// FUNCTION: GAMEMD 0x67A7C0
int FUN_0067A7C0(LeafObj_0x10* self)
{
    return self->unknown_10;
}

// FUNCTION: GAMEMD 0x67A8A0
int FUN_0067A8A0(LeafObj_0x10* self)
{
    return self->unknown_10;
}


// FUNCTION: GAMEMD 0x711E80
bool __cdecl FUN_00711E80()
{
    return true;
}

// FUNCTION: GAMEMD 0x717A70
int FUN_00717A70(LeafObj_0x04* self)
{
    return self->unknown_04;
}

