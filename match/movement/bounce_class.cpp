// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//   Cross-checked against YRpp.
//
// Translation unit: BounceClass read accessors.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4399A0   BounceClass::GetCoords        (__thiscall)
//   FUNCTION: GAMEMD 0x4399E0   BounceClass::GetDrawingMatrix (__thiscall)
//   FUNCTION: GAMEMD 0x646980   Matrix3D::FromQuaternion      (__fastcall; reloc)
//   LIBRARY:  GAMEMD 0x7C5F00   __ftol  (CRT float->long; excluded from target)

#include "bounce_class.h"

// FUNCTION: GAMEMD 0x4399A0  BounceClass::GetCoords (__thiscall)
// Truncate each precision float component to int (__ftol) into the buffer,
// returning the buffer pointer.
//
// MATCHED 100% (22/22) 2026-09-18. The three conversions go into a local
// CoordStruct and the whole struct is assigned to the caller's buffer in one
// statement. That form produces retail's shape end to end: the conversions run
// in source order X,Y,Z (spilled to EDI, EBX, EAX), and the struct copy takes
// its own base register, which is retail's `MOV ECX,[ESP+0x10]; MOV EDX,ECX;
// ...; MOV EAX,ECX` - the copy is the struct-assignment base, not a redundant
// move, and ECX is kept for the return. Storing member-by-member through
// pBuffer (or through a walking `int*`) lets cl sink each conversion to its
// store, which reorders the __ftol calls to Y,Z,X and elides the base copy.
CoordStruct* BounceClass::GetCoords(CoordStruct* pBuffer) const
{
    CoordStruct temp;
    temp.X = (int)this->Coords.X;
    temp.Y = (int)this->Coords.Y;
    temp.Z = (int)this->Coords.Z;
    *pBuffer = temp;
    return pBuffer;
}

// FUNCTION: GAMEMD 0x4399E0  BounceClass::GetDrawingMatrix (__thiscall)
// Build a rotation matrix from CurrentAngle into a local, copy it to the
// caller's buffer, and return the buffer pointer.
Matrix3D* BounceClass::GetDrawingMatrix(Matrix3D* pBuffer) const
{
    Matrix3D buffer;
    Matrix3D* p = Matrix3D::FromQuaternion(&buffer, &this->CurrentAngle);
    *pBuffer = *p;
    return pBuffer;
}
