// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
//
// More file-scope DynamicVectorClass<T> objects whose exit-time destructors were
// emitted as stand-alone stubs (same shape as static_vector_dtor_stubs.cpp):
// each stub restores the VectorClass<T> vtable, frees the array when it is
// owned, and clears the flag and capacity. T is the element type of the
// RTTI TypeDescriptor behind the vtable the stub stores. The initialisers are
// left to the translation-unit migration; they compile here as a by-product and
// are not claimed.
#include "vector_class_operations.h"

class ObjectClass;
class ThemeControl;

// Element types of the two by-value vectors: placeholders that declare only the
// fields and the element operations the vector template instantiates.
struct AcceleratorTracker
{
    int unknown_00;
    int unknown_04;
    AcceleratorTracker() : unknown_00(0), unknown_04(0) {}
    bool operator==(const AcceleratorTracker& o) const { return unknown_00 == o.unknown_00 && unknown_04 == o.unknown_04; }
    bool operator!=(const AcceleratorTracker& o) const { return !(*this == o); }
};

struct UndoInfoStruct
{
    int unknown_00;
    int unknown_04;
    int unknown_08;
    UndoInfoStruct() : unknown_00(0), unknown_04(0), unknown_08(0) {}
    bool operator==(const UndoInfoStruct& o) const { return unknown_00 == o.unknown_00 && unknown_04 == o.unknown_04 && unknown_08 == o.unknown_08; }
    bool operator!=(const UndoInfoStruct& o) const { return !(*this == o); }
};

// GLOBAL: GAMEMD 0x0087F778
// SYNTHETIC: GAMEMD 0x0040CBC0 -- exit-time destructor stub of DAT_0087F778
DynamicVectorClass<ObjectClass*> DAT_0087F778;

// GLOBAL: GAMEMD 0x00A83D24
// SYNTHETIC: GAMEMD 0x004E7E50 -- exit-time destructor stub of DAT_00A83D24
DynamicVectorClass<ThemeControl*> DAT_00A83D24;

// GLOBAL: GAMEMD 0x00ABFCB8
// SYNTHETIC: GAMEMD 0x005D4D10 -- exit-time destructor stub of DAT_00ABFCB8
DynamicVectorClass<AcceleratorTracker> DAT_00ABFCB8;

// GLOBAL: GAMEMD 0x00B0B650
// SYNTHETIC: GAMEMD 0x006B23F0 -- exit-time destructor stub of DAT_00B0B650
DynamicVectorClass<UndoInfoStruct> DAT_00B0B650;
