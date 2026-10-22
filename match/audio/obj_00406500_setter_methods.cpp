// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// One-instruction field setters on the object described in the header.
// Functions ordered ascending by retail address.

#include "obj_00406500_setter_methods.h"

// FUNCTION: GAMEMD 0x406520
void Obj_00406500::FUN_00406520(int value)
{
    this->unknown_138 = value;
}

// FUNCTION: GAMEMD 0x406530
void Obj_00406500::FUN_00406530(int value)
{
    this->unknown_13C = value;
}

// FUNCTION: GAMEMD 0x406540
void Obj_00406500::FUN_00406540(int value)
{
    this->unknown_40 = value;
}

// FUNCTION: GAMEMD 0x4065C0
void Obj_00406500::FUN_004065C0(int value)
{
    this->unknown_14 = value;
}

// FUNCTION: GAMEMD 0x4065D0
void Obj_00406500::FUN_004065D0(int value)
{
    this->unknown_48 = value;
}

// FUNCTION: GAMEMD 0x4065E0
void Obj_00406500::FUN_004065E0(int value)
{
    this->unknown_50 = value;
}

// FUNCTION: GAMEMD 0x406640
void Obj_00406500::FUN_00406640(int value)
{
    this->unknown_4C = value;
}
