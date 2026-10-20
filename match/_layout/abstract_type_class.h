// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: ctor FUN_0x00410800 (docs/decomp_spec/type_hierarchy_layout.md),
//   cross-checked vs YRpp AbstractTypeClass.h + the matched *TypeClass agents
//   (BulletType/Campaign/ObjectType confirmed ID@0x24). P2 layout-spine.
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
struct AbstractTypeClass : AbstractClass
{
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
