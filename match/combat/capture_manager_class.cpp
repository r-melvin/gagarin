// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp CaptureManagerClass.h (consult-only).
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
    for (int i = ControlNodes_Count - 1; i >= 0; --i)
        FreeUnit(ControlNodes_Items[i]->Unit);
}

// FUNCTION: GAMEMD 0x4722A0  (__thiscall)
// True when control capacity is exhausted. Infinite control is never "full".
// MATCHED 100% (10/10) on 2026-09-18. The trailing `Count >= Max` bool is
// bound to a named `bool` local and returned on its own statement; that is the
// banked "final compare through a named bool" lever and it emits retail's lean
// `MOV EAX,[+34]; MOV EDX,[+3C]; CMP EAX,EDX; SETGE AL; RET` with no
// normalisation. Returning the comparison directly is what produced the spilly
// `PUSH ESI; ... XOR EDX,EDX; SETGE DL; MOV AL,DL` form under every VC6 backend
// tested (8168/8447/8943/8966/9044/9782), which is why this was previously
// recorded as unreachable - it was a phrasing delta, not a backend delta.
// docs/toolchain_evidence.md section 2a can drop the correction note.
bool CaptureManagerClass::CannotControlAnyMore() const
{
    if (InfiniteControl)
        return false;
    bool full = ControlNodes_Count >= MaxControlNodes;
    return full;
}

// FUNCTION: GAMEMD 0x4722C0  (__thiscall)
bool CaptureManagerClass::IsControllingSomething() const
{
    return ControlNodes_Count > 0;
}

// FUNCTION: GAMEMD 0x4722D0  (__thiscall)
int CaptureManagerClass::GetControlledCount()
{
    return ControlNodes_Count;
}
