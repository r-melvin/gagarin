// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x70FEC0 (Ghidra disasm).
//
// Translation unit: BuildingClass::IsBeingDrained.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x70FEC0   BuildingClass::IsBeingDrained   (__thiscall)

#include "building_class_drain.h"

// FUNCTION: GAMEMD 0x70FEC0  (__thiscall)
//
// Retail body (len 0xE):
//   MOV  EDX,[ECX+0x1d0]   ; DrainingMe
//   XOR  EAX,EAX
//   TEST EDX,EDX
//   SETNZ AL
//   RET
//
// i.e. `return DrainingMe != 0;` — boolean of a pointer null test, which cl
// lowers to the xor/test/setnz tail above.
bool BuildingClass::IsBeingDrained() const
{
    return this->DrainingMe != 0;
}
