// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// Static data members of vector type: each retail definition is guarded by a
// bit in a shared byte, so the exit-time destructor stub tests that bit before
// restoring the VectorClass<T> vtable and releasing the array. Every member here
// is the lowest bit of its guard byte (a single-member group), so each is given
// its own placeholder holder; the owning classes are not recoverable. T is the
// element type of the vector's RTTI TypeDescriptor, read through the vptr stored
// by the matching initialiser. The initialisers (__xc table entries) are left to
// the translation-unit migration and compile here as a by-product, unclaimed.
#include "vector_class_operations.h"

class AlphaLightingRemapClass;
class BulletClass;
class ConvertClass;
class EMPulseClass;
class FoggedObjectClass;
class HouseClass { public:
    struct BuildChoiceClass;
};

struct StaticVectorHolder_0088A080 {
    // GLOBAL: GAMEMD 0x0088A080
    static DynamicVectorClass<AlphaLightingRemapClass*> DAT_0088A080;
};
// SYNTHETIC: GAMEMD 0x004200C0 -- exit-time destructor stub of DAT_0088A080, guard byte 0x0088A098 bit 0
// SYNTHETIC: GAMEMD 0x00420080 -- initialiser of DAT_0088A080
DynamicVectorClass<AlphaLightingRemapClass*> StaticVectorHolder_0088A080::DAT_0088A080;

struct StaticVectorHolder_0089DE18 {
    // GLOBAL: GAMEMD 0x0089DE18
    static DynamicVectorClass<BulletClass*> DAT_0089DE18;
};
// SYNTHETIC: GAMEMD 0x00466320 -- exit-time destructor stub of DAT_0089DE18, guard byte 0x0089DDD0 bit 0
// SYNTHETIC: GAMEMD 0x004662E0 -- initialiser of DAT_0089DE18
DynamicVectorClass<BulletClass*> StaticVectorHolder_0089DE18::DAT_0089DE18;

#include "../_layout/staticvectorholder_0089ecf8.h"

struct StaticVectorHolder_008A3870 {
    // GLOBAL: GAMEMD 0x008A3870
    static DynamicVectorClass<EMPulseClass*> DAT_008A3870;
};
// SYNTHETIC: GAMEMD 0x004C5250 -- exit-time destructor stub of DAT_008A3870, guard byte 0x008A3818 bit 0
// SYNTHETIC: GAMEMD 0x004C5210 -- initialiser of DAT_008A3870
DynamicVectorClass<EMPulseClass*> StaticVectorHolder_008A3870::DAT_008A3870;

struct StaticVectorHolder_008B3D10 {
    // GLOBAL: GAMEMD 0x008B3D10
    static DynamicVectorClass<FoggedObjectClass*> DAT_008B3D10;
};
// SYNTHETIC: GAMEMD 0x004D0790 -- exit-time destructor stub of DAT_008B3D10, guard byte 0x008B3CD5 bit 0
// SYNTHETIC: GAMEMD 0x004D0750 -- initialiser of DAT_008B3D10
DynamicVectorClass<FoggedObjectClass*> StaticVectorHolder_008B3D10::DAT_008B3D10;

struct StaticVectorHolder_00A8EFC8 {
    // GLOBAL: GAMEMD 0x00A8EFC8
    static DynamicVectorClass<HouseClass::BuildChoiceClass*> DAT_00A8EFC8;
};
// SYNTHETIC: GAMEMD 0x004F5130 -- exit-time destructor stub of DAT_00A8EFC8, guard byte 0x00A8EF60 bit 0
// SYNTHETIC: GAMEMD 0x004F50F0 -- initialiser of DAT_00A8EFC8
DynamicVectorClass<HouseClass::BuildChoiceClass*> StaticVectorHolder_00A8EFC8::DAT_00A8EFC8;

