// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Bodies and
//   member offsets derived directly from the disassembly; signatures
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x47EBA0  CellClass::GetUnit      (__thiscall)
//   FUNCTION: GAMEMD 0x47EBF0  CellClass::GetAircraft  (__thiscall)
//   FUNCTION: GAMEMD 0x47EC40  CellClass::GetInfantry  (__thiscall)
//   GLOBAL:   GAMEMD 0x00A8E9A0 CellOccupiersValid (byte; reloc-normalised)

#include "cell_class_occupier_methods.h"

// AbstractType discriminants returned by WhatAmI() (YRpp).
#define ABS_UNIT     0x01  // CMP EAX,0x01
#define ABS_AIRCRAFT 0x02  // CMP EAX,0x02
#define ABS_INFANTRY 0x0F  // CMP EAX,0x0F

// Read the occupier's WhatAmI() through its primary vtable slot +0x2C.
// `MOV EAX,[obj]; MOV ECX,obj; CALL [EAX+0x2C]`.
#define WHAT_AM_I(obj) ((*(WhatAmIFunc*)(*(char**)(obj) + 0x2c))(obj))

// FUNCTION: GAMEMD 0x47EBA0  (__thiscall)
// First unit occupying the cell; `alt` selects the on-bridge list.
UnitClass* CellClass::GetUnit(bool alt) const
{
    if (CellOccupiersValid) {
        ObjectClass* obj = alt ? this->AltObject : this->FirstObject;
        for (; obj; obj = (ObjectClass*)obj->NextObject) {
            if (WHAT_AM_I(obj) == ABS_UNIT) {
                return (UnitClass*)obj;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x47EBF0  (__thiscall)
// First aircraft occupying the cell; `alt` selects the on-bridge list.
AircraftClass* CellClass::GetAircraft(bool alt) const
{
    if (CellOccupiersValid) {
        ObjectClass* obj = alt ? this->AltObject : this->FirstObject;
        for (; obj; obj = (ObjectClass*)obj->NextObject) {
            if (WHAT_AM_I(obj) == ABS_AIRCRAFT) {
                return (AircraftClass*)obj;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x47EC40  (__thiscall)
// First infantry occupying the cell; `alt` selects the on-bridge list.
InfantryClass* CellClass::GetInfantry(bool alt) const
{
    if (CellOccupiersValid) {
        ObjectClass* obj = alt ? this->AltObject : this->FirstObject;
        for (; obj; obj = (ObjectClass*)obj->NextObject) {
            if (WHAT_AM_I(obj) == ABS_INFANTRY) {
                return (InfantryClass*)obj;
            }
        }
    }
    return 0;
}
