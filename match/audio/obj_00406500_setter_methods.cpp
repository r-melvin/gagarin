// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// One-instruction field setters on the object described in the header.
// Functions ordered ascending by retail address.

#include "obj_00406500_setter_methods.h"

// FUNCTION: GAMEMD 0x406520
void AudioEventType::FUN_00406520(int value)
{
    this->Attack = value;
}

// FUNCTION: GAMEMD 0x406530
void AudioEventType::FUN_00406530(int value)
{
    this->Decay = value;
}

// FUNCTION: GAMEMD 0x406540
void AudioEventType::FUN_00406540(int value)
{
    this->Priority = value;
}

// FUNCTION: GAMEMD 0x4065C0
void AudioEventType::FUN_004065C0(int value)
{
    this->Type = value;
}

// FUNCTION: GAMEMD 0x4065D0
void AudioEventType::FUN_004065D0(int value)
{
    this->Limit = value;
}

// FUNCTION: GAMEMD 0x4065E0
void AudioEventType::FUN_004065E0(int value)
{
    this->Range = value;
}

// FUNCTION: GAMEMD 0x406640
void AudioEventType::FUN_00406640(int value)
{
    this->Loop = value;
}
