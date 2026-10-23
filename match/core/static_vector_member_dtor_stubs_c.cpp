// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
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
class IonBlastClass;
class RadarEventClass;
class ShadowControlClass;
class VeinholeMonsterClass;

struct StaticVectorHolder_00A9F9D0 {
    // GLOBAL: GAMEMD 0x00A9F9D0
    static DynamicVectorClass<const AnimClass*> DAT_00A9F9D0;
};
// SYNTHETIC: GAMEMD 0x00539660 -- exit-time destructor stub of DAT_00A9F9D0, guard byte 0x00A9F9A8 bit 0
DynamicVectorClass<const AnimClass*> StaticVectorHolder_00A9F9D0::DAT_00A9F9D0;

struct StaticVectorHolder_00AA0118 {
    // GLOBAL: GAMEMD 0x00AA0118
    static DynamicVectorClass<IonBlastClass*> DAT_00AA0118;
};
// SYNTHETIC: GAMEMD 0x0053CAB0 -- exit-time destructor stub of DAT_00AA0118, guard byte 0x00A9FAD8 bit 0
DynamicVectorClass<IonBlastClass*> StaticVectorHolder_00AA0118::DAT_00AA0118;

struct StaticVectorHolder_00B04DA8 {
    // GLOBAL: GAMEMD 0x00B04DA8
    static DynamicVectorClass<RadarEventClass*> DAT_00B04DA8;
};

struct StaticVectorHolder_00B0CDE8 {
    // GLOBAL: GAMEMD 0x00B0CDE8
    static DynamicVectorClass<ShadowControlClass*> DAT_00B0CDE8;
};
// SYNTHETIC: GAMEMD 0x006D1B50 -- exit-time destructor stub of DAT_00B0CDE8, guard byte 0x00B0CD59 bit 0
DynamicVectorClass<ShadowControlClass*> StaticVectorHolder_00B0CDE8::DAT_00B0CDE8;

struct StaticVectorHolder_00B1D290 {
    // GLOBAL: GAMEMD 0x00B1D290
    static DynamicVectorClass<VeinholeMonsterClass*> DAT_00B1D290;
};
// SYNTHETIC: GAMEMD 0x0074C3C0 -- exit-time destructor stub of DAT_00B1D290, guard byte 0x00B1D250 bit 0
DynamicVectorClass<VeinholeMonsterClass*> StaticVectorHolder_00B1D290::DAT_00B1D290;

