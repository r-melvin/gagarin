// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x4722F0).
//   Names cross-checked against YRpp CaptureManagerClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4722F0  CaptureManagerClass::GetOriginalOwner (__thiscall)

#include "capture_manager_class_more_methods.h"

// FUNCTION: GAMEMD 0x4722F0  (__thiscall)
// Walk the control-node vector back-to-front; for the node controlling `unit`,
// return its captured-from house. Returns null if `unit` is not controlled.
HouseClass* CaptureManagerClass::GetOriginalOwner(TechnoClass* unit) const
{
    for (int i = ControlNodes.Count - 1; i >= 0; --i)
    {
        if (((ControlNode**)ControlNodes.Items)[i]->Unit == unit)
            return ((ControlNode**)ControlNodes.Items)[i]->OriginalOwner;
    }
    return 0;
}
