// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm @0x48DCD0).
//   The AbstractType enum values and the four type-array globals were derived
//   from the switch byte-table @0x48DD24 and the jump-table @0x48DD10; the enum
//   constants were cross-checked against YRpp (consult-only).
//
// TechnoTypeClass::GetByTypeAndIndex — given an AbstractType discriminator and an
// index, returns the Items[index] entry of the matching {Unit/Aircraft/Building/
// Infantry}TypeClass static array (or NULL for any unhandled type).
#ifndef GG_MATCH_CORE_TECHNO_TYPE_CLASS_GETBYTYPE_METHODS_H
#define GG_MATCH_CORE_TECHNO_TYPE_CLASS_GETBYTYPE_METHODS_H

#include <stddef.h>

// AbstractType discriminator (unsigned int enum). Only the values the switch
// @0x48DCD0 reaches are reproduced here; ordering matches YRpp's enum so the
// numeric case constants are byte-exact against the retail byte-table.
enum AbstractType
{
    AbstractType_None         = 0,
    AbstractType_Unit         = 1,
    AbstractType_Aircraft     = 2,
    AbstractType_AircraftType = 3,
    AbstractType_Building     = 6,
    AbstractType_BuildingType = 7,
    AbstractType_Infantry     = 15,
    AbstractType_InfantryType = 16,
    AbstractType_UnitType     = 40
};

class TechnoTypeClass;

// The four static type arrays. Each global holds the Items pointer of a static
// DynamicVectorClass (retail reads it as a single dword load, then indexes), so
// it is modelled as a TechnoTypeClass** pointer variable:
//   MOV EAX,[GLOBAL]; MOV EAX,[EAX+index*4].
extern TechnoTypeClass** UnitTypeClass_ArrayItems;     // @0x00A83CE4
extern TechnoTypeClass** AircraftTypeClass_ArrayItems; // @0x00A8B21C
extern TechnoTypeClass** BuildingTypeClass_ArrayItems; // @0x00A83C6C
extern TechnoTypeClass** InfantryTypeClass_ArrayItems; // @0x00A8E34C

class TechnoTypeClass
{
public:
    // FUNCTION: GAMEMD 0x48DCD0  (__fastcall)
    static TechnoTypeClass* __fastcall GetByTypeAndIndex(AbstractType abs, int index);
};

#endif // GG_MATCH_CORE_TECHNO_TYPE_CLASS_GETBYTYPE_METHODS_H
