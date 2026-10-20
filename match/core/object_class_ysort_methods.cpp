// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Body and
//   member offsets derived directly from the disassembly at 0x5F6BD0;
//   signature cross-checked against YRpp ObjectClass.h (consult-only).
//
// reccmp annotation:
//   FUNCTION: GAMEMD 0x5F6BD0  ObjectClass::GetYSort (__thiscall)

#include "object_class_ysort_methods.h"

// FUNCTION: GAMEMD 0x5F6BD0  (__thiscall)
// Isometric depth key: fill a CoordStruct via the primary-vtable coordinate
// accessor (slot 0xAC) and return its Y; a second, independent call supplies the
// X. Retail:  CALL [vtbl+0xAC] -> Y(+0x4); CALL [vtbl+0xAC] -> X(+0x0); add.
int ObjectYSort::GetYSort() const
{
    CoordStruct coord1;
    CoordStruct coord2;
    const ObjCoordVCall* self = (const ObjCoordVCall*)this;
    return self->GetTargetCoords(&coord1)->Y + self->GetTargetCoords(&coord2)->X;
}
