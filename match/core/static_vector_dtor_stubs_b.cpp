// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// More file-scope DynamicVectorClass<T> objects whose exit-time destructors were
// emitted as stand-alone stubs (same shape as static_vector_dtor_stubs.cpp):
// each stub restores the VectorClass<T> vtable, frees the array when it is
// owned, and clears the flag and capacity. T is the element type of the
// RTTI TypeDescriptor behind the vtable the stub stores. The initialisers
// compile here as the fused constructor + atexit run-time initialiser and are
// claimed with their stubs.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "vector_class_operations.h"
#include "../_layout/layer_class.h"

class ObjectClass;
class ParasiteClass;
class SpawnManagerClass;
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

#include "undo_info_struct.h"

// GLOBAL: GAMEMD 0x0087F778
// SYNTHETIC: GAMEMD 0x0040CBC0 -- exit-time destructor stub of DAT_0087F778
// SYNTHETIC: GAMEMD 0x0040CB80 -- initialiser of DAT_0087F778
LogicClass DAT_0087F778;

// The theme-list object at 0xA83D10: its constructor (0x720960, defined out of
// line) also builds the vector at +0x14; the exit-time stub at 0x4E7E50 is the
// vector's destructor inlined into this class's empty one.
class Obj_00A83D10
{
public:
    char unknown_00[0x14];
    DynamicVectorClass<ThemeControl*> Themes;
    // FUNCTION: GAMEMD 0x720960 (decl; reloc)
    Obj_00A83D10();
    ~Obj_00A83D10() {}
};
GG_STATIC_ASSERT(offsetof(Obj_00A83D10, Themes) == 0x14);
GG_STATIC_ASSERT(sizeof(Obj_00A83D10) == 0x2C);

// GLOBAL: GAMEMD 0x00A83D10
// SYNTHETIC: GAMEMD 0x004E7E30
// SYNTHETIC: GAMEMD 0x004E7E50 -- exit-time destructor stub of DAT_00A83D10
Obj_00A83D10 DAT_00A83D10;

// GLOBAL: GAMEMD 0x00ABFCB8
// SYNTHETIC: GAMEMD 0x005D4D10 -- exit-time destructor stub of DAT_00ABFCB8
// SYNTHETIC: GAMEMD 0x005D4CD0 -- initialiser of DAT_00ABFCB8
DynamicVectorClass<AcceleratorTracker> DAT_00ABFCB8;

// GLOBAL: GAMEMD 0x00B0B650
// SYNTHETIC: GAMEMD 0x006B23F0 -- exit-time destructor stub of DAT_00B0B650
// SYNTHETIC: GAMEMD 0x006B23B0 -- initialiser of DAT_00B0B650
DynamicVectorClass<UndoInfoStruct> DAT_00B0B650;

// GLOBAL: GAMEMD 0x00AC4910
// SYNTHETIC: GAMEMD 0x006291D0 -- exit-time destructor stub of DAT_00AC4910
// SYNTHETIC: GAMEMD 0x00629190 -- initialiser of DAT_00AC4910
DynamicVectorClass<ParasiteClass*> DAT_00AC4910;

// GLOBAL: GAMEMD 0x00B0B880
// SYNTHETIC: GAMEMD 0x006B6C50 -- exit-time destructor stub of DAT_00B0B880
// SYNTHETIC: GAMEMD 0x006B6C10 -- initialiser of DAT_00B0B880
DynamicVectorClass<SpawnManagerClass*> DAT_00B0B880;
