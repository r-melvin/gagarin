// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm
//   0x70E280-0x70E2A4, len 0x25). Names cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x70E280  TechnoView_0070E280::DisguiseAs (__thiscall)

#include "techno_class_disguise.h"

// FUNCTION: GAMEMD 0x70E280  (__thiscall)
// Record the start of a disguise -- set the flag and stamp the creation frame
// -- when a target was supplied, then dispatch the virtual that actually
// applies it and hand its result straight back.
unsigned long TechnoView_0070E280::DisguiseAs(AbstractClass* pTarget)
{
    if (pTarget != 0) {
        this->Disguised = 1;
        this->DisguiseCreationFrame = CurrentFrame;
    }
    return (this->*this->Vfptr->At_49C)();
}
