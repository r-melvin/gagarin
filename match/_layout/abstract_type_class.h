// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp naming consult only
//   Retail ctor 0x00410800 has a contiguous 340-byte body through 0x00410953;
//   it calls 0x00410170, writes four vptrs at +0/+4/+8/+0xC, copies the ID
//   beginning at +0x24 through its terminator at +0x3C, zeroes +0x3D, sets
//   UIName at +0x60, and copies Name beginning at +0x64. Raw RTTI has
//   TypeDescriptor 0x00817808 = ".?AVAbstractTypeClass@@"; COL 0x007FB210
//   and CHD 0x007FB200 identify AbstractClass as a direct base at offset 0
//   and its inherited COM subobjects at offsets 0, 4, 8 and 12.
//
// AbstractTypeClass — base of every INI-defined "blueprint" type (UnitType,
// InfantryType, BuildingType, BulletType, Campaign, Script, …). Derives the
// AbstractClass COM base (0x00..0x23) and adds the type identity strings.
#ifndef GG_MATCH_LAYOUT_ABSTRACT_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_ABSTRACT_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"

// AbstractTypeClass  (0x24..0x97, sizeof = 0x98)
class AbstractTypeClass : public AbstractClass
{
public:
    char           ID[0x18];          // +0x24  strncpy(pID, 0x18)
    unsigned char  zero_3C;           // +0x3C  ID NUL-terminator slot
    char           UINameLabel[0x20]; // +0x3D
    unsigned char  _pad_5D[3];        // +0x5D  (align UIName to +0x60)
    const wchar_t* UIName;            // +0x60
    char           Name[0x31];        // +0x64  strncpy(…, 0x30)
    unsigned char  _pad_95[3];        // +0x95  (pad to sizeof 0x98)
};

GG_STATIC_ASSERT(offsetof(AbstractTypeClass, ID)          == 0x24);
GG_STATIC_ASSERT(offsetof(AbstractTypeClass, zero_3C)     == 0x3C);
GG_STATIC_ASSERT(offsetof(AbstractTypeClass, UINameLabel) == 0x3D);
GG_STATIC_ASSERT(offsetof(AbstractTypeClass, UIName)      == 0x60);
GG_STATIC_ASSERT(offsetof(AbstractTypeClass, Name)        == 0x64);
GG_STATIC_ASSERT(sizeof(AbstractTypeClass)                == 0x98);

#endif  // GG_MATCH_LAYOUT_ABSTRACT_TYPE_CLASS_H
