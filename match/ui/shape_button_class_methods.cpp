// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x69DEA0 / 0x69DFC0 /
//   0x69DFF0 (Ghidra disasm). Names cross-checked against YRpp
//   ShapeButtonClass.h (consult-only, no LICENSE; each offset reconfirmed
//   against the user's binary).
//
// Translation unit: ShapeButtonClass flash-control accessors.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x69DEA0   ShapeButtonClass::SetLoadedStatus  (__thiscall)
//   FUNCTION: GAMEMD 0x69DFC0   ShapeButtonClass::StartFlashing    (__thiscall)
//   FUNCTION: GAMEMD 0x69DFF0   ShapeButtonClass::StopFlashing     (__thiscall)

#include "shape_button_class_methods.h"

// FUNCTION: GAMEMD 0x69DEA0   ShapeButtonClass::SetLoadedStatus  (__thiscall)
//   MOV AL,[ESP+4]; MOV [ECX+0x5c],AL; RET 4
void ShapeButtonClass::SetLoadedStatus(bool status)
{
    this->IsShapeLoaded = status;
}

// FUNCTION: GAMEMD 0x69DFC0   ShapeButtonClass::StartFlashing  (__thiscall)
//   if (FlashDelay != 0) return false;
//   FlashDelay   = nDelay;
//   FlashCounter = nDelay + nInitDelay;
//   IsToFlash    = bStart;
//   return true;
bool ShapeButtonClass::StartFlashing(int nDelay, int nInitDelay, bool bStart)
{
    if (this->FlashDelay == 0)
    {
        this->FlashDelay = nDelay;
        this->FlashCounter = nDelay + nInitDelay;
        this->IsToFlash = bStart;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x69DFF0   ShapeButtonClass::StopFlashing  (__thiscall)
//   if (FlashDelay == 0) return false;
//   IsToFlash = 0; FlashCounter = 0; FlashDelay = 0;
//   return true;
bool ShapeButtonClass::StopFlashing()
{
    if (this->FlashDelay != 0)
    {
        this->IsToFlash = 0;
        this->FlashCounter = 0;
        this->FlashDelay = 0;
        return true;
    }
    return false;
}
