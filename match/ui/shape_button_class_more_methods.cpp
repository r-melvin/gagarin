// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x69DE70 / 0x6CFD40
//   (Ghidra disasm). Names cross-checked against YRpp ShapeButtonClass.h
//   (consult-only, no LICENSE; each offset reconfirmed against the user's
//   binary).
//
// Translation unit: ShapeButtonClass::ClearShape + the static GetButton lookup.
//
//   LIBRARY:  GAMEMD 0x7C8B3D   GameDelete (free/operator delete; excluded)
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x69DE70   ShapeButtonClass::ClearShape  (__thiscall)
//   FUNCTION: GAMEMD 0x6CFD40   ShapeButtonClass::GetButton   (__fastcall)

#include "shape_button_class_more_methods.h"

// __cdecl game free used to release the cached shape: raw
// `push p; call 0x7C8B3D; add esp,4`. Declared (no body) so cl emits a
// normalised call reloc. GAMEMD 0x7C8B3D.
void __cdecl GameDelete(void* block);

// Static button table + the button array, both at fixed global addresses.
//   ButtonIndexTable : int[]            @ 0x00B0CB78  (index -> slot, or <0)
//   ButtonArray      : ShapeButtonClass[] @ 0x00B0C1C0 (stride 0x60)
extern int              ButtonIndexTable[];   // GAMEMD 0x00B0CB78
extern ShapeButtonClass ButtonArray[];        // GAMEMD 0x00B0C1C0

// FUNCTION: GAMEMD 0x69DE70   ShapeButtonClass::ClearShape  (__thiscall)
//   if (IsShapeLoaded && ShapeData) {
//       GameDelete(ShapeData);
//       ShapeData = 0; IsShapeLoaded = 0; Width = 0; Height = 0;
//   }
void ShapeButtonClass::ClearShape()
{
    if (this->IsShapeLoaded && this->ShapeData != 0)
    {
        GameDelete(this->ShapeData);
        this->ShapeData = 0;
        this->IsShapeLoaded = 0;
        this->Width = 0;
        this->Height = 0;
    }
}

// FUNCTION: GAMEMD 0x6CFD40   ShapeButtonClass::GetButton  (__fastcall)
//   int slot = ButtonIndexTable[index];
//   if (slot >= 0 && slot < 25) return &ButtonArray[slot];
//   return 0;
ShapeButtonClass* __fastcall ShapeButtonClass::GetButton(int index)
{
    int slot = ButtonIndexTable[index];
    if (slot >= 0 && slot < 0x19)
        return &ButtonArray[slot];
    return 0;
}
