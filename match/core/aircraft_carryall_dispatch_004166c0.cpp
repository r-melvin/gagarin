// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read off retail gamemd.exe v1.001 at 0x4166C0 via the local Ghidra CLI: the
//   type pointer at +0x6C4 and the type's flag byte at +0xDFC.

#include "../_layout/aircraft_class.h"
#include "../_layout/aircraft_type_class.h"

// FUNCTION: GAMEMD 0x416D50 (decl; reloc) -- the carryall variant, __fastcall.
int __fastcall FUN_00416D50(AircraftClass* self);
// FUNCTION: GAMEMD 0x4166E0 (decl; reloc) -- the ordinary variant, __fastcall.
int __fastcall FUN_004166E0(AircraftClass* self);

// FUNCTION: GAMEMD 0x4166C0
// Hand off to the carryall routine when the aircraft's type is a carryall,
// otherwise to the ordinary one; both are tail calls.
int __fastcall FUN_004166C0(AircraftClass* self)
{
    if (self->Type->Carryall) {
        return FUN_00416D50(self);
    }
    return FUN_004166E0(self);
}
