// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x439080  BombListClass::AddDetector    (__thiscall)
//   FUNCTION: GAMEMD 0x4390D0  BombListClass::RemoveDetector (__thiscall)

#include "../_layout/bomb_list_class.h"

// FUNCTION: GAMEMD 0x439080  (__thiscall)
// Append a bomb-revealing TechnoClass to the Detectors vector (inlined AddItem;
// SetCapacity is the only out-of-line, virtual, call).
void BombListClass::AddDetector(TechnoClass* Detector)
{
    this->Detectors.AddItem(Detector);
}

// FUNCTION: GAMEMD 0x4390D0  (__thiscall)
// Locate the detector in the vector and shift the tail down over it (inlined
// Remove + RemoveItem; FindItemIndex is the only out-of-line, virtual, call).
void BombListClass::RemoveDetector(TechnoClass* Detector)
{
    int idx = this->Detectors.FindItemIndex(Detector);
    if (idx != -1)
        this->Detectors.RemoveItem(idx);
}
