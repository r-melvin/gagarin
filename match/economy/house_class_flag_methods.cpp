// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x4FC060).
//   Each offset and constant reconfirmed numerically from the disassembly; YRpp
//   consulted for names only.
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x4FC060   HouseClass::PickedUpFlag       (__thiscall)
//   FUNCTION: GAMEMD 0x4FBE40   HouseClass::UpdateFlagCoords   (callee, reloc)
//   FUNCTION: GAMEMD 0x740DF0   UnitClass::FlagAttach (callee, reloc)

#include "house_class_flag_methods.h"

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x4FC060  (__thiscall)
//
// A unit picks up this house's flag. Rejected if the carrier is null or in
// limbo (off-map). Otherwise the previous carrier's flag bookkeeping is updated
// (UpdateFlagCoords with the old OurFlagCarrier), the new carrier is stamped with
// this house's owner/colour index (Type->ColorSchemeIndex_B8), OurFlagCarrier is
// repointed to the new carrier, and true is returned.
//   TEST EDI,EDI / JZ fail; MOV AL,[EDI+0x81] / TEST / JNZ fail;
//   push dwUnk / push [ESI+0x53DC] / call 0x4FBE40;
//   MOV EDX,[ESI+0x34]; MOV EAX,[EDX+0xB8]; push EAX; call 0x740DF0;
//   MOV [ESI+0x53DC],EDI; MOV AL,1.
// ---------------------------------------------------------------------------
char HouseClass::PickedUpFlag(UnitClass* Who, DWORD dwUnk)
{
    if (Who == NULL || Who->InLimbo != 0) {
        return 0;
    }

    this->UpdateFlagCoords((UnitClass*)this->OurFlagCarrier, dwUnk);
    Who->FlagAttach(this->Type->ColorSchemeIndex_B8);
    this->OurFlagCarrier = Who;
    return 1;
}
