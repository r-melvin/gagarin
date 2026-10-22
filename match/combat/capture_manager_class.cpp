// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x472140  CaptureManagerClass::FreeAll               (__thiscall)
//   FUNCTION: GAMEMD 0x4722A0  CaptureManagerClass::CannotControlAnyMore  (__thiscall)
//   FUNCTION: GAMEMD 0x4722C0  CaptureManagerClass::IsControllingSomething(__thiscall)
//   FUNCTION: GAMEMD 0x4722D0  CaptureManagerClass::GetControlledCount    (__thiscall)
//   FUNCTION: GAMEMD 0x471FF0  CaptureManagerClass::FreeUnit  (referenced; matched elsewhere)

#include "capture_manager_class.h"

// FUNCTION: GAMEMD 0x472140  (__thiscall)
// Free every controlled unit, walking the node vector back-to-front.
void CaptureManagerClass::FreeAll()
{
    for (int i = ControlNodes.Count - 1; i >= 0; --i)
        FreeUnit(((ControlNode**)ControlNodes.Items)[i]->Unit);
}

// FUNCTION: GAMEMD 0x4722A0  (__thiscall)
// True when control capacity is exhausted. Infinite control is never "full".
// Retail tests the infinite-control byte first, then compares Count with Max.
// The named bool local preserves the observed VC6 comparison sequence.
bool CaptureManagerClass::CannotControlAnyMore() const
{
    if (InfiniteMindControl)
        return false;
    bool full = ControlNodes.Count >= MaxControlNodes;
    return full;
}

// FUNCTION: GAMEMD 0x4722C0  (__thiscall)
bool CaptureManagerClass::IsControllingSomething() const
{
    return ControlNodes.Count > 0;
}

// FUNCTION: GAMEMD 0x4722D0  (__thiscall)
int CaptureManagerClass::GetControlledCount()
{
    return ControlNodes.Count;
}
