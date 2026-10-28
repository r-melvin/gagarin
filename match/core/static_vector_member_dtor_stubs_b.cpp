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

class AnimClass;
class LaserDrawClass;
class MapRegionClass;
class ObjectTypeClass;
class IsometricTileTypeClass { public:
    struct TileInsertType;
};
class LightSourceClass { public:
    class PendingCellClass;
};

struct StaticVectorHolder_00A9FA60 {
    // GLOBAL: GAMEMD 0x00A9FA60
    static DynamicVectorClass<const AnimClass*> DAT_00A9FA60;
};
// SYNTHETIC: GAMEMD 0x005395C0 -- exit-time destructor stub of DAT_00A9FA60, guard byte 0x00A9F9A9 bit 0
DynamicVectorClass<const AnimClass*> StaticVectorHolder_00A9FA60::DAT_00A9FA60;

struct StaticVectorHolder_00AA1078 {
    // GLOBAL: GAMEMD 0x00AA1078
    static DynamicVectorClass<IsometricTileTypeClass::TileInsertType*> DAT_00AA1078;
};
// SYNTHETIC: GAMEMD 0x00543EB0 -- exit-time destructor stub of DAT_00AA1078, guard byte 0x00AA0E2C bit 0
DynamicVectorClass<IsometricTileTypeClass::TileInsertType*> StaticVectorHolder_00AA1078::DAT_00AA1078;

struct StaticVectorHolder_00ABC878 {
    // GLOBAL: GAMEMD 0x00ABC878
    static DynamicVectorClass<LaserDrawClass*> DAT_00ABC878;
};
// SYNTHETIC: GAMEMD 0x0054FE00 -- exit-time destructor stub of DAT_00ABC878, guard byte 0x00ABC718 bit 0
DynamicVectorClass<LaserDrawClass*> StaticVectorHolder_00ABC878::DAT_00ABC878;

struct StaticVectorHolder_00ABCA40 {
    // GLOBAL: GAMEMD 0x00ABCA40
    static DynamicVectorClass<LightSourceClass::PendingCellClass*> DAT_00ABCA40;
};
// SYNTHETIC: GAMEMD 0x00554700 -- exit-time destructor stub of DAT_00ABCA40, guard byte 0x00ABC9C0 bit 0
DynamicVectorClass<LightSourceClass::PendingCellClass*> StaticVectorHolder_00ABCA40::DAT_00ABCA40;

struct StaticVectorHolder_00ABDF90 {
    // GLOBAL: GAMEMD 0x00ABDF90
    static DynamicVectorClass<MapRegionClass*> DAT_00ABDF90;
};
// SYNTHETIC: GAMEMD 0x0058BC70 -- exit-time destructor stub of DAT_00ABDF90, guard byte 0x00ABDFB0 bit 0
DynamicVectorClass<MapRegionClass*> StaticVectorHolder_00ABDF90::DAT_00ABDF90;

// Keep this declaration at its original position: VC6 numbers guarded
// static-member callbacks when it encounters their declaring class.
#include "object_type_registry.h"

// SYNTHETIC: GAMEMD 0x005F7030 -- exit-time destructor stub of DAT_00AC1418, guard byte 0x00AC1470 bit 0
DynamicVectorClass<ObjectTypeClass*> StaticVectorHolder_00AC1418::DAT_00AC1418;

