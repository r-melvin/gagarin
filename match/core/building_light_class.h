// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail RTTI at 0x7E3ACC -> COL 0x7FC040 -> TypeDescriptor 0x818BE0 names
//   BuildingLightClass, an ObjectClass whose four vtables sit at 0x7E3AD0
//   (IPersistStream side), 0x7E3AB4, 0x7E3AAC and 0x7E3AA4. The constructor
//   at 0x435820 (entry-bounded, RET 4, 0x330 bytes) stores every member below
//   and the four vptrs; the primary table's slots 3, 6, 10, 12, 30 and 34 point
//   at 0x436910, 0x4369C0, 0x436A00, 0x436900, 0x4369F0 and 0x4369E0.
#ifndef GG_MATCH_CORE_BUILDING_LIGHT_CLASS_H
#define GG_MATCH_CORE_BUILDING_LIGHT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_class.h"
#include "../_layout/building_class.h"

class BuildingLightClass : public ObjectClass
{
public:
    // FUNCTION: GAMEMD 0x435820
    BuildingLightClass(BuildingClass* source);

    // Overrides present in the primary table 0x7E3AD0 (bodies not recovered here).
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3  0x436910
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6  0x4369C0
    virtual void vf_10(void* target, bool removed);                       // 10 0x436A00
    virtual int vf_12();                                                  // 12 0x436900
    virtual int vf_30();                                                  // 30 0x4369F0
    virtual ObjectTypeClass* vf_34();                                     // 34 0x4369E0

    // FUNCTION: GAMEMD 0x436BE0 (decl; reloc) -- one stack argument.
    void FUN_00436BE0(int unknownStackArg0);

    // FUNCTION: GAMEMD 0x436E80 (decl; reloc) -- no stack arguments.
    int FUN_00436E80();

    // FUNCTION: GAMEMD 0x435BE0
    void FUN_00435BE0(int unknownStackArg0, int unknownStackArg1);

    int         unknown_AC;     // +0xAC
    int         unknown_B0;     // +0xB0
    int         unknown_B4;     // +0xB4
    CoordStruct unknown_B8;     // +0xB8
    CoordStruct unknown_C4;     // +0xC4
    int         unknown_D0;     // +0xD0
    int         unknown_D4;     // +0xD4
    bool        unknown_D8;     // +0xD8
    unsigned char _padD9[3];    // +0xD9
    int         unknown_DC;     // +0xDC
    int         unknown_E0;     // +0xE0
    BuildingClass* source;      // +0xE4
};
GG_STATIC_ASSERT(offsetof(BuildingLightClass, unknown_B0) == 0xB0);
GG_STATIC_ASSERT(offsetof(BuildingLightClass, unknown_B4) == 0xB4);
GG_STATIC_ASSERT(offsetof(BuildingLightClass, unknown_B8) == 0xB8);
GG_STATIC_ASSERT(offsetof(BuildingLightClass, unknown_C4) == 0xC4);
GG_STATIC_ASSERT(offsetof(BuildingLightClass, unknown_D0) == 0xD0);
GG_STATIC_ASSERT(offsetof(BuildingLightClass, unknown_D4) == 0xD4);
GG_STATIC_ASSERT(offsetof(BuildingLightClass, unknown_D8) == 0xD8);
GG_STATIC_ASSERT(offsetof(BuildingLightClass, unknown_DC) == 0xDC);
GG_STATIC_ASSERT(offsetof(BuildingLightClass, unknown_E0) == 0xE0);
GG_STATIC_ASSERT(offsetof(BuildingLightClass, source) == 0xE4);
GG_STATIC_ASSERT(sizeof(BuildingLightClass) == 0xE8);

#endif
