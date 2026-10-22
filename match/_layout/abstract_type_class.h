// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
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

class CCINIClass;

// AbstractTypeClass  (0x24..0x97, sizeof = 0x98)
// VTABLE: GAMEMD 0x7E2000 (IPersistStream side, slots 0-26)
// VTABLE: GAMEMD 0x7E1FE4 (IRTTITypeInfo side, +0x04)
// VTABLE: GAMEMD 0x7E1FDC (INoticeSink side, +0x08)
// VTABLE: GAMEMD 0x7E1FD4 (INoticeSource side, +0x0C)
class AbstractTypeClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x410800 (constructor declaration)
    AbstractTypeClass(const char* id);
    // FUNCTION: GAMEMD 0x410960 (declaration; no-initialisation constructor)
    AbstractTypeClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x4109C0 (declaration; destructor, slot 8 = 0x410C30)
    virtual ~AbstractTypeClass();
    // Overrides and new slots of the primary table 0x7E2000 (27 slots).
    // Signatures are not recovered; placeholders keep the shape.
    virtual void vf_13(Obj_004A1D30* crc); // 13  0x410BE0
    virtual void vf_24();                 // 24  0x410C20 (new)
    virtual bool vf_25(CCINIClass* ini);  // 25  0x410A60 (new; RET 4, bool)
    virtual void vf_26();                 // 26  0x410B90 (new)
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
